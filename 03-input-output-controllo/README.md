# 03 — Input, output e strutture di controllo

> Lezioni di riferimento: Dispensa 2.3.2 "Input e Output", Appunti Unità 2 (capitolo 1 par. 1.20 "Controllo del flusso"; capitolo 2 par. 2.2–2.16: scanf, specificatori di formato, buffer di input, operatore ternario, else pendente, switch, while, do-while, for, operatore virgola, break/continue, invarianti di ciclo, errori comuni), LEZ 09.
> **Nota sulle fonti:** per l'argomento 2.3 **non esiste la trascrizione della videolezione**. Gli esempi qui sotto vengono quindi dalla dispensa 2.3.2 e dagli Appunti di fine Unità 2.
> Tempo stimato: ~4 ore.

## Teoria flash

**stdin e stdout.** Un programma C ha due "canali" sempre aperti. *stdin* (standard input, cioè l'ingresso standard) è da dove arrivano i dati: di solito la tastiera, ma nei test è un file `.in`. *stdout* (standard output, cioè l'uscita standard) è dove vanno i risultati: di solito lo schermo. Pensa a un tubo che entra e un tubo che esce. Le funzioni per usarli stanno in `stdio.h` (standard input/output header, il file che "dichiara" printf, scanf, getchar, putchar).

**printf e la stringa di formato.** `printf("testo %d\n", x)` stampa il testo e sostituisce ogni *segnaposto* (il pezzo che inizia con `%`) con il valore della variabile corrispondente. È come un modulo prestampato con degli spazi vuoti da riempire, nell'ordine. I segnaposto principali (dispensa 2.3.2):

| segnaposto | tipo | esempio | stampa |
|---|---|---|---|
| `%d` | int | `printf("%d", 42)` | `42` |
| `%f` | double/float | `printf("%f", 2.5)` | `2.500000` |
| `%.2f` | double con 2 decimali | `printf("%.2f", 2.5)` | `2.50` |
| `%c` | char | `printf("%c", 'A')` | `A` |
| `%s` | stringa | `printf("%s", "ciao")` | `ciao` |
| `%%` | il simbolo % | `printf("22%%")` | `22%` |

La **larghezza di campo** è un numero tra `%` e la lettera: `%5d` occupa almeno 5 colonne, allineando a destra (`"    7"`); `%-5d` allinea a sinistra (`"7    "`); `%05d` riempie con zeri (`"00007"`); `%8.2f` = 8 colonne in tutto, 2 decimali. Serve per fare tabelle con le colonne in fila. Nota: il prof nella dispensa usa `%lf` anche in printf; in printf `%f` e `%lf` sono equivalenti per i double, in **scanf no** (vedi sotto).

**scanf.** `scanf("%d", &x)` legge dal buffer di input, *interpreta* i caratteri secondo il segnaposto e mette il risultato in `x`. La `&` (si legge "indirizzo di") passa a scanf il *posto* in memoria di `x`, non il suo valore: è come dare a qualcuno l'indirizzo di casa invece di una foto della casa, così può entrarci e cambiare cosa c'è dentro. La vedremo bene con i puntatori; per ora: in scanf ci vuole sempre `&` (tranne per le stringhe `%s`). In scanf: `%d` int, `%f` **float**, `%lf` **double** (qui la `l` è obbligatoria), `%c` char.

**Il valore di ritorno di scanf.** scanf restituisce un `int`: *quante variabili è riuscita a riempire* (dispensa: "Restituisce un int che indica il numero di elementi assegnati"). Con `scanf("%d %d", &a, &b)` e input `3 5` → 2; input `3 ciao` → 1; input `ciao` → 0; input finito → `EOF` (End Of File, cioè "fine del file": una costante negativa, di solito -1, definita in stdio.h). Controllarlo è l'unico modo per sapere se la variabile contiene davvero un dato letto.

**Il buffer di input.** I caratteri digitati non arrivano subito al programma: si accumulano in un *buffer* (una coda di attesa, come la fila alla posta) e vengono consegnati quando premi Invio, **compreso il carattere `\n`** dell'Invio. scanf prende dalla coda solo quello che le serve e lascia il resto. Conseguenze:
- dopo `scanf("%d", &n)` il `\n` resta in coda, e un successivo `scanf("%c", &c)` legge proprio quel `\n`. Rimedio: `scanf(" %c", &c)`, dove lo spazio significa "salta spazi, tab e a capo";
- se l'input non è numerico, `%d` fallisce e **non consuma** i caratteri sbagliati: se rileggi senza toglierli, fallisci all'infinito. Rimedio: scartarli con `getchar()` fino al `\n`;
- nella stringa di formato si possono mettere caratteri "fissi" che devono comparire nell'input: l'esempio del prof (Appunti 2.6) è `scanf("%2d/%2d/%4d", &giorno, &mese, &anno)`, dove `2` e `4` sono la larghezza massima (quante cifre leggere al massimo) e `/` deve esserci identico.

