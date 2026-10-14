# 04 — Tipi enumerati e typedef

> Lezioni di riferimento: trascrizione 2.4 "Tipi Enum e TypeDef", Appunti Unità 2 (par. 2.17 "Tipi definiti dall'utente", 2.18 "Tipi enumerativi": 2.18.1–2.18.6), LEZ 10.
> Tempo stimato: ~2,5 ore.

## Teoria flash

**Il problema.** Con i soli tipi di base (int, char, double...) un seme di carte, un giorno della settimana o lo stato di un ordine diventano "un int qualunque". Chi legge `int s = 2;` non sa cosa sia 2. Il prof apre la lezione proprio così: i tipi servono anche alla **leggibilità** (cioè a far capire il programma a chi lo legge, senza bisogno di commenti). C offre due strumenti: `typedef` e `enum`.

**typedef: un nuovo nome per un tipo esistente.** Sintassi: `typedef tipo_esistente nuovo_nome;` (con il punto e virgola, come ogni dichiarazione). Esempio del prof:
```c
typedef int anno;              /* "anno" ora è un altro nome per int */
anno a = 2010;
typedef anno anno_bisestile;   /* si può fare anche "in catena" */
```
Non nasce un tipo nuovo con regole nuove: per il compilatore `anno` **è** un int (si legge con `%d`, ci puoi mettere -7). È un'etichetta sul barattolo: il contenuto non cambia, ma chi apre la dispensa capisce cosa c'è dentro. Il prof dice che il compilatore aggiunge il nuovo nome alla sua *tabella dei simboli* (l'elenco interno di tutti i nomi che conosce, con il loro tipo). Un typedef scritto dentro un blocco `{ }` vale solo lì; scritto fuori da tutte le funzioni vale per l'intero file (*scope globale*, cioè visibile in tutto il file).

**enum: un tipo con un elenco finito di valori.** Si elencano i valori possibili, ognuno con un nome:
```c
enum seme {PICCHE, CUORI, QUADRI, FIORI};   /* "seme" è il TAG (il nome dell'enum) */
enum seme s = CUORI;                        /* con il tag serve sempre la parola enum */
```
- **Valori impliciti:** senza indicazioni il primo vale 0 e ogni successivo vale il precedente + 1 (PICCHE=0, CUORI=1, QUADRI=2, FIORI=3).
- **Valori espliciti:** `enum {FALSE = 0, TRUE = 1}`, oppure `enum {CREATO = 1, PAGATO, SPEDITO}` (PAGATO=2, SPEDITO=3: dopo un valore esplicito si riprende a contare da lì). Due nomi possono anche avere lo stesso valore.
- **Sono interi.** Gli Appunti dicono che `enum {PICCHE, ...} seme;` è "concettualmente equivalente" a quattro `#define` più `int seme;`. Differenza: le `#define` sono sostituite come testo dal *preprocessore* (il programma che "ricopia" il sorgente prima della compilazione), i nomi dell'enum invece sono costanti vere che il compilatore conosce. Ma il comportamento è quello di un int: puoi fare somme, confronti, usarli nei `for` e negli `switch`, e stamparli con `%d` (stampa il **numero**, non il nome).
- **Il C non controlla.** Una variabile `enum seme` può contenere 7 o -1 senza errori né warning. Frase del prof: "il C controlla poco, è un'idea che deve rimanerci in testa". Per questo negli switch si mette sempre un `default`.
- **Nomi unici nello stesso scope.** `enum state {WORKING, FAILED}; enum result {FAILED, PASSED};` (esempio del prof) non compila: `FAILED` è dichiarato due volte. Stessa cosa per `FIORI` nell'esempio carte/cioccolatini degli Appunti.

**Tre modi di dichiarare un enum** (Appunti 2.18.3):
```c
enum {FALSE, TRUE} b;                    /* 1. anonimo: solo la variabile b, il tipo non ha nome */
enum boolean {FALSE, TRUE};  enum boolean b;   /* 2. con tag: ogni volta "enum boolean" */
typedef enum {FALSE, TRUE} boolean;  boolean b;  /* 3. con typedef: "boolean" è un nome di tipo */
```
Il terzo è il più comodo ed è quello usato in quasi tutti gli esercizi.

**Il booleano simulato.** In C89 non esiste un tipo vero/falso. Il prof lo costruisce in due modi: `#define TRUE 1` con `typedef int boolean;`, oppure `typedef enum {FALSE, TRUE} boolean;`. Funziona perché in C una condizione è vera quando vale "non zero" (cartella 03). Il prof **non cita** `stdbool.h`. Per completezza: dal C99 esiste `#include <stdbool.h>`, che fornisce `bool`, `true`, `false` (minuscoli). Non mescolare le due cose nello stesso file.

**Il tipo intero "nascosto" (trappola del prof).** Ogni enum è memorizzato con un tipo intero scelto dal compilatore. Con gcc e clang: se c'è almeno un valore negativo si usa `int` (con segno), altrimenti `unsigned int` (*senza segno*, cioè solo numeri ≥ 0: sotto lo 0 "si gira" e si arriva al numero più grande, 4294967295, come un contachilometri che torna indietro). Esempio del prof:
```c
typedef enum {MENOUNO = -1, ZERO, UNO, DUE} intero;   /* tipo con segno */
typedef enum {ZERO_N, UNO_N, DUE_N} naturale;          /* tipo senza segno */
naturale b = ZERO_N;
b - 1 >= ZERO_N     /* vale 1 (vero!): b - 1 non è -1 ma 4294967295 */
```
Questo vale per le **variabili** di tipo enum. Le **costanti** (`ZERO_N`, `UNO_N`...) per lo standard C sono sempre `int`: `ZERO_N - 1` vale davvero -1. Vedi es03 ed es05. `sizeof` (l'operatore che dice quanti byte occupa un tipo o un'espressione; restituisce un `size_t`, un tipo intero senza segno che si stampa con `%zu`) su un enum dà 4 sia su Linux x86-64 sia su macOS arm64.

**Imprecisioni e contraddizioni nelle fonti:**
- *Trascrizione automatica*: "tipi numerativi" = enumerativi, "type def" = typedef, "size off" = sizeof, "sizeT" = size_t, "0n, 1n, 2n" = ZERO_N, UNO_N, DUE_N, "fade e fade" = i due FAILED.
- Trascrizione: "I valori sono locali al blocco... posso poi anche volendo alterarli". Le **costanti** di un enum **non** si possono modificare: `PICCHE = 5;` → gcc `error: lvalue required as left operand of assignment` (clang: `expression is not assignable`). Si possono modificare le **variabili** di tipo enum.
- Appunti 2.18.2: `enum {ZERO, UNO, DUE} numero; numero x = UNO;` **non compila**: `numero` è una *variabile*, non un tipo (gcc: `error: expected ';' before 'x'`). Per usarlo come tipo serve `typedef enum {ZERO, UNO, DUE} numero;`.
- Il prof dice "nel GCC tradizionale... utilizzo unsigned int", gli Appunti dicono "potrebbe utilizzare". Abbiamo verificato con gcc 13 e clang 18: entrambi usano unsigned int, quindi `b - 1 >= ZERO_N` vale 1. Lo standard C lascia la scelta al compilatore. Le costanti invece sono sempre int: questa distinzione nelle fonti non c'è.
- Dispensa e trascrizione usano `true`/`TRUE` creati con `#define`: in C standard i minuscoli `true`/`false` esistono già dentro `stdbool.h`. Se lo includi e poi li ridefinisci, nascono conflitti.

**Errori tipici** (messaggi reali di gcc / clang):
1. **Tag senza `enum`**: `enum seme {...}; seme s;` → gcc `error: unknown type name 'seme'; use 'enum' keyword to refer to the type`; clang `error: must use 'enum' tag to refer to type 'seme'`. Rimedio: `enum seme s;` oppure un typedef.
2. **Stesso nome in due enum**: `error: redeclaration of enumerator 'FAILED'` (clang: `redefinition of enumerator 'FAILED'`).
3. **Stampare un enum con `%s` sperando di vedere il nome**: `warning: format '%s' expects argument of type 'char *', but argument 2 has type 'unsigned int'`. A runtime di solito crash. Il nome si stampa con uno switch (es01, es03).
4. **switch su enum senza tutti i case e senza default**: `warning: enumeration value 'GIALLO' not handled in switch [-Wswitch]`. È utile: segnala i case dimenticati quando aggiungi un valore all'enum.
5. **Fidarsi che l'enum resti nell'elenco**: `s = s + 1` dopo l'ultimo valore dà un numero "fuori elenco" senza nessun warning (es04).
6. **Aritmetica con enum senza segno e numeri negativi**: `g + n` con `g` enum senza segno e `n = -10` dà un risultato enorme (es03). Rimedio: `(int)g + n`.

## Esercizi

### es01 — I semi delle carte con enum e switch  ·  Base
**Fonte:** Trascrizione 2.4 (esempio `enum {picche, cuori, quadri, fiori} s`, "picche vale 0, cuori vale 1..."); Appunti Unità 2, par. 2.18 e 2.18.6 (enum nello switch).

**Testo:** dichiara `enum seme {PICCHE, CUORI, QUADRI, FIORI};` e completa `stampa_seme`. Il main legge interi fino a fine input. Per ciascuno stampa nome e colore del seme, oppure `Seme non valido: N`.
```text
Input:  1 3 0 2 7 -1
Output:
CUORI (rosso)
FIORI (nero)
PICCHE (nero)
QUADRI (rosso)
Seme non valido: 7
Seme non valido: -1
```
**File:** `es01_semi.c` · **Test:** `make test T=04 E=es01`

<details><summary>💡 Suggerimento</summary>
Nei <code>case</code> scrivi i nomi (<code>case CUORI:</code>), non i numeri: è lo scopo dell'enum. Il <code>default</code> raccoglie i valori fuori elenco. Per passare l'int letto alla funzione puoi usare un cast: <code>(enum seme)n</code>.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Dichiarazione.** `enum seme {PICCHE, CUORI, QUADRI, FIORI};` fuori dal main, così il tipo è visibile in tutto il file. Valori impliciti: 0, 1, 2, 3.
2. **Firma.** `void stampa_seme(enum seme s)`: con il tag serve la parola `enum`. Così la firma (cioè la prima riga della funzione, con tipi e parametri) dice chiaramente "qui arriva un seme", non "un intero qualsiasi".
3. **switch.** Funziona perché i valori dell'enum sono interi costanti. Ogni case finisce con `break` (cartella 03).
4. **default.** Una variabile enum può contenere qualunque intero: 7 o -1 passano senza errori. Il default è l'unica protezione.
5. **Perché leggere un int.** `scanf` non conosce gli enum: non esiste un `%` per "leggi un seme". Si legge un int e lo si converte con un cast.
6. **Il -1.** Con gcc e clang `enum seme` è senza segno, quindi -1 dentro `s` diventa 4294967295. Nella printf lo riconvertiamo con `(int)s` per rivedere -1.

Codice completo in `soluzioni/es01_semi.c`.
</details>

### es02 — typedef anno e boolean: anni bisestili  ·  Base
**Fonte:** Trascrizione 2.4 (`typedef int anno`, `typedef anno anno_bisestile`, "type definition boolean"); Appunti Unità 2, par. 2.17 e 2.18.3 (`typedef enum {FALSE, TRUE} boolean;`).

**Testo:** crea con `typedef` i tipi `anno` (basato su int) e `boolean` (enum con FALSE e TRUE). Completa `boolean e_bisestile(anno a)`. Regola: bisestile se divisibile per 4 ma non per 100, oppure se divisibile per 400. Il main stampa `A: bisestile` o `A: non bisestile` per ogni anno letto.
```text
Input:  2024 2023 1900 2000
Output:
2024: bisestile
2023: non bisestile
1900: non bisestile
2000: bisestile
```
**File:** `es02_bisestile.c` · **Test:** `make test T=04 E=es02`

<details><summary>💡 Suggerimento</summary>
Traduci la regola in una sola condizione con <code>&&</code>, <code>||</code> e <code>%</code>. Non dimenticare le parentesi intorno alla parte "divisibile per 4 e non per 100".
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **typedef.** `typedef int anno;` e `typedef enum {FALSE, TRUE} boolean;`. FALSE vale 0 e TRUE vale 1, proprio i valori che il C usa per falso e vero.
2. **La firma racconta il significato.** `boolean e_bisestile(anno a)` si legge "dato un anno, dimmi vero o falso". Con `int f(int a)` lo dovresti indovinare.
3. **La condizione.** `(a % 4 == 0 && a % 100 != 0) || a % 400 == 0`. 1900 è divisibile per 4 e per 100 ma non per 400: non bisestile. 2000 è divisibile per 400: bisestile.
4. **Usare il boolean.** Nel main `if (b)` funziona direttamente: TRUE è 1, cioè "non zero", cioè vero.
5. **Cosa NON fa typedef.** `anno a = -3;` compila senza problemi: typedef migliora la leggibilità ma non aggiunge controlli. È proprio quello che dice il prof: "io ci posso mettere dentro un numero che non è un anno".

Codice completo in `soluzioni/es02_bisestile.c`.
</details>

### es03 — Che giorno sarà tra n giorni? Aritmetica sugli enum  ·  Base
**Fonte:** Appunti Unità 2, par. 2.18.2 ("i valori enumerativi possono essere utilizzati in espressioni aritmetiche") e 2.18.6 (`enum week {Mon, Tue, Wed, Thur, Fri, Sat, Sun}`); trascrizione 2.4 (unsigned int e "overflow non segnalati").

**Testo:** con `typedef enum {LUN, MAR, MER, GIO, VEN, SAB, DOM} giorno;` (già dato) completa `stampa_giorno` (switch, senza a capo) e `avanza(g, n)`, che restituisce il giorno dopo n giorni. n può essere negativo ("n giorni fa").
```text
4 3      ->  venerdi' + 3 giorni = lunedi'
1 -10    ->  martedi' + -10 giorni = sabato
6 365    ->  domenica + 365 giorni = lunedi'
9 1      ->  Input non valido
```
**File:** `es03_giorno_futuro.c` · **Test:** `make test T=04 E=es03`

<details><summary>💡 Suggerimento</summary>
La settimana è circolare: usa <code>% 7</code>. Due trappole. (1) In C <code>-9 % 7</code> vale <code>-2</code>, non 5. (2) Rileggi in Teoria flash di che tipo è un enum senza valori negativi, e chiediti cosa succede a <code>g + n</code> se <code>n</code> è -10.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Somma e modulo.** Gli enum sono interi: venerdì (4) + 3 = 7, e 7 % 7 = 0 = lunedì. Il `% 7` fa "girare" i giorni come le ore sull'orologio.
2. **La trappola unsigned.** Il primo tentativo naturale è `(g + n) % 7`. Con martedì (1) e n = -10 dà **mercoledì**, sbagliato. Perché? `giorno` non ha valori negativi, quindi gcc e clang lo memorizzano come `unsigned int`. In una somma tra `unsigned int` e `int`, il C converte tutto in unsigned: 1 + (-10) non dà -9 ma 4294967287. E 4294967287 % 7 = 2 = mercoledì. È esattamente l'"overflow non segnalato" dell'esempio `naturale` del prof. **Rimedio:** `(int)g + n`.
3. **Resto negativo.** `((int)g + n) % 7` = -9 % 7 = -2. In C il resto ha il segno del dividendo. Se `r < 0` aggiungo 7: -2 + 7 = 5 = sabato. Controllo: martedì meno 7 giorni è martedì, meno altri 3 è sabato.
4. **Validazione.** Nel main `partenza < LUN || partenza > DOM` usa le costanti come limiti: se un giorno cambia l'enum, il controllo resta giusto.

```c
int r = ((int)g + n) % 7;
if (r < 0)
    r += 7;
return (giorno)r;
```
Codice completo in `soluzioni/es03_giorno_futuro.c`.
</details>

### es04 — Trova e correggi l'errore: tracciamento di un pacco  ·  Intermedio
**Fonte:** Trascrizione 2.4 ("non controllano se stanno uscendo dei valori possibili per un certo enumerativo", "valori enumerativi... posso utilizzarli nei cicli"); Appunti Unità 2, par. 2.18.1 (valori espliciti) e 2.18.6 (enum nei cicli e nello switch); Appunti 2.16.2 (off-by-one).

**Testo:** `typedef enum {CREATO = 1, PAGATO, SPEDITO, CONSEGNATO} stato;`. Il programma elenca tutti gli stati, legge stato di partenza e numero di passi, e fa avanzare lo stato fermandosi a CONSEGNATO. Compila, ma ci sono **3 errori**.
```text
Input: 1 4
Output atteso:
Stati possibili: creato pagato spedito consegnato
partenza: creato
passo 1: pagato
passo 2: spedito
passo 3: consegnato
passo 4: consegnato
```
**File:** `es04_pacco.c` · **Test:** `make test T=04 E=es04`

<details><summary>💡 Suggerimento</summary>
Esegui lo starter e confronta riga per riga: una parola "incollata", uno stato mancante nell'elenco, un "sconosciuto(5)". Ogni sintomo corrisponde a un errore diverso.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output dello starter con `1 4`:
```text
Stati possibili: creato pagatospedito spedito
partenza: creato
passo 1: pagatospedito
passo 2: spedito
passo 3: consegnato
passo 4: sconosciuto(5)
```
1. **"pagatospedito" → manca un `break`.** Nello switch, `case PAGATO` stampa e poi "cade" nel `case SPEDITO` (fall-through, cartella 03). gcc lo segnala (`this statement may fall through`), clang su macOS no. Correzione: `break;` dopo `printf("pagato")`.
2. **"consegnato" manca nell'elenco → off-by-one.** `for (s = CREATO; s < CONSEGNATO; s++)` si ferma prima dell'ultimo valore. Deve essere `<=`. Il ciclo sull'enum funziona perché i valori sono interi consecutivi (1, 2, 3, 4).
3. **"sconosciuto(5)" → nessun controllo sull'ultimo stato.** `avanza` fa sempre `s + 1`, e il C accetta 5 in una variabile `stato` senza dire nulla. Correzione: `if (s == CONSEGNATO) return s;` prima della somma. È il "C controlla poco" del prof: i limiti dell'enum li deve far rispettare il programmatore.

Codice corretto in `soluzioni/es04_pacco.c`.
</details>

### es05 — Cosa stampa? Valori, segno e typedef  ·  Intermedio
**Fonte:** Trascrizione 2.4 (esempio `intero`/`naturale` con `a - 1 >= MENOUNO` e `b - 1 >= ZERO_N`, sizeof, `typedef anno anno_bisestile`); Appunti Unità 2, par. 2.18.1, 2.18.4, 2.18.6 (`enum year {Jan, ..., Dec}` nel for).

**Testo:** **non modificare il file.** Leggi `es05_cosa_stampa.c` e scrivi la tua previsione per le righe A–G. Poi esegui il test. (Ipotesi: int di 4 byte, gcc o clang.)
```text
La mia previsione:
A: ...
B: ...
C: ...
D: ...
E: ...
F: ...
G: ...
```
**File:** `es05_cosa_stampa.c` · **Test:** `make test T=04 E=es05` (passa già)

<details><summary>💡 Suggerimento</summary>
Riga A: dopo un valore esplicito si continua a contare da lì. Righe C e D: chiediti chi è <em>senza segno</em>, la variabile o la costante.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

```text
A: 0 5 6 2 3
B: 7
C: 0 1
D: 0
E: 13
F: 0 3 6 9
G: 2028 4 4
```
- **A.** `ROSSO` è il primo: 0. `VERDE = 5` esplicito. `BLU` non ha valore: precedente + 1 = 6. `GIALLO = 2` esplicito: il conteggio riparte da lì. `NERO` = 3. I valori non devono essere in ordine crescente.
- **B.** `6 - 5 + 3 * 2` = 1 + 6 = 7 (la moltiplicazione ha la precedenza). Le costanti enum sono interi a tutti gli effetti.
- **C.** `a` è di tipo `intero`, che ha un valore negativo (MENOUNO), quindi è un int con segno: `a - 1` = -2, e -2 > 1000 è falso → **0**. `b` è di tipo `naturale` (nessun valore negativo), quindi è unsigned: `b - 1` = 0 - 1 "gira" a 4294967295 → **1**. È l'esempio del prof (lui confronta con `>= ZERO_N`; qui usiamo `> 1000` perché il confronto `>= 0` su un unsigned fa scattare un warning di gcc, `comparison of unsigned expression in '>= 0' is always true`).
- **D.** Stessa sottrazione, ma su `ZERO_N`, cioè la **costante**. Per lo standard C le costanti enum sono sempre `int`: `ZERO_N - 1` = -1 → falso → **0**. Il segno dipende da *cosa* sottrai: la variabile ha il tipo dell'enum (unsigned), la costante no.
- **E.** `NERO + 10` = 13. Non esiste un colore 13, ma il C non controlla: la variabile lo contiene senza errori.
- **F.** `Jan` = 0, `Dec` = 11. Con `i += 3`: 0, 3, 6, 9; poi 12 > 11 ed esce. Gli enum si possono usare come limiti di un for.
- **G.** `anno_bisestile` → `anno` → `int`: `2024 + 4` = 2028. `sizeof(anno_bisestile)` = sizeof(int) = 4. `sizeof(enum colore)` = 4 (unsigned int). `%zu` è il segnaposto per `size_t`, il tipo restituito da sizeof.
</details>

### es06 — Contare le parole con un booleano simulato  ·  Intermedio
**Fonte:** Appunti Unità 2, par. 2.18.3 (`typedef enum {FALSE, TRUE} boolean;`, "avvicina il linguaggio C a linguaggi che possiedono tipi booleani nativi"); trascrizione 2.4 (boolean con `#define true 1`); Dispensa 2.3.2 (getchar). Combina cartella 03 e 04.

**Testo:** definisci `boolean` con typedef. Completa `e_separatore` (spazio, tab, a capo) ed `e_vocale` (a e i o u, maiuscole e minuscole, con uno switch a case raggruppati). Nel main leggi tutto con `getchar` fino a EOF e stampa numero di parole, vocali e lunghezza della parola più lunga. Una parola è una sequenza di caratteri non separatori.
```text
Input:
Il prof   dice: typedef	migliora la leggibilita

fine
Output:
parole=8 vocali=18 piu_lunga=11
```
Casi limite: input vuoto o fatto solo di spazi → `parole=0 vocali=0 piu_lunga=0`.
**File:** `es06_conta_parole.c` · **Test:** `make test T=04 E=es06`

<details><summary>💡 Suggerimento</summary>
Contare gli spazi non funziona: ce ne possono essere tanti di fila. Conta invece i <em>passaggi</em> da "fuori parola" a "dentro parola", usando una variabile <code>boolean dentro</code>.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Il flag con un tipo che parla.** `boolean dentro = FALSE;` dice chiaramente che la variabile può valere solo vero o falso. Con `int dentro = 0;` funzionerebbe uguale, ma è meno chiaro.
2. **Le funzioni restituiscono boolean.** `return c == ' ' || c == '\t' || c == '\n';` restituisce già 0 o 1, cioè FALSE o TRUE.
3. **La macchina a due stati.**

   | stato attuale | carattere letto | azione | nuovo stato |
   |---|---|---|---|
   | FALSE (fuori) | separatore | niente | FALSE |
   | FALSE (fuori) | altro | `parole++`, `lung = 1` | TRUE |
   | TRUE (dentro) | altro | `lung++` | TRUE |
   | TRUE (dentro) | separatore | `lung = 0` | FALSE |

   I tre spazi dopo "prof" producono tre volte la prima riga: nessuna parola in più.
4. **Vocali con case raggruppati.** `case 'a': case 'e': ... return TRUE;`: il fall-through è voluto (raggruppamento, cartella 03).
5. **piu_lunga.** Si aggiorna a ogni carattere della parola (`if (lung > piu_lunga)`), così funziona anche se il file finisce senza un separatore finale (test 4: `AEIOU` senza `\n`).

Codice completo in `soluzioni/es06_conta_parole.c`.
</details>

### es07 — Punteggio di una mano di carte  ·  Tipo esame
**Fonte:** Trascrizione 2.4 (enum dei semi; enum con valori negativi = tipo con segno; "possono essere utilizzati come indici... nei cicli"); Appunti Unità 2, par. 2.18.3 (typedef enum), 2.18.4 (tipo sottostante), 2.18.6 (enum in cicli e switch).

**Testo:** leggi carte fino a fine input nel formato `VALORE SEME` (valore 1..13; seme P, C, Q, F, maiuscolo o minuscolo). Punti: asso (1) = 11, tre = 10, re (13) = 4, regina (12) = 3, fante (11) = 2, le altre 0. Per ogni carta non valida stampa subito `Carta non valida: V S` e ignorala. Alla fine stampa una riga per seme (nell'ordine dell'enum, nome con `%-7s`), il totale e il seme con più punti (a parità vince il primo nell'ordine). Se nessuna carta è valida stampa solo `Nessuna carta valida`. Usa `typedef enum {SEME_NON_VALIDO = -1, PICCHE, CUORI, QUADRI, FIORI} seme;`.
```text
Input:  1 C / 3 c / 13 P / 7 Q / 12 f / 11 F / 1 F   (una carta per riga)
Output:
PICCHE  carte=1 punti=4
CUORI   carte=2 punti=21
QUADRI  carte=1 punti=0
FIORI   carte=3 punti=16
Totale: 41 punti in 7 carte
Seme migliore: CUORI (21 punti)
```
**File:** `es07_mano_carte.c` · **Test:** `make test T=04 E=es07`

<details><summary>💡 Suggerimento</summary>
Scomponi in tre funzioni con uno switch ciascuna: <code>seme_da_char</code>, <code>nome_seme</code>, <code>punti_carta</code>. Non avendo ancora i vettori ti servono 8 contatori (carte e punti per ogni seme). Per la tabella finale scorri l'enum con <code>for (seme s = PICCHE; s &lt;= FIORI; s++)</code> e prendi i contatori giusti con uno switch.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché `SEME_NON_VALIDO = -1`.** Serve un valore per dire "lettera sbagliata". Metterlo a -1 ha due vantaggi: PICCHE resta 0 (i valori successivi continuano da -1: 0, 1, 2, 3), e l'enum diventa **con segno**, come `intero` del prof. Così confronti e cicli non hanno sorprese da unsigned.
2. **Conversioni con switch.** `seme_da_char` usa case raggruppati (`case 'P': case 'p':`) per accettare maiuscole e minuscole. `nome_seme` restituisce il testo del nome: un enum non "sa" il proprio nome, `%d` stamperebbe solo il numero.
3. **Lettura.** `while (scanf("%d %c", &v, &ch) == 2)`: si esce a fine input o se il formato non torna. Lo spazio prima di `%c` salta l'a capo. Le carte non valide si scartano con `continue`.
4. **Smistamento.** Uno switch su `s` incrementa la coppia di contatori giusta. Con i vettori (lezione 2.5) diventerà `carte[s]++`: è il senso di "gli enum possono essere usati come indici".
5. **Tabella e massimo.** Il for scorre PICCHE..FIORI. `migliore` si aggiorna solo con `>` (non `>=`), quindi a parità resta il primo seme (test 3: tutti a 0 → PICCHE).
6. **Caso vuoto.** Se `valide == 0` si stampa solo il messaggio: niente tabella e niente seme migliore.

| carta | seme | punti | punti per seme P/C/Q/F |
|---|---|---|---|
| 1 C | CUORI | 11 | 0/11/0/0 |
| 3 c | CUORI | 10 | 0/21/0/0 |
| 13 P | PICCHE | 4 | 4/21/0/0 |
| 7 Q | QUADRI | 0 | 4/21/0/0 |
| 12 f | FIORI | 3 | 4/21/0/3 |
| 11 F | FIORI | 2 | 4/21/0/5 |
| 1 F | FIORI | 11 | 4/21/0/16 |

Codice completo in `soluzioni/es07_mano_carte.c`.
</details>

## Prompt pronti per questo argomento

1. «Interrogami con 5 domande su enum e typedef (valori impliciti/espliciti, tag contro typedef, enum con e senza segno, collisione di nomi), **una alla volta**. Aspetta la mia risposta e correggimi spiegando il perché.»
2. «Scrivimi 3 piccoli programmi "Cosa stampa?" con enum a valori espliciti e aritmetica su variabili enum con e senza segno. Io scrivo la previsione, tu mi spieghi riga per riga.»
3. «Ho scritto questa soluzione per es07 di 04-enum-typedef: [incolla codice]. Dimmi se è corretta e se uso bene enum e typedef, senza riscrivermela tutta.»
4. «Mostrami 4 dichiarazioni di enum/typedef, alcune giuste e alcune che non compilano (tag senza enum, nome duplicato, enum anonimo usato come tipo). Per ognuna chiedimi se compila e perché.»
5. «Generami 2 esercizi nuovi tipo es04 (trova l'errore) su un enum usato come macchina a stati, con l'output atteso, senza soluzione.»

## Riepilogo
- `typedef tipo_esistente nuovo_nome;` dà un nome più chiaro a un tipo, ma non aggiunge controlli: `anno` resta un int.
- `enum` elenca valori con un nome; senza indicazioni partono da 0 e crescono di 1, con `=` si fissano a mano. Sono interi: si usano in switch, for e calcoli, ma il C non impedisce valori fuori elenco.
- Tre forme: enum anonimo, enum con tag (sempre `enum nome`), `typedef enum {...} nome;` (la più comoda). Il booleano del corso è `typedef enum {FALSE, TRUE} boolean;`.
- Con gcc e clang un enum senza valori negativi è una variabile `unsigned int`: sottrarre o sommare negativi può "girare" a numeri enormi. Le costanti, invece, sono sempre int.

## Glossario
- **typedef** — dà un nuovo nome a un tipo esistente.
- **enum (tipo enumerativo)** — tipo con un elenco finito di valori con un nome, rappresentati da interi.
- **costante enumerativa** — uno dei nomi dell'elenco (es. `CUORI`); è un int costante, non modificabile.
- **tag** — il nome dato a un enum (`enum seme`), da usare sempre insieme alla parola `enum`.
- **enum anonimo** — enum senza tag né typedef: si possono dichiarare variabili solo insieme alla definizione.
- **booleano simulato** — tipo vero/falso costruito con `#define` o con `typedef enum {FALSE, TRUE} boolean`.
- **stdbool.h** — file standard (dal C99) che fornisce `bool`, `true`, `false`.
- **unsigned int** — intero senza segno: solo valori ≥ 0; sotto lo 0 "gira" al valore massimo.
- **overflow** — risultato che non sta nel tipo e "gira" dall'altra parte.
- **sizeof** — operatore che dice quanti byte occupa un tipo o un'espressione.
- **size_t** — tipo intero senza segno restituito da sizeof, si stampa con `%zu`.
- **scope** — zona del programma in cui un nome è visibile (un blocco o tutto il file).
- **tabella dei simboli** — elenco interno del compilatore con tutti i nomi dichiarati e i loro tipi.
- **cast** — conversione esplicita di tipo, es. `(int)g`, `(enum seme)n`.
- **fall-through** — in uno switch senza break, l'esecuzione prosegue nel case successivo.
