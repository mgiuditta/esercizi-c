# 01 — Primo programma in C, compilazione e goto

> Lezioni di riferimento: trascrizioni 2.0, 2.1 e 2.1 E-tivity, Dispensa 2.2.2 "Primi programmi in C", Appunti Unità 2 (cap. 1: §1.3–1.6, 1.7.3, 1.11, 1.19, 1.20.1; §2.2 su scanf), LEZ 07.
> Tempo stimato: ~3 ore.

## Teoria flash

**Programma sorgente.** Un programma C è un file di testo con estensione `.c` (il *sorgente*, cioè il testo che scrivi tu). Il computer non lo capisce così com'è: va tradotto in *linguaggio macchina* (le istruzioni numeriche che il processore esegue davvero).

**Compilazione = traduzione in tre fasi.** Pensa a un libro da tradurre e poi rilegare.
1. **Preprocessore**: esegue le righe che iniziano con `#` (le *direttive*). `#include <stdio.h>` copia dentro il tuo file il contenuto di `stdio.h`, un *file di intestazione* (header) che descrive funzioni già scritte da altri, come `printf`. Toglie anche i commenti. Puoi vedere il risultato con `cc -E es01_mcd_goto.c`.
2. **Compilatore**: controlla la grammatica (es. il `;` alla fine di ogni istruzione) e traduce in *codice oggetto* (linguaggio macchina non ancora completo).
3. **Linker** (il "collegatore"): unisce il tuo codice oggetto con il codice delle *librerie* (raccolte di funzioni già pronte, es. quella che contiene `printf`) e produce l'*eseguibile*, cioè il file che puoi lanciare.

```sh
cc -std=c11 -Wall -Wextra -pedantic es01_mcd_goto.c -o es01   # compila
./es01                                                        # esegue
```
`cc` è il nome generico del compilatore C. Su macOS `cc` (e anche `gcc`) è in realtà **clang**; su Linux di solito è **gcc**. `-o es01` dice il nome dell'eseguibile. `-Wall -Wextra` accendono gli *avvisi* (warning: il programma compila, ma il compilatore sospetta un errore). Leggili sempre. In questa repo non scrivi questi comandi a mano: `make test T=01 E=es01` compila ed esegue i test per te.

**Struttura minima.**
```c
#include <stdio.h>          /* direttiva: niente ';' perche' non e' un'istruzione C */

int main(void)              /* main = punto di partenza. int = restituisce un intero */
{                           /* { } = blocco: le istruzioni che fanno parte di main  */
    int x = 0;              /* dichiarazione: tipo + nome (+ valore iniziale)       */
    printf("x = %d\n", x);  /* ogni istruzione finisce con ';'                      */
    return 0;               /* 0 = "tutto bene", lo legge il sistema operativo      */
}
```
- **Variabile**: una "scatola" in memoria con un nome e un **tipo**. Il tipo dice quanto è grande la scatola e cosa ci puoi mettere: `int` per gli interi (qui 4 byte = 32 bit), `float`/`double` per i numeri con la virgola. In C ogni variabile va **dichiarata** prima di usarla.
- **`=` è assegnamento**, non uguaglianza: `x = y` copia il valore di `y` dentro `x`. Il confronto è `==`.
- **`printf`** stampa. Dentro la stringa, `%d` è un *segnaposto* (un buco da riempire) per un `int`, `%f` per un `double`, `%.2f` con 2 decimali; `\n` va a capo; `%%` stampa il carattere `%`.
- **`scanf("%d", &x)`** legge un intero dalla tastiera e lo mette in `x`. La `&` significa "indirizzo di": a `scanf` devi dire **dove** scrivere, non quanto vale ora `x`. Restituisce quanti valori è riuscita a leggere: `if (scanf("%d", &x) != 1)` scopre un input sbagliato o finito.
- **Vero/falso in C**: 0 è falso, qualsiasi altro numero è vero. `if (cond) istruzione; else altra;` — con più istruzioni servono le graffe.
- **Divisione**: tra due `int`, `/` è la divisione intera (`7 / 2` fa `3`), e `%` è il resto (`7 % 2` fa `1`). Basta un operando reale per avere la divisione reale (`7 / 2.0` fa `3.5`).

