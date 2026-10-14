# 07 — Funzioni, call and return e stack

> Lezioni di riferimento: trascrizioni 3.0 (Introduzione Blocco 3) e 3.1 (Funzioni), Appunti Unità 3 (cap. 1 "Funzioni e Sottoprogrammi", cap. 2 §2.6–2.11 "Parametri", cap. 3 "Call and Return"), LEZ 13 (Funzioni), LEZ 15 (Call and return, stack e record di attivazione).
> **Nota sulle fonti:** la trascrizione della videolezione 3.3 (call and return) **non è disponibile**. Per stack e record di attivazione la fonte è il cap. 3 degli Appunti Unità 3 più la LEZ 15.
> Tempo stimato: ~4 ore.

## Teoria flash

**Sottoprogramma.** Un pezzo di programma con un nome, che riceve dei dati, fa un lavoro e produce un risultato. Il prof lo spiega con l'equazione di secondo grado: il problema "trova le radici" si spezza in sottoproblemi più piccoli, cioè "leggi i coefficienti", "calcola il discriminante" e "calcola le radici". Ogni sottoproblema diventa una funzione. Questo modo di lavorare si chiama **progettazione top-down** (dall'alto verso il basso): parti dal problema intero e lo dividi in pezzi sempre più piccoli.

**Procedura e funzione.** In teoria una *procedura* fa qualcosa ma non restituisce un valore (per esempio stampa), mentre una *funzione* restituisce un valore, come una funzione matematica. In C esiste solo la funzione. Una "procedura" in C è una funzione con tipo di ritorno `void`, cioè "nessun valore".

**Prototipo, definizione e uso.** Sono tre momenti diversi.
```c
int somma(int a, int b);          /* PROTOTIPO (dichiarazione): finisce con ';' */

int main(void) {
    int r = somma(2, 3);          /* USO (chiamata, o invocazione) */
    return 0;
}

int somma(int a, int b) {         /* DEFINIZIONE: intestazione + corpo */
    return a + b;
}
```
- Il **prototipo** dice al compilatore il tipo di ritorno, il nome e i tipi dei parametri. È come il menù di un ristorante: dice cosa puoi ordinare, non come si cucina.
- La **definizione** è l'**intestazione** (la prima riga, uguale al prototipo ma senza `;`) più il **corpo** tra `{ }`.
- Il compilatore legge il file dall'alto in basso. Se trova una chiamata prima di aver visto il prototipo o la definizione, non sa che tipi usare. Per questo i prototipi si mettono in cima al file. In C non si può definire una funzione dentro un'altra funzione.

**`void`.** Ha due usi. `void stampa(int n)` vuol dire "non restituisce nulla". `int leggi(void)` vuol dire "non riceve parametri".

**Parametri formali e attuali.** I **parametri formali** sono le variabili scritte nell'intestazione (`a` e `b` in `int somma(int a, int b)`). I **parametri attuali**, chiamati anche **argomenti**, sono i valori che passi nella chiamata (`2` e `3` in `somma(2, 3)`). Vengono abbinati in ordine: il primo valore va al primo parametro, e così via.

**Passaggio per valore.** In C ogni parametro formale riceve una **copia** del valore. È come dare a qualcuno una fotocopia: se ci scrive sopra, il tuo originale non cambia.
```c
void raddoppia(int x) { x = x * 2; }   /* raddoppia la COPIA */
int  a = 5;  raddoppia(a);             /* a vale ancora 5 */
int  doppio(int x) { return x * 2; }   /* versione giusta: restituisco il risultato */
a = doppio(a);                         /* ora a vale 10 */
```
Per questo una funzione `scambia(a, b)` scritta "per valore" **non può** scambiare le variabili del chiamante. La soluzione sono i puntatori: li anticipiamo in 08 e li approfondiamo in 09.

**`return`.** Fa due cose. Calcola il valore da restituire e fa un **salto** che riporta il controllo al chiamante, cioè alla funzione che aveva fatto la chiamata. Dopo un `return` le righe successive della funzione non vengono eseguite. In una funzione `void` puoi scrivere `return;` senza valore, oppure ometterlo.

