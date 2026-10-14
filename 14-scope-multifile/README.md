# 14 — Controllo dello scope: static, extern e programmi su più file

> Lezioni di riferimento: trascrizione 4.4 (Controllo dello scope), trascrizione 3.2 (extern su due file), Appunti Unità 4 (capitolo 3 "Argomenti da linea di comando e puntatori a funzione", capitolo 4 "Qualificatori const e static"), Appunti Unità 3 (par. 2.4 "Variabili globali e parola chiave extern"), LEZ 21.
> Tempo stimato: ~4 ore.

## Teoria flash

**Tre parole da non confondere.**
- **Scope** (visibilità): la zona del codice in cui un nome si può usare. Esempio: una variabile dichiarata dentro un blocco `{ }` esiste per il compilatore solo lì dentro.
- **Durata**: per quanto tempo, mentre il programma gira, la variabile occupa memoria e conserva il suo valore.
- **Linkage** (collegamento): se un nome globale è condiviso con gli altri file del programma (*linkage esterno*) oppure resta privato del suo file (*linkage interno*).

Analogia: lo scope è "chi può vedere la lavagna", la durata è "per quanto tempo la scritta resta sulla lavagna", il linkage è "se la lavagna sta nel corridoio (tutti i file) o dentro un'aula (un file solo)".

**Classi di memorizzazione** (cioè le parole chiave che decidono durata e linkage):
- `auto`: è il comportamento normale delle variabili locali. Una variabile **automatica** viene creata nel record di attivazione (sullo stack) quando la funzione parte e distrutta quando la funzione finisce. Nessuno scrive mai `auto`, perché è già il default.
- `static`: ha **due significati** a seconda di dove la scrivi (vedi sotto).
- `extern`: dichiara che una variabile globale *esiste* ma è definita altrove (di solito in un altro file).
- `register`: antico suggerimento al compilatore ("tieni questa variabile in un registro del processore, cioè in una cella di memoria velocissima dentro la CPU"). Oggi i compilatori lo ignorano.

Nota: `auto` e `register` **non compaiono nelle fonti del corso** (trascrizioni, Appunti, LEZ). Li cito solo perché fanno parte dell'elenco completo delle classi di memorizzazione del C.

**`static` dentro una funzione = cambia la DURATA.**
```c
void contatore(void)          /* esempio degli Appunti, par. 4.6 */
{
    static int c = 0;         /* inizializzata UNA volta sola */
    c++;
    printf("%d\n", c);        /* 1, poi 2, poi 3, ... */
}
```
Lo scope resta quello di una variabile locale (fuori dalla funzione `c` non si vede). La variabile però non sta nel record di attivazione: sta nel **segmento dati**, cioè la zona di memoria delle variabili globali, che esiste per tutta la vita del programma. Per questo "ricorda" il valore tra una chiamata e l'altra. Uso tipico citato dal prof: contare quante volte una funzione viene chiamata senza passarle un contatore.

**`static` fuori dalle funzioni = cambia il LINKAGE.**
```c
int x;               /* globale: visibile anche dagli altri file (linkage esterno) */
static int y;        /* globale static: visibile SOLO in questo file (linkage interno) */
static void fun(void) { ... }   /* funzione usabile solo in questo file */
```
Le funzioni sono "extern di default": qualunque file può chiamarle, se conosce il prototipo (cioè la riga che ne descrive nome, parametri e tipo restituito). Scrivendo `static` le rendi private del file. A cosa serve: proteggere i dati ("se non è visibile non può essere modificata", dice il prof) e poter riusare lo stesso nome in file diversi senza conflitti.

**Definizione e dichiarazione.** Una **definizione** crea davvero la cosa: alloca la memoria di una variabile o scrive il corpo di una funzione. Una **dichiarazione** dice solo "esiste, ed è fatta così". Regola (trascrizione 3.2): una variabile globale si **definisce una volta sola** in tutto il programma, ma si può **dichiarare** quante volte vuoi con `extern`.
```c
/* modulo1.c */  int n = 0;        /* definizione */
/* modulo2.c */  extern int n;     /* dichiarazione: "n è in un altro file" */
```

**Header e include guard.** Un **header** (file `.h`) raccoglie le dichiarazioni che un modulo offre agli altri: prototipi e `extern`. Chi usa il modulo scrive `#include "modulo.h"` (con le virgolette: il file va cercato prima nella cartella del progetto). Un **include guard** impedisce che lo stesso header venga incluso due volte nello stesso file:
```c
#ifndef PILA_H     /* "se PILA_H non è ancora definita..." */
#define PILA_H     /* "...definiscila" (alla seconda inclusione salta tutto fino a #endif) */
void pila_svuota(void);
#endif
```