**goto ed etichette.** Un'*etichetta* è un nome seguito da due punti, messo davanti a un'istruzione: `modulo:`. L'istruzione `goto modulo;` fa saltare l'esecuzione lì. È la traduzione diretta del "goto 3" dello pseudocodice del blocco 1. Il prof (E-tivity 2.1): invece di numerare ogni riga, "metto delle etichette nelle posizioni in cui voglio saltare".
```c
modulo:
    r = x % y;
    if (r == 0) goto risultato;   /* salto condizionato: if + goto   */
    x = y;
    y = r;
    goto modulo;                  /* salto incondizionato: torna su  */
risultato:
    printf("L'MCD e' %d\n", y);
```
**Teorema di Böhm-Jacopini** (blocco 1): ogni programma con i salti si può riscrivere usando solo *sequenza*, *selezione* (`if`) e *iterazione* (un ciclo, es. `while`). `while (cond) { ... }` ripete il blocco finché `cond` è vera, e controlla la condizione **prima** di ogni giro. Il `goto` è *sconsigliato* (rende il flusso difficile da seguire, il cosiddetto "codice spaghetti"), ma esiste ancora: il prof spiega che serve per efficienza e per la vicinanza del C alla macchina. In questa cartella lo usi apposta, per allenarti a tradurre lo pseudocodice; poi riscrivi con `while`.

**Imprecisioni e contraddizioni nelle fonti (leggile!).**
- Le trascrizioni sono automatiche: "Gotu", "gotoo", "Couture" = `goto`; "scan f per 100d e commerciale x" = `scanf("%d", &x)`; "l'mcde per cento di" = `"L'MCD e' %d"`; "den" = `then`; "ben mio copini" = Böhm-Jacopini; "strenga" = stringa.
- **Fasi di compilazione**: la dispensa 2.2.2 parla di *due* fasi (pre-compilazione e compilazione); la trascrizione 2.1 e gli Appunti (§1.4) di *tre* (preprocessore, compilatore, linker). Vale la versione a tre: la dispensa semplifica, includendo il linker nella "compilazione".
- **Dimensioni dei tipi**: la dispensa dice `int` = 16 bit e `double` = "32 bit precisione doppia". Oggi, su macOS (Apple Silicon) e Linux a 64 bit, `int` è 32 bit (4 byte) e `double` è 64 bit (8 byte). Il 16 bit era vero su macchine vecchie; il "32" del double è un refuso. Gli Appunti (§1.7.3) dicono solo che "la dimensione dipende dall'architettura": è la frase corretta.
- **Esempio di overflow**: la dispensa scrive `int a=8; a=a+1` con interi a 3 bit, ma con 3 bit il massimo è 7 (111): 8 non ci sta già. La trascrizione 2.1 usa correttamente 7 (7 + 1 = 8 non rappresentabile).
- **Versione del C**: gli Appunti (§1.2) dicono che il corso usa l'ANSI C (C89). La repo compila con `-std=c11` (standard del 2011): tutto ciò che usi qui funziona in entrambi, ma i commenti `//` (che anche la dispensa usa) e le dichiarazioni a metà blocco non erano ammessi in C89.
- **`main`**: la dispensa usa `int main(int argc, char *argv[])`, altri esempi `int main()`. Il prof stesso dice che "poteva essere buono anche un main senza argc argv". Qui usiamo `int main(void)` (il `void` dice esplicitamente "nessun parametro") per evitare avvisi su parametri inutilizzati.
- **goto "deprecato"**: la trascrizione dice prima "deprecato" poi "non dico deprecato però sconsigliato". Lo standard C non l'ha mai deprecato (cioè dichiarato "da eliminare"): è solo sconsigliato.
- **Trattino nella dispensa**: nel PDF `gcc programma.c –o eseguibile` ha un trattino lungo (–) al posto del meno (-). Se lo copi e incolli, il compilatore non lo riconosce: riscrivi `-o` a mano.

