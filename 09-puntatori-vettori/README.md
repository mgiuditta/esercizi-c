# 09 — Puntatori e vettori

> Lezioni di riferimento: trascrizioni 3.4 (Puntatori e vettori) e 3.4 E-tivity, Appunti Unità 3 (cap. 4 "Puntatori", par. 4.1–4.15, e par. 6.6 "Passaggio dei vettori alle funzioni"), LEZ 16.
> Tempo stimato: ~4 ore.

## Teoria flash

**Memoria e indirizzi.** La memoria è una lunga fila di celle da 1 byte. Ogni cella ha un numero d'ordine, l'**indirizzo** (come il numero civico di una casa). Una variabile occupa una o più celle *consecutive*. Il suo indirizzo è quello della *prima* cella. `sizeof(tipo)` ti dice quanti byte occupa un tipo.

> In questa repo diamo per scontato (vale su macOS arm64 e su Linux x86-64): `sizeof(char)` = 1, `sizeof(int)` = 4, `sizeof(double)` = 8, `sizeof` di **qualsiasi puntatore** = 8.

**Puntatore.** Un **puntatore** è una variabile che contiene un indirizzo. Si dichiara con `tipo_puntato *nome;`. Esempio: `int *p;` si legge "p è un puntatore a int". Il **tipo puntato** (qui `int`) è fondamentale: dice al compilatore *quante celle* leggere partendo da quell'indirizzo e *come interpretarle*. Il prof lo ripete nell'E-tivity: "il tipo determina la dimensione della memoria riferita". Un `char *` "vede" 1 byte, un `int *` ne vede 4.

**I due operatori.**
- `&x` (operatore *indirizzo*, detto anche di **referenziazione**): "dammi l'indirizzo di x". Lo usi già nella `scanf("%d", &n)`.
- `*p` (operatore di **dereferenziazione**): "l'elemento puntato da p". Leggilo proprio così, come suggerisce il prof.

```c
int i = 2, j;
int *p = &i;   /* p contiene l'indirizzo di i: "p punta a i"      */
j = *p;        /* j = l'elemento puntato da p, cioè i: j vale 2   */
*p = 7;        /* scrivo nell'elemento puntato da p: ora i vale 7 */
```
Dopo `p = &i`, `*p` è un **alias** di `i` (un secondo nome per la stessa cella, come "Matteo" e "il tutor" che indicano la stessa persona).

Attenzione alla differenza tra `q = p` (ora q punta *alla stessa variabile* di p) e `*q = *p` (copio il *valore*: q continua a puntare alla sua variabile). È l'esempio di `i` e `j` della trascrizione 3.4.

**NULL.** `NULL` è il valore "non punto a niente". È il modo sensato di inizializzare un puntatore, come si inizializza un contatore a 0. Dereferenziare `NULL` (`*p` con `p == NULL`) fa terminare il programma ("Segmentation fault", cioè: il sistema operativo ferma il programma perché ha toccato memoria proibita). Un puntatore **non inizializzato** è peggio: contiene un indirizzo a caso, e scriverci può rovinare dati senza avvisarti.

**Aritmetica dei puntatori.** Se `p` è un `int *`, allora `p + 1` **non** è l'indirizzo successivo di 1 byte: è l'indirizzo successivo di `sizeof(int)` = 4 byte, cioè *l'intero dopo*. Regola generale: `p + k` avanza di `k * sizeof(tipo puntato)` byte. Sono permesse:
- puntatore ± intero (`p + 2`, `p--`);
- puntatore − puntatore dello stesso tipo, nello **stesso vettore**: il risultato è *quanti elementi* li separano (non quanti byte!). Se `p = &v[1]` e `q = &v[4]`, allora `q - p` vale 3;
- confronto (`<`, `==`, ...) tra puntatori nello stesso vettore: `p < q` significa "p viene prima di q".

**Il nome del vettore.** Scritto da solo, il nome di un vettore vale l'indirizzo del suo primo elemento: `v` equivale a `&v[0]`. Per questo `int *p = v;` funziona senza `&`. E per definizione del linguaggio:

```c
v[i]  ==  *(v + i)        /* l'elemento i-esimo è "l'elemento puntato da v + i" */
&v[i] ==  v + i
```
Vale anche per i puntatori: se `p = v`, puoi scrivere `p[3]`. **Però** il vettore *non è* una variabile puntatore: è un **puntatore costante**. `p++` va bene, `v++` o `v = p` sono errori di compilazione.

**Scorrere un vettore con un puntatore** (Appunti, par. 4.13):
```c
int v[5] = {1, 2, 3, 4, 5};
int *p;
for (p = v; p < v + 5; p++)   /* v + 5 = "uno oltre l'ultimo": traguardo, mai letto */
    printf("%d\n", *p);
```