**Compilazione separata.** `cc main.c pila.c -o prog` fa tre passi per ogni file: il **preprocessore** esegue `#include` e `#define`; il **compilatore** traduce ogni `.c` in un **file oggetto** `.o` (codice macchina incompleto, con "buchi" dove servono nomi definiti altrove); il **linker** unisce tutti i `.o` e riempie i buchi cercando le definizioni. Un nome `static` non viene offerto al linker: per questo usarlo da un altro file dà errore **al link**, non alla compilazione. Il runner `make test` fa esattamente questo: compila insieme tutti i `.c` della cartella `esNN_nome/`.

**Puntatori a funzione.** Anche una funzione ha un indirizzo, e lo si può mettere in una variabile:
```c
int (*cond)(int);      /* cond: puntatore a una funzione che riceve un int e restituisce un int */
cond = pari;           /* il nome della funzione "decade" nel suo indirizzo */
if (cond(4)) ...       /* chiamata tramite puntatore (equivale a (*cond)(4)) */
```
Le parentesi in `(*cond)` sono obbligatorie: `int *cond(int);` sarebbe invece il prototipo di una funzione che restituisce un `int *`. Usi visti negli Appunti: un vettore di puntatori a funzione al posto di uno `switch` (`fun_ptr_arr`) e una funzione passata come parametro a un'altra (`wrapper(fun1)`).

**argc e argv.** `int main(int argc, char *argv[])`: `argc` (argument count) è il numero di parole della riga di comando, **nome del programma compreso**; `argv` (argument vector) è un vettore di stringhe. Con `programma par1 par2` si ha `argc = 3`, `argv[0] = "programma"`, `argv[1] = "par1"`. Gli argomenti sono **stringhe**: per avere un numero serve `atoi` di `<stdlib.h>` (`atoi("42")` → 42). Il valore restituito da `main` arriva al sistema operativo: 0 significa "tutto bene".