**Gli esercizi non stampano messaggi tipo "Inserisci x:"** (che il prof invece usa): il test confronta l'output parola per parola, e quei messaggi lo sporcherebbero.

### Errori tipici
1. **`;` dimenticato** → errore, niente eseguibile. clang: `error: expected ';' at end of declaration` (gcc: `error: expected ',' or ';' before 'printf'`, che segnala la riga *dopo*).
2. **`scanf` senza `&`** → compila, ma con avviso: `warning: format specifies type 'int *' but the argument has type 'int' [-Wformat]`. Eseguendo, il programma va in *crash* (si interrompe con errore), perché scanf scrive in un indirizzo a caso.
3. **`=` al posto di `==` nell'if** (`if (r = 0)`) → avviso `warning: using the result of an assignment as a condition without parentheses [-Wparentheses]`, con il suggerimento `use '==' to turn this assignment into an equality comparison`. L'if assegna 0 a `r` e la condizione è sempre falsa.
4. **Etichetta sbagliata** (`goto fien;`) → `error: use of undeclared label 'fien'` (gcc: `label 'fien' used but not defined`).
5. **Etichetta seguita da una dichiarazione** (`fine: int y = x;`) → in C11 un'etichetta deve stare davanti a un'*istruzione*, e una dichiarazione non lo è. clang: `warning: label followed by a declaration is a C23 extension`; gcc: `a label can only be part of a statement and a declaration is not a statement`. Rimedio: dichiara le variabili all'inizio del blocco, come consiglia il prof.
6. **`#include <stdio.h>` dimenticato** → clang: `error: call to undeclared library function 'printf' ...` con la nota `include the header <stdio.h>`.

## Esercizi

