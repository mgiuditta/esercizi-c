> **Spostata.** Dal 28 ottobre 2026 questi esercizi vivono in `esercizi/c/` della repo unica
> [`mgiuditta/universita`](https://github.com/mgiuditta/universita). Questa repo non viene più aggiornata.

# Esercizi C — Programmazione e Algoritmi I (UniMi SecAI)

Questa repo raccoglie la **parte in linguaggio C** del corso del prof. Marco Anisetti, cioè i blocchi 2, 3 e 4.
Sono 15 cartelle in ordine di corso, con **120 esercizi**. Ogni esercizio ha:

- un **file di partenza** (lo *starter*, cioè il `.c` con i `TODO` da completare);
- una **soluzione commentata** nella sottocartella `soluzioni/`;
- dei **test automatici** (396 casi in tutto). Ti dicono subito se il tuo codice è giusto.

Ogni esercizio indica la **fonte**: trascrizione, E-tivity o capitolo degli Appunti di fine Unità da cui è preso.
Così sai sempre a quale lezione del prof si riferisce.

---

## 1. Prima di iniziare (una volta sola, su macOS)

Ti serve il compilatore C. Il *compilatore* è il programma che traduce il tuo `.c` in un eseguibile.
Su Mac lo installi con gli strumenti a riga di comando di Xcode:

```bash
xcode-select --install
```

Poi apri il Terminale in questa cartella e verifica che tutto funzioni.
Il comando sotto prova tutte le soluzioni, quindi devono passare tutte:

```bash
make sol
```

Alla fine devi leggere `Risultato: 396 superati, 0 falliti, 0 non compilano`.

> Su macOS il comando `cc` è **clang**, mentre il prof usa **gcc** nella macchina virtuale del corso.
> Per gli esercizi la differenza non conta. Dove i due compilatori danno avvisi diversi, il README della cartella lo dice.

---

## 2. Come si lavora

1. Apri il `README.md` della cartella. Leggi la **Teoria flash** e poi il testo dell'esercizio.
2. Apri lo starter, ad esempio `03-input-output-controllo/es02_....c`, e completa i `TODO`.
3. Testa solo quell'esercizio:

   ```bash
   make test T=03 E=es02
   ```

   - **OK** vuol dire che l'output coincide con quello atteso.
   - **FAIL** ti mostra le righe diverse. Quelle con `<` sono l'output atteso, quelle con `>` sono il tuo.
   - **CRASH** vuol dire che il programma è stato fermato da un errore di memoria. Il messaggio indica la riga.
   - **TIMEOUT** vuol dire che il programma non è finito entro 10 secondi: di solito è un ciclo infinito.
4. Se sei bloccato, apri **💡 Suggerimento** nel README. Solo alla fine apri **✅ Soluzione spiegata**.
5. Per farti correggere da Claude, usa i prompt in [`PROMPTS.md`](PROMPTS.md).

### Comandi utili

| Comando | Cosa fa |
|---|---|
| `make test` | testa **tutti** i tuoi esercizi |
| `make test T=09` | testa la cartella `09-...` |
| `make test T=09 E=es03` | testa un solo esercizio |
| `make sol T=09` | testa le **soluzioni** della cartella (utile per vedere come dovrebbe andare) |
| `make nosan T=09` | come `test`, ma senza i controlli di memoria (più veloce, messaggi meno chiari) |

### I tre tipi speciali di esercizio
- **Cosa stampa?** Il codice è già completo. Scrivi su carta la tua previsione dell'output, poi lancia il test e confronta.
  La spiegazione riga per riga è nella soluzione del README.
- **Trova e correggi l'errore.** Lo starter contiene bug realistici. Il test fallisce, o va in CRASH, finché non li correggi.
- **Tipo esame.** È un problema completo che combina più argomenti, come in un compito.

### I controlli di memoria (sanitizer)
I test compilano con **AddressSanitizer** e **UndefinedBehaviorSanitizer** (`-fsanitize=address,undefined`).
- *AddressSanitizer* (ASan) controlla ogni accesso alla memoria.
- *UndefinedBehaviorSanitizer* (UBSan) controlla le operazioni che il C vieta, come uscire da un vettore o usare un puntatore NULL.

Senza questi controlli, molti errori in C non danno nessun segnale e il programma stampa numeri a caso.
Con i controlli, il programma si ferma subito e ti dice **in quale riga** sta l'errore.

---

## 3. Il percorso

| # | Cartella | Lezioni | Esercizi | Tempo |
|---|---|---|---|---|
| 01 | [Primo programma, compilazione e goto](01-primo-programma-goto/) | 2.0, 2.1 + E-tivity | 10 | ~3 h |
| 02 | [Tipi di dato, operatori e macro](02-tipi-operatori-macro/) | 2.2 | 8 | ~3 h |
| 03 | [Input, output e strutture di controllo](03-input-output-controllo/) | 2.3 (dispensa) | 8 | ~4 h |
| 04 | [Tipi enumerati e typedef](04-enum-typedef/) | 2.4 | 7 | ~2,5 h |
| 05 | [Gestione della memoria e vettori](05-vettori-memoria/) | 2.5 | 8 | ~4 h |
| 06 | [Stringhe](06-stringhe/) | 2.6 | 8 | ~4 h |
| 07 | [Funzioni, call and return e stack](07-funzioni-stack/) | 3.0, 3.1, 3.3 | 8 | ~4 h |
| 08 | [Scope, parametri e macro](08-parametri-macro/) | 3.2 + E-tivity 3.6 | 8 | ~4 h |
| 09 | [Puntatori e vettori](09-puntatori-vettori/) | 3.4 + E-tivity | 8 | ~4 h |
| 10 | [Strutture e union](10-strutture-union/) | 3.5 | 8 | ~4 h |
| 11 | [Approfondimento puntatori, matrici e file](11-puntatori-avanzati-file/) | 3.6 + 3 E-tivity, Dispensa Stream | 8 | ~5 h |
| 12 | [Memoria dinamica](12-memoria-dinamica/) | 4.0, 4.1 | 8 | ~5 h |
| 13 | [Ricorsione](13-ricorsione/) | 4.2 | 8 | ~4 h |
| 14 | [Static, extern e programmi su più file](14-scope-multifile/) | 4.4 | 7 | ~4 h |
| 15 | [**Simulazione d'esame**](15-simulazione-esame/) | tutto | 8 | ~6 h |

**Percorso completo:** circa 60 ore.

### Percorso veloce (~25 ore)
Per chiudere il C in fretta, in ogni cartella da 01 a 14 fai solo questi esercizi:
1. il **Cosa stampa?**, per verificare di aver capito la teoria senza scrivere codice;
2. il **Trova e correggi l'errore**, che contiene gli errori classici del C;
3. gli esercizi **Tipo esame** (es07–es08).

Leggi la Teoria flash solo se uno dei tre va male. Poi fai la cartella **15** a tempo.
Se un esercizio della 15 va male, il campo **Ripassa** ti dice quale cartella riprendere.

Le cartelle che richiedono più attenzione sono **09, 11, 12**: puntatori, matrici con puntatori, memoria dinamica.
È lì che il C è diverso dai linguaggi che conosci già.
Le cartelle **01–04** puoi farle velocemente, perché sono sintassi.

---

## 4. Note sulle fonti

- Ogni README ha una sezione che elenca le **contraddizioni e imprecisioni** trovate tra trascrizioni, slide e dispense, con la versione corretta verificata compilando.
  Esempi: la copia di matrici con `<=` negli Appunti Unità 2, `sizeof` di una struct senza padding nella trascrizione 4.1, la descrizione sbagliata di `strcmp` nella trascrizione 2.6.
- Le trascrizioni sono automatiche, quindi alcune parole sono storpiate. "Gotu" vuol dire `goto`, "scan f per 100d" vuol dire `scanf("%d")`, "HIP" vuol dire heap.
  I README le traducono quando le citano.
- Mancano le trascrizioni video **2.3** (I/O) e **3.3** (call and return). Per quelle parti le fonti sono la Dispensa 2.3.2, gli Appunti e le LEZ.
- Le lezioni Word (`LEZIONI/07–21`) contengono altri esercizi. Quelli della repo sono **nuovi** o varianti diverse, quindi non li ripeti.

---

## 5. Struttura della repo

```
NN-argomento/
  README.md               teoria flash, esercizi, suggerimenti, soluzioni spiegate, prompt, glossario
  esXX_nome.c             starter da completare (oppure cartella esXX_nome/ per esercizi su più file)
  soluzioni/esXX_nome.c   soluzione commentata
  tests/esXX_nome*.in     input dei test
  tests/esXX_nome*.out    output atteso
  tests/fixtures/         file di prova per gli esercizi sui file
scripts/run_tests.sh      compila ed esegue i test (compatibile con la bash di macOS)
Makefile                  scorciatoie: make test / make sol / make nosan
PROMPTS.md                prompt pronti da usare con Claude
```