**Imprecisioni e contraddizioni nelle fonti:**
- **Quando si inizializza una static locale?** Nella trascrizione 4.4 il prof dice prima "viene inizializzata una sola volta, la prima volta che tale funzione viene chiamata", poi "l'inizializzazione avviene solo una volta prima dell'esecuzione del programma". La seconda frase è quella tecnicamente esatta: il valore iniziale è già scritto nel segmento dati quando il programma parte. Per chi scrive codice l'effetto è identico: l'inizializzazione avviene **una volta sola** e non viene ripetuta a ogni chiamata.
- Il prof dice che le static si inizializzano "solo con costanti letterali". Più precisamente servono **espressioni costanti**, cioè calcolabili durante la compilazione: `static int c = 2 * 3;` va bene; `static int c = leggi();` no (vedi Errori tipici).
- Appunti par. 4.10: "le variabili globali, se dichiarate con extern, possono essere utilizzate anche in altri file". È impreciso: la variabile si **definisce senza** `extern` in un file; `extern` si scrive negli **altri** file, che la usano (Appunti Unità 3, par. 2.4).
- Gli Appunti chiamano `const` e `static` entrambi "qualificatori". Tecnicamente `const` è un *qualificatore di tipo*, mentre `static` è uno *specificatore di classe di memorizzazione*. A livello pratico non cambia nulla.
- Header `.h` e include guard non compaiono nella trascrizione 4.4 né negli Appunti Unità 4: li uso perché sono il modo standard di organizzare i programmi su più file (in LEZ 14 c'è un cenno a `#ifndef`).
- Trascrizione automatica: "externa" = `extern`; "quantificatore" = qualificatore; "file.org", "i punti o" = i file `.o` (file oggetto); "put" = `puts`; nell'esempio la funzione si chiama a volte "fun" e a volte "fun1" (è sempre la stessa).

### Errori tipici
1. **Chiamare da un altro file una funzione `static`, o usare con `extern` una globale `static`** (l'esempio file1.c/file2.c del prof). Ogni file compila, ma il linker non trova i nomi:
   ```text
   file2.c:(.text+0x9): undefined reference to `fun1'
   file2.c:(.text+0xf): undefined reference to `y'
   collect2: error: ld returned 1 exit status
   ```
2. **Definire la stessa globale in due file** (`int x = 1;` in uno e `int x = 2;` nell'altro, senza `extern`):
   ```text
   multiple definition of `x'; /tmp/ccNViu8I.o:(.data+0x4): first defined here
   ```
3. **Inizializzare una static con un valore calcolato a runtime** (cioè durante l'esecuzione):
   ```text
   file4.c:2:30: error: initializer element is not constant
       2 | int f(void) { static int c = leggi(); return c; }
   ```
4. **Usare lo stato privato di un modulo da fuori** (`cima = 50;` in main.c, mentre `cima` è static in pila.c):
   ```text
   file5.c:2:18: error: 'cima' undeclared (first use in this function)
   ```
5. **"Azzerare" la static a ogni chiamata**, con `static int n; n = 0;` invece di `static int n = 0;`. La prima forma è un *assegnamento* eseguito a ogni chiamata. Nessun avviso del compilatore: lo trovi in es06.
6. **Una variabile locale che nasconde una globale con lo stesso nome** (in inglese *shadowing*). Con `-Wall` non c'è nessun avviso; con l'opzione `-Wshadow` sì:
   ```text
   warning: declaration of 'totale_vendite' shadows a global declaration [-Wshadow]
   ```

## Esercizi

### es01 — Media "che ricorda" con static locali  ·  Base
**Fonte:** Ispirato a: Trascrizione 4.4 (static locale: "il valore resta inalterato tra le varie chiamate"), Appunti Unità 4 par. 4.6 (funzione `contatore` con `static int c = 0`).
**Testo:** completa `double media_corrente(int x)`. Riceve un valore alla volta e restituisce la media di **tutti** i valori ricevuti finora. Il main non le passa né la somma né il conteggio: la funzione deve ricordarseli.
```text
input:
10 20 30
output:
valore 10 -> media 10.00
valore 20 -> media 15.00
valore 30 -> media 20.00
```
**File:** `es01_media_static.c` · **Test:** `make test T=14 E=es01`

<details><summary>💡 Suggerimento</summary>
Ti servono due variabili locali che non si azzerino quando la funzione termina. Per la divisione, attenzione: `int / int` in C dà un `int` (troncato).
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché una normale variabile locale non basta.** `int somma = 0;` vive nel record di attivazione: viene ricreata e rimessa a 0 a ogni chiamata, quindi ogni media sarebbe solo l'ultimo valore.
2. **Perché non una globale.** Funzionerebbe, ma chiunque nel file potrebbe modificarla per errore. Con `static` locale la variabile resta privata della funzione (scope locale) e intanto sopravvive tra le chiamate (durata di tutto il programma).
3. **L'inizializzazione `= 0`** avviene una volta sola, non a ogni chiamata.
4. **La divisione.** `(double)somma / conteggio` converte prima `somma` in `double`, così la divisione è "con la virgola": 11/3 dà 3.67 e non 3.

```c
double media_corrente(int x)
{
    static int conteggio = 0;
    static long somma = 0;
    conteggio++;
    somma += x;
    return (double)somma / conteggio;
}
```

| chiamata | x | conteggio | somma | restituisce |
|---|---|---|---|---|
| 1ª | 10 | 1 | 10 | 10.00 |
| 2ª | 20 | 2 | 30 | 15.00 |
| 3ª | 30 | 3 | 60 | 20.00 |

Le colonne `conteggio` e `somma` "continuano" da una riga all'altra: è proprio questo l'effetto di `static`.

Codice completo: `soluzioni/es01_media_static.c`.
</details>

### es02 — Cosa stampa? static, globali e variabili nascoste  ·  Base
**Fonte:** Ispirato a: Trascrizione 4.4 (static locale e globale), Trascrizione 3.1 (variabile globale `n` modificata da una funzione), Appunti Unità 4 par. 4.6–4.7.
**Testo:** apri `es02_cosa_stampa.c` (è **già completo**). Senza eseguirlo, scrivi qui sotto le 13 righe che stampa. Poi lancia il test e confronta.
```text
La mia previsione:
f: a=? s=?
...
```
**File:** `es02_cosa_stampa.c` · **Test:** `make test T=14 E=es02`

<details><summary>💡 Suggerimento</summary>
Per ogni variabile chiediti: dove è dichiarata (scope)? Viene ricreata a ogni chiamata o esiste una volta sola (durata)? Quando due variabili hanno lo stesso nome, vince quella dichiarata nel blocco più interno.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output reale:
```text
f: a=1 s=1
f: a=1 s=2
f: a=1 s=3
main: x=1
blocco: x=2
main: x=1
stampa_x: x=100
scendi(2): livello=1
scendi(1): livello=2
scendi(0): livello=3
scendi(1): livello=4
scendi(0): livello=5
chiamate_g=3
```

1. **`f()` tre volte.** `a` è automatica: a ogni chiamata nasce a 0 e diventa 1, quindi `a=1` sempre. `s` è static: nasce a 0 una volta sola e poi vale 1, 2, 3.
2. **`main: x=1`.** Nel main c'è `int x = 1;`, una variabile locale che **nasconde** la globale `x = 100`: dentro il main il nome `x` indica quella locale.
3. **`blocco: x=2`.** Il blocco `{ }` dichiara una terza `x`, che nasconde quella del main finché il blocco non si chiude. Dopo la `}` torna visibile la `x` del main: di nuovo `x=1`.
4. **`stampa_x: x=100`.** `stampa_x` è fuori dal main: lì l'unica `x` visibile è la globale. Le variabili locali del main non si "vedono" dentro un'altra funzione, anche se è il main a chiamarla.
5. **`scendi`.** Collegamento con la cartella 13: ogni chiamata ricorsiva ha il suo record con la sua `n`, ma `livello` è static, quindi ne esiste **una sola**, condivisa da tutte le chiamate. `scendi(2)` crea 3 chiamate (livello 1, 2, 3). La seconda chiamata `scendi(1)` **non** riparte da 1: continua da 3 e arriva a 4, 5.
6. **`chiamate_g=3`.** La globale static è stata incrementata solo da `f`, chiamata 3 volte. Essendo `static` globale, nessun altro file del programma potrebbe toccarla.

Il file della soluzione è identico allo starter.
</details>

### es03 — Una variabile condivisa tra file con extern  ·  Base
**Fonte:** Ispirato a: Trascrizione 3.2 (programma `main.c` + `foo.c` con `extern int n`), Appunti Unità 3 par. 2.4, Appunti Unità 4 par. 4.10.
**Testo:** cartella multi-file `es03_extern_condivisa/` con `punteggio.h`, `punteggio.c`, `main.c`. `punteggio.c` **definisce** `int punteggio_totale`. Devi:
1. **dichiararla** con `extern` in `punteggio.h`;
2. completare `aggiungi_punti(p)`, che aggiunge p al totale senza mai farlo scendere sotto 0;
3. in `main.c`, togliere la variabile `finto` e usare direttamente `punteggio_totale`.
```text
input:
10 -3 7 -20 5
output:
mossa 1: +10 -> totale 10
mossa 2: -3 -> totale 7
mossa 3: +7 -> totale 14
mossa 4: -20 -> totale 0
mossa 5: +5 -> totale 5
fine partita, totale azzerato: 0
```
**File:** `es03_extern_condivisa/` (3 file) · **Test:** `make test T=14 E=es03`

<details><summary>💡 Suggerimento</summary>
La riga da aggiungere nell'header è identica alla definizione, ma con `extern` davanti e senza `= 0`. Prova anche a togliere `extern` da quella riga: cosa dice il linker?
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Il problema.** `main.c` viene compilato da solo, senza vedere `punteggio.c`. Se scrive `punteggio_totale`, il compilatore risponde `'punteggio_totale' undeclared`: per lui quel nome non esiste.
2. **La dichiarazione.** In `punteggio.h`: `extern int punteggio_totale;`. È una promessa al compilatore: "esiste un `int` con questo nome; la sua memoria è da un'altra parte". Il compilatore lascia un "buco" nel file oggetto `main.o`, e il linker lo riempie con l'indirizzo della variabile definita in `punteggio.o`.
3. **Perché nell'header e non direttamente in main.c.** Funzionerebbe anche così (è quello che fa il prof nella trascrizione 3.2). Con l'header, però, ogni file che usa il modulo riceve la stessa dichiarazione. E poiché anche `punteggio.c` include l'header, il compilatore controlla che dichiarazione e definizione coincidano: se una dicesse `int` e l'altra `long`, darebbe errore.
4. **Cosa succede senza `extern`.** `int punteggio_totale;` nell'header diventerebbe una **definizione** in ogni file che lo include. Due definizioni → `multiple definition of 'punteggio_totale'` (errore del linker; vedi Errori tipici 2).
5. **`aggiungi_punti`:**
   ```c
   void aggiungi_punti(int p)
   {
       punteggio_totale += p;
       if (punteggio_totale < 0)
           punteggio_totale = 0;
   }
   ```
6. **Condivisione vera.** Alla fine il main scrive `punteggio_totale = 0;`: è **la stessa** cella di memoria usata da `punteggio.c`, non una copia.

Codice completo: `soluzioni/es03_extern_condivisa/`.
</details>

### es04 — Modulo "dado" con stato nascosto  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 4.4 (variabile globale static e funzione static, "linkage interno"), Appunti Unità 4 par. 4.8–4.10.
**Testo:** cartella `es04_modulo_dado/`. Il modulo `generatore.c` produce lanci di dado "pseudo-casuali": numeri che *sembrano* casuali ma sono sempre gli stessi a parità di **seme** (il valore di partenza). Il seme e il contatore `estrazioni` sono globali `static`; la formula sta nella funzione `static` `prossimo()` (già scritta). Completa `gen_seme`, `gen_dado` (che deve restituire `(r / 65536) % 6 + 1`) e controlla che `gen_estrazioni` funzioni. `main.c` è già completo.
```text
input:
42 12
output:
lanci: 2 6 6 4 3 2 4 5 2 2 3 1
1: * (1)
2: **** (4)
3: ** (2)
4: ** (2)
5: * (1)
6: ** (2)
estrazioni: 12
```
**File:** `es04_modulo_dado/` (3 file) · **Test:** `make test T=14 E=es04`

<details><summary>💡 Suggerimento</summary>
`gen_seme` deve anche azzerare `estrazioni`. In `gen_dado` il risultato di `prossimo()` è un `unsigned long long`: convertilo in `int` con un cast solo alla fine. Esperimento: in `main.c` scrivi `seme = 0;` e guarda l'errore.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Lo stato privato.** `static unsigned long long seme` è globale (esiste per tutto il programma, e ogni funzione di `generatore.c` lo vede), ma il suo nome non esce dal file. Da `main.c` l'unico modo per cambiarlo è `gen_seme`. È l'**incapsulamento** di cui parlano gli Appunti (par. 4.9): nascondere i dettagli interni e offrire solo poche funzioni "ufficiali".
2. **La funzione static `prossimo`.** È un attrezzo interno: `main.c` non deve usarla, perché salterebbe il conteggio delle estrazioni. Se ci provasse, il linker risponderebbe `undefined reference to 'prossimo'`.
3. **Il codice:**
   ```c
   void gen_seme(unsigned int s) { seme = s; estrazioni = 0; }
   int gen_dado(void)
   {
       estrazioni++;
       return (int)((prossimo() / 65536ULL) % 6ULL) + 1;
   }
   ```
4. **Perché `unsigned long long`.** `seme * 1103515245` può arrivare quasi a 2⁶²: in un `int` (al massimo circa 2·10⁹) andrebbe in overflow, e per un intero con segno questo è comportamento indefinito, cioè il C non garantisce il risultato. `unsigned long long` è sempre di almeno 64 bit.
5. **Perché `/ 65536`.** Le cifre binarie basse di questo tipo di generatore si ripetono con un periodo breve (il bit più basso alterna 0 e 1). Dividendo per 65536 = 2¹⁶ usiamo i bit alti, più vari.
6. **Anche in main.c c'è uno `static`.** `stampa_istogramma` serve solo al main: renderla static evita conflitti se un altro modulo avesse una funzione con lo stesso nome.

| lancio | seme dopo `prossimo()` | (seme / 65536) % 6 + 1 |
|---|---|---|
| (inizio) | 42 | — |
| 1 | 1250496027 | 2 |
| 2 | 1116302264 | 6 |

Codice completo: `soluzioni/es04_modulo_dado/`.
</details>

### es05 — argc/argv e tabella di puntatori a funzione  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 4 cap. 3 (par. 3.4 argc/argv, 3.6 somma con `atoi`, 3.7 valore di ritorno, 3.12 `fun_ptr_arr`, 3.13 `wrapper`), LEZ 21 par. 3.16–3.19.
**Testo:** il programma simulato si usa così: `conta <criterio> <numeri...>`. Stampa quanti numeri soddisfano il criterio (`pari`, `dispari`, `positivi`, `primi`). Completa:
- `conta_se(v, n, cond)`: conta gli elementi per cui la funzione `cond` restituisce vero;
- `esegui(argc, argv)`: con `argc < 3` stampa `Uso: conta <criterio> <numeri...>` e restituisce 1; con un criterio sconosciuto stampa `Criterio sconosciuto: X` e restituisce 2; altrimenti stampa `pari: 3 su 5` e restituisce 0.

Il runner dei test non può passare argomenti al programma, quindi il main (già scritto) trasforma ogni riga di input in un finto `argv`.
```text
input:
pari 4 7 10 -2 3
boh 1 2
output:
> conta pari 4 7 10 -2 3
pari: 3 su 5
codice di uscita: 0
> conta boh 1 2
Criterio sconosciuto: boh
codice di uscita: 2
```
**File:** `es05_riga_comando.c` · **Test:** `make test T=14 E=es05`

<details><summary>💡 Suggerimento</summary>
Controlla `argc` **prima** di leggere `argv[1]`. Cerca il criterio con un ciclo e `strcmp(argv[1], nomi_criteri[k]) == 0`: l'indice k trovato è anche l'indice giusto in `criteri[]`. I numeri partono da `argv[2]`, quindi sono `argc - 2`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **`conta_se` riceve una funzione come parametro.** `int (*cond)(int)` si legge "cond è un puntatore a una funzione che riceve un int e restituisce un int". `conta_se` non sa *quale* controllo farà: lo decide chi la chiama. È il `wrapper(fun1)` degli Appunti, applicato a un vettore.
   ```c
   for (i = 0; i < n; i++)
       if (cond(v[i]))
           c++;
   ```
2. **La tabella.** `static int (*criteri[])(int) = {pari, dispari, positivo, primo};` è un vettore di puntatori a funzione, come `fun_ptr_arr` degli Appunti. Insieme a `nomi_criteri[]`, nella stessa posizione, sostituisce uno `switch` con quattro `case`. Aggiungere un criterio significa aggiungere una voce alla tabella, senza toccare la logica.
3. **argc prima di argv.** Con la riga vuota, `argc` vale 1 e `argv[1]` è `NULL`: passarlo a `strcmp` farebbe crollare il programma. Per questo il controllo `argc < 3` va per primo.
4. **atoi.** `argv[2]` è la stringa `"4"`, non il numero 4. `atoi` la converte. Attenzione: `atoi("ciao")` restituisce 0 senza segnalare errori.
5. **Valore di ritorno.** `esegui` restituisce 0, 1 o 2 come farebbe `main`: per convenzione 0 = successo e un altro valore = errore. In un terminale vero lo leggeresti con `echo $?`.

| riga | argc | argv[1] | k trovato | risultato |
|---|---|---|---|---|
| `pari 4 7 10 -2 3` | 7 | "pari" | 0 | conta_se(v, 5, pari) = 3 → 0 |
| `dispari` | 2 | "dispari" | — | argc < 3 → 1 |
| `boh 1 2` | 4 | "boh" | 4 (= N_CRITERI, non trovato) | → 2 |

Codice completo: `soluzioni/es05_riga_comando.c`.
</details>

### es06 — Trova e correggi l'errore: static e scope  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 4.4 (static locale inizializzata una sola volta), Trascrizione 3.1 (globale modificata da una funzione), LEZ 21 par. 5.8.
**Testo:** una cassa registra gli incassi. Ci sono **tre errori**, tutti legati a static e scope. Il programma compila senza avvisi con le opzioni normali (prova a compilarlo a mano anche con `-Wshadow`).
```text
input:
100 150 120
output corretto:
ricevuta 1: importo 100, variazione +100
ricevuta 2: importo 150, variazione +50
ricevuta 3: importo 120, variazione -30
totale vendite: 370
```
**File:** `es06_trova_errore.c` · **Test:** `make test T=14 E=es06`

<details><summary>💡 Suggerimento</summary>
Le ricevute escono tutte con il numero 1, il totale resta 0 e la variazione è sempre uguale all'importo. Per ogni funzione chiediti: quale variabile dovrebbe ricordare il valore tra una chiamata e l'altra? E a quale variabile si riferisce davvero quel nome?
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

**Errore 1 — `nuova_ricevuta`: la static viene riazzerata.**
```c
static int numero;   /* inizializzazione (implicita a 0): avviene una volta */
numero = 0;          /* ASSEGNAMENTO: eseguito a OGNI chiamata */
```
La variabile è static, ma la seconda riga la rimette a 0 a ogni chiamata, quindi la ricevuta vale sempre 1. Correzione: `static int numero = 0;` in un'unica riga, e cancellare l'assegnamento. Il segno `=` nella dichiarazione è un'**inizializzazione** (eseguita una volta), non un'istruzione ripetuta.

**Errore 2 — `registra`: la locale nasconde la globale.** `int totale_vendite = 0;` dentro la funzione crea una **nuova** variabile locale con lo stesso nome. La riga successiva incrementa quella locale, che sparisce al `return`; la globale resta 0. Correzione: cancellare la dichiarazione locale, così il nome indica la globale. Con `-Wshadow` il compilatore lo segnala:
```text
warning: declaration of 'totale_vendite' shadows a global declaration [-Wshadow]
```

**Errore 3 — `variazione`: manca `static`.** `int precedente = 0;` è automatica: ogni chiamata la ricrea a 0, quindi `diff` è sempre uguale all'importo, e l'assegnamento `precedente = importo` si perde al `return`. Correzione: `static int precedente = 0;`.

Simulazione corretta di `variazione`:

| chiamata | importo | precedente (prima) | diff | precedente (dopo) |
|---|---|---|---|---|
| 1ª | 100 | 0 | +100 | 100 |
| 2ª | 150 | 100 | +50 | 150 |
| 3ª | 120 | 150 | −30 | 120 |

Codice completo: `soluzioni/es06_trova_errore.c` (righe marcate `CORRETTO`).
</details>

### es07 — Modulo pila con stato privato: parentesi bilanciate  ·  Tipo esame
**Fonte:** Ispirato a: Trascrizione 4.4 ("se non è visibile non può essere modificata, quindi viene protetta"), Appunti Unità 4 par. 4.8–4.10 (static e incapsulamento), Appunti Unità 4 cap. 2 (lo stack dei record di attivazione come pila); variante (pila di caratteri usata per le parentesi) dell'esercizio 9 di LEZ 21.
**Testo:** cartella `es07_pila_parentesi/`. Una **pila** è una struttura in cui si aggiunge (*push*) e si toglie (*pop*) solo in cima, come una pila di piatti: l'ultimo inserito è il primo a uscire. Il modulo `pila.c` tiene i dati in variabili globali `static`. Completa:
1. `pila_pop(char *c)` in `pila.c`;
2. `controlla(s, &pos)` in `main.c`, che verifica se le parentesi `()[]{}` di una parola sono **bilanciate**: ogni chiusa corrisponde all'ultima aperta non ancora chiusa. Gli altri caratteri si ignorano.
```text
input:
([]{}) a*(b+c) (] (( ) {[()()]}
output:
([]{}) -> bilanciata
a*(b+c) -> bilanciata
(] -> errore in posizione 1
(( -> 2 parentesi non chiuse
) -> errore in posizione 0
{[()()]} -> bilanciata
```
**File:** `es07_pila_parentesi/` (3 file) · **Test:** `make test T=14 E=es07`

<details><summary>💡 Suggerimento</summary>
Apertura → push. Chiusura → pop: se la pila è vuota, oppure il carattere tolto non è l'apertura corrispondente (`apertura_di(c)`), errore in posizione i. Alla fine la pila deve essere vuota. Ricordati di chiamare `pila_svuota()` all'inizio: la pila è una sola per tutto il programma.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **`pila_pop`.** Se `cima == 0` non c'è niente da togliere → `return 0`. Altrimenti `cima--` e `*c = dati[cima]`. Il valore tolto esce dal parametro puntatore `c`, perché il `return` è già usato per dire "riuscito / non riuscito".
   ```c
   int pila_pop(char *c)
   {
       if (cima == 0) return 0;
       cima--;
       *c = dati[cima];
       return 1;
   }
   ```
2. **Perché `dati` e `cima` sono static.** Se fossero globali normali, `main.c` potrebbe scrivere `cima = 500;` e poi `pila_push` scriverebbe fuori dal vettore. Con `static` l'unico accesso passa dalle funzioni, che controllano sempre i limiti (`cima == MAX_PILA` → rifiuto). Il compilatore stesso lo impedisce: `'cima' undeclared`.
3. **Perché una pila risolve il problema.** Le parentesi devono chiudersi in ordine inverso a come si aprono: l'ultima aperta è la prima da chiudere. È lo stesso principio dello stack dei record di attivazione (cartella 13): l'ultima funzione chiamata è la prima a terminare.
4. **`controlla`:**
   ```c
   pila_svuota();
   for (i = 0; s[i] != '\0'; i++) {
       c = s[i];
       if (c == '(' || c == '[' || c == '{') {
           if (!pila_push(c)) { *pos = i; return 3; }
       } else if (c == ')' || c == ']' || c == '}') {
           if (!pila_pop(&top) || top != apertura_di(c)) { *pos = i; return 1; }
       }
   }
   if (!pila_vuota()) { *pos = pila_dimensione(); return 2; }
   return 0;
   ```
   Nella condizione `!pila_pop(&top) || top != ...` l'ordine conta: l'operatore `||` valuta la parte destra solo se la sinistra è falsa. Così `top` viene confrontato solo se il pop è riuscito, cioè solo quando contiene davvero un valore.
5. **Pila piena.** Con 101 aperture consecutive, la push numero 101 (posizione 100) fallisce: `troppo annidata (posizione 100)`. Senza il controllo si scriverebbe fuori da `dati` e ASan segnalerebbe `global-buffer-overflow` (scrittura fuori da un vettore globale).

Simulazione di `{[()]}`:

| i | carattere | azione | pila dopo (fondo → cima) |
|---|---|---|---|
| 0 | { | push | { |
| 1 | [ | push | { [ |
| 2 | ( | push | { [ ( |
| 3 | ) | pop → ( corrisponde | { [ |
| 4 | ] | pop → [ corrisponde | { |
| 5 | } | pop → { corrisponde | (vuota) → bilanciata |

Codice completo: `soluzioni/es07_pila_parentesi/`.
</details>

## Prompt pronti per questo argomento
1. "Interrogami con 6 domande su scope, durata e linkage in C (static locale, static globale, funzione static, extern, definizione vs dichiarazione), una alla volta. Per ogni risposta sbagliata spiegami il perché con un esempio di due file."
2. "Scrivimi un programma C su due file (main.c e modulo.c) con un errore di linkage nascosto (static, extern o doppia definizione). Chiedimi di prevedere se compila, se linka e cosa stampa, poi spiegami la risposta."
3. "Ho scritto questa soluzione per es07 di 14-scope-multifile: [incolla i tre file]. Dimmi se è corretta e perché, e se ho rispettato l'incapsulamento (niente accesso diretto allo stato della pila da main.c), senza riscrivermela tutta."
4. "Spiegami passo passo cosa fanno preprocessore, compilatore e linker con `cc main.c pila.c -o prog`, usando i file di es07. Fammi vedere cosa contiene ogni file .o (quali nomi offre e quali cerca) e perché `cima` non è tra quelli offerti."
5. "Generami 3 esercizi nuovi tipo es04 di 14-scope-multifile (un modulo con stato static nascosto e un header con include guard), con input/output di esempio, senza soluzione."

## Riepilogo
- `static` **dentro** una funzione cambia la **durata**: la variabile esiste per tutto il programma, viene inizializzata una volta sola e ricorda il valore tra le chiamate. Lo scope resta locale.
- `static` **fuori** dalle funzioni cambia il **linkage**: la variabile o la funzione resta privata del file. È il modo per costruire moduli con stato nascosto (incapsulamento).
- Una globale si **definisce una volta** (`int n = 0;`) e si **dichiara** negli altri file con `extern int n;`, di solito tramite un header `.h` protetto da include guard. Gli errori su questi nomi arrivano dal **linker**.
- I puntatori a funzione permettono di passare "un comportamento" come parametro o di metterlo in una tabella; `argc`/`argv` portano dentro `main` le parole della riga di comando, sempre come stringhe.

## Glossario
- **Scope (visibilità)** — la zona di codice in cui un nome si può usare.
- **Durata** — per quanto tempo una variabile esiste in memoria durante l'esecuzione.
- **Linkage** — se un nome globale è condiviso tra file (esterno) o privato del suo file (interno).
- **Classe di memorizzazione** — parola chiave che decide durata e linkage: `auto`, `static`, `extern`, `register`.
- **Variabile automatica** — variabile locale normale: nasce nel record di attivazione e muore al `return`.
- **Static locale** — variabile locale che vive per tutto il programma e ricorda il valore tra le chiamate.
- **Static globale / funzione static** — nome visibile solo nel file in cui è definito.
- **extern** — dichiara una variabile globale definita altrove, senza allocarla.
- **Definizione** — crea la cosa: alloca la memoria o scrive il corpo della funzione (una sola volta).
- **Dichiarazione** — annuncia che una cosa esiste e com'è fatta (anche più volte).
- **Header (.h)** — file con le dichiarazioni che un modulo offre agli altri.
- **Include guard** — `#ifndef` / `#define` / `#endif` che impedisce di includere due volte un header.
- **Modulo** — coppia `.c` + `.h` che offre funzioni e nasconde i dettagli interni.
- **Incapsulamento** — nascondere lo stato interno di un modulo e permetterne l'uso solo tramite funzioni.
- **Shadowing (nascondere)** — una variabile interna con lo stesso nome di una esterna la rende invisibile nel suo blocco.
- **Segmento dati** — zona di memoria delle globali e delle static, che esiste per tutta l'esecuzione.
- **Preprocessore** — fase che esegue `#include` e `#define` prima della compilazione.
- **File oggetto (.o)** — codice macchina di un solo file `.c`, ancora da collegare agli altri.
- **Linker** — programma che unisce i file `.o` e collega ogni nome alla sua definizione.
- **Puntatore a funzione** — variabile che contiene l'indirizzo di una funzione e permette di chiamarla.
- **argc / argv** — numero e vettore delle parole della riga di comando (`argv[0]` = nome del programma).
- **atoi** — funzione di `<stdlib.h>` che converte una stringa in un `int`.
- **Pila (stack)** — struttura in cui l'ultimo elemento inserito è il primo a uscire.
- **Generatore pseudo-casuale** — formula che produce numeri dall'aspetto casuale, ripetibili a partire dallo stesso seme.
