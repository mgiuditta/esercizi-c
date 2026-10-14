#!/usr/bin/env bash
# =====================================================================
# run_tests.sh — compila ed esegue i test degli esercizi.
#
# Uso:
#   scripts/run_tests.sh                     -> tutti gli esercizi, TUA versione
#   scripts/run_tests.sh 03                  -> solo la cartella che inizia con "03"
#   scripts/run_tests.sh 03 es02             -> solo l'esercizio es02 della cartella 03
#   SOL=1 scripts/run_tests.sh ...           -> usa le SOLUZIONI invece dei tuoi file
#   SAN=0 scripts/run_tests.sh ...           -> disattiva i sanitizer (AddressSanitizer)
#
# Come funziona (in breve):
#   per ogni esercizio esNN_nome.c (oppure cartella esNN_nome/ con più file .c)
#   1. lo compila con il compilatore C (cc = clang su macOS, gcc su Linux)
#   2. per ogni file tests/esNN_nome*.in lo esegue dandogli quel file come input
#      (se non ci sono .in, lo esegue con input vuoto)
#   3. confronta l'output con il file .out corrispondente.
#      Se sono uguali: OK. Se no: FAIL e ti mostra le differenze.
#
# Compatibile con la bash 3.2 di macOS (niente funzioni "moderne").
# =====================================================================

set -u

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
CC="${CC:-cc}"
CFLAGS="${CFLAGS:--std=c11 -Wall -Wextra -pedantic -g}"
SAN="${SAN:-1}"
SOL="${SOL:-0}"
FILTER_DIR="${1:-}"
FILTER_EX="${2:-}"

if [ "$SAN" = "1" ]; then
  # AddressSanitizer + UndefinedBehaviorSanitizer: fanno "esplodere" il programma
  # con un messaggio chiaro se leggi/scrivi fuori da un vettore, usi memoria liberata, ecc.
  SANFLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer"
else
  SANFLAGS=""
fi

# Su macOS il controllo dei memory leak di ASan non è supportato: lo spegniamo
# per evitare messaggi di errore inutili.
export ASAN_OPTIONS="${ASAN_OPTIONS:-detect_leaks=0}"
export UBSAN_OPTIONS="${UBSAN_OPTIONS:-print_stacktrace=1:halt_on_error=1}"

if [ -t 1 ]; then
  GREEN=$'\033[32m'; RED=$'\033[31m'; YEL=$'\033[33m'; BOLD=$'\033[1m'; RST=$'\033[0m'
else
  GREEN=""; RED=""; YEL=""; BOLD=""; RST=""
fi

TMP="$(mktemp -d 2>/dev/null || mktemp -d -t esc)"
trap 'rm -rf "$TMP"' EXIT

pass=0; fail=0; cerr=0

for dir in "$ROOT"/[0-9][0-9]-*/; do
  dir="${dir%/}"
  dname="$(basename "$dir")"
  if [ -n "$FILTER_DIR" ]; then
    case "$dname" in "$FILTER_DIR"*) ;; *) continue ;; esac
  fi

  if [ "$SOL" = "1" ]; then src_dir="$dir/soluzioni"; else src_dir="$dir"; fi
  [ -d "$src_dir" ] || continue

  echo "${BOLD}== $dname ==${RST}"

  for ex in "$src_dir"/es[0-9][0-9]_*; do
    [ -e "$ex" ] || continue
    base="$(basename "$ex")"
    base="${base%.c}"
    # salta file non .c che non sono cartelle
    if [ -f "$ex" ]; then
      case "$ex" in *.c) ;; *) continue ;; esac
    fi
    if [ -n "$FILTER_EX" ]; then
      case "$base" in "$FILTER_EX"*) ;; *) continue ;; esac
    fi

    bin="$TMP/$dname-$base"
    if [ -d "$ex" ]; then
      srcs="$ex/*.c"
      inc="-I$ex"
    else
      srcs="$ex"
      inc=""
    fi

    # shellcheck disable=SC2086
    if ! $CC $CFLAGS $SANFLAGS $inc $srcs -o "$bin" -lm 2> "$TMP/cc.log"; then
      echo "  ${RED}COMPILE ERROR${RST} $base"
      sed 's/^/      /' "$TMP/cc.log" | head -25
      cerr=$((cerr+1))
      continue
    fi
    if [ -s "$TMP/cc.log" ]; then
      echo "  ${YEL}warning${RST} $base (il compilatore ha segnalato qualcosa):"
      sed 's/^/      /' "$TMP/cc.log" | head -10
    fi

    tests_dir="$dir/tests"
    found=0
    for inf in "$tests_dir/$base".in "$tests_dir/$base".*.in; do
      [ -e "$inf" ] || continue
      found=1
    done

    run_case () {
      # $1 = file di input (o /dev/null), $2 = file output atteso, $3 = etichetta
      local input="$1" expected="$2" label="$3"
      local work="$TMP/run"
      rm -rf "$work"; mkdir -p "$work"
      # eventuali file di supporto (per gli esercizi sui file) vengono copiati
      if [ -d "$tests_dir/fixtures" ]; then cp -R "$tests_dir/fixtures/." "$work/"; fi
      # perl alarm = timeout portabile (macOS non ha il comando "timeout"):
      # se il programma gira più di 10 secondi (ciclo infinito) viene fermato.
      ( cd "$work" && perl -e 'alarm shift; exec @ARGV' "${TIMEOUT:-10}" "$bin" \
          < "$input" > "$TMP/actual.txt" 2> "$TMP/stderr.txt" )
      local rc=$?
      if [ $rc -eq 142 ]; then
        echo "  ${RED}TIMEOUT${RST} $label (più di ${TIMEOUT:-10}s: ciclo infinito? oppure aspetta input che non arriva)"
        fail=$((fail+1))
        return
      fi
      if [ ! -f "$expected" ]; then
        echo "  ${YEL}?${RST}    $label (manca il file atteso $(basename "$expected"))"
        return
      fi
      if [ $rc -ge 128 ] || grep -q -e "Sanitizer" -e "runtime error" "$TMP/stderr.txt" 2>/dev/null; then
        echo "  ${RED}CRASH${RST} $label (exit $rc)"
        sed 's/^/      /' "$TMP/stderr.txt" | head -15
        fail=$((fail+1))
        return
      fi
      if diff -b "$expected" "$TMP/actual.txt" > "$TMP/diff.txt"; then
        echo "  ${GREEN}OK${RST}   $label"
        pass=$((pass+1))
      else
        echo "  ${RED}FAIL${RST} $label   (righe con < = atteso, > = il tuo output)"
        sed 's/^/      /' "$TMP/diff.txt" | head -20
        if [ -s "$TMP/stderr.txt" ]; then
          echo "      --- messaggi su stderr ---"
          sed 's/^/      /' "$TMP/stderr.txt" | head -8
        fi
        fail=$((fail+1))
      fi
    }

    if [ $found -eq 0 ]; then
      run_case /dev/null "$tests_dir/$base.out" "$base"
    else
      for inf in "$tests_dir/$base".in "$tests_dir/$base".*.in; do
        [ -e "$inf" ] || continue
        outf="${inf%.in}.out"
        run_case "$inf" "$outf" "$(basename "${inf%.in}")"
      done
    fi
  done
done

echo
echo "${BOLD}Risultato:${RST} ${GREEN}$pass superati${RST}, ${RED}$fail falliti${RST}, ${RED}$cerr non compilano${RST}"
[ $fail -eq 0 ] && [ $cerr -eq 0 ]