**Variabili locali e globali, shadowing.** Una variabile dichiarata dentro una funzione o un blocco è **locale**: esiste solo lì e solo mentre quel codice è in esecuzione. Una variabile dichiarata fuori da tutte le funzioni è **globale**: tutte le funzioni del file la vedono. Se una locale ha lo stesso nome di una globale, la locale "fa ombra" alla globale. Questo effetto si chiama **shadowing**. Lo approfondiamo in 08.

**Call and return, stack e record di attivazione.** Una chiamata è un salto di andata verso il corpo della funzione. Il `return` è il salto di ritorno all'istruzione che segue la chiamata. Per tornare al punto giusto, il programma deve ricordare l'**indirizzo di ritorno**, cioè il punto da cui riprendere. Queste informazioni stanno nello **stack** (pila), una zona di memoria che funziona **LIFO** (Last In, First Out: l'ultimo che entra è il primo che esce), come una pila di piatti. A ogni chiamata viene messo in cima un **record di attivazione** (una "scheda" della chiamata) che contiene:
- l'indirizzo di ritorno;
- i parametri, cioè le copie dei valori passati;
- le variabili locali;
- lo spazio per il valore restituito.

Quando la funzione termina, la scheda viene tolta dalla cima e le sue variabili locali spariscono. Per questo una locale non ricorda il valore che aveva nella chiamata precedente. Le globali invece stanno nel **segmento dati**, una zona fissa che esiste per tutto il programma. Le istruzioni del programma stanno nel **segmento codice**.

Esempio degli Appunti (§3.9): `main` chiama `cubo(2)`, e `cubo` chiama `quadrato(2)`. La figura mostra lo stack mentre `quadrato` è in esecuzione.
```text
   cima ->  | quadrato: y=2, ritorno -> dentro cubo  |   <- tolto per primo
            | cubo:     y=2, q=?, ritorno -> main    |
            | main:     x=2, r=?                     |
   segmento dati: (globali)      segmento codice: istruzioni
```

**Contraddizioni e imprecisioni nelle fonti**
- Trascrizione 3.1: "il compilatore assume che sia int e genera un **warning**" se usi una funzione prima di dichiararla. Questa regola vale per il vecchio C89. Dal C99 in poi la dichiarazione implicita **non esiste più**: gcc 13 dà ancora un warning, mentre clang su macOS (e gcc dalla versione 14) dà un **errore**. Gli Appunti (§1.10) dicono "warning o errori": sono più precisi.
- Trascrizione 3.1: "basta anche mettere aperta chiusa parentesi piuttosto che indicare il void". Non è la stessa cosa. In C11 `int f()` vuol dire "parametri non specificati", mentre `int f(void)` vuol dire "nessun parametro" e permette al compilatore di controllare le chiamate. Gli Appunti (§1.7) consigliano `void`, ed è la scelta giusta.
- Trascrizione 3.1, sul `return` in una funzione void: "può essere omesso… sarebbe sempre meglio ometterlo". La frase è contorta. Il senso è che in una `void` il `return;` finale è facoltativo.
- Errori della trascrizione automatica: "Marco Nisetti" = Marco Anisetti, "fu"/"foo" = `foo`, "programma CI" = programma C.
- Lo stack negli Appunti (cap. 3) ha tre zone: codice, dati e stack. La LEZ 15 aggiunge lo **heap**, la zona della memoria dinamica, che il corso tratta nel blocco 4.

**Errori tipici** (messaggi veri di `gcc 13 -std=c11 -Wall -Wextra -pedantic`)
1. Usare una funzione prima di dichiararla: `warning: implicit declaration of function 'stampa' [-Wimplicit-function-declaration]` e poi `warning: conflicting types for 'stampa'`. Su macOS con clang diventa un errore: `call to undeclared function 'stampa'; ISO C99 and later do not support implicit function declarations`. Rimedio: metti il prototipo in cima al file.
2. Dimenticare un `return` in un ramo: `warning: control reaches end of non-void function [-Wreturn-type]`. Se il programma usa quel valore, il risultato è spazzatura.
3. Passare un numero sbagliato di argomenti: `error: too few arguments to function 'somma'`.
4. Usare il "valore" di una funzione void, per esempio `int x = saluta();`: `error: void value not ignored as it ought to be`.
5. Mettere `;` dopo l'intestazione della definizione: `error: expected identifier or '(' before '{' token`.
6. Credere che modificare un parametro modifichi la variabile del chiamante. Il compilatore **non dice nulla**: vedi es06.

## Esercizi

### es01 — Massimo di due e di tre numeri  ·  Base
**Fonte:** Ispirato a: Appunti Unità 3, §2.11 "Esempio di funzioni riutilizzabili" (`cubo` che riusa `quadrato`).
**Testo:** completa `max2(a, b)`, che restituisce il maggiore dei due, e `max3(a, b, c)`, che deve **chiamare `max2`** invece di riscrivere i confronti. Il main legge tre interi.
```text
input:  3 7 5
output: max2(3, 7) = 7
        max3(3, 7, 5) = 7
```
**File:** `es01_massimo.c` · **Test:** `make test T=07 E=es01`

<details><summary>💡 Suggerimento</summary>
Il massimo di tre numeri è il massimo tra "il massimo dei primi due" e il terzo. Una chiamata può stare dentro un'altra chiamata.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. `max2` deve restituire un valore, quindi usa `return`. Se `a > b` restituisci `a`. Altrimenti l'esecuzione arriva alla riga dopo, e lì restituisci `b`. Non serve `else`, perché il primo `return` è già uscito dalla funzione.
2. `max3` riusa `max2`: `return max2(max2(a, b), c);`. Prima viene valutata la chiamata interna. Il suo risultato diventa il primo parametro attuale della chiamata esterna.
3. Perché non riscrivere i confronti? Perché se un giorno `max2` cambia (o ha un bug), lo correggi in un solo punto. È il **riuso** di cui parla il prof.
4. I prototipi in cima servono perché `main` usa `max2` e `max3` **prima** di trovarne la definizione nel file.

```c
int max2(int a, int b) { if (a > b) return a; return b; }
int max3(int a, int b, int c) { return max2(max2(a, b), c); }
```
Simulazione con `max3(-2, -9, -4)`: chiamata interna `max2(-2, -9)` → -2; poi chiamata esterna `max2(-2, -4)` → -2.
Vedi `soluzioni/es01_massimo.c`.
</details>

### es02 — Potenza con un ciclo  ·  Base
**Fonte:** Ispirato a: Appunti Unità 3, §1.12 "Funzioni con parametri" (`quadrato(x)` generalizzato a un esponente qualsiasi).
**Testo:** completa `potenza(base, esp)` con un `for`, senza usare `pow()`. Vale `esp >= 0`: il main rifiuta gli esponenti negativi.
```text
input:  2 10        output: potenza(2, 10) = 1024
input:  5 0         output: potenza(5, 0) = 1
```
**File:** `es02_potenza.c` · **Test:** `make test T=07 E=es02`

<details><summary>💡 Suggerimento</summary>
Ti serve una variabile "accumulatore" che a ogni giro viene moltiplicata per `base`. Pensa bene al suo valore iniziale: con `esp = 0` il ciclo non gira mai.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. Il risultato parte da **1**, l'elemento neutro della moltiplicazione. Se partisse da 0, ogni prodotto darebbe 0.
2. Un ciclo che gira `esp` volte esegue `risultato = risultato * base`.
3. Con `esp = 0` il ciclo non parte e la funzione restituisce 1, cioè x⁰ = 1.
4. Il controllo `esp < 0` sta nel main. Così la funzione fa una cosa sola, e fa il calcolo soltanto quando l'input ha senso.

| i | risultato (base = -3) |
|---|---|
| inizio | 1 |
| 0 | -3 |
| 1 | 9 |
| 2 | -27 |

Vedi `soluzioni/es02_potenza.c`.
</details>

### es03 — Fattoriale iterativo  ·  Base
**Fonte:** Ispirato a: Appunti Unità 3, §1.4 "Sottoprogrammi" (una funzione = nome + parametri + corpo + valore di ritorno). Questa è la versione iterativa (con un ciclo); quella ricorsiva arriva con la lezione 4.2.
**Testo:** completa `fattoriale(n)`, che restituisce un `long long` (un intero "lungo": su macOS arm64 e Linux x86-64 occupa 8 byte e arriva a circa 9,2·10¹⁸). Il main accetta solo n tra 0 e 20.
```text
input:  5           output: 5! = 120
input:  20          output: 20! = 2432902008176640000
input:  21          output: n fuori intervallo (0..20)
```
**File:** `es03_fattoriale.c` · **Test:** `make test T=07 E=es03`

<details><summary>💡 Suggerimento</summary>
È come la potenza: c'è un accumulatore che parte da 1, ma a ogni giro moltiplichi per il contatore `i` invece che per un valore fisso.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. `long long f = 1;`: parte da 1, così 0! e 1! valgono già 1 senza casi speciali.
2. `for (i = 2; i <= n; i++) f = f * i;`. Partire da 2 evita un'inutile moltiplicazione per 1.
3. Perché il limite 20? Perché 21! ≈ 5,1·10¹⁹ supera il massimo di un `long long`. L'**overflow** (cioè il superamento del valore massimo) di un intero con segno è *comportamento indefinito*: il C non garantisce nulla sul risultato. Per questo il main controlla l'input **prima** di chiamare la funzione.
4. In `printf` il segnaposto per un `long long` è `%lld`. Con `%d` otterresti un warning e un numero sbagliato.

Vedi `soluzioni/es03_fattoriale.c`.
</details>

### es04 — Numeri primi con una funzione "sì/no"  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 3, §1.11 "L'istruzione return" (il return che fa uscire subito dalla funzione) combinato con i cicli del blocco 2.
**Testo:** completa `e_primo(n)`, che restituisce 1 se n è primo e 0 altrimenti. Il main la chiama per ogni k da 2 a N.
```text
input:  20
output: primi fino a 20: 2 3 5 7 11 13 17 19
        totale: 8
```
**File:** `es04_primi.c` · **Test:** `make test T=07 E=es04`

<details><summary>💡 Suggerimento</summary>
Appena trovi un divisore puoi fare `return 0`, anche dentro il ciclo. Se il ciclo finisce senza averne trovati, il numero è primo. Non serve provare divisori più grandi della radice di n (condizione `d * d <= n`).
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. I numeri minori di 2 non sono primi: `if (n < 2) return 0;`.
2. Prova i divisori `d = 2, 3, …` finché `d * d <= n`. Se n = d·e con d ≤ e, allora d·d ≤ n: un divisore "piccolo" esiste sempre, se n non è primo.
3. `if (n % d == 0) return 0;`. Il `return` esce **subito** da `e_primo`, anche da dentro il `for`: è un salto, come spiega il prof.
4. Se il ciclo termina, nessun divisore funziona: `return 1;`.
5. Nel main `if (e_primo(k))` usa direttamente il valore restituito come condizione: 0 = falso, diverso da 0 = vero.

Simulazione di `e_primo(15)`: d = 2 → 15 % 2 = 1; d = 3 → 15 % 3 = 0 → `return 0`.
Vedi `soluzioni/es04_primi.c`.
</details>

### es05 — MCD come funzione, e mcm che la riusa  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 2.1 E-tivity (MCD con il metodo di Euclide e i goto) + Appunti Unità 3, §2.10 "Struttura delle chiamate" (una funzione che ne chiama un'altra).
**Testo:** completa `mcd(a, b)` con Euclide usando un `while` e `mcm(a, b) = a / mcd(a, b) * b`. Con uno zero: mcd(a, 0) = a e mcm = 0.
```text
input:  12 18       output: mcd(12, 18) = 6
                            mcm(12, 18) = 36
```
**File:** `es05_mcd_mcm.c` · **Test:** `make test T=07 E=es05`

<details><summary>💡 Suggerimento</summary>
Euclide dice che mcd(a, b) = mcd(b, a % b). Ripeti finché il secondo numero diventa 0: a quel punto il primo è il MCD. Metti il controllo `b != 0` nella condizione del while, così non dividi mai per zero.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. Il prof scriveva: `r = x % y; se r == 0 il risultato è y; altrimenti x = y, y = r` e torna su. Il suo schema richiede y ≠ 0, perché `x % 0` è una divisione per zero (comportamento indefinito). Con `while (b != 0)` il caso b = 0 è gestito gratis: il ciclo non parte e la funzione restituisce a.
2. Dentro `mcd` modifico `a` e `b`. Va bene così: sono **copie** (passaggio per valore), e le variabili del main restano intatte. Lo vedi dall'output, che stampa ancora 12 e 18.
3. `mcm` chiama `mcd`: nello stack ci sono main → mcm → mcd. Prima dividi e poi moltiplichi (`a / mcd * b`), così il numero intermedio resta piccolo.

| giro | a | b | r |
|---|---|---|---|
| inizio | 12 | 18 | – |
| 1 | 18 | 12 | 12 |
| 2 | 12 | 6 | 6 |
| 3 | 6 | 0 | 0 → esce, restituisce 6 |

Vedi `soluzioni/es05_mcd_mcm.c`.
</details>

### es06 — Trova e correggi l'errore: la funzione che "non fa niente"  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 3, §3.19 "Passaggio per valore" e §3.22 "Il modello del linguaggio C" (si può modificare il chiamante solo passando l'indirizzo).
**Testo:** il programma legge a e b, dovrebbe ordinarli (a = minore) e stampare il doppio del minore. Compila **senza avvisi** ma stampa valori sbagliati. Trova i 2 errori e correggili **senza puntatori**.
```text
input:  5 3
atteso: prima: a=5 b=3
        dopo: a=3 b=5
        doppio del minimo: 6
```
**File:** `es06_trova_errore.c` · **Test:** `make test T=07 E=es06`

<details><summary>💡 Suggerimento</summary>
Cosa ricevono davvero `scambia` e `raddoppia`: le variabili del main o delle copie? Una funzione può restituire **un** valore con `return`. Allora fatti restituire il minimo, il massimo e il doppio, e fai le assegnazioni nel main.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Errore 1, `scambia(a, b)`.** Nel record di attivazione di `scambia` ci sono `x` e `y`, che sono **copie** di a e b. Lo scambio avviene tra le copie. Al `return` il record viene tolto dallo stack e le copie spariscono, quindi a e b del main non cambiano.
2. **Errore 2, `raddoppia(a)`.** Stesso problema. In più, il risultato non esce dalla funzione, perché è `void`.
3. **Correzione per raddoppia:** la funzione diventa `int raddoppia(int x) { return x * 2; }` e il main scrive `a = raddoppia(a);`. Il valore esce con `return` ed è il main ad assegnarlo alla **sua** variabile.
4. **Correzione per scambia:** `return` restituisce un solo valore, quindi non basta per uno scambio. Si aggira il problema così: `m = minimo(a, b); M = massimo(a, b); a = m; b = M;`. Anche uno scambio scritto direttamente nel main (`int t = a; a = b; b = t;`) va bene.
5. Una **vera** `scambia` riutilizzabile richiede di passare gli **indirizzi** delle variabili: `void scambia(int *x, int *y)`. La scrivi in 08 (es02) e la approfondisci con i puntatori nella cartella 09.
6. Perché il compilatore non avvisa? Perché il codice è legale: `x = y` usa y, e `int t = x` usa x. L'errore è di **logica**, non di sintassi.

Vedi `soluzioni/es06_trova_errore.c`.
</details>

### es07 — Cosa stampa? Chiamate annidate, locali omonime e stack  ·  Tipo esame
**Fonte:** Ispirato a: Trascrizione 3.1 (esempio della globale `n` modificata da `foo` e shadowing) + Appunti Unità 3, §3.7–3.9 (record di attivazione, esempio `main → cubo → quadrato`).
**Testo:** senza eseguirlo, scrivi le 8 righe stampate da `es07_stack_cosa_stampa.c`. Disegna lo stack nel momento in cui `g` è in esecuzione dentro `f`. Poi lancia il test e confronta.

La mia previsione:
```text
main: x=? y=?
...
```
**File:** `es07_stack_cosa_stampa.c` · **Test:** `make test T=07 E=es07`

<details><summary>💡 Suggerimento</summary>
Ci sono **quattro** variabili diverse di nome `x`: la globale, la locale di `f`, il parametro di `g` e quella del blocco `{ }` del main. Per ogni `printf`, chiediti quale `x` è visibile in quel punto. Ricorda anche che ogni parametro è una copia.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output:
```text
main: x=1 y=3
f prima: x=5 y=3
g: x=6 y=50
f dopo: x=5 y=56
main: x=1 y=3 r=61
blocco: x=100
g: x=2 y=10
fine: x=1 r=12
```
1. `main`: non dichiara una `x`, quindi usa la globale (1). La sua `y` vale 3. → `main: x=1 y=3`.
2. `r = f(y)`: viene creato il record di `f`. Il parametro `y` riceve una **copia** di 3. La locale `x = y + 2 = 5` fa ombra alla globale. → `f prima: x=5 y=3`.
3. `y = g(x)`: viene creato il record di `g`. Il parametro `x` riceve una copia di 5, poi `y = 5*10 = 50` e `x = 5+1 = 6` (cambia solo la copia di `g`). → `g: x=6 y=50`. `g` restituisce 50 + 6 = 56 e il suo record viene tolto.
4. Si torna in `f`: la **sua** `x` è ancora 5, perché `g` ha modificato una copia. La **sua** `y` ora vale 56. → `f dopo: x=5 y=56`. `f` restituisce 5 + 56 = 61.
5. Si torna in `main`: la `y` di main è ancora 3, perché `f` aveva una copia. La globale non è mai stata toccata. → `main: x=1 y=3 r=61`.
6. Nel blocco `{ int x = 100; }` c'è una nuova `x` che fa ombra alla globale. → `blocco: x=100`. Alla `}` questa variabile smette di esistere.
7. `r = g(x)`: qui `x` è di nuovo la globale, e `g` riceve una copia di 1: `y = 10`, `x = 2`. → `g: x=2 y=10`. Restituisce 12.
8. → `fine: x=1 r=12`.

Stack durante il punto 3 (cresce verso l'alto; ogni riquadro è un record di attivazione):
```text
  cima -> +-----------------------------------------+
          | g    parametro x: 5 -> 6                |
          |      locale    y: 50                    |
          |      ritorno: in f, a "y = g(x)"        |
          +-----------------------------------------+
          | f    parametro y: 3                     |
          |      locale    x: 5                     |
          |      ritorno: in main, a "r = f(y)"     |
          +-----------------------------------------+
          | main locale y: 3,  r: (non ancora)      |
          +-----------------------------------------+
  segmento dati (fuori dallo stack):  x globale = 1
```
Quando `g` fa `return`, il suo riquadro viene tolto (pop) ed `f` riprende da dove era rimasta. Questa è la logica LIFO.
Vedi `soluzioni/es07_stack_cosa_stampa.c`.
</details>

### es08 — Equazione di secondo grado scomposta in funzioni  ·  Tipo esame
**Fonte:** Ispirato a: Trascrizione 3.1 (esempio delle radici reali scomposto in "calcolo discriminante" e "calcolo radici") e alla scomposizione dell'E-tivity 3.6 (qui ancora senza puntatori).
**Testo:** completa `discriminante(a, b, c)`, `numero_radici(delta)` (2, 1 o 0) e `radice(a, b, delta, segno)`, con `segno` uguale a +1 o -1. Il main legge a b c con `%lf` e stampa con `%.2f`. Se a = 0 non è un'equazione di secondo grado.
```text
input:  1 -5 6          input:  1 2 1                    input: 1 0 4
output: delta = 1.00    output: delta = 0.00             output: delta = -16.00
        radici reali: 2         radici reali: 1 (coincidenti)    nessuna radice reale
        x1 = 3.00               x1 = x2 = -1.00
        x2 = 2.00
```
**File:** `es08_equazione.c` · **Test:** `make test T=07 E=es08`

<details><summary>💡 Suggerimento</summary>
Ogni funzione restituisce **un** solo valore. Le due radici differiscono solo per il segno davanti alla radice quadrata, quindi basta una funzione con il parametro `segno`. `sqrt` sta in `<math.h>`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Scomposizione** (top-down, come nel diagramma del prof): leggi → discriminante → quante radici → calcola. Ogni rettangolo del diagramma diventa una funzione con ingressi e uscita chiari.
2. `discriminante` riceve a, b, c e restituisce `b*b - 4*a*c`. È una funzione "pura": non stampa e non legge, calcola e basta.
3. `numero_radici` trasforma un `double` in una decisione (2/1/0). Il confronto `delta == 0` tra `double` è sicuro **solo** se il calcolo è esatto. Con coefficienti interi lo è; con numeri come 0.1 potresti avere errori di arrotondamento.
4. `radice` calcola `(-b + segno*sqrt(delta)) / (2*a)`. Una sola funzione al posto di due quasi uguali.
5. Le stampe stanno nel main. Il prof stesso nell'E-tivity dice che "sarebbe più elegante mantenere le stampe nel main e far ritornare i valori alle funzioni".
6. **Limite di questa versione:** una funzione restituisce un valore solo, quindi le radici si chiedono una alla volta. In 08 (es08) userai i puntatori per leggere i coefficienti dentro una funzione, come fa il prof.

Simulazione con `2 -3 -2`: delta = 9 + 16 = 25 → 2 radici; x1 = (3 + 5)/4 = 2.00; x2 = (3 − 5)/4 = −0.50.
Vedi `soluzioni/es08_equazione.c`.
</details>

## Prompt pronti per questo argomento
1. "Interrogami con 6 domande su prototipo, definizione, parametri formali/attuali, passaggio per valore e record di attivazione in C, una alla volta. Aspetta la mia risposta prima di passare alla successiva e correggimi spiegando il perché."
2. "Ho scritto questa soluzione per es05 di 07-funzioni-stack (MCD ed mcm): [incolla codice]. Dimmi se è corretta e perché, senza riscrivermela tutta."
3. "Generami 3 esercizi nuovi tipo es07 di 07-funzioni-stack ('Cosa stampa?' con funzioni annidate, parametri e locali con lo stesso nome della globale). Dammi solo il codice; la soluzione con il disegno dello stack me la dai quando te la chiedo."
4. "Disegnami passo passo lo stack (push e pop dei record di attivazione) per questo programma: [incolla codice]. Per ogni record indica parametri, locali e indirizzo di ritorno."
5. "Dammi un problema tipo esame da scomporre in 3-4 funzioni (come l'equazione di secondo grado del prof): prima chiedimi io come lo scomporrei, poi commenta la mia scomposizione."

## Riepilogo
- Una funzione si **dichiara** (prototipo, con `;`), si **definisce** (intestazione + corpo) e si **usa** (chiamata). I prototipi vanno in cima perché il compilatore legge dall'alto.
- I parametri passano **per valore**: la funzione lavora su copie. Per restituire un risultato si usa `return`, e il chiamante lo assegna.
- Ogni chiamata mette sullo **stack** un **record di attivazione** (indirizzo di ritorno, parametri, locali) che viene tolto al `return`. Per questo le locali "muoiono", mentre le globali, nel segmento dati, restano.
- Un problema grande si **scompone** in sottoprogrammi (top-down), come l'equazione di secondo grado del prof.

## Glossario
- **sottoprogramma** — pezzo di codice con un nome, che riceve dati e produce un risultato o un effetto.
- **procedura** — sottoprogramma che non restituisce valori; in C è una funzione `void`.
- **prototipo** — dichiarazione di una funzione (tipo di ritorno, nome, tipi dei parametri) che termina con `;`.
- **definizione** — intestazione più corpo: dice cosa fa davvero la funzione.
- **intestazione** — prima riga della definizione, uguale al prototipo ma senza `;`.
- **corpo** — istruzioni della funzione racchiuse tra `{ }`.
- **`void`** — tipo che significa "nessun valore": nessun ritorno o nessun parametro.
- **parametro formale** — variabile dichiarata nell'intestazione, che riceve il valore.
- **parametro attuale / argomento** — valore passato nella chiamata.
- **passaggio per valore** — il parametro formale riceve una copia del valore dell'argomento.
- **`return`** — restituisce un valore e riporta il controllo al chiamante.
- **chiamante** — la funzione che esegue la chiamata.
- **variabile locale** — dichiarata in una funzione o in un blocco; esiste solo lì e solo durante l'esecuzione.
- **variabile globale** — dichiarata fuori da tutte le funzioni; visibile in tutto il file e viva per tutto il programma.
- **shadowing** — una locale con lo stesso nome nasconde la variabile più esterna.
- **top-down** — progettazione che parte dal problema intero e lo divide in sottoproblemi.
- **call and return** — salto di andata verso la funzione e salto di ritorno all'istruzione dopo la chiamata.
- **indirizzo di ritorno** — punto del codice da cui riprendere quando la funzione termina.
- **stack (pila)** — zona di memoria LIFO dove vivono i record di attivazione.
- **LIFO** — Last In, First Out: l'ultimo inserito è il primo tolto.
- **record di attivazione** — "scheda" di una chiamata sullo stack: indirizzo di ritorno, parametri, locali e valore di ritorno.
- **segmento dati** — zona di memoria delle variabili globali, che esiste per tutto il programma.
- **segmento codice** — zona di memoria (in sola lettura) con le istruzioni del programma.
- **overflow** — risultato troppo grande per il tipo; per gli interi con segno è comportamento indefinito.
- **`long long`** — intero di almeno 64 bit; si stampa con `%lld`.
