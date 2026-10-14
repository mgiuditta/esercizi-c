# 05 — Gestione della memoria e vettori

> Lezioni di riferimento: trascrizione 2.5 (Introduzione alla gestione della memoria e vettori), Appunti di fine Unità 2 (capitolo 3 "Memoria e vettori nel linguaggio C", paragrafi 3.1–3.13), LEZ 11.
> Tempo stimato: ~4 ore.

## Teoria flash

**La memoria è una fila di celle.** Il prof la paragona al nastro della macchina di Turing, ma finito. Ogni **cella** contiene 8 bit, cioè un **byte** (l'unità minima di memoria, abbastanza per un carattere). Ogni cella ha un **indirizzo**: un numero che la identifica, come il numero civico di una casa. Il contenuto (i bit) è come gli abitanti della casa: l'indirizzo dice *dove*, il contenuto dice *cosa*.

**Allocazione.** Quando dichiari `int a = 10;` il compilatore (il programma che traduce il tuo C in linguaggio macchina) **alloca** la variabile: le riserva abbastanza celle consecutive. Un `int` qui occupa 4 byte (`sizeof(int)` = 4 su macOS arm64 e Linux x86-64; nelle slide il prof usa 2 byte per semplicità). Per leggere una variabile servono due informazioni: l'indirizzo della prima cella e quante celle occupa (lo dice il tipo).

**L'operatore `&`** (si legge "e commerciale"; nelle trascrizioni automatiche diventa "e-commerciale") restituisce l'indirizzo di una variabile. Per questo `scanf("%d", &x)` vuole `&x`: scanf deve sapere *dove* scrivere il numero letto.

**Vettore (array).** Un vettore è una fila di elementi **dello stesso tipo**, uno dopo l'altro in memoria (si dice **contigui**: attaccati, senza buchi). Si dichiara così: `tipo nome[numero_elementi];`
```c
#define N 10        /* costante: il preprocessore sostituisce N con 10 ovunque */
int v[N];           /* 10 interi: v[0], v[1], ..., v[9] */
int a[10 * N + 4];  /* va bene: è un'espressione costante */
```
Il numero di elementi deve essere una **costante positiva**: il compilatore deve sapere *prima* quanto spazio riservare. Per questo si usa `#define` per le dimensioni: se un giorno ti serve un vettore più grande, cambi un solo numero e tutti i cicli si adattano.

**Indici da 0 a N-1.** `v[i]` è l'elemento in posizione `i`. Il primo è `v[0]`, l'ultimo è `v[N-1]`. Perché da 0? Perché l'indice è lo **spostamento** dall'inizio: `v[0]` è "0 passi dopo l'inizio". L'indirizzo dell'intero vettore coincide con quello di `v[0]`. Un elemento è una variabile a tutti gli effetti: può stare a destra (`x = v[4];`) o a sinistra (`v[3] = 7;`) di un assegnamento.

**Inizializzazione.** `int v[5] = {3, 7, 1, 0, -3};` Se metti meno valori della dimensione (`int v[5] = {3, 7};`), le celle rimanenti valgono **0**. Se invece non metti nessun `= {...}`, le celle di un vettore dentro una funzione contengono **spazzatura** (i bit lasciati lì da prima).

**`sizeof` di un vettore.** `sizeof(v)` dà i byte di **tutto** il vettore: numero di elementi × dimensione di un elemento. Quindi `sizeof(v) / sizeof(v[0])` è il numero di elementi. Attenzione: funziona solo dove `v` è dichiarato come vettore, non dentro una funzione che lo riceve come parametro (lo vedrai nella cartella su puntatori e vettori).

**Scorrere con un `for`.** Si usa il `for` perché sappiamo in anticipo quante volte ripetere:
```c
for (i = 0; i < N; i++)      /* i < N, MAI i <= N */
    somma = somma + v[i];
```
Il prof scrive la stessa cosa con un while: `while (i <= n-1) somma = somma + v[i++];`. Con `v[i++]` si usa prima `i` e poi lo si incrementa. Con `v[++i]` si incrementerebbe *prima*: si salterebbe `v[0]` e, all'ultimo giro, si leggerebbe `v[n]`, fuori dal vettore.

**Uscire dai limiti (out of bounds).** Il C **non controlla** gli indici. `v[N] = 5;` compila senza errori e scrive nella cella *dopo* il vettore, che magari appartiene a un'altra variabile (nell'esempio del prof, gli indici `i` e `j` del ciclo: il programma non termina più). È un **comportamento indefinito** (in inglese *undefined behavior*: lo standard del C non dice cosa succede, quindi può succedere di tutto). È anche la base del **buffer overflow** (straripamento di un vettore che invade la memoria vicina), un attacco informatico classico.
In questa repo i test usano **ASan** (AddressSanitizer, cioè uno strumento che il compilatore inserisce nel programma per controllare ogni accesso alla memoria) e **UBSan** (UndefinedBehaviorSanitizer, che controlla i comportamenti indefiniti). Se esci dai limiti, il programma si ferma con un messaggio come:
```text
es05_trova_errore.c:32:19: runtime error: index 5 out of bounds for type 'int [5]'
```
oppure `ERROR: AddressSanitizer: stack-buffer-overflow`. Quando il controllo ferma il programma, `make test` mostra **CRASH** con il messaggio. Se vuoi vederlo per intero, compila e lancia a mano:
`cc -std=c11 -g -fsanitize=address,undefined es05_trova_errore.c -o prova && ./prova < tests/es05_trova_errore.1.in`

