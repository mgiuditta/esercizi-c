# 13 — Ricorsione

> Lezioni di riferimento: trascrizione 4.2 (Ricorsione), trascrizione 2.1 E-tivity (MCD con goto), Appunti Unità 4 (capitolo 2 "Ricorsione", paragrafi 2.1–2.15), LEZ 20.
> Tempo stimato: ~4 ore.

## Teoria flash

**Relazione di ricorrenza.** È una definizione in cui il risultato di un problema si ottiene dal risultato dello *stesso* problema, ma più piccolo. Esempio del prof: il fattoriale `n! = n · (n-1)!`, con `0! = 1`. Il prof dice che una ricorrenza si può realizzare in due modi:
- con l'**iterazione** (cioè un ciclo `for`/`while` che ripete delle istruzioni);
- con la **ricorsione** (cioè una funzione che, dentro il proprio corpo, chiama se stessa).

**Funzione ricorsiva.** È una funzione che richiama se stessa (direttamente, o passando da un'altra funzione). Il codice è sempre lo stesso; cambia solo il valore dei parametri, che si avvicina a ogni chiamata a un caso di cui conosciamo già la risposta. Analogia: una fila di persone. Chiedi "quante persone ci sono davanti a te?" alla persona in fondo. Lei non conta: chiede alla persona davanti e aggiunge 1. Solo la prima della fila risponde subito "zero".

**Caso base e passo ricorsivo (o passo induttivo).**
- Il **caso base** è il caso semplice: la funzione risponde *subito*, senza richiamarsi. Nella fila è la prima persona.
- Il **passo ricorsivo** trasforma il problema in uno più piccolo dello stesso tipo e si richiama.

```c
int fattoriale(int n)            /* esempio esatto del prof (trascrizione 4.2) */
{
    if (n <= 1)                  /* caso base */
        return 1;
    else
        return n * fattoriale(n - 1);   /* passo ricorsivo */
}
```

Le tre condizioni degli Appunti (par. 2.5) per una ricorsione corretta: (1) esiste almeno un caso base; (2) il passo riduce il problema; (3) la riduzione **garantisce** di arrivare prima o poi al caso base. Il prof dice: una ricorsione è *ben definita* se ogni passo si avvicina al caso base; se no la definizione è "circolare" e non termina mai.

**Winding e unwinding.** La **fase di winding** (in italiano "avvolgimento", gli Appunti la chiamano "fase di discesa") è quando le chiamate si accumulano: `fattoriale(3)` chiama `fattoriale(2)`, che chiama `fattoriale(1)`. La **fase di unwinding** ("srotolamento", "fase di risalita") inizia quando si raggiunge il caso base: le chiamate terminano una dopo l'altra, in ordine inverso, e i `return` combinano i risultati (`return 1`, poi `2*1`, poi `3*2` = 6).

Regola pratica, utilissima per i "Cosa stampa?": un'istruzione scritta **prima** della chiamata ricorsiva viene eseguita durante il winding (ordine "di andata"); un'istruzione scritta **dopo** viene eseguita durante l'unwinding (ordine inverso). È il trucco della funzione `leggi` del prof, che stampa al contrario una sequenza letta:

```c
void leggi(void) {          /* trascrizione 4.2 */
    int n;
    scanf("%d", &n);
    if (n)                  /* se n != 0 continuo a leggere */
        leggi();
    printf("%d ", n);       /* eseguita al ritorno: ordine inverso */
}
```

**Record di attivazione e stack.** Lo **stack** (in italiano "pila") è la zona di memoria dove il programma tiene le variabili delle funzioni in corso. Un **record di attivazione** è il "foglio" che viene aggiunto in cima alla pila a ogni chiamata: contiene i parametri, le variabili locali e l'indirizzo a cui tornare. Ogni chiamata ricorsiva ha il **suo** record, quindi la sua copia privata di `n`. Nell'esempio del prof `Primo(10)` vengono creati 11 record (a = 10, 9, ..., 0). Lo stack ha una dimensione massima fissata prima che il programma parta (su Linux di solito 8 MB): se la ricorsione non si ferma, la pila si riempie e il programma crolla. Questo crollo si chiama **stack overflow** ("traboccamento della pila").

**Ricorsione multipla.** Quando una funzione si richiama più di una volta nello stesso passo. Esempio degli Appunti: Fibonacci, `F(n) = F(n-1) + F(n-2)` con `F(0) = 0`, `F(1) = 1`. È elegante ma lenta: ricalcola gli stessi valori moltissime volte (lo misuri in es04). Anche la Torre di Hanoi fa due chiamate, ma lì non c'è lavoro ripetuto.

**Ricorsione o iterazione?** Il prof dice che la ricorsione costa di più, perché ogni chiamata alloca un record (tempo e spazio). In cambio il codice è spesso più compatto e più vicino alla definizione matematica. L'iterazione si adatta alle strutture dati "statiche" (un vettore si scorre con un indice); la ricorsione si adatta alle strutture dati dinamiche (liste, alberi: le vedrai più avanti).

**Imprecisioni e contraddizioni nelle fonti** (le trascrizioni sono automatiche):
- "winning", "winding and winding" = *winding* e *unwinding*; "ricorrettivazioni" = *record di attivazione*; "l'attore da noi" = *la torre di Hanoi*; "NAM" = la variabile `num`.
- Nella trascrizione il prof dice "se è 1 so che è 0": è un lapsus. Il caso base restituisce **1** (sia 0! sia 1! valgono 1).
- **Caso base del fattoriale.** Il prof (trascrizione e Appunti par. 2.6) usa `n <= 1`. Gli Appunti al par. 2.10 usano invece `n == 0`. Per n ≥ 0 le due versioni danno lo stesso risultato. Con un n negativo, però, la versione `n == 0` non si ferma mai (−1, −2, ...) e va in stack overflow; `n <= 1` invece termina. Negli esercizi uso `n <= 1`.
- **Hanoi.** Negli Appunti il numero minimo di mosse compare come "2n − 1": l'esponente si è perso nella conversione del PDF. La formula giusta è **2ⁿ − 1** (3 dischi → 7 mosse). Inoltre il caso base `n == 1` degli Appunti non regge `n = 0` (scenderebbe a −1, −2, ...): per questo in es08 il main rifiuta n < 1.
- Nei disegni del prof gli interi occupano 3 celle "per semplificare": in realtà `sizeof(int)` = 4 byte su macOS arm64 e su Linux x86-64. Nei disegni lo stack cresce "verso l'alto" come una pila di piatti; in memoria, sui PC comuni, cresce verso indirizzi più bassi. È la stessa cosa disegnata in due modi.

### Errori tipici
1. **Caso base mancante.** gcc 13 (il compilatore C di Linux) se ne accorge:
   ```text
   e1.c:2:5: warning: infinite recursion detected [-Winfinite-recursion]
   e1.c:4:16: note: recursive call
       4 |     return n * fattoriale(n - 1);
   ```
   Se lo esegui, crolla. Con ASan (AddressSanitizer, cioè lo strumento che `make test` attiva per controllare la memoria mentre il programma gira) il messaggio è chiaro: `AddressSanitizer: stack-overflow`, seguito da centinaia di righe con la stessa funzione.
2. **Caso base che si può "scavalcare"** (`if (n == 1)` con n = 0, oppure `n == 0` con n negativo). Il compilatore **non** avvisa, perché un caso base c'è. Te ne accorgi solo a runtime (cioè mentre il programma gira) con lo stack overflow. Rimedio: un caso base "largo" (`n <= 0`, `n <= 1`) o un controllo dei dati nel main.
3. **Dimenticare il `return` nel passo ricorsivo** (`n * fattoriale(n - 1);` da solo):
   ```text
   e2.c:7:11: warning: value computed is not used [-Wunused-value]
   e2.c:8:1: warning: control reaches end of non-void function [-Wreturn-type]
   ```
   Il valore calcolato viene buttato via e la funzione restituisce un valore casuale.
4. **Stampa dalla parte sbagliata della chiamata.** Una `printf` dopo la chiamata stampa in ordine inverso (unwinding). Nessun avviso: è un errore di logica.
5. **Usare `n--` al posto di `n - 1`** nella chiamata: `fattoriale(n--)` passa il valore *vecchio* di n (il decremento avviene dopo), quindi si richiama sempre con lo stesso valore → ricorsione infinita.
6. **Ricorsione multipla esplosiva.** Fibonacci ricorsivo con n = 45 impiega secondi interi: non è un errore di sintassi, è un costo di 2·F(n+1) − 1 chiamate.

## Esercizi

### es01 — Fattoriale e potenza ricorsivi  ·  Base
**Fonte:** Ispirato a: Trascrizione 4.2 (fattoriale ricorsivo e potenza), Appunti Unità 4, par. 2.6 e 2.8.
**Testo:** completa `fattoriale(n)` e `potenza(i, n)` **senza cicli**: ognuna deve richiamare se stessa. Il main legge n, poi base ed esponente.
```text
input:
3
2 10
output:
3! = 6
2^10 = 1024
```
**File:** `es01_fattoriale_potenza.c` · **Test:** `make test T=13 E=es01`

<details><summary>💡 Suggerimento</summary>
Scrivi prima il caso base con un `if` e un `return` diretto. Poi chiediti: "se qualcuno mi desse già il risultato per n-1, come otterrei quello per n?". Quella è la riga del passo ricorsivo.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Caso base del fattoriale.** 0! e 1! valgono 1: con `if (n <= 1) return 1;` li risolviamo subito. Usiamo `<=` e non `==` perché così anche un n negativo termina subito, invece di scendere all'infinito.
2. **Passo.** `n! = n · (n-1)!`, quindi `return n * fattoriale(n - 1);`. Il parametro cala di 1 a ogni chiamata: prima o poi arriva a 1 (caso base).
3. **Potenza.** Stessa struttura: `i^0 = 1` (caso base `n == 0`), `i^n = i · i^(n-1)`. La base `i` non cambia mai; cala solo l'esponente. Il main rifiuta gli esponenti negativi, perché n non arriverebbe mai a 0.

```c
int fattoriale(int n) { if (n <= 1) return 1; return n * fattoriale(n - 1); }
int potenza(int i, int n) { if (n == 0) return 1; return i * potenza(i, n - 1); }
```

Simulazione di `fattoriale(3)` (la stessa del prof):

| chiamata | n | caso | cosa restituisce |
|---|---|---|---|
| 1ª | 3 | passo | 3 * fattoriale(2) → aspetta |
| 2ª | 2 | passo | 2 * fattoriale(1) → aspetta |
| 3ª | 1 | base | **1** |
| 2ª riprende | 2 | | 2 * 1 = **2** |
| 1ª riprende | 3 | | 3 * 2 = **6** |

Le prime tre righe sono il winding, le ultime due l'unwinding. Attenzione: con `int` (4 byte) il fattoriale è corretto solo fino a 12! = 479001600; 13! non ci sta più (overflow, cioè il risultato supera il valore massimo di un `int`).

Codice completo: `soluzioni/es01_fattoriale_potenza.c`.
</details>

### es02 — MCD ricorsivo (algoritmo di Euclide)  ·  Base
**Fonte:** Ispirato a: Trascrizione 2.1 E-tivity (MCD con goto), riscritto con la ricorsione della Trascrizione 4.2.
**Testo:** nel blocco 2 il prof calcolava il massimo comune divisore (MCD, cioè il numero più grande che divide esattamente entrambi) con i salti `goto modulo` / `goto risultato`. Riscrivilo come funzione ricorsiva `mcd(x, y)`, senza `goto` e senza cicli.
```text
input:
48 18
18 48
output:
MCD(48, 18) = 6
MCD(18, 48) = 6
```
**File:** `es02_mcd_ricorsivo.c` · **Test:** `make test T=13 E=es02`

<details><summary>💡 Suggerimento</summary>
Nel programma con il goto, ogni "giro" sostituisce la coppia (x, y) con (y, x % y) e si ferma quando il resto è 0. "Ripeti con la nuova coppia" diventa "richiamati con la nuova coppia".
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Il legame con il goto.** Nel programma del blocco 2: `r = x % y; if (r == 0) goto risultato; x = y; y = r; goto modulo;`. Ogni giro passa dalla coppia (x, y) alla coppia (y, r). Il `goto modulo` è la ripetizione.
2. **Caso base.** Quando y vale 0, l'MCD è x (ogni numero divide 0). Il prof si fermava un passo prima (resto 0 → stampa y), ma è la stessa cosa: al giro dopo la coppia diventerebbe (y, 0).
3. **Passo.** `return mcd(y, x % y);`. Il resto `x % y` è sempre minore di y, quindi il secondo numero cala a ogni chiamata e prima o poi vale 0: la ricorsione è ben definita.
4. **Bonus.** Il prof nel blocco 2 assumeva x > y "senza verificarlo". Qui non serve: se x < y, `x % y` vale x e la prima chiamata scambia i due numeri da sola (vedi la tabella sotto).

```c
int mcd(int x, int y)
{
    if (y == 0)
        return x;
    return mcd(y, x % y);
}
```

| chiamata | x | y | x % y |
|---|---|---|---|
| mcd(18, 48) | 18 | 48 | 18 |
| mcd(48, 18) | 48 | 18 | 12 |
| mcd(18, 12) | 18 | 12 | 6 |
| mcd(12, 6) | 12 | 6 | 0 |
| mcd(6, 0) | 6 | 0 | caso base → **6** |

Qui l'unwinding non fa calcoli: ogni chiamata restituisce così com'è il valore della chiamata successiva. Questo tipo di ricorsione, in cui la chiamata è l'ultima cosa che la funzione fa, si chiama *ricorsione in coda*.

Codice completo: `soluzioni/es02_mcd_ricorsivo.c`.
</details>

### es03 — Cosa stampa? Prima e dopo la chiamata  ·  Base
**Fonte:** Ispirato a: Trascrizione 4.2 (funzione `leggi`, winding e unwinding), LEZ 20 par. 5.6.
**Testo:** apri `es03_cosa_stampa.c`. È **già completo**. Senza eseguirlo, scrivi qui sotto cosa stampa (parti A, B e C). Poi lancia il test: se passa, il programma fa davvero ciò che è scritto nel `.out`. Confronta con la tua previsione.
```text
La mia previsione:
--- A ---
...
--- B ---
...
--- C ---
...
```
**File:** `es03_cosa_stampa.c` · **Test:** `make test T=13 E=es03`

<details><summary>💡 Suggerimento</summary>
Per ogni funzione dividi le istruzioni in "prima della chiamata" (escono scendendo) e "dopo la chiamata" (escono risalendo, in ordine inverso). Disegna la pila delle chiamate.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output reale:
```text
--- A ---
giu 2
giu 1
giu 0
su 0
su 1
su 2
--- B ---
1 2 3 
--- C ---
110
1101
```

**Parte A — `scendi(2)`.**
1. `scendi(2)` stampa `giu 2`, poi chiama `scendi(1)` e **resta in attesa** (la sua `printf("su ...")` non è ancora stata eseguita).
2. `scendi(1)` stampa `giu 1` e chiama `scendi(0)`.
3. `scendi(0)` stampa `giu 0`; `0 > 0` è falso, quindi non si richiama: stampa subito `su 0` e termina. Fine del winding.
4. Unwinding: riprende `scendi(1)` dopo la chiamata e stampa `su 1`; poi riprende `scendi(2)` e stampa `su 2`.

Ogni chiamata ha la **sua** n nel suo record di attivazione: per questo `scendi(1)`, quando riprende, stampa 1 e non 0.

**Parte B — `conta(3)`.** La `printf` è **dopo** la chiamata. Scendendo non stampa nessuno: 3 → 2 → 1 → 0 (caso base, `return`). Risalendo stampa prima la chiamata con n=1, poi 2, poi 3: `1 2 3 `. Il conto alla rovescia esce "al dritto" perché la stampa avviene in unwinding.

**Parte C — `misterio`.** `misterio(6)`: 6 > 1 → chiama `misterio(3)` → chiama `misterio(1)` → 1 > 1 è falso, quindi stampa `1 % 2` = `1`. Risalendo: `misterio(3)` stampa `3 % 2` = `1`, poi `misterio(6)` stampa `6 % 2` = `0`. Risultato: `110`. Per 13: 13 → 6 → 3 → 1, che risalendo stampano 1, 1, 0, 1 → `1101`.

La funzione misteriosa stampa il numero **in binario** (base 2): 110₂ = 6, 1101₂ = 13. Le cifre binarie si ottengono dalla meno significativa (`n % 2`) alla più significativa. La stampa in unwinding le rimette nell'ordine giusto, con lo stesso trucco della `leggi` del prof.

Il file della soluzione (`soluzioni/es03_cosa_stampa.c`) è identico allo starter.
</details>

### es04 — Fibonacci: quanto costa la ricorsione multipla?  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 4, par. 2.11 (Ricorsione multipla) e par. 2.13 (Ricorsione ed efficienza).
**Testo:** implementa `F(n)` ricorsiva, come negli Appunti, facendole incrementare a ogni chiamata la variabile globale `chiamate` (una variabile **globale** è dichiarata fuori da tutte le funzioni, quindi tutte la vedono). Poi implementa `F_iter(n)` con un ciclo. Il main stampa i due risultati e il numero di chiamate.
```text
input:
5
10
output:
F(5) = 5 | chiamate ricorsive: 15 | iterativo: 5
F(10) = 55 | chiamate ricorsive: 177 | iterativo: 55
```
**File:** `es04_fibonacci_chiamate.c` · **Test:** `make test T=13 E=es04`

<details><summary>💡 Suggerimento</summary>
`chiamate++` va come **prima** istruzione di F, prima dei casi base, così conti anche le chiamate che terminano subito. Per la versione iterativa ti bastano due variabili: "il penultimo" e "l'ultimo" valore calcolato.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Due casi base.** Il passo usa sia `n-1` sia `n-2`. Con un solo caso base, F(1) chiamerebbe F(0) e F(−1), e F(−1) scenderebbe all'infinito. Servono quindi `F(0) = 0` e `F(1) = 1`.
2. **Il contatore.** `chiamate++` all'inizio della funzione: ogni record di attivazione creato vale +1. La variabile è globale, quindi tutte le chiamate incrementano **la stessa** variabile. Se fosse locale, ogni record avrebbe la sua copia, che sparirebbe al ritorno.
3. **Perché è lenta.** Ecco le chiamate di F(4):
   ```text
   F(4)
   ├── F(3)
   │   ├── F(2)
   │   │   ├── F(1)
   │   │   └── F(0)
   │   └── F(1)
   └── F(2)
       ├── F(1)
       └── F(0)
   ```
   F(2) è calcolato due volte e F(1) tre volte: 9 chiamate in tutto per un risultato di 3. In generale le chiamate sono 2·F(n+1) − 1. Con n = 25 diventano 242785, con n = 40 più di 300 milioni. La crescita è *esponenziale*, cioè a ogni +1 di n il lavoro si moltiplica circa per 1,6.
4. **Versione iterativa.** Un ciclo che fa "scorrere" una finestra di due valori: n − 1 somme in tutto, nessun record di attivazione in più.

```c
int F_iter(int n)
{
    int prec = 0, corr = 1, i, prossimo;
    if (n == 0) return 0;
    for (i = 2; i <= n; i++) {
        prossimo = prec + corr;
        prec = corr;
        corr = prossimo;
    }
    return corr;
}
```

| i | prec | corr (= F(i)) |
|---|---|---|
| inizio | 0 | 1 |
| 2 | 1 | 1 |
| 3 | 1 | 2 |
| 4 | 2 | 3 |
| 5 | 3 | 5 |

È la conclusione degli Appunti (par. 2.13): la ricorsione è più vicina alla definizione, l'iterazione è più efficiente. Nota: `F(46)` è il più grande che sta in un `int`, ma qui il main si ferma a 30 per non far aspettare la versione ricorsiva.

Codice completo: `soluzioni/es04_fibonacci_chiamate.c`.
</details>

### es05 — Palindroma ricorsiva  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 4.2 (riduzione del problema verso il caso base), Appunti Unità 4 par. 2.5; variante (senza distinguere maiuscole e minuscole, con due indici) dell'esercizio "parola palindroma" di LEZ 20.
**Testo:** una parola è **palindroma** se si legge uguale nei due versi ("osso", "Radar"). Scrivi `palindroma(s, i, j)`, che controlla la parte di stringa da `s[i]` a `s[j]` senza cicli e senza distinguere maiuscole e minuscole (usa `tolower` di `<ctype.h>`, che trasforma una lettera in minuscola).
```text
input:
Anna osso ciao
output:
Anna: palindroma
osso: palindroma
ciao: non palindroma
```
**File:** `es05_palindroma.c` · **Test:** `make test T=13 E=es05`

<details><summary>💡 Suggerimento</summary>
Ci sono due modi di "rispondere subito": la parte rimasta è lunga 0 o 1 (allora è palindroma), oppure i due estremi sono diversi (allora non lo è). Altrimenti richiamati sulla parte interna: `i+1` e `j-1`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Il problema più piccolo.** "Radar" è palindroma se `R` = `r` (ignorando le maiuscole) **e** la parte interna "ada" è palindroma. La parte interna si accorcia di 2 caratteri a ogni passo.
2. **Caso base 1:** `i >= j`, cioè la parte rimasta ha 0 caratteri (lunghezza pari, gli indici si sono incrociati) o 1 carattere (lunghezza dispari). Una parola così si legge uguale nei due versi: `return 1`.
3. **Caso base 2:** se gli estremi sono diversi, la risposta è subito 0. Non serve guardare dentro.
4. **Passo:** `return palindroma(s, i + 1, j - 1);`. i cresce e j cala, quindi prima o poi `i >= j`: la ricorsione termina sempre.
5. **Il cast `(unsigned char)`.** `tolower` vuole un valore non negativo. Su molti sistemi `char` può essere negativo (per esempio con le lettere accentate), e passarlo così è comportamento indefinito, cioè il C non garantisce cosa succede.

```c
int palindroma(char s[], int i, int j)
{
    if (i >= j) return 1;
    if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j])) return 0;
    return palindroma(s, i + 1, j - 1);
}
```

| chiamata | i | j | s[i] | s[j] | esito |
|---|---|---|---|---|---|
| 1ª | 0 | 4 | R | r | uguali → continua |
| 2ª | 1 | 3 | a | a | uguali → continua |
| 3ª | 2 | 2 | — | — | i >= j → **1** |

Con una parola di 1 lettera ("x") la prima chiamata è già `palindroma(s, 0, 0)` → caso base.

Codice completo: `soluzioni/es05_palindroma.c`.
</details>

### es06 — Trova e correggi l'errore  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 4.2 ("una ricorsione è ben definita se ogni passo si avvicina al caso base"), Appunti Unità 4 par. 2.5, LEZ 20 cap. 5.
**Testo:** il file compila, ma contiene **tre errori**, uno per funzione. Con input `5` l'output è sbagliato; con input `0` il programma crolla (AddressSanitizer scrive `stack-overflow`). Trovali e correggili.
```text
input:
5
output corretto:
cifre(5) = 1
somma 1..5 = 15
rovescia: 5 4 3 2 1 via!
```
**File:** `es06_trova_errore.c` · **Test:** `make test T=13 E=es06`

<details><summary>💡 Suggerimento</summary>
Per ogni funzione chiediti tre cose: il valore restituito dal caso base è giusto? Il caso base si raggiunge con **tutti** gli input ammessi (anche 0)? Le stampe stanno dalla parte giusta della chiamata?
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

**Errore 1 — `cifre`: caso base con il valore sbagliato.** `if (n < 10) return 0;` dice che un numero di una cifra ha 0 cifre. Tutti i risultati escono quindi più piccoli di 1 (cifre(5) = 0, cifre(1234) = 3). Correzione: `return 1;`. Questo errore **non** fa crollare il programma: dà un risultato sbagliato e silenzioso, ed è proprio per questo che va controllato con un test.

**Errore 2 — `somma_fino`: caso base che si può scavalcare.** `if (n == 1) return 1;` funziona per n ≥ 1. Con n = 0, però, la chiamata successiva è `somma_fino(-1)`, poi −2, −3, ...: n si **allontana** dal caso base. Ogni chiamata aggiunge un record di attivazione, finché lo stack (circa 8 MB) si riempie. ASan lo segnala così:
```text
ERROR: AddressSanitizer: stack-overflow on address 0x7ffd01bffff8 ...
    #0 ... in somma_fino es06_trova_errore.c:28
    #1 ... in somma_fino es06_trova_errore.c:31
    #2 ... in somma_fino es06_trova_errore.c:31
```
La stessa funzione ripetuta migliaia di volte è il segno di una ricorsione infinita. Correzione: un caso base "largo", `if (n <= 0) return 0;`. Così n = 0 è gestito e la somma vuota vale 0, come in matematica. Il compilatore non avvisa, perché un caso base esiste: è la terza condizione degli Appunti ("la riduzione deve garantire di raggiungere il caso base") a essere violata.

**Errore 3 — `rovescia`: stampa in unwinding.** La `printf("%d ", n)` sta **dopo** la chiamata, quindi viene eseguita risalendo: prima `via!`, poi 1 2 3 4 5. Correzione: stampa prima di richiamarti.
```c
printf("%d ", n);
rovescia(n - 1);
```

Codice completo: `soluzioni/es06_trova_errore.c` (le righe corrette sono marcate con `CORRETTO`).
</details>

### es07 — Vettore ricorsivo: somma, massimo, ricerca binaria  ·  Tipo esame
**Fonte:** Ispirato a: Trascrizione 4.2 e Appunti Unità 4 par. 2.10 (iterazione e ricorsione sulle stesse strutture); variante (tracciata e unita a somma e massimo) degli esercizi 4 e 9 di LEZ 20.
**Testo:** input: n (1..100), poi n interi **ordinati in modo crescente**, poi un numero qualsiasi di valori da cercare. Implementa senza cicli:
- `somma(v, n)`: somma dei primi n elementi;
- `massimo(v, n)`: massimo dei primi n elementi;
- `cerca(v, sx, dx, x)`: **ricerca binaria** in `v[sx..dx]`. È la ricerca "del dizionario": guardi l'elemento centrale e scarti la metà in cui x non può stare. A ogni chiamata su un intervallo non vuoto stampa `[sx,dx] `. Restituisce la posizione oppure −1.
```text
input:
8
1 3 4 7 9 11 15 20
7
8
output:
somma = 70
massimo = 20
cerco 7: [0,7] -> trovato in posizione 3
cerco 8: [0,7] [4,7] [4,4] -> non presente
```
**File:** `es07_vettore_ricorsivo.c` · **Test:** `make test T=13 E=es07`

<details><summary>💡 Suggerimento</summary>
Somma e massimo: "il problema su n elementi = l'ultimo elemento combinato con il problema sui primi n−1". Ricerca: il caso base "non c'è" è l'intervallo vuoto (`sx > dx`). Controllalo **prima** di stampare e di leggere `v[med]`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **somma.** Caso base: n = 0, il vettore "vuoto" ha somma 0. Passo: `v[n-1] + somma(v, n-1)`. Ricorda che un vettore passato a una funzione è in realtà l'indirizzo del suo primo elemento: nessuna copia, tutte le chiamate guardano lo stesso vettore e cambia solo n, cioè "quanti elementi considero".
2. **massimo.** Il caso base è n = 1 (il massimo di un elemento è lui stesso), non n = 0: un vettore vuoto non ha massimo. Passo: calcolo il massimo dei primi n−1 e lo confronto con `v[n-1]`.
3. **cerca.** A ogni chiamata l'intervallo si dimezza:
   - se `sx > dx`, l'intervallo è vuoto → `return -1` (caso base "non trovato");
   - `med = (sx + dx) / 2`; se `v[med] == x` → `return med` (caso base "trovato");
   - se `x < v[med]` cerco in `[sx, med-1]`, altrimenti in `[med+1, dx]`.
   Funziona **solo** se il vettore è ordinato: è l'ordinamento che permette di scartare una metà.
4. **Perché il controllo del vuoto va per primo.** Con `sx > dx`, `med` potrebbe valere −1 o n, e `v[med]` leggerebbe fuori dal vettore. ASan lo segnalerebbe come `stack-buffer-overflow` (lettura fuori dai confini di un vettore che sta sullo stack).

```c
int cerca(int v[], int sx, int dx, int x)
{
    int med;
    if (sx > dx) return -1;
    printf("[%d,%d] ", sx, dx);
    med = (sx + dx) / 2;
    if (v[med] == x) return med;
    if (x < v[med]) return cerca(v, sx, med - 1, x);
    return cerca(v, med + 1, dx, x);
}
```

Simulazione di "cerco 8" in `1 3 4 7 9 11 15 20`:

| chiamata | sx | dx | med | v[med] | decisione |
|---|---|---|---|---|---|
| 1ª | 0 | 7 | 3 | 7 | 8 > 7 → destra |
| 2ª | 4 | 7 | 5 | 11 | 8 < 11 → sinistra |
| 3ª | 4 | 4 | 4 | 9 | 8 < 9 → sinistra |
| 4ª | 4 | 3 | — | — | vuoto → −1 (nessuna stampa) |

Con 8 elementi bastano al massimo 4 chiamate. Con 1000 elementi ne bastano circa 10: ecco perché la ricerca binaria è così veloce.

Codice completo: `soluzioni/es07_vettore_ricorsivo.c`.
</details>

### es08 — Torre di Hanoi con conteggio delle mosse  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 4, par. 2.12 (funzione `hanoi(n, s, d, a)` e `muoviDisco`), citata dal prof nella trascrizione 4.2.
**Testo:** tre paletti (1, 2, 3) e n dischi (1..10) infilati sul paletto 1, dal più grande in basso al più piccolo in alto. Bisogna spostarli tutti sul paletto 3. Regole: si sposta un disco alla volta, e mai un disco grande sopra uno più piccolo. Usa la funzione degli Appunti, con in più il **numero del disco** (1 = il più piccolo) e un **contatore delle mosse** passato per indirizzo. Alla fine verifica la formula 2ⁿ − 1 usando la tua `potenza` di es01.
```text
input:
3
output:
mossa 1: disco 1 da 1 a 3
mossa 2: disco 2 da 1 a 2
mossa 3: disco 1 da 3 a 2
mossa 4: disco 3 da 1 a 3
mossa 5: disco 1 da 2 a 1
mossa 6: disco 2 da 2 a 3
mossa 7: disco 1 da 1 a 3
Totale mosse: 7 (2^3 - 1 = 7)
```
**File:** `es08_hanoi.c` · **Test:** `make test T=13 E=es08`

<details><summary>💡 Suggerimento</summary>
Nel caso base si sposta sempre il disco 1. Nel passo, la mossa "centrale" (quella tra le due chiamate) sposta il disco n, il più grande del sottoproblema. Il contatore va incrementato con `(*mosse)++`: le parentesi servono, perché `*mosse++` sposterebbe il puntatore invece di incrementare il valore puntato.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **L'idea "di fiducia".** Supponi di saper già spostare n−1 dischi. Allora per spostarne n da s a d: (1) sposti gli n−1 dischi di sopra su a, usando d come appoggio; (2) sposti il disco n, ora libero, su d; (3) riporti gli n−1 dischi da a a d, usando s come appoggio. Nota come i ruoli dei paletti si scambiano nelle due chiamate.
2. **Caso base.** n = 1: si sposta direttamente il disco 1. Il main rifiuta n = 0, che scavalcherebbe questo caso base.
3. **Perché il contatore è un puntatore.** Ogni chiamata ha il suo record di attivazione. Se passassimo `int mosse` per valore, ogni record avrebbe una copia privata e il main vedrebbe sempre 0. Passando `&mosse`, tutte le chiamate scrivono nella stessa cella, quella del main. È il caso "parametro passato per indirizzo nella ricorsione" che il prof cita nella trascrizione: "in alcuni casi potrebbe aver senso".
4. **Formula.** Le mosse sono M(n) = 2·M(n−1) + 1 con M(1) = 1, cioè 1, 3, 7, 15, ... = 2ⁿ − 1.

```c
void hanoi(int n, int s, int d, int a, int *mosse)
{
    if (n == 1)
        muoviDisco(1, s, d, mosse);
    else {
        hanoi(n - 1, s, a, d, mosse);
        muoviDisco(n, s, d, mosse);
        hanoi(n - 1, a, d, s, mosse);
    }
}
```

Albero delle chiamate per n = 2 (s=1, d=3, a=2):

| chiamata | cosa fa | mossa stampata |
|---|---|---|
| hanoi(2,1,3,2) | passo 1: hanoi(1,1,2,3) | mossa 1: disco 1 da 1 a 2 |
| hanoi(2,1,3,2) | passo 2: muoviDisco(2,1,3) | mossa 2: disco 2 da 1 a 3 |
| hanoi(2,1,3,2) | passo 3: hanoi(1,2,3,1) | mossa 3: disco 1 da 2 a 3 |

Codice completo: `soluzioni/es08_hanoi.c`.
</details>

## Prompt pronti per questo argomento
1. "Interrogami con 5 domande sulla ricorsione in C (caso base, passo ricorsivo, winding/unwinding, record di attivazione, stack overflow), una alla volta. Aspetta la mia risposta prima di passare alla successiva e correggimi spiegando il perché."
2. "Dammi 3 funzioni ricorsive brevi in C con `printf` sia prima sia dopo la chiamata ricorsiva e chiedimi cosa stampano con un certo input. Non darmi la soluzione finché non rispondo."
3. "Ho scritto questa soluzione per es07 di 13-ricorsione: [incolla codice]. Dimmi se è corretta e perché, segnala i casi limite che non gestisco (vettore di 1 elemento, valore assente), senza riscrivermela tutta."
4. "Prendi questa funzione iterativa: [incolla codice]. Guidami passo passo a riscriverla in forma ricorsiva: prima chiedimi qual è il caso base, poi qual è il passo, poi controlla con me che la ricorsione termini."
5. "Generami 3 esercizi nuovi tipo es08 di 13-ricorsione (ricorsione multipla, tipo esame) con input/output di esempio, senza soluzione."

## Riepilogo
- Una funzione ricorsiva ha un **caso base** (risponde subito) e un **passo ricorsivo** (si richiama su un problema più piccolo). Il passo deve avvicinarsi **sempre** al caso base, per ogni input ammesso.
- Ogni chiamata crea il suo **record di attivazione** sullo stack, con la sua copia di parametri e variabili locali. Troppe chiamate, o una ricorsione infinita, provocano lo **stack overflow**.
- Le istruzioni prima della chiamata vengono eseguite nel **winding** (in ordine); quelle dopo vengono eseguite nell'**unwinding** (in ordine inverso).
- Ricorsione: più vicina alla definizione matematica. Iterazione: più efficiente. La ricorsione multipla (Fibonacci) può costare un numero esponenziale di chiamate.

## Glossario
- **Relazione di ricorrenza** — definizione di un risultato in termini dello stesso problema su dati più piccoli.
- **Iterazione** — ripetizione ottenuta con un ciclo (`for`, `while`).
- **Ricorsione** — ripetizione ottenuta con una funzione che chiama se stessa.
- **Caso base** — input per cui la funzione risponde senza richiamarsi.
- **Passo ricorsivo (passo induttivo)** — parte che riduce il problema e si richiama.
- **Winding (fase di discesa)** — fase in cui le chiamate si accumulano verso il caso base.
- **Unwinding (fase di risalita)** — fase in cui le chiamate terminano in ordine inverso e combinano i risultati.
- **Stack (pila)** — zona di memoria che contiene i record delle funzioni in corso; l'ultimo aggiunto è il primo tolto.
- **Record di attivazione** — blocco sullo stack con i parametri, le variabili locali e l'indirizzo di ritorno di una chiamata.
- **Stack overflow** — crollo del programma quando lo stack supera la dimensione massima.
- **Ricorsione multipla** — più chiamate ricorsive nello stesso passo (Fibonacci, Hanoi).
- **Ricorsione in coda** — la chiamata ricorsiva è l'ultima operazione della funzione (es. `mcd`).
- **Ricerca binaria** — ricerca in un vettore ordinato che a ogni passo scarta metà degli elementi.
- **MCD (massimo comune divisore)** — il numero più grande che divide esattamente due interi.
- **Variabile globale** — variabile dichiarata fuori da tutte le funzioni, visibile da tutte.
- **Overflow (di un intero)** — risultato troppo grande per il tipo (es. 13! in un `int`).
- **Runtime** — il momento in cui il programma è in esecuzione (contrario: compile time, la compilazione).
- **ASan (AddressSanitizer)** — strumento del compilatore che, mentre il programma gira, segnala gli errori di memoria (stack overflow, letture fuori da un vettore).
- **Comportamento indefinito** — situazione in cui lo standard C non garantisce cosa succede.