### es01 — MCD con goto  ·  Base
**Fonte:** Ispirato a: Trascrizione 2.1 E-tivity (traduzione in C dell'MCD con goto ed etichette `modulo` e `risultato`).
**Testo:** completa `mcd_goto(x, y)` traducendo "pari pari" lo pseudocodice del prof (righe 3–8) con `if`, `goto` e due etichette. Il `main` legge `x y` e stampa il risultato.
```text
1 read x   2 read y   3 r = x mod y   4 if r = 0 then goto 8
5 x = y    6 y = r    7 goto 3        8 write y

input:  48 18
output: MCD(48, 18) = 6
```
**File:** `es01_mcd_goto.c` · **Test:** `make test T=01 E=es01`

<details><summary>💡 Suggerimento</summary>
Ti servono solo due etichette: una dove si torna (la riga 3) e una dove si salta per finire (la riga 8). "mod" in C si scrive <code>%</code>, e nel confronto servono due uguali.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Dove servono le etichette?** Lo pseudocodice salta a due righe: la 3 (da `goto 3`) e la 8 (da `goto 8`). Quindi due etichette: `modulo:` davanti a `r = x % y;` e `risultato:` davanti al `return`.
2. **Riga 4.** `if r = 0 then goto 8` diventa `if (r == 0) goto risultato;`. Con un solo `=` assegneresti 0 a `r` e la condizione sarebbe sempre falsa (ciclo infinito o risultato sbagliato).
3. **Righe 5–7.** Restano identiche, con il `;`: `x = y; y = r; goto modulo;`.
4. **Riga 8.** Invece di stampare, la funzione *restituisce* `y` con `return`. La stampa la fa il `main`: così la funzione si può testare e riusare.

```c
modulo:
    r = x % y;
    if (r == 0) goto risultato;
    x = y;
    y = r;
    goto modulo;
risultato:
    return y;
```
Simulazione con `x = 48, y = 18`:

| giro | x | y | r = x % y | r == 0? |
|---|---|---|---|---|
| 1 | 48 | 18 | 12 | no → x=18, y=12 |
| 2 | 18 | 12 | 6 | no → x=12, y=6 |
| 3 | 12 | 6 | 0 | sì → return 6 |

Nota: il prof "assume x maggiore di y senza verificarlo". Il test `5 15` mostra che funziona anche se x < y: al primo giro `5 % 15 = 5` e i due numeri si scambiano. Con `y = 0` invece `x % 0` è una divisione per zero: crash. Lo risolve es02. Codice completo: `soluzioni/es01_mcd_goto.c`.
</details>

### es02 — MCD senza goto, con while  ·  Base
**Fonte:** Ispirato a: Trascrizione 2.1 E-tivity ("vedremo più avanti come fare a ripetere gli stessi flussi senza utilizzare il costrutto del salto incondizionato") + teorema di Böhm-Jacopini citato nella trascrizione 2.1.
**Testo:** riscrivi l'MCD in `mcd_while(x, y)` usando un `while` e nessun `goto`. Deve funzionare anche con `y = 0` (MCD(x, 0) = x).
```text
input:  7 0
output: MCD(7, 0) = 7
```
**File:** `es02_mcd_while.c` · **Test:** `make test T=01 E=es02`

<details><summary>💡 Suggerimento</summary>
Chiediti: "quando devo continuare?" invece di "quando devo saltare via?". Se il while controlla <code>y</code> prima di fare il <code>%</code>, la divisione per zero non può succedere.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Rovescio la condizione.** Nel goto: "se il resto è 0, esci". Nel while: "finché c'è ancora un divisore diverso da 0, continua": `while (y != 0)`.
2. **Il corpo del ciclo** sono le righe 3, 5, 6: `r = x % y; x = y; y = r;`. La riga 7 (`goto 3`) sparisce: il ritorno all'inizio lo fa il `while` da solo.
3. **Dove sta il risultato?** Ho spostato il controllo di un passo: quando esco `y` vale 0, e l'ultimo divisore utile è stato appena copiato in `x`. Quindi `return x;`.
4. **Perché `y = 0` ora va bene?** Il `while` controlla *prima* di entrare: con `y = 0` non entra mai e restituisce `x`. La versione con goto calcolava `x % y` *prima* di qualsiasi controllo.

```c
while (y != 0) {
    r = x % y;
    x = y;
    y = r;
}
return x;
```
Simulazione con `18 48`: giro 1: r = 18 % 48 = 18, x = 48, y = 18; giro 2: r = 12, x = 18, y = 12; giro 3: r = 6, x = 12, y = 6; giro 4: r = 0, x = 6, y = 0 → esco, restituisco 6. Codice: `soluzioni/es02_mcd_while.c`.
</details>

### es03 — Somma dei primi N numeri con goto  ·  Base
**Fonte:** Ispirato a: Appunti Unità 2, §2.15.1 "Esempio: somma dei primi numeri naturali", tradotto con goto come nell'E-tivity 2.1.
**Testo:** completa `somma_primi_goto(n)` che restituisce 1 + 2 + … + n (0 se n ≤ 0), traducendo lo pseudocodice con goto.
```text
1 s = 0   2 i = 1   3 if i > n then goto 7   4 s = s + i
5 i = i + 1   6 goto 3   7 write s

input:  5
output: Somma da 1 a 5 = 15
```
**File:** `es03_somma_goto.c` · **Test:** `make test T=01 E=es03`

<details><summary>💡 Suggerimento</summary>
Le righe 1 e 2 sono già nelle dichiarazioni. L'etichetta del controllo va davanti all'<code>if</code>, perché il <code>goto 3</code> deve rifare il controllo a ogni giro.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. Righe 1–2: `int s = 0; int i = 1;`. `s` parte da 0 perché sommare 0 non cambia nulla (0 è l'*elemento neutro* della somma).
2. Riga 3 con etichetta: `controllo: if (i > n) goto fine;`.
3. Righe 4–6: `s = s + i; i = i + 1; goto controllo;`.
4. Riga 7: `fine: return s;`.
5. **Caso limite** `n = 0` (o negativo): `1 > 0` è vero al primo controllo, si salta subito a `fine` e la somma resta 0. Nessun caso speciale da scrivere: il controllo *prima* della somma lo gestisce da solo.

Simulazione `n = 3`:

| i | i > n? | s dopo |
|---|---|---|
| 1 | no | 1 |
| 2 | no | 3 |
| 3 | no | 6 |
| 4 | sì → fine | 6 |

Gli Appunti chiamano *invariante* una frase vera a ogni passaggio dal controllo: qui "s = 1 + … + (i − 1)". Codice: `soluzioni/es03_somma_goto.c`.
</details>

### es04 — Massimo di numeri letti fino a 0, con goto  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 2.1 E-tivity (tradurre flussi con salti in C) + Dispensa 2.2.2 (uso di `scanf`); il "tappo" 0 è il classico schema di lettura del blocco 1.
**Testo:** leggi interi finché arriva 0 (che non conta). Stampa quanti numeri hai letto e il massimo, oppure `Nessun numero inserito`. Se l'input finisce senza lo 0, fermati lo stesso. Solo `if` e `goto`.
```text
input:  3 9 -2 7 0
output: Numeri letti: 4, massimo = 9

input:  -5 -2 -9 0
output: Numeri letti: 3, massimo = -2
```
**File:** `es04_massimo_goto.c` · **Test:** `make test T=01 E=es04`

<details><summary>💡 Suggerimento</summary>
Non partire da <code>massimo = 0</code>: con tutti numeri negativi stamperesti 0, che non è nemmeno tra i dati. Il primo numero letto è il miglior "massimo provvisorio".
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Primo numero a parte.** Lo leggo; se la lettura fallisce o vale 0 → `goto fine` (contati resta 0 e stampo "Nessun numero"). Altrimenti `massimo = x; contati = 1;`.
2. **Il ciclo con etichetta `leggi:`**: leggo il prossimo; se `scanf` non restituisce 1 (input finito) o `x == 0` → `goto fine`.
3. Altrimenti lo conto e, se è più grande del massimo, aggiorno: `if (x > massimo) massimo = x;`. Poi `goto leggi;`.
4. **Perché controllare `scanf(...) != 1`?** Se l'input finisce senza 0, `scanf` non legge nulla e lascia `x` com'era: senza il controllo rileggeresti all'infinito lo stesso numero.

Simulazione `-5 -2 -9 0`: primo: massimo = −5, contati = 1; −2 > −5 → massimo = −2, contati = 2; −9 no, contati = 3; 0 → fine. Codice: `soluzioni/es04_massimo_goto.c`.
</details>

### es05 — Trova e correggi l'errore: media e distanza  ·  Intermedio
**Fonte:** Ispirato a: Dispensa 2.2.2 (esempio del valore assoluto `if (numero < 0) numero = -numero;` e nota su `&` in scanf) + Trascrizione 2.1 (divisione intera tra `int` anche se il risultato va in un `float`).
**Testo:** il programma legge `a b` e dovrebbe stampare la media con 2 decimali e la distanza |a − b|. Compila (con avvisi) ma ha **3 errori**. Correggili senza riscriverlo.
```text
input:  7 2
output: Media = 4.50
        Distanza = 5
```
**File:** `es05_trova_errore.c` · **Test:** `make test T=01 E=es05`

<details><summary>💡 Suggerimento</summary>
Parti dagli avvisi del compilatore: due errori su tre sono segnalati lì. Il terzo è sulla media: chiediti di che tipo sono i due operandi della divisione.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **`scanf("%d", b)` → `scanf("%d", &b)`.** Avviso: `format specifies type 'int *' but the argument has type 'int'`. `int *` significa "indirizzo di un int". Senza `&` passi il *valore* di `b` (0) e scanf prova a scrivere all'indirizzo 0: il programma va in crash (nel test: `CRASH`).
2. **`(a + b) / 2` → `(a + b) / 2.0`.** Il prof (trascrizione 2.1): "l'operatore guarda gli operandi", non dove va il risultato. `a + b` e `2` sono `int` → divisione intera: 9 / 2 = 4, e solo *dopo* 4 diventa 4.00. Con `2.0` (un `double`) l'intero viene *promosso* (convertito automaticamente) a double e la divisione è reale: 4.5.
3. **`if (distanza < 0);` → togli il `;`.** Avviso: `if statement has empty body` (corpo vuoto). Quel `;` è un'istruzione vuota che fa da ramo "then"; la riga sotto, anche se indentata, viene eseguita sempre. Con `7 2`: distanza = 5, poi diventa −5. Con `3 8` invece funzionava per caso (−5 → 5): per questo servono più casi di test.

Codice: `soluzioni/es05_trova_errore.c`.
</details>

### es06 — Cosa stampa? (goto)  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 2.1 (goto, etichette, operatore `%` definito solo tra interi, divisione intera).
**Testo:** senza eseguirlo, scrivi qui sotto l'output del programma `es06_cosa_stampa_goto.c`, riga per riga. Poi esegui il test e confronta.
```text
La mia previsione:
...
```
**File:** `es06_cosa_stampa_goto.c` · **Test:** `make test T=01 E=es06` (passa già: serve a verificare la previsione)

<details><summary>💡 Suggerimento</summary>
Fai una tabella con le colonne i, s e "cosa succede". Attenzione: <code>i</code> cresce di 2, e quando si salta a <code>salta:</code> la <code>printf</code> non viene eseguita.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output:
```text
i = 1, s = 1
i = 5, s = 6
i = 7, s = 13
Fine: i = 11, s = 13, s / 3 = 4
```
| i | i > 10? | i % 3 == 0? | azione | s |
|---|---|---|---|---|
| 1 | no | no (1) | somma e stampa | 1 |
| 3 | no | **sì** (0) | `goto salta`: niente somma, niente stampa | 1 |
| 5 | no | no (2) | somma e stampa | 6 |
| 7 | no | no (1) | somma e stampa | 13 |
| 9 | no | **sì** | salta | 13 |
| 11 | **sì** | — | `goto fine` | 13 |

1. Dopo `salta:` si arriva in due modi: col salto (i multiplo di 3) o *proseguendo in sequenza* dopo la `printf`. Un'etichetta non blocca chi ci arriva da sopra: è solo un "segnalibro".
2. In `fine`, `s / 3` è `13 / 3` tra interi: fa 4, non 4.33.
3. Il ciclo si chiude perché `i` supera 10. Il valore stampato è 11 (l'ultimo `i` controllato), non 9.
</details>

### es07 — Divisione intera per sottrazioni successive  ·  Tipo esame
**Fonte:** Ispirato a: Trascrizione 2.1 (operatori `/` e `%` tra interi; goto; Böhm-Jacopini) + E-tivity 2.1 (traduzione pseudocodice → C). Algoritmo in stile blocco 1.
**Testo:** scrivi `quoziente_goto(a, b)` (con goto) e `resto_while(a, b)` (con while), senza usare `/` e `%`: togli `b` da `a` finché puoi. Il `main` controlla i tuoi risultati con `/` e `%`. Con `a < 0` o `b <= 0` stampa `Input non valido`.
```text
1 read a   2 read b   3 q = 0   4 if a < b then goto 8
5 a = a - b   6 q = q + 1   7 goto 4   8 write q, a

input:  17 5
output: 17 = 5 * 3 + 2
        Controllo con / e %: OK
```
**File:** `es07_divisione_sottrazioni.c` · **Test:** `make test T=01 E=es07`

<details><summary>💡 Suggerimento</summary>
Le due funzioni fanno lo stesso ciclo: una conta i giri (il quoziente), l'altra restituisce quello che avanza (il resto). Nel while la condizione è il contrario di quella del goto.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **`quoziente_goto`**: etichetta `controllo:` sulla riga 4: `if (a < b) goto fine;`, poi `a = a - b; q = q + 1; goto controllo;` e `fine: return q;`.
2. **Posso modificare `a` dentro la funzione?** Sì. La funzione riceve una *copia* dei valori (in C i parametri sono copie): il `main` vede ancora il suo `a` originale. Infatti stampa `17 = ...`, non `2 = ...`.
3. **`resto_while`**: "se a < b esci" diventa "finché a ≥ b resta dentro": `while (a >= b) a = a - b; return a;`.
4. **Casi limite.** `4 9`: 4 < 9 subito → q = 0, resto 4. `0 7` → q = 0, resto 0. `5 0`: con b = 0, `a - 0` non diminuirebbe mai → ciclo infinito; per questo il `main` rifiuta `b <= 0` *prima* di chiamare le funzioni.
5. **Il controllo nel main** usa `&&`: stampa OK solo se *entrambi* i confronti sono veri. `%%` in printf stampa un `%`.

Simulazione `17 5`: a = 17 → 12 (q = 1) → 7 (q = 2) → 2 (q = 3); 2 < 5 → stop. Quoziente 3, resto 2: 17 = 5 · 3 + 2. Codice: `soluzioni/es07_divisione_sottrazioni.c`.
</details>

### es08 — Numeri primi fino a N  ·  Tipo esame
**Fonte:** Ispirato a: E-tivity 2.1 (traduzione con goto di un algoritmo in pseudocodice) + Trascrizione 2.1 (in C "vero" è un numero ≠ 0, "falso" è 0; `%` tra interi).
**Testo:** scrivi `e_primo(n)` con goto (restituisce 1 se n è primo, 0 altrimenti) e `conta_primi(n)` con while (quanti primi tra 2 e n). Il `main` stampa lista e totale.
```text
1 if n < 2 then goto 8   2 d = 2   3 if d * d > n then goto 7
4 if n mod d = 0 then goto 8   5 d = d + 1   6 goto 3
7 return 1   8 return 0

input:  30
output: Primi fino a 30: 2 3 5 7 11 13 17 19 23 29
        Totale: 10
```
**File:** `es08_primi_goto.c` · **Test:** `make test T=01 E=es08`

<details><summary>💡 Suggerimento</summary>
Tre etichette: <code>prova</code> (riga 3), <code>si</code> (riga 7), <code>no</code> (riga 8). Per <code>conta_primi</code> guarda come il <code>main</code> scorre i numeri da 2 a n: ti serve lo stesso ciclo, ma invece di stampare conti.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Riga 1**: 0, 1 e i negativi non sono primi per definizione → `if (n < 2) goto no;`.
2. **Perché `d * d > n`?** Se n = d · e e entrambi i fattori fossero più grandi della radice di n, il prodotto supererebbe n. Quindi almeno un divisore è ≤ radice di n: basta provare fino lì. Scrivere `d * d > n` evita di calcolare la radice (che richiederebbe numeri reali). Per 97 provo d = 2…9 invece che 2…96.
3. **Riga 4**: `n % d == 0` vuol dire "d divide n esattamente" → non primo.
4. **`return 1` / `return 0`**: il prof ricorda che in C vero e falso sono numeri. Così il `main` può scrivere `if (e_primo(k))`.
5. **`conta_primi`**: `k` da 2 a n con `while (k <= n)`; se `e_primo(k)` vale 1 incremento `conta`. Con n = 1 il while non parte e restituisce 0.

Simulazione `e_primo(9)`: 9 ≥ 2; d = 2: 4 > 9? no; 9 % 2 = 1 → d = 3: 9 > 9? no; 9 % 3 = 0 → `goto no` → 0. `e_primo(7)`: d = 2: 7 % 2 = 1 → d = 3: 9 > 7 → `goto si` → 1. Codice: `soluzioni/es08_primi_goto.c`.
</details>

## Prompt pronti per questo argomento
1. "Interrogami con 5 domande, una alla volta, su: fasi della compilazione (preprocessore, compilatore, linker), ruolo di `#include`, `main` e `return 0`, `&` nella scanf. Aspetta la mia risposta prima di passare alla successiva e correggimi spiegando il perché."
2. "Ti do uno pseudocodice con i salti (stile blocco 1 del corso di Anisetti): [incolla]. Non darmi la soluzione: guidami a tradurlo in C con goto ed etichette, poi a riscriverlo con while, facendomi una domanda per volta."
3. "Ho scritto questa soluzione per es04 di 01-primo-programma-goto: [incolla codice]. Dimmi se è corretta e perché, quali casi limite potrebbero romperla, senza riscrivermela tutta."
4. "Generami 3 esercizi nuovi tipo es07 di 01-primo-programma-goto: un algoritmo in pseudocodice con goto da tradurre in C e poi riscrivere con while. Dammi input/output di esempio ma non le soluzioni."
5. "Scrivimi un programma C di 15 righe con goto ed etichette e chiedimi cosa stampa. Poi correggi la mia risposta con una tabella dei valori delle variabili."

## Riepilogo
- Un programma C passa da preprocessore (direttive `#`), compilatore (controllo grammatica e traduzione) e linker (unione con le librerie) prima di diventare un eseguibile; su macOS `cc` è clang.
- Ogni variabile ha un tipo e va dichiarata; `printf` stampa con i segnaposto, `scanf` legge e vuole l'indirizzo (`&`) della variabile.
- `goto etichetta;` traduce i salti dello pseudocodice; per Böhm-Jacopini lo stesso flusso si scrive con `if` e `while`, che controlla la condizione prima di ogni giro.
- Tra due `int`, `/` è divisione intera e `%` il resto: il tipo degli operandi decide l'operazione, non il tipo della variabile che riceve il risultato.

## Glossario
- **sorgente** — il file di testo `.c` che scrivi tu.
- **preprocessore** — prima fase della compilazione: esegue le direttive `#` (es. copia gli header) e toglie i commenti.
- **direttiva** — riga che inizia con `#`, letta dal preprocessore; non finisce con `;`.
- **header (file di intestazione)** — file `.h` che descrive funzioni di libreria, es. `stdio.h` per `printf`/`scanf`.
- **compilatore** — programma che controlla la grammatica del C e traduce in codice oggetto.
- **codice oggetto** — traduzione in linguaggio macchina di un singolo sorgente, non ancora eseguibile.
- **linker** — unisce codice oggetto e librerie in un unico eseguibile.
- **libreria** — raccolta di funzioni già scritte da altri, pronte da usare.
- **eseguibile** — il file finale che lanci con `./nome`.
- **clang / gcc** — due compilatori C; `cc` è clang su macOS e di solito gcc su Linux.
- **warning (avviso)** — messaggio del compilatore su un probabile errore; il programma compila lo stesso.
- **main** — funzione da cui parte l'esecuzione; il suo `return 0` dice al sistema "tutto bene".
- **blocco** — gruppo di istruzioni tra `{ }`.
- **variabile** — spazio di memoria con nome e tipo, il cui valore può cambiare.
- **tipo** — dice quanti byte occupa un valore, come è codificato e quali operazioni ammette (`int`, `float`, `double`).
- **dichiarazione** — riga che crea una variabile: tipo + nome (+ valore iniziale).
- **assegnamento (`=`)** — copia il valore a destra nella variabile a sinistra.
- **segnaposto** — `%d`, `%f`... dentro printf/scanf: indica dove e come stampare/leggere un valore.
- **`&` (indirizzo di)** — dà la posizione in memoria di una variabile; serve a scanf per sapere dove scrivere.
- **etichetta** — nome seguito da `:` davanti a un'istruzione, destinazione di un goto.
- **goto** — salto incondizionato all'etichetta indicata.
- **teorema di Böhm-Jacopini** — ogni programma si può scrivere con sola sequenza, selezione e iterazione, senza goto.
- **while** — ciclo che ripete un blocco finché la condizione è vera, controllandola prima di ogni giro.
- **divisione intera** — `/` tra due interi: tronca la parte decimale (`7 / 2` = 3).
- **modulo (`%`)** — resto della divisione intera, solo tra interi (`7 % 2` = 1).
- **promozione** — conversione automatica di un tipo "più piccolo" in uno più grande (es. int → double) per fare un'operazione.
- **overflow** — risultato troppo grande per i bit del tipo.
- **crash** — interruzione improvvisa del programma per un errore durante l'esecuzione.
- **invariante** — frase sulle variabili vera a ogni passaggio di un ciclo.