**Vettori passati a funzione.** Quando scrivi `somma(v, 5)`, il C **non copia** il vettore: passa l'indirizzo del primo elemento. Quindi `int somma(int v[], int n)` e `int somma(int *v, int n)` sono la *stessa* dichiarazione. Conseguenze: (1) la funzione può modificare il vettore del chiamante; (2) la funzione non sa quanto è lungo, per questo passi sempre `n`; (3) puoi passare *un pezzo* di vettore: `somma(v + n/2, n - n/2)` somma la seconda metà (esempio della trascrizione 3.4). Se la funzione deve solo leggere, scrivi `const int *v`: `const` è la promessa "attraverso questo puntatore non modifico niente", controllata dal compilatore.

**Stringhe con `char *`.** Una stringa è un vettore di `char` che finisce con il **terminatore** `'\0'` (il carattere di codice 0). Per scorrerla non serve conoscerne la lunghezza: si avanza finché `*p != '\0'`.

### Contraddizioni e imprecisioni nelle fonti
- **Moltiplicazioni e divisioni.** Nella trascrizione 3.4 il prof dice che, con l'unità di misura del tipo puntato, si possono usare "anche le moltiplicazioni e le divisioni". **Non è così**: il C permette solo somma/sottrazione di un intero, differenza tra puntatori e confronti. `p * 2` dà `error: invalid operands to binary * (have 'int *' and 'int')`. Gli Appunti (par. 4.10) elencano correttamente solo le quattro operazioni ammesse.
- **Confronti "convertendo in interi".** La trascrizione dice che nei confronti "si convertono gli indirizzi in interi". È un'immagine utile, ma il linguaggio garantisce un risultato sensato solo confrontando puntatori **dentro lo stesso vettore**.
- **"Referenziazione" due volte.** La trascrizione automatica chiama "referenziazione" sia `&` sia `*`. Il nome giusto di `*` è **dereferenziazione** (Appunti, par. 4.6).
- **E-tivity `pi2 = &v[1]`.** Il prof scrive l'assegnamento senza cast e dice che il *valore* assegnato è corretto (è pur sempre un indirizzo). Il compilatore però avvisa: `warning: assignment to 'int *' from incompatible pointer type 'char *'`. E *usare* `*pi2` è **comportamento indefinito** (il C non garantisce nulla: può dare un numero strano, un crash, o "funzionare" per caso), perché legge 4 byte dove c'è un `char` solo, "sforando" — come dice il prof — nella memoria vicina. Per questo nell'es03 non lo eseguiamo.
- **E-tivity `&pc2 + 1`.** Il prof lo assegna a `pc2`. Il tipo di `&pc2` è `char **` (indirizzo di un puntatore a char), quindi l'assegnamento a un `char *` dà `warning: assignment to 'char *' from incompatible pointer type 'char **'`, come anticipa lui ("questo dà almeno un warning").
- **Errori di trascrizione:** "macchina di touring" = macchina di Turing; "CIDA" = "C"; "int star più 1, int star più 2" = `int *pi1, *pi2`; "PDA" = `pa` (puntatore ad `a`); "e commerciale" = `&`; "star" = `*`.

### Errori tipici
1. **Puntatore non inizializzato.** `int *p; *p = 10;` → gcc: `warning: 'p' is used uninitialized [-Wuninitialized]` (clang: `variable 'p' is uninitialized when used here`). A runtime: crash o dati rovinati a caso.
2. **Confondere `p` e `*p`.** `p++` sposta il puntatore; `(*p)++` incrementa il valore puntato. Senza parentesi, `*p++` incrementa il puntatore (il `++` "lega" prima del `*`). È l'errore dell'es06.
3. **Intero dove serve un indirizzo.** `int *q = x;` → gcc: `warning: initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]` (clang lo tratta come errore: `take the address with &`). Mancava `&`.
4. **Modificare il nome del vettore.** `int w[10]; w++;` → gcc: `error: lvalue required as increment operand` (clang: `cannot increment value of type 'int[10]'`). Un vettore è un puntatore *costante*.
5. **Tipo puntato sbagliato.** `int *pi2 = &v[1];` con `v` di `char` → `warning: assignment to 'int *' from incompatible pointer type 'char *'`. Il warning è un allarme vero, non rumore.
6. **Uscire dal vettore.** `for (p = v; p <= v + n; p++)` legge `*(v + n)`, una cella *oltre* la fine. Il compilatore non dice nulla; AddressSanitizer (uno strumento che controlla gli accessi alla memoria mentre il programma gira, attivo nei test) spesso sì.

## Esercizi

### es01 — Somma di un pezzo di vettore con un puntatore  ·  Base
**Fonte:** Ispirato a: Trascrizione 3.4 (esempio `S = somma(v, n)` poi `p` a metà vettore e `somma(p, n/2)`), Appunti Unità 3, par. 4.13 e 6.6.
**Testo:** implementa `int somma(const int *p, int n)` che somma gli `n` interi a partire dall'indirizzo `p`, **scorrendoli con un puntatore** (niente indice, niente `p[i]`). Il `main` è già scritto: legge `n` e il vettore, poi stampa la somma totale, della prima metà (`n/2` elementi) e della seconda metà (gli altri, a partire da `v + n/2`).
```text
input:   5
         1 2 3 4 5
output:  totale: 15
         prima meta': 3
         seconda meta': 12
```
**File:** `es01_somma_intervallo.c` · **Test:** `make test T=09 E=es01`