**getchar e putchar.** `c = getchar()` legge **un** carattere da stdin; `putchar(c)` scrive un carattere su stdout. La variabile va dichiarata `int`, non `char`: getchar deve poter restituire anche `EOF`, che non è un carattere. La dispensa dice "Restituisce una variabile di tipo char. Formalmente restituisce una variabile di tipo int": la seconda frase è quella giusta, la prima è una semplificazione. Il ciclo classico: `while ((c = getchar()) != EOF) { ... }`.

**Condizioni: in C lo zero è falso.** Non esiste un tipo booleano "di base" (lo vediamo nella cartella 04): ogni condizione è un numero; `0` = falso, **qualunque altro valore** = vero. `x > 3` vale 1 o 0.

**if / else.** `if (cond) { A } else { B }`: esegue A se la condizione è vera, altrimenti B. Le catene `else if` servono per casi che si escludono a vicenda. *Else pendente* (Appunti 2.9): senza graffe, un `else` si attacca all'`if` **più vicino** che non ha ancora un else, anche se l'indentazione (i rientri) fa pensare altro. Rimedio: graffe sempre. *Operatore ternario* (Appunti 2.8): `v = (cond ? a : b);` è un if/else che produce un valore.

**switch.** Confronta un'espressione **intera** (int, char, enum) con delle costanti:
```c
switch (cmd) {
case 'v':            /* etichetta: un punto a cui saltare */
    totale += imp;
    break;           /* esce dallo switch */
case 's':            /* due etichette di fila = stesso codice per 's' e 'S' */
case 'S':
    stampa();
    break;
default:             /* tutti gli altri valori */
    printf("?\n");
}
```
`case` è solo un'etichetta di ingresso: una volta entrato, il programma esegue **tutto quello che segue, fino al primo `break`**, anche le istruzioni dei case successivi. Questo comportamento si chiama *fall-through* ("cadere attraverso"). Dispensa: "Interrompe la valutazione! Altrimenti esegue tutte le istruzioni successive fino al primo break. Ricordarsi di usare i break!". L'unico uso voluto è il *raggruppamento* (`case 's': case 'S':`).