**Matrici (vettori bidimensionali).** `int m[R][C];` è una tabella di R righe e C colonne; `m[i][j]` è l'elemento in riga `i`, colonna `j`. In memoria la matrice è salvata **una riga dopo l'altra** (*row-major order*, "ordine per righe"): `m[0][0] m[0][1] ... m[0][C-1] m[1][0] ...`. Si scorre con due `for` annidati: quello esterno sulle righe, quello interno sulle colonne.

**Passare un vettore a una funzione.** Negli esercizi trovi funzioni come `int somma(int v[], int n)`. Si scrive `int v[]` senza dimensione e si passa a parte `n` (quanti elementi sono usati), perché la funzione non può saperlo da sola. La funzione lavora **sul vettore originale**, non su una copia: se lo modifica (es. inversione, ordinamento), il chiamante vede le modifiche. Per una matrice si scrive `int m[][MAX]`: il numero di colonne è obbligatorio, perché il compilatore deve calcolare dove inizia ogni riga. Il perché esatto lo vedrai con funzioni e puntatori.

**Un vettore non si copia né si confronta "in blocco".** `b = a;` è un errore di compilazione. `a == b` confronta gli **indirizzi** dei due vettori, non il contenuto, quindi è sempre falso per due vettori diversi. Si copia e si confronta elemento per elemento, con un ciclo.