<details><summary>💡 Suggerimento</summary>

Traduci il solito `for (i = 0; i < n; i++) s += v[i];`: `i = 0` diventa `q = p`, `i < n` diventa `q < p + n`, `i++` diventa `q++`, `v[i]` diventa `*q`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Dove parto?** Da `p`: è l'indirizzo del primo elemento da sommare. Non so (e non mi interessa) se è l'inizio vero del vettore o la sua metà: per la funzione è "un vettore che comincia lì". È il trucco del sottovettore del prof.
2. **Dove mi fermo?** All'indirizzo `p + n`: per l'aritmetica dei puntatori è `n` interi più avanti, cioè la cella *subito dopo* l'ultimo elemento. È un traguardo: ci arrivo ma non lo leggo mai. Il C permette di calcolare questo indirizzo "uno oltre la fine" proprio per poterlo usare come confine.
3. **Come avanzo?** `q++` sposta `q` di un `int` (4 byte). Se avanzassi di 1 byte finirei "a metà" di un intero.
4. **Perché `const`?** Perché la funzione legge soltanto. Se per errore scrivessi `*q = 0`, il compilatore si rifiuterebbe.

```c
int somma(const int *p, int n)
{
    const int *q;
    int s = 0;
    for (q = p; q < p + n; q++)
        s += *q;
    return s;
}
```
Simulazione con `v = {1,2,3,4,5}`, chiamata `somma(v + 2, 3)` (seconda metà):

| passo | q punta a | *q | s |
|---|---|---|---|
| inizio | v[2] | 3 | 0 → 3 |
| q++ | v[3] | 4 | 7 |
| q++ | v[4] | 5 | 12 |
| q++ | v + 5 = traguardo | (non letto) | **12** |

Con `n = 1` la prima metà ha `1/2 = 0` elementi (divisione intera): il ciclo non parte e la somma è 0. Codice completo: `soluzioni/es01_somma_intervallo.c`.
</details>

### es02 — La mia strlen con i puntatori  ·  Base
**Fonte:** Ispirato a: Appunti Unità 3, par. 4.15 (stringhe e terminatore `\0`) e par. 4.10 (sottrazione tra puntatori); Trascrizione 3.4 ("q − p vale j − i").
**Testo:** implementa `int lunghezza(const char *s)` che restituisce il numero di caratteri della stringa (senza contare `'\0'`), **senza `strlen` e senza indici**: fai scorrere un puntatore fino al terminatore e restituisci la *differenza tra puntatori*. Il `main` stampa la lunghezza e l'ultimo carattere.
```text
input:   ciao mondo
output:  "ciao mondo": lunghezza 10
         ultimo carattere: 'o'
```
**File:** `es02_lunghezza_stringa.c` · **Test:** `make test T=09 E=es02`

<details><summary>💡 Suggerimento</summary>

Quando `p` arriva sul `'\0'`, quanti elementi ha superato partendo da `s`? Esattamente `p - s`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. Copio l'indirizzo di partenza in un secondo puntatore `p`: `s` mi serve intatto alla fine, per la sottrazione.
2. Avanzo `p` finché il carattere puntato non è `'\0'`. Il ciclo si ferma *sul* terminatore, senza contarlo.
3. `p - s` è il numero di elementi tra i due indirizzi. Per i `char` coincide con i byte, ma la regola generale è "numero di elementi", non di byte. Il risultato ha un tipo speciale (`ptrdiff_t`, un intero con segno pensato per le differenze tra puntatori): lo converto a `int` con `(int)` perché la funzione restituisce `int`.

```c
int lunghezza(const char *s)
{
    const char *p = s;
    while (*p != '\0')
        p++;
    return (int)(p - s);
}
```
Con `s = "ciao"`: p va su `c`,`i`,`a`,`o` e si ferma su `'\0'`, che è a 4 posizioni da `s`, quindi il risultato è 4. Con la stringa vuota `p` è già su `'\0'`: il ciclo non parte, risultato 0. Nel `main`, `*(riga + n - 1)` è l'ultimo carattere: `riga + n` sarebbe il `'\0'`, quindi tolgo 1. Codice completo: `soluzioni/es02_lunghezza_stringa.c`.
</details>