**I cicli.**
- `while (cond) { corpo }` — *controllo in ingresso*: la condizione è verificata prima; il corpo può essere eseguito **zero** volte. Si usa quando non sai quante ripetizioni farai (es. "leggi finché non arriva 0").
- `do { corpo } while (cond);` — *controllo in uscita*: il corpo è eseguito **almeno una volta**. Si usa per la validazione dell'input ("chiedi finché non è valido"): prima devi leggere, poi puoi controllare. Attenzione al `;` finale, obbligatorio.
- `for (iniz; cond; incr) { corpo }` — un while compatto: (1) iniz una volta, (2) cond, (3) corpo, (4) incr, si torna a (2). Si usa quando c'è un contatore. `for (i = 0; i < n; i++)` fa esattamente n giri.
- *Sentinella*: un valore speciale che segnala "basta" (es. lo 0 in una lista di voti). Si controlla **prima** di elaborare il dato, così la sentinella non viene contata.
- `break` esce **dal ciclo (o switch) più interno** in cui si trova. `continue` salta il resto del corpo e passa al giro successivo (nel for esegue comunque l'incremento; nel do-while salta alla condizione).
- *Cicli annidati*: un ciclo dentro un altro. Per ogni giro dell'esterno, l'interno fa tutti i suoi giri (come le lancette: per ogni ora, i minuti fanno tutto il giro).
- *Operatore virgola* (Appunti 2.13): `for (i = 0, j = 5; i < j; i++, j--)` valuta le espressioni da sinistra a destra.

Il prof (dispensa 2.3.2, "while vs do-while", "while vs for", "if vs switch") insiste sul **costrutto appropriato**: do-while quando il corpo va fatto almeno una volta, while con lettura prima del ciclo quando c'è una sentinella, for quando c'è un indice, switch invece di tanti if sulla stessa variabile.

**Imprecisioni nelle fonti (da sapere):**
- La dispensa 2.3.2 usa `void main()` e `while(true)` senza includere `stdbool.h`. In C standard si scrive `int main(void)`, e `true` esiste solo dopo `#include <stdbool.h>`: con `-std=c11` il codice della slide **non compila** (`'true' undeclared`). Nei nostri file usiamo `while (1)` o una variabile flag.
- Nella slide "if vs switch" la versione con gli if confronta `a == 0`, `a == 1`, `a == 3`, mentre lo switch "equivalente" usa `case 0`, `case 1`, `case 2`: i due codici non sono davvero equivalenti (refuso).
- Gli Appunti 2.11 dicono "oltre al ciclo for, già analizzato", ma il for è spiegato dopo, in 2.12.
- La dispensa dice che getchar "restituisce un char" e subito dopo "formalmente un int": vale la seconda.

**Errori tipici** (messaggi reali di gcc; su macOS clang dà messaggi simili):
1. **scanf senza `&`**: `scanf("%d", n);` → `warning: format '%d' expects argument of type 'int *', but argument 2 has type 'int'` (clang: `format specifies type 'int *' but the argument has type 'int'`). A runtime di solito il programma va in crash.
2. **`=` al posto di `==`**: `if (n = 0)` → `warning: suggest parentheses around assignment used as truth value [-Wparentheses]`. Assegna 0 a n e la condizione è sempre falsa.
3. **switch senza break**: gcc → `warning: this statement may fall through [-Wimplicit-fallthrough=]`. **Clang su macOS NON lo segnala** con `-Wall -Wextra`: devi accorgertene tu.
4. **Segnaposto sbagliato**: `printf("%d", 2.5)` → `warning: format '%d' expects argument of type 'int', but argument 2 has type 'double'`. Stampa un numero senza senso.
5. **`;` dopo while**: `while (x < 10); { x++; }` (esempio "Cosa fa questo programma?" della dispensa). Il `;` è un'istruzione vuota ed è *lui* il corpo del ciclo: il blocco tra graffe non è nel ciclo e il programma resta bloccato all'infinito. Nessun warning né da gcc né da clang.
6. **Off-by-one** (sbagliare di uno): `for (i = 0; i <= 10; i++)` fa 11 giri, non 10 (Appunti 2.16.2).

> **Nota sui test:** i programmi della cartella **non stampano messaggi di richiesta** tipo "Inserisci un numero:", perché finirebbero nell'output e renderebbero i test fragili. Il confronto ignora le differenze nel *numero* di spazi (`diff -b`), ma non la loro presenza o assenza né i decimali.

## Esercizi

### es01 — Scontrino formattato con printf  ·  Base
**Fonte:** Dispensa 2.3.2, slide "Stampare a schermo con printf" (`printf("PI: %lf, num: %d, c: %c\n", ...)`); Appunti Unità 2, par. 2.5 "Specificatori di formato".

**Testo:** il programma legge quantità (int), prezzo unitario (double) e categoria (char). La lettura è già scritta. Devi scrivere le tre printf che producono una tabella allineata: intestazione con larghezze 8 (allineata a sinistra), 5, 9, 9 (a destra); riga dati con le stesse larghezze e i prezzi con 2 decimali; riga dell'IVA (22% del totale).
```text
Input:   3 2.5 A
Output:
Cat.      Qta   Prezzo   Totale
A           3     2.50     7.50
IVA 22% inclusa: 1.65
```
**File:** `es01_scontrino.c` · **Test:** `make test T=03 E=es01`

<details><summary>💡 Suggerimento</summary>
Il segno meno nella larghezza (<code>%-8s</code>, <code>%-8c</code>) allinea a sinistra. Larghezza e decimali si combinano: <code>%9.2f</code>. Per far comparire il simbolo % devi scriverlo due volte.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Intestazione.** Le parole sono stringhe costanti: le passo come argomenti a `%s`, così posso dare loro una larghezza. `%-8s` riserva 8 colonne e mette "Cat." a sinistra; `%5s` e `%9s` allineano a destra, come i numeri sotto. Perché non scrivere a mano gli spazi? Perché se cambi una larghezza devi ricontarli tutti; così la larghezza è in un punto solo.
2. **Riga dati.** Stesse larghezze, segnaposto diversi: `%-8c` per il char, `%5d` per l'int, `%9.2f` per i double. Se usassi `%f` senza `.2` avresti 6 decimali (`2.500000`) e la tabella si storcerebbe.
3. **Il simbolo %.** Dentro la stringa di formato `%` significa "qui inizia un segnaposto". Per stampare il simbolo vero si scrive `%%`.
4. **Arrotondamento.** `%.2f` arrotonda, non tronca: con `12 1.333 C` il totale vero è 15.996 e viene stampato `16.00`.

```c
printf("%-8s%5s%9s%9s\n", "Cat.", "Qta", "Prezzo", "Totale");
printf("%-8c%5d%9.2f%9.2f\n", cat, qta, prezzo, totale);
printf("IVA 22%% inclusa: %.2f\n", iva);
```
Nota anche la lettura: `scanf("%d %lf %c", ...)` usa `%lf` perché `prezzo` è double. Lo spazio prima di `%c` salta il separatore: nel test 3 la categoria è addirittura sulla riga dopo, e funziona lo stesso. Codice completo in `soluzioni/es01_scontrino.c`.
</details>

### es02 — Leggere una data e controllare il valore di ritorno di scanf  ·  Base
**Fonte:** Appunti Unità 2, par. 2.6 "Buffer di input" (esempio del prof `scanf("%2d/%2d/%4d", &giorno, &mese, &anno)`); Dispensa 2.3.2, slide "Funzione scanf" ("Restituisce un int che indica il numero di elementi assegnati").

**Testo:** leggi una data `gg/mm/aaaa` con **una sola** scanf e stampa una di queste righe:
- `Errore: nessun input (EOF)` se l'input è vuoto;
- `Errore: letti N campi su 3` se scanf ha letto meno di 3 numeri;
- `Errore: data fuori intervallo` se il mese non è fra 1 e 12 o il giorno non è fra 1 e 31;
- altrimenti `Data: gg-mm-aaaa`, con gli zeri iniziali.
```text
6/10/2026   ->  Data: 06-10-2026
31/13/2025  ->  Errore: data fuori intervallo
12-05-2024  ->  Errore: letti 1 campi su 3
(vuoto)     ->  Errore: nessun input (EOF)
1/1/5       ->  Data: 01-01-0005
```
**File:** `es02_data.c` · **Test:** `make test T=03 E=es02`

<details><summary>💡 Suggerimento</summary>
Salva il risultato: <code>letti = scanf(...)</code>. Controlla prima il caso EOF, poi il caso "meno di 3", poi l'intervallo. L'ordine conta: se scanf non ha letto il mese, controllarne il valore non ha senso. <code>%02d</code> mette lo zero davanti.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Una scanf con il "modello".** `"%2d/%2d/%4d"` dice: leggi al massimo 2 cifre, poi aspettati una `/`, poi altre 2 cifre, una `/`, 4 cifre. Il prof negli Appunti fa notare che la stringa di formato è una piccola *grammatica* (un insieme di regole che descrive quali testi sono accettati): scanf la usa come stampo.
2. **Perché controllare il ritorno.** Con `12-05-2024` scanf legge `12`, poi si aspetta `/` e trova `-`: si ferma e restituisce 1. Mese e anno **non vengono toccati**. Se li stampassi, stamperesti valori mai letti.
3. **Perché EOF va controllato per primo.** Con input vuoto scanf restituisce `EOF` (negativo), non 0. Se controllassi solo `letti != 3` stamperesti "letti -1 campi su 3", che non ha senso.
4. **Forma contro significato.** `31/13/2025` ha la forma giusta (scanf restituisce 3), ma il mese 13 non esiste. scanf controlla la forma; il significato lo controlli tu con un if.
5. **Zeri iniziali.** `%02d` = almeno 2 colonne, riempite con `0`. `%04d` per l'anno.

```c
int letti = scanf("%2d/%2d/%4d", &giorno, &mese, &anno);
if (letti == EOF)        printf("Errore: nessun input (EOF)\n");
else if (letti != 3)     printf("Errore: letti %d campi su 3\n", letti);
else if (mese < 1 || mese > 12 || giorno < 1 || giorno > 31)
                         printf("Errore: data fuori intervallo\n");
else                     printf("Data: %02d-%02d-%04d\n", giorno, mese, anno);
```
Codice completo in `soluzioni/es02_data.c`.
</details>

### es03 — Copia in MAIUSCOLO con getchar/putchar fino a EOF  ·  Base
**Fonte:** Dispensa 2.3.2, slide "Funzione getchar" ("Formalmente restituisce una variabile di tipo int ... errori possibili!"); Appunti Unità 2, par. 2.11.1 (ciclo while).

**Testo:** leggi l'input un carattere alla volta e ricopialo in output, trasformando le minuscole in maiuscole (senza `toupper`). Alla fine stampa `--` e i conteggi: caratteri letti (tutti, compresi spazi e `\n`), righe (numero di `\n`), cifre.
```text
Input:
ciao mondo 2026
SecAI UniMi, anno 1!
Output:
CIAO MONDO 2026
SECAI UNIMI, ANNO 1!
--
caratteri=37 righe=2 cifre=5
```
Caso limite: input vuoto → solo `--` e `caratteri=0 righe=0 cifre=0`.
**File:** `es03_maiuscolo.c` · **Test:** `make test T=03 E=es03`

<details><summary>💡 Suggerimento</summary>
Le lettere minuscole hanno codici consecutivi ('a'=97 ... 'z'=122), e così le maiuscole ('A'=65 ...). La distanza tra una minuscola e la sua maiuscola è sempre la stessa: <code>'a' - 'A'</code>.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Variabile `int`.** `getchar` restituisce un carattere oppure `EOF` (di solito -1). Se `c` fosse `char`, su alcune macchine (dove char non ha segno) -1 diventerebbe 255 e il ciclo non finirebbe mai. È l'"errore possibile" della dispensa.
2. **Il ciclo.** `while ((c = getchar()) != EOF)`: prima assegna, poi confronta. Le parentesi interne sono necessarie: `!=` ha precedenza più alta di `=`, quindi senza parentesi `c` riceverebbe il risultato del confronto (0 o 1).
3. **Classificare.** Un `\n` aumenta le righe; `c >= '0' && c <= '9'` riconosce una cifra (anche le cifre sono consecutive); per le minuscole `c = c - 'a' + 'A'`: `c - 'a'` è la posizione nell'alfabeto (0 per 'a', 2 per 'c'), `+ 'A'` porta alla stessa posizione fra le maiuscole.
4. **putchar.** Ristampa `c` (trasformato o no).

Simulazione sui primi caratteri di `ciao`:

| c letto | codice | è minuscola? | c stampato |
|---|---|---|---|
| `c` | 99 | sì | 99-97+65 = 67 → `C` |
| `i` | 105 | sì | 73 → `I` |
| ` ` (spazio) | 32 | no | ` ` |
| `2` | 50 | no (è cifra, cifre=1) | `2` |

Codice completo in `soluzioni/es03_maiuscolo.c`. Per provarlo a mano: `./a.out` poi scrivi del testo e premi **Ctrl+D** (su macOS/Linux, a inizio riga) per mandare EOF.
</details>

### es04 — Trova e correggi l'errore: la cassa con lo switch  ·  Intermedio
**Fonte:** Dispensa 2.3.2, slide "Costrutto switch - 2/3" ("Ricordarsi di usare i break!", "Raggruppamento di diverse condizioni"); Appunti Unità 2, par. 2.10.

**Testo:** il programma simula una cassa. Legge comandi fino alla sentinella `q`: `v IMPORTO` (vendita), `r IMPORTO` (reso), `s` o `S` (stampa totale), altro → `Comando sconosciuto: X`. Il codice compila ma i risultati sono sbagliati. Trova e correggi gli errori **senza riscrivere il programma**.
```text
Input:  v 10.50 / v 4 / s / r 2.25 / x / S / q / v 100   (uno per riga)
Output atteso:
Totale: 14.50 (vendite: 2, resi: 0)
Comando sconosciuto: x
Totale: 12.25 (vendite: 2, resi: 1)
Cassa chiusa. Totale finale: 12.25
```
**File:** `es04_cassa.c` · **Test:** `make test T=03 E=es04`

<details><summary>💡 Suggerimento</summary>
Su Linux gcc ti indica due righe con "may fall through". Su macOS clang tace: esegui il test e guarda in quali punti l'output ha <em>troppe</em> righe o un totale a zero. Attenzione: non tutti gli "attraversamenti" sono errori.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Sintomo 1: le vendite non contano.** Al primo `s` il totale dovrebbe essere 14.50, ma lo starter stampa `Totale: 0.00 (vendite: 2, resi: 2)`. Perché? `case 'v'` non ha `break`: dopo `totale += imp` l'esecuzione "cade" nel `case 'r'` ed esegue anche `totale -= imp; resi++;`. **Correzione 1:** `break;` dopo `vendite++`.
2. **Sintomo 2: dopo ogni totale compare "Comando sconosciuto: s" (o "S").** Il blocco di `s`/`S` non ha `break` e cade nel `default`. **Correzione 2:** `break;` dopo la printf del totale.
3. **Il falso errore.** `case 's': case 'S':` sono due etichette consecutive senza niente in mezzo: è il *raggruppamento* legittimo mostrato dal prof. Qui il fall-through è voluto (e infatti gcc non lo segnala).
4. **Altre cose da notare.** `scanf(" %c", &cmd)`: lo spazio salta l'a capo della riga precedente (senza, `cmd` varrebbe `'\n'` e avresti "Comando sconosciuto" a ogni riga). La condizione del while è composta: si esce se scanf non legge niente (EOF) **oppure** se il comando è `q`. Così `v 100` dopo la `q` non viene mai letto. Il `break` dentro `if (scanf(...) != 1)` si trova **fuori** dallo switch, quindi esce dal while (test 3: `v` senza importo).

Codice corretto in `soluzioni/es04_cassa.c`.
</details>

### es05 — Cosa stampa? Cicli, break e continue  ·  Intermedio
**Fonte:** Dispensa 2.3.2, slide "Il ciclo while - 11…21" (simulazione riga per riga) e "Cosa fa questo programma?"; Appunti Unità 2, par. 2.11.5 (while vs do-while con `i = 10`), 2.13 (operatore virgola), 2.14 (break e continue).

**Testo:** **non modificare il file.** Leggi `es05_cosa_stampa.c` e scrivi qui sotto, parte per parte, l'output che prevedi. Poi esegui il test e confronta con `tests/es05_cosa_stampa.out`.
```text
La mia previsione:
Parte A: ...
Parte B: ...
Parte C: ...
Parte D: ...
Parte E: ...
Parte F: ...
```
**File:** `es05_cosa_stampa.c` · **Test:** `make test T=03 E=es05` (passa già: serve a confermare l'output reale)

<details><summary>💡 Suggerimento</summary>
Fai come il prof nella dispensa: una tabella con il valore delle variabili a ogni giro. Ricorda: <code>continue</code> nel for esegue comunque l'incremento; <code>x++</code> restituisce il valore <em>prima</em> dell'incremento.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

```text
A-do 10
1 2 4 5 7 | B: i=8
1
12
123
1234
x=1 x=2 x=3 | D: x=4
(0,5) (1,4) (2,3) | E: i=3 j=2
[   1][1   ]
[  10][10  ]
[ 100][100 ]
```
- **A.** `x = 10`, `10 < 5` è falso: il while non esegue il corpo **nemmeno una volta**. Il do-while invece esegue il corpo prima di controllare: stampa `A-do 10`, poi `x` diventa 11, `11 < 5` falso, esce. È l'esempio degli Appunti 2.11.5.
- **B.**

  | i | i%3==0? | i>7? | azione |
  |---|---|---|---|
  | 0 | sì | – | continue |
  | 1, 2 | no | no | stampa |
  | 3 | sì | – | continue |
  | 4, 5 | no | no | stampa |
  | 6 | sì | – | continue |
  | 7 | no | no | stampa |
  | 8 | no | **sì** | break |

  Il `break` esce con `i = 8` (l'incremento non viene eseguito). Nota l'ordine: il controllo `continue` viene prima del controllo `break`. Con `i = 9` non si arriva mai.
- **C.** Per ogni `i`, il ciclo interno stampa `j` finché `j <= i`; quando `j > i` il `break` esce **solo dal for interno** e si esegue `printf("\n")` dell'esterno. Ne esce un triangolo.
- **D.** `x++ < 3` confronta il valore **vecchio** di x e poi lo incrementa. Giri: confronta 0 (vero, x=1, stampa 1), 1 (vero, x=2), 2 (vero, x=3), 3 (falso, ma x diventa comunque 4). Per questo alla fine `x=4` e non 3.
- **E.** L'operatore virgola inizializza due variabili e ne aggiorna due. `i` sale e `j` scende: (0,5), (1,4), (2,3); poi i=3, j=2 e `3 < 2` è falso.
- **F.** `i *= 10` moltiplica: 1, 10, 100, poi 1000 > 100 ed esce. `[%4d]` allinea a destra in 4 colonne, `[%-4d]` a sinistra.
</details>

### es06 — Validazione dell'input con do-while  ·  Intermedio
**Fonte:** Dispensa 2.3.2, slide "Il ciclo do while - 2" (`printf("Inserisci un valore > 0\n"); scanf(...)` ripetuto finché `x<=0`) e "while vs do-while - 1"; Appunti Unità 2, par. 2.11.6 "Uso tipico del ciclo do-while".

**Testo:** completa `int leggi_voto(void)`: deve leggere interi finché non arriva un voto valido fra 18 e 30, e restituirlo. Se l'input non è numerico stampa `Input non numerico, riprova` e scarta il resto della riga; se il numero è fuori intervallo stampa `Voto V fuori intervallo (18-30), riprova`. Se l'input finisce restituisce -1. Il `main` (già scritto) legge 3 voti e stampa la media.
```text
Input:          Output:
abc             Input non numerico, riprova
15              Voto 15 fuori intervallo (18-30), riprova
31              Voto 31 fuori intervallo (18-30), riprova
27              Input non numerico, riprova
x 28            Media: 25.00
30
18
```
**File:** `es06_voti_validi.c` · **Test:** `make test T=03 E=es06`

<details><summary>💡 Suggerimento</summary>
Tre esiti di scanf: <code>EOF</code>, <code>0</code>, <code>1</code>. Nel caso 0 i caratteri sbagliati sono ancora nel buffer: se non li togli con un ciclo di <code>getchar()</code> fino a <code>'\n'</code>, il programma riprova all'infinito sugli stessi caratteri. Usa una variabile <code>valido</code> (0/1) come condizione del do-while.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché do-while.** Devo leggere almeno una volta prima di poter dire se il voto va bene. Con un while dovrei scrivere la scanf due volte (prima del ciclo e dentro): è il "costrutto inappropriato" della dispensa.
2. **Tre esiti.** `r == EOF` → `return -1` (inutile insistere: non arriverà altro). `r == 0` → input non numerico. Altrimenti controllo l'intervallo.
3. **Svuotare il buffer.** `while ((c = getchar()) != '\n' && c != EOF) { }` consuma tutti i caratteri fino a fine riga. Il controllo `c != EOF` evita un ciclo infinito se l'ultima riga non ha `\n`. Nota il test: `x 28` produce **un solo** messaggio e il 28 viene perso, perché viene scartato insieme alla `x`.
4. **La flag.** `int valido = 0;` diventa 1 solo nel ramo buono; il ciclo ripete `while (!valido)`. `!` è il "non" logico: `!0` = 1.
5. **Media.** `(double)somma / 3`: il *cast* (conversione esplicita di tipo) a double evita la divisione intera (73/3 darebbe 24, non 24.33).

```c
do {
    int r = scanf("%d", &v);
    if (r == EOF) return -1;
    else if (r == 0) { int c; while ((c = getchar()) != '\n' && c != EOF) { }
                       printf("Input non numerico, riprova\n"); }
    else if (v < 18 || v > 30) printf("Voto %d fuori intervallo (18-30), riprova\n", v);
    else valido = 1;
} while (!valido);
```
Codice completo in `soluzioni/es06_voti_validi.c`.
</details>

### es07 — Tabella dei numeri primi fino a n  ·  Tipo esame
**Fonte:** Appunti Unità 2, par. 2.12 (for), 2.14 (break), 2.16.2 (off-by-one); Dispensa 2.3.2 "while vs for - 3" (con un indice si usa il for). Esercizio nuovo che combina cicli annidati e printf con larghezza.

**Testo:** leggi `n` e stampa tutti i numeri primi `<= n`, ognuno con `%5d`, **8 per riga**. Poi stampa `Trovati K numeri primi`, oppure `Nessun primo <= n` se non ce ne sono. Se l'input non è un numero stampa `Input non valido`. Un numero è *primo* se è maggiore di 1 e ha come divisori solo 1 e se stesso.
```text
Input: 30
    2    3    5    7   11   13   17   19
   23   29
Trovati 10 numeri primi
Input: 1    ->  Nessun primo <= 1
Input: -5   ->  Nessun primo <= -5
```
**File:** `es07_numeri_primi.c` · **Test:** `make test T=03 E=es07`

<details><summary>💡 Suggerimento</summary>
Separa i due cicli: <code>e_primo(k)</code> prova i divisori (ciclo interno); il main scorre i candidati da 2 a n (ciclo esterno). Per l'a capo usa il contatore dei primi trovati e l'operatore <code>%</code> (resto della divisione).
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **e_primo.** Se `k < 2` restituisco 0 (0, 1 e i negativi non sono primi). Poi provo `d = 2, 3, ...` finché `d * d <= k`: se `k` avesse un divisore più grande della radice, avrebbe anche il "compagno" più piccolo della radice, che avrei già trovato. Appena `k % d == 0` faccio `return 0`: come un `break`, smetto di cercare. Se il ciclo finisce senza trovare divisori, `return 1`.
2. **Ciclo esterno.** `for (k = 2; k <= n; k++)`: `<=` e non `<`, altrimenti con n = 19 perderei il 19 (errore off-by-one). Se n < 2 il ciclo non fa neanche un giro e `trovati` resta 0: il caso "nessun primo" (anche per i negativi) è gestito senza if aggiuntivi.
3. **8 per riga.** Dopo ogni stampa `trovati++`; se `trovati % 8 == 0` vado a capo. Alla fine, se l'ultima riga è incompleta (`trovati % 8 != 0`), aggiungo l'a capo mancante. Con n = 19 i primi sono esattamente 8: la riga è completa e non serve un secondo a capo (test 3).
4. **Input non valido.** `scanf("%d", &n) != 1` → messaggio e `return 1`.

| k | d provati | primo? | trovati |
|---|---|---|---|
| 2 | nessuno (2*2 > 2) | sì | 1 |
| 9 | 2, 3 → 9%3==0 | no | 4 |
| 25 | 2, 3, 4, 5 → 25%5==0 | no | 9 |
| 29 | 2..5 (6*6 > 29) | sì | 10 |

Codice completo in `soluzioni/es07_numeri_primi.c`.
</details>

### es08 — Registro voti con sentinella e istogramma  ·  Tipo esame
**Fonte:** Dispensa 2.3.2, slide "while vs do-while - 2" (lettura prima del ciclo con `STOP`, il while "evita un doppio controllo"); Appunti Unità 2, par. 2.14 (continue), 2.16.5 (uso di continue), 2.15.1 (somma accumulata in un ciclo).

**Testo:** leggi voti interi fino alla sentinella `0` (oppure fino alla fine dell'input o a un dato non numerico). I voti fuori da 18..30 vanno ignorati stampando `Ignorato: V`. Alla fine stampa numero dei voti validi, media (2 decimali), minimo e massimo, e un istogramma per fasce 18-23, 24-27, 28-30 con un `*` per voto. Se non ci sono voti validi stampa solo `Nessun voto valido` (e non calcolare la media: sarebbe una divisione per zero).
```text
Input: 24 30 18 27
       28 0 25
Output:
Voti validi: 5
Media: 25.40
Minimo: 18  Massimo: 30
18-23 | * (1)
24-27 | ** (2)
28-30 | ** (2)
```
**File:** `es08_registro_voti.c` · **Test:** `make test T=03 E=es08`

<details><summary>💡 Suggerimento</summary>
Metti scanf <em>dentro</em> la condizione del while: <code>while (scanf("%d", &v) == 1 && v != 0)</code>. Per min e max: il primo voto valido li inizializza entrambi. Per le fasce basta una catena if / else if / else.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Sentinella nella condizione.** `scanf(...) == 1 && v != 0`: grazie alla *valutazione short-circuit* (cortocircuito: se la prima parte di `&&` è falsa la seconda non viene valutata), se scanf fallisce non si guarda `v`, che conterrebbe un valore vecchio. Lo 0 non entra mai nel corpo, quindi non viene contato come voto. È la forma "appropriata" della dispensa: un solo controllo sulla sentinella.
2. **Scartare con continue.** Se il voto è fuori intervallo stampo `Ignorato` e faccio `continue`: il resto del corpo viene saltato. Gli Appunti (2.16.5) fanno notare che si potrebbe anche mettere il resto del corpo in un `else`: entrambe le versioni sono corrette.
3. **Min e max.** Inizializzarli a 0 sarebbe sbagliato (il minimo risulterebbe 0, che non è un voto). Uso `n == 1 ||`: il primo voto valido li imposta, i successivi li aggiornano solo se serve.
4. **Fasce.** `if (v <= 23) f1++; else if (v <= 27) f2++; else f3++;`: siccome i rami si escludono, il secondo test non deve ricontrollare `v >= 24`.
5. **Istogramma.** `stampa_barra` contiene il ciclo che stampa `quanti` asterischi con `putchar('*')`. Chiamarla tre volte nel main produce un ciclo dentro una sequenza di chiamate: è lo stesso schema dei cicli annidati, con il ciclo interno spostato in una funzione.
6. **Media.** `(double)somma / n`, eseguita solo se `n > 0`.

Tabella del test 1:

| v letto | valido? | n | somma | min | max | f1 f2 f3 |
|---|---|---|---|---|---|---|
| 24 | sì | 1 | 24 | 24 | 24 | 0 1 0 |
| 30 | sì | 2 | 54 | 24 | 30 | 0 1 1 |
| 18 | sì | 3 | 72 | 18 | 30 | 1 1 1 |
| 27 | sì | 4 | 99 | 18 | 30 | 1 2 1 |
| 28 | sì | 5 | 127 | 18 | 30 | 1 2 2 |
| 0 | sentinella: esce | | | | | |

127 / 5 = 25.40. Il 25 dopo lo 0 non viene mai letto. Codice completo in `soluzioni/es08_registro_voti.c`.
</details>

## Prompt pronti per questo argomento

1. «Interrogami con 6 domande su printf, scanf e il buffer di input (valore di ritorno di scanf, `%lf` contro `%f`, lo spazio prima di `%c`), **una alla volta**. Aspetta la mia risposta prima di passare alla successiva e correggimi spiegando il perché.»
2. «Scrivimi 4 frammenti di codice C con cicli (while, do-while, for, break, continue, cicli annidati) in stile "Cosa stampa?", uno alla volta. Io scrivo la previsione, tu mi dici se è giusta e mi fai la tabella delle variabili giro per giro.»
3. «Ho scritto questa soluzione per es06 di 03-input-output-controllo: [incolla codice]. Dimmi se è corretta e perché, cosa succede con input non numerico ed EOF, senza riscrivermela tutta.»
4. «Generami 3 esercizi nuovi tipo es08 (lettura con sentinella + statistiche + stampa formattata), con input e output di esempio, ma senza soluzione. Me la dai solo quando te la chiedo.»
5. «Mostrami 3 programmi con uno switch che contiene un errore di fall-through o un raggruppamento di case. Per ognuno chiedimi se è un errore o è voluto, e perché.»

## Riepilogo
- printf e scanf usano una stringa di formato con segnaposto (`%d`, `%f`/`%lf`, `%c`, `%s`); in printf larghezza e precisione (`%5d`, `%9.2f`) impaginano l'output; in scanf servono `&` e `%lf` per i double.
- scanf restituisce quante variabili ha riempito (o EOF): va controllato, e l'input sbagliato resta nel buffer finché non lo scarti (con `getchar`).
- switch confronta con costanti ed esegue tutto fino al primo `break`: dimenticarlo causa il fall-through, che è voluto solo per raggruppare case.
- while (0 o più giri, adatto alle sentinelle), do-while (almeno 1 giro, adatto alla validazione), for (contatore); break esce dal ciclo più interno, continue salta al giro dopo.

## Glossario
- **stdin / stdout** — canale di ingresso (tastiera o file) e di uscita (schermo) del programma.
- **stringa di formato** — il primo argomento di printf/scanf, un "modello" con i segnaposto.
- **segnaposto (specificatore di formato)** — `%` + lettera, indica tipo e forma del dato (`%d`, `%.2f`).
- **larghezza di campo** — numero minimo di colonne occupate da un valore stampato (`%5d`).
- **valore di ritorno** — il risultato che una funzione restituisce a chi l'ha chiamata (per scanf: quanti campi ha letto).
- **EOF** — End Of File, "fine del file": costante negativa che segnala che l'input è finito.
- **buffer di input** — coda dove aspettano i caratteri digitati, `\n` compreso, finché qualcuno li legge.
- **getchar / putchar** — leggono / scrivono un singolo carattere.
- **switch / case / default** — selezione multipla fra costanti intere; `default` raccoglie gli altri valori.
- **break** — esce subito dallo switch o dal ciclo più interno.
- **continue** — salta il resto del corpo e passa al giro successivo del ciclo.
- **fall-through** — in uno switch senza break, l'esecuzione prosegue nel case successivo.
- **while / do-while / for** — cicli con controllo in ingresso, in uscita, e con contatore.
- **sentinella** — valore speciale che segnala la fine dei dati (es. 0).
- **flag** — variabile 0/1 usata come interruttore logico (es. `valido`).
- **cicli annidati** — un ciclo dentro il corpo di un altro.
- **off-by-one** — errore di un giro in più o in meno (es. `<=` invece di `<`).
- **else pendente** — ambiguità di un else senza graffe: si lega all'if più vicino.
- **operatore ternario** — `cond ? a : b`, un if/else che produce un valore.
- **operatore virgola** — valuta più espressioni da sinistra a destra (usato nel for).
- **cast** — conversione esplicita di tipo, es. `(double)somma`.
- **short-circuit** — in `a && b`, se `a` è falso `b` non viene valutato.