**Imprecisioni e contraddizioni nelle fonti** (te le segnalo perché all'esame conta la versione corretta):
- **Dispensa 3.11 (copia di vettori)**: l'esempio usa `for (i = 0; i <= M; i++) for (j = 0; j <= N; j++) B[i][j] = A[i][j];`. Con `<=` si esce dalla matrice: è proprio l'errore che il prof mostra nella trascrizione. Va scritto `i < M` e `j < N`, come fa la stessa dispensa al paragrafo 3.12.
- **Dispensa 3.3 e trascrizione**: `printf("indirizzo di a=%d", &a)` stampa un indirizzo con `%d`. Il prof stesso dice che il compilatore "si arrabbia" (warning). La forma corretta è `printf("%p", (void *)&a);`.
- **Dispensa 3.13 e trascrizione ("trucco del ciclo singolo")**: `for (i = 0; i < M*N; i++) B[0][i] = 2;` sfrutta il fatto che le righe sono attaccate. La disposizione in memoria è vera, ma per lo standard del C `B[0][i]` con `i >= N` è un accesso fuori dalla riga 0: comportamento indefinito. UBSan infatti lo ferma: `runtime error: index 3 out of bounds for type 'int [3]'`. Lo stesso vale per "`V[0][2]` equivale a `V[1][0]`": è vero come indirizzo, ma non va usato. Usa sempre due cicli.
- **Dimensione costante**: il prof e la dispensa dicono che la dimensione deve essere una costante. È la regola del C89 (lo standard del 1989) ed è la pratica corretta per il corso. Dal C99 esistono anche i **VLA** (*Variable Length Array*, vettori di lunghezza variabile, es. `int v[n];` con `n` letto da tastiera): compilano anche con `-std=c11 -pedantic`. Nei nostri esercizi non li usiamo.
- **Trascrizione automatica**: "e-commerciale" = `&`; "per 100D" = `%d`; "celli" = celle.

### Errori tipici
1. **`i <= N` al posto di `i < N`**: si legge o si scrive `v[N]`, che non esiste. Il compilatore non dice nulla. Senza sanitizer il programma stampa numeri strani (es. `somma: 32838`); con i sanitizer si ferma con `runtime error: index 5 out of bounds for type 'int [5]'`.
2. **Assegnare un vettore a un altro**: `b = a;` →
   `error: assignment to expression with array type`
3. **Confrontare due vettori con `==`**: `if (a == b)` →
   `warning: comparison between two arrays [-Warray-compare]` con la nota `use '&a[0] == &b[0]' to compare the addresses`. Confronta gli indirizzi, non i valori.
4. **Stampare un indirizzo con `%d`**: `printf("%d\n", &x);` →
   `warning: format '%d' expects argument of type 'int', but argument 2 has type 'int *' [-Wformat=]`
5. **Partire da 0 per cercare il massimo**: con un vettore di soli negativi il "massimo" diventa 0. Si parte da `v[0]`.
6. **Dimenticare di inizializzare un accumulatore** (`int somma;` senza `= 0`): il risultato parte da spazzatura.

## Esercizi

### es01 — Somma, media, massimo e minimo  ·  Base
**Fonte:** Ispirato a: trascrizione 2.5, esempio "somma = somma + vettore[i++]" con il while; Appunti Unità 2, par. 3.7 (indicizzazione).
**Testo:** leggi `n` (da 1 a `N_MAX` = 100) e poi `n` interi. Completa le funzioni `somma`, `massimo`, `minimo`. Il `main` stampa anche la media con 2 decimali. Se `n` non è valido stampa `n non valido` (già fatto nel main).
```text
input:  5
        3 -2 7 0 4
output: somma: 12
        media: 2.40
        massimo: 7
        minimo: -2
```
**File:** `es01_statistiche.c` · **Test:** `make test T=05 E=es01`

<details><summary>💡 Suggerimento</summary>
Per il massimo, la variabile che "ricorda il migliore visto finora" deve partire da un valore che sta davvero nel vettore. Quale cella hai sicuramente, visto che n ≥ 1?
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Somma**: un accumulatore `s` parte da 0 (lo 0 non cambia una somma). Per ogni `i` da 0 a `n-1` aggiungiamo `v[i]`. La condizione è `i < n`: l'ultimo indice valido è `n-1`.
2. **Massimo**: partiamo da `max = v[0]`. Se partissimo da 0 e i numeri fossero tutti negativi (caso di test `-8`), il risultato sarebbe 0, che nel vettore non c'è. Poi scorriamo da `i = 1` (la cella 0 l'abbiamo già considerata) e aggiorniamo `max` quando `v[i] > max`.
3. **Minimo**: identico, con `<`.
4. **Media**: nel main c'è `(double)somma(v, n) / n`. Il `(double)` (un *cast*, cioè una conversione esplicita di tipo) va *prima* della divisione: `12 / 5` tra interi fa 2, perdendo i decimali.

```c
int massimo(int v[], int n)
{
    int i, max = v[0];
    for (i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];
    return max;
}
```
Simulazione del massimo con `3 -2 7 0 4`:

| i | v[i] | v[i] > max? | max |
|---|------|-------------|-----|
| – | –    | –           | 3   |
| 1 | -2   | no          | 3   |
| 2 | 7    | sì          | 7   |
| 3 | 0    | no          | 7   |
| 4 | 4    | no          | 7   |

Codice completo: `soluzioni/es01_statistiche.c`.
</details>

### es02 — Cosa stampa?  ·  Base
**Fonte:** Ispirato a: trascrizione 2.5 (inizializzazione, `sizeof` di un vettore, ciclo con `v[i++]`, `v[3] = 7`, matrici m×n); Appunti Unità 2, par. 3.4, 3.7, 3.9, 3.12.
**Testo:** apri `es02_cosa_stampa.c`. **Senza eseguirlo**, scrivi su un foglio (o in fondo al file, nel commento) cosa stampano le righe A, B, C, D, E, F, G. Poi lancia il test: passa già, quindi l'output atteso è in `tests/es02_cosa_stampa.out`. Confronta con la tua previsione. Ipotesi: `sizeof(int)` = 4.
```text
A: ? ?
B: ? ?
...
G: ?
```
**File:** `es02_cosa_stampa.c` · **Test:** `make test T=05 E=es02`