### es03 — Cosa stampa? Il tipo puntato comanda  ·  Base
**Fonte:** Ispirato a: Trascrizione 3.4 E-tivity (`pc`, `pc2`, `pi`, `pi2`, `v[]`, `i`; `&v[1]`; `&pc2 + 1`; `(char*)&i + 1`).
**Testo:** il file è **già completo**. Aprilo, leggi il codice e, **prima di eseguirlo**, scrivi qui sotto cosa stamperà ogni riga (A–O). Poi lancia il test: passa già, quindi confronta la tua previsione con il file `tests/es03_cosa_stampa_tipi.out` (o con l'output di `make test`). Per avere un output uguale su ogni computer il programma non stampa mai indirizzi, ma solo **differenze in byte** e valori di `sizeof`. Assunzione: `sizeof(int)` = 4 e ogni puntatore occupa 8 byte (macOS arm64, Linux x86-64).
```text
La mia previsione:
A) *pc = ...
B) pc - v = ...
C) sizeof *pc = ..., sizeof pc = ...
D) *pi = ..., sizeof *pi = ...
E) byte tra pi e pi + 1 = ...
F) pi2 == NULL vale ...
G) byte tra &i e pc2 = ...
H) *pc2 = ...
I) byte tra &i e (char *)(&i + 1) = ...
L) byte tra &pc2 e &pc2 + 1 = ...
M) v = ...
N) *(v + 2) == v[2] vale ...
O) &v[3] - &v[0] = ...
```
**File:** `es03_cosa_stampa_tipi.c` · **Test:** `make test T=09 E=es03`

<details><summary>💡 Suggerimento</summary>

Per ogni riga chiediti: "qual è il **tipo** di questa espressione, e quindi qual è il tipo puntato?". `+ 1` avanza sempre di `sizeof(tipo puntato)` byte. E un cast scritto davanti si applica *prima* del `+`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output atteso:
```text
A) *pc = b
B) pc - v = 1
C) sizeof *pc = 1, sizeof pc = 8
D) *pi = 16843009, sizeof *pi = 4
E) byte tra pi e pi + 1 = 4
F) pi2 == NULL vale 1
G) byte tra &i e pc2 = 1
H) *pc2 = 1
I) byte tra &i e (char *)(&i + 1) = 4
L) byte tra &pc2 e &pc2 + 1 = 8
M) v = aXcd
N) *(v + 2) == v[2] vale 1
O) &v[3] - &v[0] = 3
```
Il trucco per stampare "byte tra due indirizzi" è convertirli entrambi in `char *` e sottrarli: siccome un `char` è 1 byte, la differenza in *elementi* è anche la differenza in *byte*.

- **A.** `pc = &v[1]`: punta al secondo elemento, `'b'`. È il primo caso dell'E-tivity, "perfetto" per il prof: `char *` su un `char`.
- **B.** `v` vale `&v[0]`; `pc` vale `&v[1]`. Differenza = 1 elemento.
- **C.** `*pc` è un `char`: 1 byte. `pc` invece è un *puntatore*, e ogni puntatore occupa 8 byte. Non confondere la grandezza del puntatore con la grandezza di ciò che punta.
- **D.** `i = 0x01010101` è scritto in **esadecimale** (base 16: ogni coppia di cifre dopo `0x` è un byte). Vale 16843009 in decimale. Abbiamo scelto un numero con *tutti i byte uguali a 1* apposta (vedi H). `*pi` è un `int`: 4 byte.
- **E.** `pi + 1` avanza di `sizeof(int)` = 4 byte. Nota: `&i + 1` punta *subito dopo* `i`. Calcolarlo è lecito ("uno oltre la fine" di un oggetto), leggerlo no: infatti non lo leggiamo.
- **F.** Il prof fa `pi2 = &v[1]`: un `int *` che punta a un `char`. Il valore (l'indirizzo) può essere copiato, ma leggendo `*pi2` si prenderebbero 4 byte (`v[1]`, `v[2]`, `v[3]` e uno *fuori* dal vettore): il prof dice "è ovviamente errato". In C è *comportamento indefinito*, quindi nel codice mettiamo `pi2 = NULL` e stampiamo solo il confronto `pi2 == NULL`, che vale 1 (vero).
- **G.** `(char *)&i + 1`: il **cast** (la conversione di tipo scritta tra parentesi) ha priorità più alta del `+`. Quindi prima `&i` diventa un `char *`, *poi* si aggiunge 1, cioè 1 byte. `pc2` punta al secondo byte di `i`, come dice il prof.
- **H.** Il secondo byte di `i` vale 1, perché *tutti* i byte di `0x01010101` valgono 1. Perché questa scelta? L'ordine in cui un `int` è salvato nei suoi 4 byte dipende dal processore. I computer **little-endian** (Mac arm64 e PC x86-64) mettono per primo il byte *meno* significativo; quelli **big-endian** mettono per primo il più significativo. Con `i = 65` (byte `00 00 00 41` in esadecimale) il *primo* byte letto con `*(char *)&i` sarebbe 65 su un little-endian e 0 su un big-endian: il risultato dipenderebbe dalla macchina. Con tutti i byte uguali la domanda non si pone.
- **I.** Qui le parentesi cambiano tutto: `&i + 1` è calcolato su un `int *` (avanza di 4 byte) e *solo dopo* convertito. Confronta con G: stesso "+1", risultato diverso.
- **L.** `&pc2` è l'indirizzo *della variabile puntatore* `pc2`. Il suo tipo è `char **` ("puntatore a puntatore a char"), quindi il tipo puntato è `char *`, che occupa 8 byte. `+ 1` avanza di 8: "la cella dopo pc2", dice il prof. Nell'E-tivity questo indirizzo viene messo in `pc2`, e il compilatore avvisa perché i tipi non coincidono.
- **M.** `*pc = 'X'` scrive nell'elemento puntato da `pc`, cioè `v[1]`: `*pc` è un alias di `v[1]`.
- **N.** `v[2]` è *definito* come `*(v + 2)`: sono la stessa cosa, il confronto vale 1.
- **O.** Differenza tra due indirizzi nello stesso vettore = differenza tra gli indici: 3 − 0 = 3. È la formula del prof "se p punta v[i] e q punta v[j], q − p vale j − i".
</details>

### es04 — Copia (solo i positivi) con due puntatori  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 3, par. 4.13 (scorrimento con puntatore) e 4.10 (sottrazione tra puntatori); Trascrizione 3.4 (vettori passati come indirizzo).
**Testo:** implementa `int copia_positivi(int *dest, const int *src, int n)`: copia in `dest`, nello stesso ordine, solo gli elementi **> 0** di `src` (0 non è positivo). Usa un puntatore che legge (`s`) e uno che scrive (`d`). Restituisci quanti elementi hai copiato calcolandolo come `d - dest`.
```text
input:   7
         3 -1 0 8 -5 2 9
output:  copiati: 4
         copia: 3 8 2 9
         originale: 3 -1 0 8 -5 2 9
```
**File:** `es04_copia_positivi.c` · **Test:** `make test T=09 E=es04`

<details><summary>💡 Suggerimento</summary>

I due puntatori viaggiano a velocità diverse: `s` avanza a ogni giro, `d` solo quando scrive. Alla fine `d` si è spostato una volta per ogni copia.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché due puntatori?** Perché le posizioni non coincidono: il quarto elemento di `src` (8) va nel secondo posto di `dest`. Un solo indice non basta.
2. `s` scorre tutto `src`, da `src` a `src + n` escluso.
3. Se `*s > 0`, scrivo `*d = *s` e **poi** avanzo `d`. Se avanzassi prima, lascerei un buco nella prima cella.
4. Il conteggio non serve tenerlo a parte: `d - dest` lo dà già.
5. `src` è `const int *`: il compilatore garantisce che la funzione non lo modifichi. Il `main` lo ristampa per mostrarlo.

```c
int copia_positivi(int *dest, const int *src, int n)
{
    const int *s;
    int *d = dest;
    for (s = src; s < src + n; s++)
        if (*s > 0) {
            *d = *s;
            d++;
        }
    return (int)(d - dest);
}
```
| *s | > 0? | scrivo in | d - dest dopo |
|---|---|---|---|
| 3 | sì | dest[0] | 1 |
| -1 | no | — | 1 |
| 0 | no | — | 1 |
| 8 | sì | dest[1] | 2 |
| -5 | no | — | 2 |
| 2 | sì | dest[2] | 3 |
| 9 | sì | dest[3] | **4** |

In C si trova spesso la forma compatta `*d++ = *s;`: il `++` agisce sul puntatore *dopo* l'uso. Funziona, ma la versione su due righe è più leggibile. Codice completo: `soluzioni/es04_copia_positivi.c`.
</details>

### es05 — Inverti un pezzo di vettore con due puntatori  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 3.4 (sottovettori: "passare una sottoparte di un vettore a una funzione"; confronto tra puntatori "v di 1 è minore di v di 3"), Appunti Unità 3 par. 4.10.
**Testo:** implementa `void scambia(int *x, int *y)` e `void inverti(int *sx, int *dx)`. `inverti` riceve due puntatori: al **primo** e all'**ultimo** elemento (compreso) del pezzo da invertire. Il `main` legge `n`, il vettore e due indici `a` e `b`, poi chiama `inverti(&v[a], &v[b])`. Se gli indici non vanno bene stampa `intervallo non valido` (già fatto).
```text
input:   6
         1 2 3 4 5 6
         1 4
output:  1 5 4 3 2 6
```
**File:** `es05_inverti_intervallo.c` · **Test:** `make test T=09 E=es05`

<details><summary>💡 Suggerimento</summary>

Finché `sx < dx`: scambia, poi `sx` va avanti e `dx` torna indietro. A `scambia` passi `sx` e `dx` così come sono: sono già indirizzi.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **`scambia` vuole indirizzi**, perché deve modificare le celle del chiamante. Se ricevesse due `int`, scambierebbe due copie e il vettore resterebbe uguale (passaggio per valore). Serve una variabile d'appoggio `t`: senza, `*x = *y` cancellerebbe il valore di `*x` prima di poterlo copiare.
2. **`inverti`**: i due puntatori partono dagli estremi e si avvicinano. `sx < dx` è un confronto tra puntatori nello *stesso* vettore: vuol dire "sx sta prima di dx".
3. **Quando mi fermo?** Quando si incontrano (`sx == dx`, lunghezza dispari: l'elemento centrale resta fermo) o si incrociano (`sx > dx`, lunghezza pari).

```c
void scambia(int *x, int *y) { int t = *x; *x = *y; *y = t; }

void inverti(int *sx, int *dx)
{
    while (sx < dx) {
        scambia(sx, dx);
        sx++;
        dx--;
    }
}
```
Simulazione con `{1,2,3,4,5,6}`, `a = 1`, `b = 4`:

| giro | sx → | dx → | vettore dopo lo scambio |
|---|---|---|---|
| 1 | v[1]=2 | v[4]=5 | 1 5 3 4 2 6 |
| 2 | v[2]=3 | v[3]=4 | 1 5 4 3 2 6 |
| 3 | v[3] | v[2] | sx > dx: stop |

Con `a == b` (un solo elemento) il ciclo non parte. Codice completo: `soluzioni/es05_inverti_intervallo.c`.
</details>

### es06 — Trova e correggi l'errore: pari e dispari  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 3, par. 4.8 (puntatori non inizializzati), 6.2 (`(*p)++` nel passaggio per indirizzo); Trascrizione 3.4 (`NULL`, ciclo `p < &v[4]` per uscire).
**Testo:** `conta_pari_dispari(v, n, pari, dispari)` deve scrivere in `*pari` e `*dispari` quanti numeri pari e dispari ci sono. Il codice compila, ma ha **tre errori**. Correggili cambiando il meno possibile.
```text
input:   6
         4 7 -3 0 -8 11
output:  pari: 3
         dispari: 3
```
Nota sul test: con i controlli attivi il programma si ferma subito al primo errore, quindi `make test` mostra **CRASH** insieme al messaggio del controllo. Se vuoi rifarlo a mano:
`cc -std=c11 -g -fsanitize=address,undefined es06_trova_errore_pari_dispari.c -o es06 && ./es06 < tests/es06_trova_errore_pari_dispari.1.in`
Vedrai: `runtime error: store to null pointer of type 'int'` con il numero di riga.
**File:** `es06_trova_errore_pari_dispari.c` · **Test:** `make test T=09 E=es06`

<details><summary>💡 Suggerimento</summary>

(1) Nel `main`: dove scrive la funzione quando le passi `np`? (2) Nel `for`: quante volte gira il ciclo con `n = 1`? (3) Nell'`if`: cosa incrementa `pari++`, il numero o il puntatore?
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

**Errore 1 — puntatore che non punta a niente.** Nel `main` c'era `int *np = NULL;` passato alla funzione. La funzione fa `*pari = 0`: scrive "nell'elemento puntato da NULL", che non esiste. Crash. Il programmatore pensava "mi serve un puntatore, quindi dichiaro un puntatore", ma serve una **variabile intera vera** di cui passare l'indirizzo, esattamente come con `scanf`:
```c
int np, nd;
conta_pari_dispari(v, n, &np, &nd);
printf("pari: %d\n", np);
```
**Errore 2 — un giro di troppo.** `p <= v + n` legge anche `*(v + n)`, che è *oltre* l'ultimo elemento. Qui il vettore è dichiarato da 100 celle tutte a zero, quindi legge uno 0 in più e conta un pari di troppo (in un vettore della misura esatta, AddressSanitizer lo segnalerebbe come lettura fuori dai limiti). Correzione: `p < v + n`.

**Errore 3 — incrementa la cosa sbagliata.** `pari++` incrementa il **puntatore** `pari`, cioè la copia locale dell'indirizzo, che si sposta su un'altra cella senza scrivere nulla. Il contatore del `main` resta a 0. Serve `(*pari)++`: "incrementa l'elemento puntato da pari". Le parentesi sono obbligatorie, perché `*pari++` significherebbe `*(pari++)`.

| Versione | Output con l'input d'esempio |
|---|---|
| originale | crash (nessun output) |
| corretto solo 1 | `pari: 0` / `dispari: 3` |
| corretti 1 e 3 | `pari: 4` / `dispari: 3` (lo 0 in più) |
| corretti tutti | `pari: 3` / `dispari: 3` |

I numeri negativi funzionano: in C `-3 % 2` vale `-1`, che è diverso da 0, quindi `-3` finisce correttamente tra i dispari. Per questo il controllo è `% 2 == 0` e non `% 2 == 1`. Codice completo: `soluzioni/es06_trova_errore_pari_dispari.c`.
</details>

### es07 — Il puntatore al massimo e l'ordinamento per selezione  ·  Tipo esame
**Fonte:** Ispirato a: Trascrizione 3.4 (sottovettori passati a una funzione che "non sa se gli sto passando una sua sottoparte"), Appunti Unità 3 par. 4.12–4.13 e 6.6; scambio tramite puntatori (Appunti par. 6.2).
**Testo:** implementa
1. `int *trova_max(int *v, int n)`: restituisce un **puntatore** all'elemento massimo tra i primi `n` (a parità, il primo trovato);
2. `void scambia(int *x, int *y)`;
3. `void ordina(int *v, int n)`: ordinamento crescente **per selezione**. Trova il massimo tra i primi `n` e scambialo con l'ultimo (`v + n - 1`). Poi ripeti sui primi `n - 1`, e così via fino a 2.

Il `main` stampa il massimo, il suo indice (calcolato come `pm - v`) e il vettore ordinato. Con `n = 0` stampa `vettore vuoto`.
```text
input:   6
         4 7 1 9 3 9
output:  massimo: 9 (indice 3)
         ordinato: 1 3 4 7 9 9
```
**File:** `es07_massimo_e_ordina.c` · **Test:** `make test T=09 E=es07`

<details><summary>💡 Suggerimento</summary>

Restituire un puntatore invece del valore permette di sapere *dove* sta il massimo, e quindi di scambiarlo. In `ordina`, la chiamata `trova_max(v, k)` guarda solo i primi `k`: è un sottovettore.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché restituire un puntatore?** Con il solo valore (9) non sapresti dove sta, né potresti modificarlo. Con l'indirizzo hai entrambe le cose: `*pm` è il valore, `pm - v` è l'indice, e `scambia(pm, ...)` lo sposta.
2. **È sicuro restituirlo?** Sì, perché punta *dentro il vettore del `main`*, che esiste ancora dopo il `return`. Sarebbe un errore grave restituire l'indirizzo di una variabile *locale* della funzione: alla fine della chiamata quella memoria viene liberata (lo stack, cioè la zona di memoria delle chiamate di funzione, vista nella LEZ 15).
3. **`trova_max`**: candidato iniziale `pmax = v`. Poi scorro da `v + 1` e aggiorno quando trovo un valore *strettamente* maggiore (`>`): così, a parità, resta il primo.
4. **`ordina`**: dopo il primo giro il massimo è in fondo, al suo posto definitivo. Ora basta ordinare i primi `n - 1`, che sono un vettore "più corto" con lo stesso indirizzo di partenza. Ripeto finché resta un solo elemento, che è ordinato per forza.

```c
int *trova_max(int *v, int n)
{
    int *pmax = v, *p;
    for (p = v + 1; p < v + n; p++)
        if (*p > *pmax)
            pmax = p;
    return pmax;
}

void ordina(int *v, int n)
{
    int k;
    for (k = n; k > 1; k--)
        scambia(trova_max(v, k), v + k - 1);
}
```
Simulazione di `ordina` con `{4, 7, 1, 9, 3, 9}`:

| k | massimo dei primi k | scambiato con | vettore |
|---|---|---|---|
| 6 | 9 (indice 3) | v[5] | 4 7 1 9 3 9 (scambio 9 con 9) |
| 5 | 9 (indice 3) | v[4] | 4 7 1 3 9 9 |
| 4 | 7 (indice 1) | v[3] | 4 3 1 7 9 9 |
| 3 | 4 (indice 0) | v[2] | 1 3 4 7 9 9 |
| 2 | 3 (indice 1) | v[1] | 1 3 4 7 9 9 |

Quando `pm` e `v + k - 1` coincidono, `scambia` scambia una cella con se stessa: non cambia nulla e non fa danni. Codice completo: `soluzioni/es07_massimo_e_ordina.c`.
</details>

### es08 — Parole e parola più lunga con `char *`  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 3, par. 4.15 (stringhe e `\0`) e 4.13 (scorrimento con puntatore); Trascrizione 3.4 (differenza tra puntatori, `NULL` come valore iniziale sensato).
**Testo:** una riga contiene parole separate da uno o più spazi `' '` (anche all'inizio e alla fine). Implementa, **solo con puntatori a char** (niente indici, niente `<string.h>`):
1. `int conta_parole(const char *s)`;
2. `const char *parola_piu_lunga(const char *s, int *lung)`: restituisce un puntatore al primo carattere della parola più lunga (a parità, la prima) e scrive la sua lunghezza in `*lung`. Se non ci sono parole restituisce `NULL` e `*lung = 0`.

Il `main` stampa la parola con `%.*s` e la sua posizione nella riga (`p - riga`).
```text
input:   il nome del vettore e un puntatore costante
output:  parole: 8
         piu' lunga: "puntatore" (9 caratteri, posizione 25)
```
**File:** `es08_parola_piu_lunga.c` · **Test:** `make test T=09 E=es08`

<details><summary>💡 Suggerimento</summary>

Struttura del ciclo: (a) salta gli spazi; (b) se sei sul `'\0'` hai finito; (c) ricorda `inizio = p`; (d) avanza finché non trovi uno spazio o `'\0'`; (e) la lunghezza della parola è `p - inizio`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché il controllo (b)?** Se la riga finisce con degli spazi, dopo averli saltati si arriva al `'\0'` senza una nuova parola. Senza il controllo conteresti una parola "vuota" in più.
2. **Perché `NULL` all'inizio?** `migliore = NULL` vuol dire "non ho ancora trovato niente". Se la riga è vuota (o solo spazi) resta `NULL`, e il `main` lo controlla *prima* di usare il puntatore. Dereferenziare `NULL` farebbe terminare il programma.
3. **Perché `const char *` come tipo di ritorno?** Perché punta dentro una stringa che la funzione ha ricevuto come `const`: chi la riceve non deve poterla modificare.
4. **`%.*s`**: stampa *al massimo* `lung` caratteri a partire da `p`. Serve perché la parola non è seguita da un `'\0'` suo (dopo c'è uno spazio e il resto della frase). Il primo argomento dopo il formato è il numero, il secondo il puntatore.

```c
const char *parola_piu_lunga(const char *s, int *lung)
{
    const char *p = s, *migliore = NULL;
    *lung = 0;
    while (*p != '\0') {
        const char *inizio;
        while (*p == ' ') p++;
        if (*p == '\0') break;
        inizio = p;
        while (*p != ' ' && *p != '\0') p++;
        if (p - inizio > *lung) {
            *lung = (int)(p - inizio);
            migliore = inizio;
        }
    }
    return migliore;
}
```
Con `"   due    spazi   ovunque  "`: le parole iniziano alle posizioni 3, 10, 18 e sono lunghe 3, 5, 7. Il risultato è `"ovunque"` (7 caratteri, posizione 18). Il confronto `>` stretto fa vincere la prima parola a parità di lunghezza (`"ciao mare sole"` → `"ciao"`). Codice completo: `soluzioni/es08_parola_piu_lunga.c`.
</details>

## Prompt pronti per questo argomento
1. `Interrogami con 6 domande su puntatori e vettori in C (aritmetica dei puntatori, v[i] == *(v+i), NULL, vettori passati a funzione), una alla volta. Aspetta la mia risposta prima di passare alla successiva e correggimi spiegando il perché.`
2. `Dammi 5 mini-programmi "Cosa stampa?" stile E-tivity 3.4 del prof Anisetti: puntatori a char e a int sulla stessa memoria, cast prima del +, &p + 1. L'output deve essere deterministico: niente indirizzi stampati, solo differenze in byte e sizeof. Non darmi la soluzione finché non rispondo.`
3. `Ho scritto questa soluzione per es07 di 09-puntatori-vettori: [incolla codice]. Dimmi se è corretta e perché, segnalami eventuali comportamenti indefiniti, senza riscrivermela tutta.`
4. `Spiegami con un disegno a celle di memoria (in testo) cosa succede in questo codice, riga per riga: [incolla codice con puntatori]. Per ogni puntatore dimmi tipo, tipo puntato e a quale cella punta.`
5. `Generami 3 esercizi nuovi tipo es08 di 09-puntatori-vettori (stringhe scorse con char*, funzioni che restituiscono un puntatore dentro la stringa), con input/output d'esempio e un caso limite ciascuno.`

## Riepilogo
- Un puntatore contiene un indirizzo; il **tipo puntato** decide quanti byte si leggono con `*p` e di quanto avanza `p + 1`.
- `v[i]` è `*(v + i)`: il nome del vettore vale `&v[0]`, ma è costante (niente `v++`). Un vettore passato a funzione arriva come puntatore, quindi serve anche `n`.
- La differenza tra puntatori nello stesso vettore dà *quanti elementi* li separano: è il modo naturale per ottenere lunghezze e indici.
- Un puntatore va sempre inizializzato (a una variabile vera o a `NULL`) e controllato prima di dereferenziarlo.

## Glossario
- **indirizzo** — numero che identifica una cella di memoria (il "numero civico").
- **puntatore** — variabile che contiene un indirizzo; si dichiara `tipo *nome`.
- **tipo puntato** — il tipo dell'oggetto a cui il puntatore si riferisce; decide quanti byte leggere.
- **`&` (indirizzo / referenziazione)** — dà l'indirizzo di una variabile.
- **`*` (dereferenziazione)** — "l'elemento puntato da".
- **alias** — un secondo nome per la stessa cella di memoria (`*p` dopo `p = &x`).
- **NULL** — valore speciale che indica "nessun oggetto puntato".
- **aritmetica dei puntatori** — `p + k` avanza di `k * sizeof(tipo puntato)` byte; `q - p` conta gli elementi.
- **puntatore costante** — un indirizzo che non può essere cambiato; il nome di un vettore si comporta così.
- **cast** — conversione di tipo esplicita, `(tipo)espressione`; ha priorità maggiore del `+`.
- **`const`** — parola chiave che vieta di modificare l'oggetto attraverso quel nome/puntatore.
- **terminatore `'\0'`** — carattere di codice 0 che segna la fine di una stringa.
- **comportamento indefinito** — operazione su cui lo standard C non garantisce nulla (crash, valori casuali o "funziona per caso").
- **little-endian** — convenzione in cui il byte meno significativo di un numero sta all'indirizzo più basso (Mac arm64, PC x86-64).
- **AddressSanitizer / UBSan** — strumenti attivati nei test che fermano il programma quando accede a memoria sbagliata o fa operazioni indefinite.
- **Segmentation fault** — il sistema operativo ferma il programma perché ha toccato memoria che non gli appartiene.
- **`%.*s`** — formato di `printf` che stampa al massimo N caratteri di una stringa (N passato come argomento).
