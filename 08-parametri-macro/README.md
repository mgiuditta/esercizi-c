# 08 — Scope, parametri e macro

> Lezioni di riferimento: trascrizioni 3.1 (Funzioni: variabili globali e shadowing) e 3.2 (Parametri e macro), E-tivity 3.6 (ParametriePuntatoribis e 2ParametriePuntatoriTRIS, l'equazione di secondo grado con `float *`), Appunti Unità 3 (cap. 2 "Scope, Parametri e Macro", cap. 3 §3.18–3.22 "Passaggio dei parametri"), LEZ 14 (Scope, parametri e macro).
> Tempo stimato: ~4 ore.

## Teoria flash

**Scope (visibilità).** Lo scope di un nome è la zona del codice in cui quel nome si può usare. In C la zona dipende da **dove** scrivi la dichiarazione:
- **scope di blocco**: una variabile dichiarata tra `{ }` (anche quella dichiarata nel `for (int i = 0; …)`) esiste solo fino alla `}` che chiude il blocco;
- **scope di funzione**: i parametri e le variabili locali di una funzione si vedono solo dentro quella funzione;
- **scope di file (globale)**: una variabile dichiarata fuori da tutte le funzioni si vede da quel punto fino alla fine del file.

Attenzione: lo scope dipende da dove il codice è **scritto**, non da chi lo chiama. Se `main` dichiara una sua `n` e poi chiama `stampa_n()`, dentro `stampa_n` la `n` di `main` **non** si vede (es01).

**Durata (lifetime).** È il periodo in cui una variabile esiste in memoria. Le locali nascono quando il programma entra nel blocco e muoiono quando ne esce: stanno sullo stack, dentro il record di attivazione (vedi 07). Le globali esistono per tutto il programma, nel segmento dati.

**Shadowing (effetto ombra).** Se in un blocco interno dichiari un nome che esiste già fuori, il nome interno **nasconde** quello esterno fino alla fine del blocco. Le variabili restano due, distinte. È come avere due persone che si chiamano Luca: in cucina "Luca" indica quello che è in cucina.
```c
int n = 5;                    /* globale */
void foo(void) { int n = 0; n++; }   /* incrementa la SUA n: la globale resta 5 */
```

**`extern`.** Il prof distingue due operazioni. *Definire* una globale vuol dire dichiararla e anche allocarla, cioè riservarle memoria. *Dichiararla* soltanto vuol dire dire "esiste, ma è allocata altrove", e si fa con `extern int n;`. Una globale si definisce **una volta sola**, ma si può dichiarare più volte. I prototipi delle funzioni sono implicitamente `extern`.

**Parametri formali e attuali.** I formali sono quelli nell'intestazione (`int somma(int a, int b)`). Gli attuali, o *argomenti*, sono quelli nella chiamata (`somma(c, 10)`). L'insieme delle chiamate, con `main` come radice, forma l'**albero di chiamata**.

**Passaggio per valore e "per indirizzo".** In C **ogni** parametro riceve una copia (07). Per permettere a una funzione di modificare una variabile del chiamante, le passi il suo **indirizzo**, cioè la posizione in memoria della variabile.
- `&a` (operatore "indirizzo di") = dove si trova `a`;
- `int *p` = `p` è un **puntatore**, cioè una variabile che contiene l'indirizzo di un `int`;
- `*p` (operatore di **dereferenziazione**, "vai all'indirizzo") = la variabile che si trova all'indirizzo `p`.
```c
void scambia(int *x, int *y) { int t = *x; *x = *y; *y = t; }
scambia(&a, &b);              /* passo DOVE stanno a e b */
```
Analogia: invece di una fotocopia del documento, dai a qualcuno l'**indirizzo di casa tua**. Lui va lì e modifica l'originale. L'indirizzo è comunque una copia, quindi tecnicamente anche questo è un passaggio per valore, ma una copia dell'indirizzo indica sempre la stessa casa. È lo schema dell'E-tivity 3.6 del prof: `void coefficienti(float *c1, float *c2, float *c3)` chiamata con `coefficienti(&a, &b, &c)`, e dentro `scanf("%f", c1)` **senza `&`**, perché `c1` è già un indirizzo.

**Vettori passati a funzione.** Quando passi un vettore, il C **non copia** gli elementi. Passa l'indirizzo del primo elemento: `int v[]` nel parametro equivale a `int *v`. Ne derivano due conseguenze.
1. La funzione **può modificare** il vettore del chiamante, anche se è `void` (es03).
2. La funzione **non sa** quanto è lungo il vettore. Devi passarle la lunghezza come parametro in più. `sizeof(v)` dentro la funzione dà 8, cioè la dimensione di un indirizzo, non quella del vettore. Qui assumiamo `sizeof(int)` = 4 e `sizeof(int *)` = 8, come su macOS arm64 e Linux x86-64.

Se la funzione deve solo leggere, scrivi `const int v[]`. `const` è una promessa di non modificare il vettore, e il compilatore la fa rispettare.

**Macro con parametri.** `#define MUL(a, b) ((a) * (b))` **non** è una funzione. Il **preprocessore** (il programma che lavora sul testo prima del compilatore) sostituisce il testo, e questa sostituzione si chiama *macroespansione*. Non c'è chiamata, non c'è salto e non c'è record di attivazione. Il prof le presenta come un modo per evitare il costo del salto di una chiamata. Ci sono due trappole.
1. **Precedenza.** `#define MOLTIPLICA(a, b) a * b` con `MOLTIPLICA(a - c, b)` diventa `a - c * b`. Rimedio: parentesi intorno a ogni parametro **e** a tutta l'espressione.
2. **Effetti collaterali.** Un *effetto collaterale* è una modifica fatta mentre si calcola un'espressione, come `i++`. Con `#define MAX(a, b) ((a) > (b) ? (a) : (b))`, la chiamata `MAX(i++, j)` incolla `i++` **due volte**, quindi `i` può essere incrementata due volte. Le parentesi qui non aiutano. Rimedio: non passare mai a una macro argomenti come `i++`, oppure usare una funzione.

Per convenzione le macro si scrivono in MAIUSCOLO, così chi legge capisce che non sono funzioni. Per vedere il codice dopo l'espansione: `cc -E file.c`.

**`#ifdef` / `#ifndef`** (compilazione condizionale): **non sono trattati dal prof** né nella trascrizione 3.2 né negli Appunti Unità 3. Li trovi solo nella LEZ 14 (§3.16). In breve: `#ifdef DEBUG … #endif` include quel codice solo se la macro `DEBUG` è definita (ad esempio compilando con `cc -DDEBUG`). Non ci sono esercizi su questo, perché non è materia del corso.

**Contraddizioni e imprecisioni nelle fonti**
- Errori della trascrizione automatica: "externa" = `extern`; "sam" = `sum`/`somma`; "mull"/"mule" = la macro `MUL`; "fu"/"funo" = `foo`; "float star" = `float *`; "commerciale" = `&` ("e commerciale").
- Appunti §3.20 parlano di "passaggio per indirizzo", mentre il §3.22 dice che il C usa "**esclusivamente** il passaggio per valore". Sono vere entrambe. Il meccanismo è sempre per valore, ma se il valore copiato è un indirizzo ottieni l'effetto di un passaggio per riferimento: il C lo *simula*.
- E-tivity 3.6: il prof legge `float a, b, c` ma il discriminante è `double d`. Funziona, perché il `float` viene promosso a `double`. Mescolare i due tipi però è solo una scelta del prof, non un obbligo. Nella soluzione di es08 il calcolo è forzato in `double`.
- E-tivity 3.6: `coefficienti` è `void` e non controlla `scanf`. In es08 restituisce un `int` (1 = letto tutto) per gestire l'input sbagliato: è un'aggiunta rispetto al prof.
- Il prof (3.2) dice che le macro servono a "non fare la chiamata" per motivi di prestazioni. È vero in principio, ma oggi il compilatore con le ottimizzazioni attive spesso copia lui stesso il corpo delle funzioni piccole nel punto di chiamata (*inlining*). Il motivo di prestazioni pesa meno delle trappole viste sopra.

**Errori tipici** (messaggi veri di `gcc 13 -std=c11 -Wall -Wextra -pedantic`)
1. Passare il valore invece dell'indirizzo, per esempio `scambia(a, b)` con `int *` nei parametri: `warning: passing argument 1 of 'scambia' makes pointer from integer without a cast [-Wint-conversion]`. Su clang recente (macOS) è un **errore**.
2. Mettere `&` su un parametro che è già un puntatore, per esempio `scanf("%d", &x)` con `int *x`: `warning: format '%d' expects argument of type 'int *', but argument 2 has type 'int **' [-Wformat=]`.
3. Usare `sizeof` su un vettore ricevuto come parametro: `warning: 'sizeof' on array function parameter 'v' will return size of 'int *' [-Wsizeof-array-argument]`.
4. Usare una variabile fuori dal suo blocco: `error: 'k' undeclared (first use in this function)`.
5. Mettere `;` alla fine di una macro e poi usarla in un `if … else`: `error: 'else' without a previous 'if'`.
6. Shadowing accidentale: scrivi `int promossi = 0;` dentro una funzione credendo di azzerare la globale. gcc **non avvisa** (es07). Le opzioni `-Wshadow` lo segnalerebbero.

## Esercizi

### es01 — Cosa stampa? Una variabile n, cinque scope  ·  Base
**Fonte:** Ispirato a: Trascrizione 3.1 (esempi `n` globale modificata da `foo` e shadowing con `int n = 0` dentro `foo`) + Appunti Unità 3, §1.14–1.16 e §2.2–2.3.
**Testo:** senza eseguirlo, prevedi le 10 righe stampate da `es01_scope_cosa_stampa.c`. Qui ci sono una `n` globale, una locale di `azzera`, un parametro `n` di `incrementa`, una `n` di blocco nel `main` e una `n` del `for`.

La mia previsione:
```text
A: n=?
...
```
**File:** `es01_scope_cosa_stampa.c` · **Test:** `make test T=08 E=es01`

<details><summary>💡 Suggerimento</summary>
Per ogni `n`, cerca la dichiarazione più vicina **risalendo il testo** del codice, dal blocco più interno verso l'esterno. Non conta chi ha chiamato la funzione.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output:
```text
A: n=10
azzera: n=1
stampa_n: n=10
incrementa: n=15
B: n=10
C: n=3
stampa_n: n=10
D: n=0
D: n=1
stampa_n: n=20
```
1. **A**: `main` (in quel punto) non ha una sua `n`, quindi usa la globale: 10.
2. **azzera**: `int n = 0` è una locale che fa ombra alla globale. `n++` porta la locale a 1, e la globale non cambia.
3. **stampa_n**: non dichiara nessuna `n`, quindi usa la globale, ancora 10.
4. **incrementa(n)**: il parametro `n` riceve una copia di 10 e fa ombra alla globale. 10 + 5 = 15, ma solo nella copia.
5. **B**: la globale è sempre 10.
6. **C**: nel blocco `{ int n = 3; }` la `n` di blocco nasconde la globale: 3.
7. **stampa_n dentro il blocco**: questo è il punto chiave. `stampa_n` è **scritta** fuori dal blocco, quindi vede la globale (10), non la `n = 3` del chiamante. Lo scope in C si decide leggendo il testo (*scope statico*), non seguendo le chiamate. Il `n++` del blocco modifica la `n` di blocco, che poi sparisce alla `}`.
8. **D**: la `n` del `for` vive solo nel ciclo e vale 0, poi 1.
9. Dopo il `for`, `n = n * 2` usa di nuovo la globale: 10 · 2 = 20. **stampa_n** stampa 20. È l'unica modifica alla globale in tutto il programma.

Vedi `soluzioni/es01_scope_cosa_stampa.c`.
</details>

### es02 — scambia() che funziona davvero  ·  Base
**Fonte:** Ispirato a: Appunti Unità 3, §3.20 "Passaggio per indirizzo" e §3.21 (esempio `incrementa(int *p)`); è la correzione del "trova l'errore" di 07/es06.
**Testo:** completa `void scambia(int *x, int *y)`; il main la chiama con `scambia(&a, &b)`.
```text
input:  5 3         output: prima: a=5 b=3
                            dopo: a=3 b=5
```
**File:** `es02_scambia.c` · **Test:** `make test T=08 E=es02`

<details><summary>💡 Suggerimento</summary>
È lo scambio classico con una variabile d'appoggio `t`, ma ogni volta che prima scrivevi `a` ora scrivi `*x`, cioè "la variabile all'indirizzo x".
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. Il main passa `&a` e `&b`, cioè gli **indirizzi**. Nel record di attivazione di `scambia`, `x` e `y` contengono quegli indirizzi.
2. `int t = *x;` legge il valore di `a` (5) passando dal suo indirizzo.
3. `*x = *y;` **scrive** dentro `a` il valore di `b` (3).
4. `*y = t;` scrive dentro `b` il vecchio valore di `a` (5).
5. Al ritorno il record di `scambia` sparisce, ma le scritture sono avvenute nelle variabili del main, che restano.

| passo | t | a (= *x) | b (= *y) |
|---|---|---|---|
| inizio | – | 5 | 3 |
| `t = *x` | 5 | 5 | 3 |
| `*x = *y` | 5 | 3 | 3 |
| `*y = t` | 5 | 3 | 5 |

Vedi `soluzioni/es02_scambia.c`. I puntatori si approfondiscono nella cartella 09.
</details>

### es03 — Azzera i primi k elementi di un vettore  ·  Base
**Fonte:** Ispirato a: Appunti Unità 3, §4.11 "Puntatori e vettori" (il nome del vettore è l'indirizzo del primo elemento) + LEZ 14, §3.11 (il vettore non viene copiato).
**Testo:** completa `azzera(v, k)`, che mette a 0 gli elementi da `v[0]` a `v[k-1]`. La funzione è `void`, eppure il main vede il vettore modificato.
```text
input:  5
        1 2 3 4 5
        2
output: prima: 1 2 3 4 5
        dopo: 0 0 3 4 5
```
**File:** `es03_azzera.c` · **Test:** `make test T=08 E=es03`

<details><summary>💡 Suggerimento</summary>
Basta un `for` da 0 a k−1. La domanda vera è *perché* funziona, mentre `raddoppia(int x)` in 07 non funzionava.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. `azzera(v, k)`: il nome `v` usato da solo vale "indirizzo del primo elemento". La funzione riceve una copia di quell'**indirizzo**, non una copia dei 5 numeri.
2. Dentro, `v[i] = 0` scrive nella memoria del vettore del main, perché è la stessa memoria.
3. Il parametro `k` è indispensabile: la funzione non può sapere da sola quanto è lungo il vettore (`sizeof(v)` darebbe 8).
4. Il main controlla `0 <= k <= n` **prima** della chiamata. Con k > n la funzione scriverebbe fuori dal vettore: AddressSanitizer (lo strumento attivato da `make test`) fermerebbe il programma con un errore.
5. `stampa` riceve `const int v[]` perché deve solo leggere.

Casi limite nei test: vettore di 1 elemento, k = 0 (non cambia nulla) e k = n (azzera tutto).
Vedi `soluzioni/es03_azzera.c`.
</details>

### es04 — Minimo e massimo "restituiti" tramite puntatori  ·  Intermedio
**Fonte:** Ispirato a: E-tivity 3.6 ParametriePuntatoribis (parametri `float *` usati per "far uscire" valori dalla funzione) + Appunti Unità 3, §3.21 "Effetti collaterali".
**Testo:** completa `void min_max(const int v[], int n, int *pmin, int *pmax)`, che deve restituire **due** risultati.
```text
input:  5
        3 -2 8 0 8
output: min = -2
        max = 8
```
**File:** `es04_min_max.c` · **Test:** `make test T=08 E=es04`

<details><summary>💡 Suggerimento</summary>
`return` restituisce un solo valore, quindi qui i risultati escono attraverso `*pmin` e `*pmax`. Fai partire entrambi da `v[0]`, non da 0.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. Il main passa `&mi` e `&ma`, quindi la funzione può scrivere nelle sue variabili. Sono **parametri di uscita**: non portano dati dentro la funzione, li portano fuori.
2. `*pmin = *pmax = v[0]` all'inizio. Perché non 0? Con il vettore `-5 -9 -1 -7` un massimo iniziale 0 resterebbe 0, che non è nemmeno nei dati (terzo test).
3. Il ciclo parte da `i = 1`, perché `v[0]` è già stato considerato. A ogni elemento aggiorna `*pmin` e `*pmax` se serve.
4. Si combinano due concetti: il vettore (passato come indirizzo, in sola lettura grazie a `const`) e due puntatori in uscita.

| i | v[i] | *pmin | *pmax |
|---|---|---|---|
| – | – | 3 | 3 |
| 1 | -2 | -2 | 3 |
| 2 | 8 | -2 | 8 |
| 3 | 0 | -2 | 8 |
| 4 | 8 | -2 | 8 |

Vedi `soluzioni/es04_min_max.c`.
</details>

### es05 — Cosa stampa? Macro contro funzioni  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 3.2 (slide `MOLTIPLICA(a-c, b)` e macro `MUL` con le parentesi) + Appunti Unità 3, §2.12–2.14 + LEZ 14, §3.14 (`MAX(i++, j)`).
**Testo:** prevedi le 8 righe stampate da `es05_macro_cosa_stampa.c`. Per ogni macro, scrivi prima il testo espanso e poi calcolalo.

La mia previsione:
```text
1) ?
...
```
**File:** `es05_macro_cosa_stampa.c` · **Test:** `make test T=08 E=es05`

<details><summary>💡 Suggerimento</summary>
Copia il testo dell'argomento **così com'è** (senza calcolarlo) in ogni punto in cui compare il parametro. Poi applica le regole di precedenza: `*` e `/` prima di `+` e `-`; `*` e `/` da sinistra a destra. Nell'operatore `? :` viene valutato **solo uno** dei due rami.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output:
```text
1) 1
2) 9
3) 9
4) 100
5) 25
6) m=4 i=3
7) m=8 i=9
8) m=7 i=8
```
Con a = 4, b = 3, c = 1, j = 4:
1. `MOLTIPLICA(a - c, b)` → `a - c * b` → 4 − 3 = **1** (non 9: la moltiplicazione ha la precedenza).
2. `MUL(a - c, b)` → `((a - c) * (b))` → 3 · 3 = **9**. Le parentesi della macro salvano il risultato.
3. `QUADRATO(a + 1)` → `a + 1 * a + 1` → 4 + 4 + 1 = **9** (non 25).
4. `100 / QUADRATO(2)` → `100 / 2 * 2`, calcolato da sinistra a destra: 50 · 2 = **100** (non 25). Qui manca la parentesi **esterna**.
5. `100 / QUAD_OK(2)` → `100 / ((2) * (2))` = **25**.
6. `i = 2`: `MAX(i++, j)` → `((i++) > (j) ? (i++) : (j))`. Il confronto usa 2 e poi porta i a 3. 2 > 4 è falso, quindi si valuta solo `(j)` → m = 4, e il secondo `i++` non viene eseguito. → **m=4 i=3**.
7. `i = 7`: il confronto usa 7 (i diventa 8). 7 > 4 è vero, quindi si valuta il secondo `(i++)`, che vale 8, e i diventa 9. → **m=8 i=9**. Il "massimo" è 8, un numero che non era nemmeno tra i dati.
8. `massimo(i++, j)` con i = 7: l'argomento `i++` viene valutato **una volta** prima della chiamata. Passa 7 e i diventa 8. → **m=7 i=8**.

Morale: le parentesi risolvono i casi 1–5. Per i casi 6–7 non bastano: o non passi `i++` alla macro, o usi una funzione. Nessun warning del compilatore ti avvisa. Prova `cc -E es05_macro_cosa_stampa.c | tail -30` per vedere il testo espanso.
Vedi `soluzioni/es05_macro_cosa_stampa.c`.
</details>

### es06 — Inverti un vettore "sul posto"  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 3, §3.20 (passaggio per indirizzo) e §4.12 (accesso agli elementi di un vettore) + LEZ 14, esercizio sui "modi di scambiare" (qui applicato agli elementi di un vettore).
**Testo:** completa `scambia(int *x, int *y)` e `inverti(int v[], int n)`, che inverte il vettore usando `scambia(&v[i], &v[…])` e senza un secondo vettore.
```text
input:  6
        1 2 3 4 5 6
output: invertito: 6 5 4 3 2 1
```
**File:** `es06_inverti.c` · **Test:** `make test T=08 E=es06`

<details><summary>💡 Suggerimento</summary>
Il "gemello" di `v[i]` è `v[n - 1 - i]`. Fermati a metà: se arrivi fino in fondo, ogni coppia viene scambiata due volte e il vettore torna com'era.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. `&v[i]` è l'indirizzo dell'elemento i. Lo passi a `scambia`, che lo modifica nel vettore originale.
2. Coppie da scambiare: (0, n−1), (1, n−2), … Il ciclo è `for (i = 0; i < n / 2; i++)`.
3. Con n dispari (5) la divisione intera `n / 2` = 2 fa due scambi, e l'elemento centrale `v[2]` resta fermo, come deve. Con n = 1 il ciclo non parte.
4. `inverti` combina i due concetti della cartella: il vettore passato per indirizzo e il puntatore a un singolo elemento.

| i | coppia scambiata | vettore (n = 6) |
|---|---|---|
| – | – | 1 2 3 4 5 6 |
| 0 | v[0] ↔ v[5] | 6 2 3 4 5 1 |
| 1 | v[1] ↔ v[4] | 6 5 3 4 2 1 |
| 2 | v[2] ↔ v[3] | 6 5 4 3 2 1 |

Vedi `soluzioni/es06_inverti.c`.
</details>

### es07 — Trova e correggi l'errore: statistiche di un appello  ·  Tipo esame
**Fonte:** Ispirato a: Trascrizione 3.2 (macro `MOLTIPLICA` senza parentesi), Trascrizione 3.1 (shadowing di una globale) e Appunti Unità 3, §3.19 (passaggio per valore).
**Testo:** il programma legge n voti, dove 0 indica un assente, e stampa presenti, promossi (voto ≥ 18), voto massimo e media dei presenti. Ci sono **3 errori**: uno in una macro, uno di scope e uno di passaggio dei parametri.
```text
input:  6
        25 0 30 15 0 29
atteso: presenti: 4
        promossi: 3
        voto massimo: 30
        media dei presenti: 24.75
```
**File:** `es07_trova_errore.c` · **Test:** `make test T=08 E=es07`

<details><summary>💡 Suggerimento</summary>
Espandi a mano `MEDIA(somma, n - assenti)`. Chiediti quale `promossi` incrementa davvero `conta_promossi`. Chiediti dove finisce il valore che `trova_max` scrive in `max`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Lo starter con il primo input stampa `promossi: 0`, `voto massimo: 0` e `media dei presenti: 14.50`. Tre sintomi, tre errori.
1. **Macro.** `#define MEDIA(tot, n) (double)tot / n` con `MEDIA(somma, n - assenti)` diventa `(double)somma / n - assenti` = 99/6 − 2 = 14.50. Correzione: `#define MEDIA(tot, n) ((double)(tot) / (n))` → 99/4 = 24.75.
2. **Scope (shadowing).** In `conta_promossi` c'è `int promossi = 0;`: è una **nuova** locale che fa ombra alla globale. Il conteggio va nella locale, che muore al `return`, e la globale resta 0. Correzione: togli `int`, cioè scrivi `promossi = 0;`, così azzeri e incrementi la globale.
3. **Passaggio dei parametri.** `void trova_max(…, int max)` riceve una **copia** di `m`. Il massimo viene calcolato nella copia, e `m` del main resta 0. Correzione: `int *max` nel prototipo e nella definizione, `*max` nel corpo, `trova_max(v, n, &m)` nella chiamata.
4. Perché non correggere il punto 2 restituendo il conteggio con `return`? Si potrebbe, ed è anzi più pulito (meno globali). Qui l'esercizio chiede di trovare lo shadowing, non di ridisegnare il programma.
5. Il caso "tutti assenti" (`0 0`) non divide per zero, perché il main lo controlla prima di usare `MEDIA`.

Vedi `soluzioni/es07_trova_errore.c` (i commenti `BUG 1/2/3` mostrano la riga originale).
</details>

### es08 — Equazione di secondo grado come nell'E-tivity 3.6  ·  Tipo esame
**Fonte:** Ispirato a: E-tivity 3.6 ParametriePuntatoribis e 2ParametriePuntatoriTRIS (prototipi `coefficienti(float *, float *, float *)`, `discriminante`, `radici`; main con `float a, b, c` e `double d`).
**Testo:** completa le tre funzioni. `coefficienti` legge con `scanf` dentro la funzione e scrive nelle variabili del main. `discriminante` restituisce un `double`. `radici` restituisce quante radici reali ci sono e le scrive in `*x1` e `*x2`. Il main stampa con `%.2f`.
```text
input:  1 -5 6          input:  1 -4 4                   input:  1 1 -1
output: delta = 1.00    output: delta = 0.00             output: delta = 5.00
        radici reali: 2         radici reali: 1 (coincidenti)    radici reali: 2
        x1 = 3.00               x1 = x2 = 2.00                   x1 = 0.62
        x2 = 2.00                                                x2 = -1.62
```
**File:** `es08_equazione.c` · **Test:** `make test T=08 E=es08`

<details><summary>💡 Suggerimento</summary>
In `coefficienti`, `c1` è **già** un indirizzo: in `scanf` va passato così com'è, senza `&`. `scanf` restituisce quanti valori ha letto, quindi confrontalo con 3. In `radici` scrivi i risultati con `*x1 = …`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Lettura.** Il main chiama `coefficienti(&a, &b, &c)`. Nella funzione, `scanf("%f %f %f", c1, c2, c3)` scrive direttamente in `a`, `b` e `c`, come spiega il prof ("li posso mettere nella scanf senza mettergli le commerciali perché ho passato già il puntatore"). `return scanf(…) == 3;` vale 1 se la lettura è riuscita. Con l'input `uno due tre` restituisce 0, e il main stampa `input non valido`.
2. **a = 0.** Il main si ferma, come nell'E-tivity, perché la formula dividerebbe per 0.
3. **Discriminante.** I parametri sono passati per valore: la funzione deve solo leggerli. `return (double)c2 * c2 - 4.0 * c1 * c3;`. Il cast porta il calcolo in `double` e il risultato è più preciso.
4. **Radici.** Tre casi. Se `d > 0`, `*x1 = (-b + sqrt(d)) / (2.0 * a)`, `*x2` con il segno meno, `return 2`. Se `d == 0`, `*x1 = *x2 = -b / (2.0 * a)`, `return 1`. Altrimenti `return 0`. È la miglioria che il prof stesso suggerisce: niente `printf` dentro `radici`, i valori escono attraverso i puntatori e il main stampa.
5. **Confronto con 07/es08.** Lì ogni funzione restituiva un solo valore e il main chiedeva le radici una alla volta. Qui una sola chiamata produce un conteggio (con `return`) e due radici (con i puntatori).

Simulazione con `1 1 -1`: d = 1 + 4 = 5; √5 ≈ 2.236; x1 = (−1 + 2.236)/2 ≈ 0.618 → `0.62`; x2 = (−1 − 2.236)/2 ≈ −1.618 → `-1.62`.
Vedi `soluzioni/es08_equazione.c`.
</details>

## Prompt pronti per questo argomento
1. "Interrogami con 6 domande su scope di blocco/funzione/file, shadowing, extern, passaggio per valore e per indirizzo in C, una alla volta. Aspetta la mia risposta e correggimi spiegando il perché."
2. "Ho scritto questa soluzione per es08 di 08-parametri-macro (equazione con float *): [incolla codice]. Dimmi se è corretta e perché, senza riscrivermela tutta."
3. "Generami 4 macro con parametri 'trappola' (precedenza e argomenti con effetti collaterali) e per ognuna una riga che la usa. Io scrivo l'espansione e il risultato; tu correggi solo dopo."
4. "Generami 3 esercizi nuovi tipo es07 di 08-parametri-macro: un programma breve con un bug di shadowing, uno di macro senza parentesi e uno di parametro passato per valore invece che per indirizzo."
5. "Spiegami con un disegno della memoria (stack del main e della funzione) cosa succede in `scambia(&a, &b)` rispetto a `scambia(a, b)`."

## Riepilogo
- Lo **scope** dipende da dove è *scritta* la dichiarazione (blocco, funzione o file). Un nome interno fa **ombra** a quello esterno con lo stesso nome.
- Il C passa sempre **copie**. Per modificare una variabile del chiamante si passa il suo **indirizzo** (`&a`) e si scrive con `*p`. I vettori arrivano già come indirizzo, quindi la funzione li può modificare, ma la lunghezza va passata a parte.
- Le **macro** sono sostituzioni di testo fatte dal preprocessore, non chiamate. Servono le parentesi intorno a ogni parametro e intorno a tutto, e non bisogna mai passare argomenti come `i++`.

## Glossario
- **scope** — zona del codice in cui un nome è visibile.
- **scope di blocco** — visibilità limitata alle `{ }` in cui la variabile è dichiarata.
- **variabile globale** — dichiarata fuori da ogni funzione; visibile in tutto il file e viva per tutto il programma.
- **variabile locale** — dichiarata in una funzione o in un blocco; vive sullo stack solo durante l'esecuzione.
- **lifetime (durata)** — periodo in cui una variabile esiste in memoria.
- **shadowing** — un nome interno nasconde un nome esterno uguale.
- **scope statico** — la visibilità si decide leggendo il testo del programma, non seguendo le chiamate.
- **`extern`** — dichiara una globale senza allocarla: "è definita altrove".
- **definizione (di una globale)** — dichiarazione più allocazione della memoria; si fa una volta sola.
- **parametro formale / attuale** — variabile dell'intestazione / valore passato nella chiamata.
- **albero di chiamata** — schema di chi chiama chi, con `main` come radice.
- **indirizzo** — posizione di una variabile in memoria; si ottiene con `&`.
- **puntatore** — variabile che contiene un indirizzo (`int *p`).
- **dereferenziazione** — `*p`: accedere alla variabile che si trova all'indirizzo p.
- **passaggio per indirizzo** — passare `&x` così che la funzione possa modificare x (in C è simulato copiando l'indirizzo).
- **parametro di uscita** — puntatore usato per far uscire un risultato dalla funzione.
- **`const`** — promessa, controllata dal compilatore, di non modificare un dato.
- **preprocessore** — programma che elabora le direttive `#` (sostituisce il testo) prima della compilazione.
- **macro / macroespansione** — `#define` con o senza parametri; sostituzione testuale del suo testo.
- **effetto collaterale** — modifica di stato durante una valutazione (es. `i++`, scrivere una globale).
- **compilazione condizionale** — `#ifdef`/`#ifndef`: includere o escludere codice in base a una macro (non trattata dal prof).
- **AddressSanitizer** — strumento attivato da `make test` che ferma il programma se legge o scrive fuori dalla memoria consentita.