<details><summary>💡 Suggerimento</summary>
Tre trappole: cosa vale una cella non elencata tra le graffe; il valore di `i` *dopo* l'ultimo `v[i++]`; l'indice `v[0] - 4` va calcolato con il valore di `v[0]` in quel momento.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output corretto:
```text
A: 20 5
B: 0 15
C: 27 5
D: 7 19 15
E: 24 3
F: 8
G: 3
```
1. **A**: `v` ha 5 `int` da 4 byte → `sizeof(v)` = 20. Diviso `sizeof(v[0])` = 4 → 5 elementi. Nota: conta la dimensione dichiarata (5), non quanti valori abbiamo scritto tra le graffe (3).
2. **B**: `{4, 8, 15}` riempie `v[0]`, `v[1]`, `v[2]`; le celle 3 e 4 valgono 0. Quindi `v[3]` = 0. `N - 3` = 2 → `v[2]` = 15.
3. **C**: il while somma `4 + 8 + 15 + 0 + 0 = 27`. Con `v[i++]` si usa `i` e poi lo si aumenta: dopo l'ultimo giro (`i` = 4) `i` diventa 5, la condizione `5 < 5` è falsa e il ciclo esce. Quindi `i` = 5.
4. **D**: `v[1] = v[0] + v[2] = 4 + 15 = 19`. Poi `v[v[0] - 4]`: `v[0]` vale 4, quindi l'indice è 0 → `v[0] = 7`. `v[2]` non è cambiato: 15.
5. **E**: `m` è 2×3 = 6 `int` = 24 byte. `m[0]` è una riga intera (3 `int` = 12 byte); 12 / 4 = 3 elementi per riga.
6. **F**: per `i` = 0 prende `m[0][2]` = 3; per `i` = 1 prende `m[1][1]` = 5. Totale 8 (è l'"antidiagonale" che parte in alto a destra).
7. **G**: conta gli elementi pari (`% 2 == 0`, cioè resto della divisione per 2 uguale a 0): 2, 4, 6 → 3.

Codice commentato: `soluzioni/es02_cosa_stampa.c`.
</details>

### es03 — Ricerca lineare e conteggio delle occorrenze  ·  Base
**Fonte:** Ispirato a: Appunti Unità 2, par. 3.7 (l'indice può essere qualsiasi espressione intera; gli indici vanno da 0 a N−1); trascrizione 2.5 (scorrere un vettore con un indice).
**Testo:** leggi `n`, poi `n` interi, poi un valore `x`. Completa `cerca` (restituisce l'indice della **prima** cella uguale a `x`, oppure -1) e `conta` (quante celle valgono `x`).
```text
input:  8
        2 4 9 4 0 4 -1 7
        4
output: posizione: 1
        occorrenze: 3
```
**File:** `es03_ricerca_conteggio.c` · **Test:** `make test T=05 E=es03`

<details><summary>💡 Suggerimento</summary>
In `cerca` puoi fare `return i;` appena trovi x, direttamente dentro il ciclo. Se il ciclo finisce senza trovare nulla, sei sicuro che x non c'è. In `conta` invece non puoi fermarti.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Ricerca lineare** (*lineare* perché guarda le celle in fila, una dopo l'altra, come cercare un nome in un elenco non ordinato). Si parte da `i = 0` così la prima corrispondenza trovata è la più a sinistra.
2. Appena `v[i] == x`, `return i;` esce dalla funzione: non serve guardare il resto.
3. Se si esce dal ciclo, nessuna cella era uguale: `return -1;`. Perché -1? Non può essere un indice vero (gli indici partono da 0), quindi chi chiama capisce "non trovato".
4. **Conteggio**: un contatore `c = 0`, e `c++` per ogni cella uguale. Qui il ciclo va fatto tutto.

```c
int cerca(int v[], int n, int x)
{
    int i;
    for (i = 0; i < n; i++)
        if (v[i] == x)
            return i;
    return -1;
}
```
Caso limite verificato dai test: vettore di un solo elemento (`n` = 1) che contiene `x` → posizione 0.
Codice completo: `soluzioni/es03_ricerca_conteggio.c`.
</details>

### es04 — Inverti un tratto del vettore "sul posto"  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 2, par. 3.7 ("ogni elemento di un vettore è una variabile e può comparire a sinistra di un assegnamento") e par. 3.8 (controllo degli indici). Variante di LEZ 11 es. 5: qui si inverte solo una porzione e si validano gli indici.
**Testo:** leggi `n`, `n` interi, poi due indici `a` e `b`. Inverti **solo** gli elementi da `v[a]` a `v[b]` compresi, senza usare un secondo vettore ("sul posto", in inglese *in place*). Se non vale `0 <= a <= b <= n-1` stampa `intervallo non valido`.
```text
input:  7
        10 20 30 40 50 60 70
        1 4
output: 10 50 40 30 20 60 70
```
**File:** `es04_inverti_tratto.c` · **Test:** `make test T=05 E=es04`

<details><summary>💡 Suggerimento</summary>
Usa due indici: uno parte da a e va avanti, l'altro parte da b e torna indietro. Scambia i due elementi e fermati quando gli indici si incontrano. Per scambiare due valori ti serve una terza variabile.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Validazione** (nel main): il C non controlla gli indici. Con `b = n` la funzione scriverebbe `v[n]`, fuori dal vettore. Quindi controlliamo `a < 0 || b >= n || a > b` *prima* di chiamare la funzione.
2. **Due indici**: `sx = a`, `dx = b`. Finché `sx < dx`: scambia `v[sx]` e `v[dx]`, poi `sx++`, `dx--`.
3. **Perché `sx < dx` e non "per tutto il tratto"?** Se andassimo avanti fino a `b`, ogni coppia verrebbe scambiata due volte e il tratto tornerebbe com'era.
4. **Scambio con variabile d'appoggio**: `tmp = v[sx]; v[sx] = v[dx]; v[dx] = tmp;`. Senza `tmp`, dopo `v[sx] = v[dx]` il vecchio valore di `v[sx]` è perso.

```c
while (sx < dx) {
    tmp = v[sx];
    v[sx] = v[dx];
    v[dx] = tmp;
    sx++;
    dx--;
}
```
Simulazione con `a` = 1, `b` = 4:

| sx | dx | scambio      | vettore                  |
|----|----|--------------|--------------------------|
| 1  | 4  | 20 ↔ 50      | 10 50 30 40 20 60 70     |
| 2  | 3  | 30 ↔ 40      | 10 50 40 30 20 60 70     |
| 3  | 2  | stop (3 < 2 falso) |                    |

Con `a == b` (test con un solo elemento) il ciclo non parte: corretto, un elemento invertito resta uguale.
Codice completo: `soluzioni/es04_inverti_tratto.c`.
</details>

### es05 — Trova e correggi l'errore: temperature della settimana  ·  Intermedio
**Fonte:** Ispirato a: trascrizione 2.5 ("proviamo a fare un piccolo errore e mettere un uguale di troppo": il ciclo con `<=` che sfonda la matrice); Appunti Unità 2, par. 3.8 e 3.12.
**Testo:** il programma legge esattamente `N` = 5 temperature, stampa somma, media e le 4 variazioni tra un giorno e il successivo. Contiene **due** errori di indice. Il test va in CRASH, perché UBSan (il controllo sulle operazioni vietate) ferma il programma. Trovali e correggili cambiando il meno possibile.
```text
input:  12 15 13 13 18
output: somma: 71
        media: 14.20
        variazioni: +3 -2 +0 +5
```
**File:** `es05_trova_errore.c` · **Test:** `make test T=05 E=es05`

<details><summary>💡 Suggerimento</summary>
Per ogni ciclo chiediti: qual è l'ultimo valore di i? Con quel valore, l'indice dentro le quadre è ancora valido per QUEL vettore? Ricorda che d ha N-1 celle, non N. Per vedere il messaggio del sanitizer lancia il programma a mano (comando nella Teoria flash).
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Errore 1 — `for (i = 0; i <= N; i++) somma += t[i];`**. L'ultimo giro ha `i` = 5 e legge `t[5]`: `t` ha celle da 0 a 4. Senza sanitizer, sulla mia macchina usciva `somma: 32838` (71 + spazzatura). Con UBSan: `runtime error: index 5 out of bounds for type 'int [5]'`. **Correzione:** `i < N`.
2. **Errore 2 — `for (i = 0; i < N; i++) d[i] = t[i + 1] - t[i];`**. Tra 5 giorni ci sono 4 variazioni, infatti `d` è `int d[N - 1]`. All'ultimo giro (`i` = 4) scrive `d[4]` (fuori da `d`) e legge `t[5]` (fuori da `t`). **Correzione:** `i < N - 1`.
3. **Perché è un errore subdolo**: senza sanitizer il secondo errore spesso non si vede proprio, perché la cella "rubata" non era usata. Il programma sembra giusto, ma ha sporcato memoria non sua: è l'inizio di un buffer overflow.
4. **Regola pratica**: un ciclo che usa `v[i + 1]` deve fermarsi un passo prima: `i < N - 1`.

Codice corretto: `soluzioni/es05_trova_errore.c`.
</details>

### es06 — Ordinamento per selezione (selection sort), passo per passo  ·  Intermedio
**Fonte:** Esercizio classico (non presente nelle trascrizioni del blocco 2), costruito con gli strumenti di Appunti Unità 2, par. 3.7 (lettura e scrittura di `v[indice]`) e con lo scambio con variabile d'appoggio già visto in es04.
**Testo:** ordina in modo crescente. Alla passata `p` (da 0 a `n-2`) cerca la **posizione** del minimo tra `v[p]` e `v[n-1]` e scambialo con `v[p]`. Dopo ogni passata stampa `passata K:` (K = p+1) seguito dal vettore. A parità di valore prendi il primo trovato (`<`, non `<=`).
```text
input:  5
        29 -4 10 -4 3
output: passata 1: -4 29 10 -4 3
        passata 2: -4 -4 10 29 3
        passata 3: -4 -4 3 29 10
        passata 4: -4 -4 3 10 29
        ordinato: -4 -4 3 10 29
```
**File:** `es06_selection_sort.c` · **Test:** `make test T=05 E=es06`

<details><summary>💡 Suggerimento</summary>
Ti servono due cicli annidati: quello esterno decide QUALE posto stai riempiendo (p), quello interno cerca CHI ci va (la posizione del minimo tra p e n-1). Memorizza l'indice del minimo, non il suo valore.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Idea**: come mettere in fila delle carte scegliendo ogni volta la più bassa tra quelle rimaste. Dopo la passata `p`, le celle da 0 a `p` sono definitive.
2. **Perché memorizzare la posizione (`pos_min`) e non il valore?** Per scambiare ci serve sapere *dove* sta il minimo.
3. **Perché `n - 1` passate?** Quando le prime `n-1` celle sono al loro posto, l'ultima contiene per forza il valore più grande.
4. **Caso `n` = 1**: il ciclo esterno (`p < 0`) non parte, si stampa solo `ordinato: 7`.

```c
for (p = 0; p < n - 1; p++) {
    pos_min = p;
    for (i = p + 1; i < n; i++)
        if (v[i] < v[pos_min])
            pos_min = i;
    tmp = v[p]; v[p] = v[pos_min]; v[pos_min] = tmp;
    printf("passata %d:", p + 1);
    stampa(v, n);
}
```
Passata 1 sull'esempio: tra `29 -4 10 -4 3` il primo minimo è `-4` in posizione 1 → scambio con la posizione 0 → `-4 29 10 -4 3`. Passata 2: tra le posizioni 1..4 (`29 10 -4 3`) il minimo è `-4` in posizione 3 → `-4 -4 10 29 3`. E così via.
Nota: nel test con il vettore già ordinato, ogni passata scambia un elemento con se stesso. Funziona, ma è lavoro inutile: il selection sort fa sempre lo stesso numero di confronti.
Codice completo: `soluzioni/es06_selection_sort.c`.
</details>

### es07 — Matrice: somme di righe e colonne, trasposta  ·  Tipo esame
**Fonte:** Ispirato a: trascrizione 2.5 (matrice m×n, "v[i][j] è l'elemento dell'i-esima riga, j-esima colonna", doppio ciclo righe/colonne per copiare una matrice); Appunti Unità 2, par. 3.9, 3.10, 3.12.
**Testo:** leggi `r` e `c` (da 1 a `MAX` = 10), poi la matrice riga per riga. Completa `somme_righe`, `somme_colonne` e `trasposta` (la **trasposta** è la matrice in cui le righe diventano colonne: l'elemento in riga i, colonna j finisce in riga j, colonna i).
```text
input:  2 3
        1 2 3
        4 5 6
output: somme righe: 6 15
        somme colonne: 5 7 9
        trasposta:
        1 4
        2 5
        3 6
```
**File:** `es07_matrice.c` · **Test:** `make test T=05 E=es07`

<details><summary>💡 Suggerimento</summary>
Per la somma di una riga tieni fermo i e fai scorrere j; per una colonna il contrario. Ricordati di azzerare out[i] prima di sommarci dentro. La trasposta è una sola riga di codice dentro due cicli.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché `int m[][MAX]`?** La matrice in memoria è una riga dopo l'altra. Per trovare `m[i][j]` il compilatore calcola `i * MAX + j` celle dall'inizio: deve conoscere `MAX` (la lunghezza di una riga *come dichiarata*), anche se noi usiamo solo `c` colonne.
2. **Somma righe**: per ogni `i`, `out[i] = 0`, poi `out[i] += m[i][j]` per `j` da 0 a `c-1`. Se non azzeri, `out[i]` parte da spazzatura.
3. **Somma colonne**: per ogni `j`, `out[j] = 0`, poi `out[j] += m[i][j]` per `i` da 0 a `r-1`.
4. **Trasposta**: `t[j][i] = m[i][j]`. `t` ha `c` righe e `r` colonne: per questo il main la stampa con il ciclo esterno fino a `c`.
5. **Validazione di r e c** (nel main): se `r` fosse 11, i cicli userebbero `m[10][...]`, fuori dalla matrice.

```c
for (i = 0; i < r; i++) {
    out[i] = 0;
    for (j = 0; j < c; j++)
        out[i] += m[i][j];
}
```
Simulazione delle colonne sull'esempio: colonna 0 = 1 + 4 = 5; colonna 1 = 2 + 5 = 7; colonna 2 = 3 + 6 = 9.
Casi limite nei test: matrice 1×1 con numero negativo, matrice 3×1 (la trasposta diventa una riga sola).
Codice completo: `soluzioni/es07_matrice.c`.
</details>

### es08 — Fusione di due vettori ordinati (merge)  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 2, par. 3.11 ("non è possibile copiare direttamente un vettore tramite l'operatore di assegnamento... è necessario copiare ogni elemento individualmente"); riusa il selection sort di es06.
**Testo:** leggi un vettore `a` (`n` da 0 a 50, poi gli elementi) e un vettore `b` (`m`, poi gli elementi). Ordinali entrambi, poi costruisci il vettore `f` con tutti gli `n + m` elementi in ordine crescente **senza riordinare tutto**: scorri `a` e `b` insieme e prendi ogni volta il più piccolo dei due elementi "in testa".
```text
input:  4
        9 1 7 3
        3
        8 2 7
output: a ordinato: 1 3 7 9
        b ordinato: 2 7 8
        fusione: 1 2 3 7 7 8 9
```
**File:** `es08_fusione.c` · **Test:** `make test T=05 E=es08`

<details><summary>💡 Suggerimento</summary>
Tre indici: i su a, j su b, k su f. Un primo ciclo va avanti finché entrambi i vettori hanno elementi; poi uno dei due è finito e devi copiare il resto dell'altro. Attenzione al caso n = 0.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché funziona**: `a` e `b` sono ordinati, quindi il più piccolo tra gli elementi rimasti è per forza `a[i]` oppure `b[j]`. Lo copiamo in `f[k]` e avanziamo l'indice da cui l'abbiamo preso. È come unire due mazzi di carte già ordinati prendendo sempre la carta più bassa in cima.
2. **Primo ciclo**: `while (i < n && j < m)`. La condizione con `&&` (e logico) garantisce che non leggiamo mai `a[n]` o `b[m]`.
3. **Svuotare il resto**: `while (i < n) f[k++] = a[i++];` e lo stesso per `b`. Solo uno dei due farà qualcosa. È la "copia elemento per elemento" della dispensa: `f = a` non compila.
4. **Dimensione di `f`**: `F_MAX = 2 * N_MAX`, perché nel caso peggiore contiene tutto `a` e tutto `b`. Un `f` più piccolo sarebbe un buffer overflow.
5. **`f[k++] = a[i++];`**: copia `a[i]` in `f[k]` e poi incrementa sia `k` sia `i`.

```c
while (i < n && j < m) {
    if (a[i] <= b[j])
        f[k++] = a[i++];
    else
        f[k++] = b[j++];
}
while (i < n) f[k++] = a[i++];
while (j < m) f[k++] = b[j++];
```
Simulazione (a = 1 3 7 9, b = 2 7 8):

| i | j | confronto | copiato | f                |
|---|---|-----------|---------|------------------|
| 0 | 0 | 1 vs 2    | 1       | 1                |
| 1 | 0 | 3 vs 2    | 2       | 1 2              |
| 1 | 1 | 3 vs 7    | 3       | 1 2 3            |
| 2 | 1 | 7 vs 7    | 7 (da a)| 1 2 3 7          |
| 3 | 1 | 9 vs 7    | 7       | 1 2 3 7 7        |
| 3 | 2 | 9 vs 8    | 8       | 1 2 3 7 7 8      |
| 3 | 3 | b finito  | 9       | 1 2 3 7 7 8 9    |

Caso limite nei test: `n` = 0 (a vuoto): il primo while non parte, si copia tutto `b`.
Codice completo: `soluzioni/es08_fusione.c`.
</details>

## Prompt pronti per questo argomento
- "Interrogami con 5 domande su vettori e memoria in C (indici, `sizeof`, inizializzazione parziale, out of bounds, matrici in row-major order), una alla volta. Aspetta la mia risposta prima di passare alla successiva e correggimi spiegando il perché."
- "Ho scritto questa soluzione per es08 di 05-vettori-memoria: [incolla codice]. Dimmi se è corretta e perché, quali casi limite potrebbe sbagliare, senza riscrivermela tutta."
- "Dammi un programma C di 15-20 righe con un vettore o una matrice in cui c'è un accesso fuori dai limiti nascosto (non solo `<=`). Non dirmi dov'è: io lo cerco e tu mi dici se ho ragione."
- "Generami 3 esercizi nuovi tipo es07 (matrici, livello esame del prof Anisetti), con input/output di esempio, senza soluzione."
- "Disegnami la memoria (celle e indirizzi, `sizeof(int)` = 4) di `int m[2][3] = {{1,2,3},{4,5,6}};` e spiegami perché `m[0][3]` 'punta' a `m[1][0]` ma è comunque un errore usarlo."

## Riepilogo
- La memoria è una fila di celle con indirizzi; un vettore occupa celle contigue e il suo indirizzo è quello di `v[0]`. Gli indici vanno da 0 a N-1.
- La dimensione si fissa con una costante (`#define`); `sizeof(v)/sizeof(v[0])` dà il numero di elementi dove `v` è dichiarato.
- Il C non controlla gli indici: `i <= N` invece di `i < N` legge/scrive memoria altrui (comportamento indefinito, buffer overflow). ASan e UBSan lo scoprono.
- Le matrici sono salvate riga dopo riga; si scorrono con due cicli. I vettori si copiano e si confrontano elemento per elemento, mai con `=` o `==`.

## Glossario
- **cella / byte** — la più piccola unità di memoria indirizzabile, 8 bit.
- **indirizzo** — numero che identifica una cella di memoria (come un numero civico).
- **allocazione** — riservare celle di memoria per una variabile.
- **`&` (operatore indirizzo)** — restituisce l'indirizzo di una variabile.
- **vettore (array)** — sequenza di elementi dello stesso tipo, in celle contigue.
- **contiguo** — attaccato al precedente, senza spazi vuoti in mezzo.
- **indice** — numero tra quadre che indica la posizione di un elemento, da 0 a N-1.
- **`sizeof`** — operatore che dà quanti byte occupa un tipo o una variabile.
- **`#define`** — direttiva del preprocessore che sostituisce un nome con un valore prima della compilazione.
- **matrice** — vettore a due dimensioni (righe e colonne), `m[i][j]`.
- **row-major order** — ordine in memoria "per righe": prima tutta la riga 0, poi la riga 1, ecc.
- **out of bounds** — accesso a un indice fuori dall'intervallo valido del vettore.
- **comportamento indefinito (undefined behavior)** — situazione in cui lo standard del C non garantisce nulla: può succedere qualsiasi cosa.
- **buffer overflow** — scrittura oltre la fine di un vettore che invade la memoria vicina; base di molti attacchi.
- **ASan (AddressSanitizer)** — strumento del compilatore che ferma il programma quando accede a memoria non sua.
- **UBSan (UndefinedBehaviorSanitizer)** — strumento del compilatore che ferma il programma su comportamenti indefiniti, come un indice fuori dai limiti.
- **VLA (Variable Length Array)** — vettore con dimensione decisa durante l'esecuzione (`int v[n]`), ammesso dal C99; non usato nel corso.
- **in place (sul posto)** — modificare un vettore senza usarne un secondo.
- **ricerca lineare** — guardare gli elementi uno dopo l'altro finché si trova quello cercato.
- **selection sort** — ordinamento che a ogni passata sceglie il minimo dei rimanenti e lo mette al suo posto.
- **merge (fusione)** — unire due sequenze ordinate in una sola sequenza ordinata.
- **trasposta** — matrice ottenuta scambiando righe e colonne.
- **cast** — conversione esplicita di tipo, es. `(double)x`.
