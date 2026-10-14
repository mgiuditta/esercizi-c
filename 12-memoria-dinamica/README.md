# 12 — Memoria dinamica

> Lezioni di riferimento: trascrizioni 4.0 (Introduzione Blocco 4) e 4.1 (Memoria dinamica), Appunti Unità 4 (cap. 1 "Memoria Dinamica", par. 1.1–1.13), LEZ 19.
> Tempo stimato: ~5 ore.

## Teoria flash

**1. Stack e heap.** La memoria di un programma in esecuzione (il **processo**) è divisa in zone. Le variabili locali stanno nello **stack** (pila): nascono quando una funzione viene chiamata e spariscono quando la funzione termina, insieme al suo record di attivazione. Lo **heap** (in inglese "mucchio"; nella trascrizione compare come "HIP") è una zona da cui il programma chiede blocchi di memoria *durante l'esecuzione*. Quei blocchi restano validi finché il programma stesso non li restituisce. Analogia: lo stack è il banco dell'aula, che a fine lezione viene sgomberato in automatico; lo heap è un armadietto preso in affitto, che resta tuo finché non riconsegni la chiave.
Serve per due motivi (lezione 4.1): (a) la dimensione di un vettore si conosce solo a runtime (per esempio la decide l'utente), e un vettore statico troppo piccolo "sfora" mentre uno troppo grande spreca; (b) una funzione deve restituire un vettore, e un vettore locale sparirebbe al `return`.

**2. Le quattro funzioni (in `stdlib.h`).**
```c
int *p = (int *) malloc(n * sizeof(int));   /* n interi, contenuto CASUALE */
int *q = (int *) calloc(n, sizeof(int));    /* n interi, tutti a 0 */
int *t = (int *) realloc(p, 2 * n * sizeof(int)); /* cambia dimensione */
free(q);                                    /* restituisce il blocco */
```
- `malloc(byte)` vuole un numero di **byte**. Per questo si scrive sempre `n * sizeof(tipo)`. `sizeof` (l'operatore che dice quanti byte occupa un tipo) rende il codice portabile tra sistemi diversi.
- Restituiscono un `void *`, cioè un "indirizzo di non so che cosa". Il cast `(int *)` dice al compilatore di trattarlo come indirizzo di interi. `size_t` è il tipo intero senza segno usato per le dimensioni.
- `realloc(p, nuovi_byte)` prova ad allargare il blocco sul posto. Se non c'è spazio, ne crea uno nuovo, ci copia i vecchi dati, libera il vecchio e restituisce il **nuovo indirizzo**. La parte nuova non viene azzerata.
- Sul blocco ottenuto si lavora come su un vettore: `p[i]` è identico a `*(p + i)`.

**3. Controllare sempre NULL.** Se la memoria non basta, le tre funzioni di allocazione restituiscono `NULL`. NULL vale "falso" in una condizione, quindi `if (!p)` equivale a `if (p == NULL)`.
```c
int *tmp = (int *) realloc(v, nuova * sizeof(int));
if (tmp == NULL) { /* v e' ancora valido: lo posso usare o liberare */ }
else v = tmp;
```
Non scrivere `v = realloc(v, ...)`: se fallisce, `v` diventa NULL e perdi l'unico indirizzo del vecchio blocco.

**4. `free` e i tre errori classici.**
- **Memory leak** (perdita di memoria): allochi e non liberi mai. Il processo occupa sempre più memoria.
- **Dangling pointer** (puntatore "pendente"): dopo `free(p)`, `p` contiene ancora il vecchio indirizzo, ma il blocco non è più tuo. Usarlo è un **use-after-free**. Rimedio: `free(p); p = NULL;`.
- **Double free**: chiamare `free` due volte sullo stesso blocco.
Regole degli appunti (par. 1.9): si libera una sola volta, si liberano solo blocchi avuti da malloc/calloc/realloc (mai un vettore locale) e si passa a `free` esattamente l'indirizzo restituito da malloc. Se devi scorrere il blocco, usa un **secondo** puntatore.

**5. Matrice dinamica = vettore di puntatori (par. 1.10).**
```c
int **A = (int **) calloc(m, sizeof(int *));   /* m caselle-puntatore */
for (i = 0; i < m; i++)
    A[i] = (int *) calloc(n, sizeof(int));     /* ogni riga per conto suo */
/* ... A[i][j] ... */
for (i = 0; i < m; i++) free(A[i]);            /* prima le righe */
free(A);                                       /* poi il vettore di puntatori */
```
Qui `int **` è corretto, perché `A` contiene davvero degli indirizzi. È diverso dalla matrice statica della cartella 11, che invece è un blocco unico di interi.

**6. Funzioni che creano vettori (par. 1.11–1.12).** Ci sono due modi. Nel primo la funzione fa `return` del puntatore allocato: `int *creavettore(int n)`. Nel secondo riceve l'indirizzo del puntatore del chiamante: `void creavettore(int **pV, int n) { *pV = calloc(...); }`, chiamata con `creavettore(&V, n)`. In entrambi i casi chi chiama dovrà fare la `free`.

**AddressSanitizer (ASan)** è lo strumento che il runner attiva con `-fsanitize=address`. Controlla ogni accesso alla memoria e ferma il programma con un rapporto: `heap-buffer-overflow` (hai scritto o letto oltre la fine di un blocco), `heap-use-after-free` (hai usato un blocco già liberato), `attempting double-free`. Il runner lo mostra come **CRASH**. Il controllo dei leak è **spento** nel runner (`detect_leaks=0`), perché su macOS non funziona: un leak non fa fallire i test.

**Assunzioni:** `sizeof(int)` = 4, `sizeof(double)` = 8, `sizeof(int *)` = `sizeof(char *)` = 8 (macOS arm64, Linux x86-64).

**Imprecisioni e contraddizioni nelle fonti:**
- Trascrizione 4.1: il `void *` "deve essere castato". In C il cast **non è obbligatorio**: `int *p = malloc(...)` compila senza avvisi. È obbligatorio in C++. Qui lo scriviamo sempre, come il prof.
- Trascrizione 4.1, esempio `typedef struct { int a; double b; } esempio;`: il prof dice che `sizeof` "stamperebbe la sizeof dell'intero più la sizeof del double" (12). In realtà stampa **16**: il compilatore aggiunge 4 byte vuoti (*padding*) dopo `a`, così `b` inizia a un indirizzo multiplo di 8. Lo verifichi in es02, riga H. Morale: usa sempre `sizeof(tipo)`, non sommare a mano.
- Trascrizione 4.1: "se [il puntatore] punta una cella a metà libererà da lì in poi e l'altra rimarrà allocata". Non è così: passare a `free` un indirizzo diverso da quello restituito da malloc è **comportamento indefinito** (il linguaggio non garantisce niente). Con glibc il programma si ferma con `free(): invalid pointer`. La conclusione pratica resta giusta: non farlo mai.
- Appunti par. 1.7 scrivono `p = realloc(p, nuova_dimensione);`. Funziona, ma se realloc fallisce perdi il blocco (vedi punto 3). Usa il puntatore temporaneo.
- Appunti par. 1.4 stampano `sizeof` con `%lu`. Il formato esatto per `size_t` è `%zu`. Negli esercizi convertiamo a `int` e usiamo `%d`.
- Appunti par. 1.8: NULL "definito in stddef.h". È definito anche in `stdio.h`, `stdlib.h` e `string.h`: sono vere entrambe le cose.
- Trascrizione automatica: "dialogare" = deallocare, "sizeT" = `size_t`, "call lock" = calloc, "Marco Nisetti" = Marco Anisetti.

### Errori tipici
1. **Dimenticare `#include <stdlib.h>`:** `warning: implicit declaration of function 'malloc' [-Wimplicit-function-declaration]` e `warning: incompatible implicit declaration of built-in function 'malloc'`.
2. **`malloc(n)` invece di `malloc(n * sizeof(int))`:** il compilatore tace, ASan in esecuzione dice `heap-buffer-overflow ... WRITE of size 4 ... located 0 bytes after 5-byte region` (es04).
3. **Usare un blocco dopo `free`:** gcc a volte se ne accorge (`warning: pointer 'v' used after 'free' [-Wuse-after-free]`); ASan sempre: `heap-use-after-free ... READ of size 4`.
4. **Liberare un vettore locale:** `int v[5]; free(v);` → `warning: 'free' called on unallocated object 'v' [-Wfree-nonheap-object]`.
5. **Restituire un vettore locale invece di allocarlo:** `int v[10]; return v;` → `warning: function returns address of local variable [-Wreturn-local-addr]`.
6. **Stringhe senza il +1:** `malloc(strlen(s))` dimentica il byte del `'\0'`; ASan segnala `heap-buffer-overflow` alla prima `strcpy`.

## Esercizi

### es01 — Un vettore di dimensione decisa a runtime  ·  Base
**Fonte:** Ispirato a: Appunti Unità 4, par. 1.5 "Vettori dinamici" (`p = (int *) malloc(n * sizeof(int));`) e par. 1.8 (controllo di NULL); trascrizione 4.1 ("dimensioni note soltanto nell'esecuzione, perché dipendono da un input utente").
**Testo:** completa `leggi_vettore(n)`. Alloca con malloc n interi, controlla NULL, legge n valori e restituisce il puntatore. Se una lettura fallisce, libera e restituisce NULL. Nel `main` aggiungi la `free` finale. Il programma stampa la media e i valori strettamente sopra la media.
```text
Input:
5
18 25 30 12 22
Output:
media: 21.40
sopra la media: 25 30 22
```
Con `n = 0`: `nessun valore`.
**File:** `es01_vettore_runtime.c` · **Test:** `make test T=12 E=es01`

<details><summary>💡 Suggerimento</summary>
Il blocco allocato dentro `leggi_vettore` resta valido dopo il `return`, perché sta nello heap e non nello stack della funzione. Per questo la `free` la fa il `main`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. `v = (int *) malloc(n * sizeof(int));` chiede n × 4 byte. Scrivere `malloc(n)` chiederebbe solo n byte (vedi es04).
2. `if (v == NULL) return NULL;` Se la memoria non basta, malloc lo segnala così. Usare v senza questo controllo farebbe crollare il programma.
3. Ciclo di `scanf("%d", &v[i])`. `&v[i]` è l'indirizzo della casella i, identico a `v + i`. Se una lettura fallisce, prima `free(v)`, poi `return NULL`: altrimenti quel blocco andrebbe perso (leak).
4. Nel `main`: `free(v); v = NULL;`. Una malloc, una free. Mettere v a NULL evita di usarlo per sbaglio dopo.

Il test 2 (n = 1, valore −4) è il caso limite: nessun valore è *strettamente* sopra la media, quindi la riga resta vuota. Codice in `soluzioni/es01_vettore_runtime.c`.
</details>

### es02 — Cosa stampa? calloc, sizeof, realloc e NULL  ·  Base
**Fonte:** Ispirato a: trascrizione 4.1 (calloc "inizializza anche l'intero blocco a zero", realloc, "null vale falso", esempio `sizeof` della struct `esempio`) e Appunti Unità 4, par. 1.4, 1.6, 1.7, 1.9.
**Testo:** `es02_cosa_stampa_heap.c` è già completo. Prima di eseguirlo, prevedi le righe A–H:
```text
A: ? ?
B: ? ?
C: ? ?
D: ?
E: ? ?
F: ? ?
G: ?
H: ? ?
```
**File:** `es02_cosa_stampa_heap.c` · **Test:** `make test T=12 E=es02`

<details><summary>💡 Suggerimento</summary>
`sizeof` su un vettore dà la dimensione di tutto il vettore. Su un puntatore dà la dimensione dell'indirizzo, qualunque sia la grandezza del blocco a cui punta. Per la riga H, ripensa all'imprecisione segnalata nella Teoria flash.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

```text
A: 40 8
B: 0 0
C: 9 3
D: 12
E: 9 81
F: 1 1
G: 0
H: 12 16
```
1. **A = 40 8.** `v` è un vettore di 10 int (10 × 4 = 40 byte). `p` è solo un indirizzo (8 byte): `sizeof` non sa nulla del blocco nello heap. Per questo, con la memoria dinamica, la dimensione la devi ricordare tu in una variabile.
2. **B = 0 0.** `calloc` azzera il blocco. Con `malloc` il contenuto sarebbe casuale (e leggerlo è un errore).
3. **C = 9 3.** Dopo il ciclo `p[i] = i*i`, `q = p + 3` punta alla casella 3, che vale 9. `q - p` è la distanza in *elementi*: 3.
4. **D = 12.** La stessa distanza in byte: 3 × 4.
5. **E = 9 81.** `realloc` conserva i vecchi valori anche se sposta il blocco. Il vecchio `q` invece non va più usato: puntava al blocco vecchio, e per questo il codice lo mette a NULL.
6. **F = 1 1.** `q == NULL` è vero (1). `!q` è vero perché NULL vale falso.
7. **G = 0.** Dopo `free(p); p = NULL;` la condizione `p ? 1 : 0` dà 0.
8. **H = 12 16.** 4 + 8 = 12, ma la struct occupa 16 byte a causa del padding (4 byte vuoti dopo `a`, così `b` inizia a un indirizzo multiplo di 8). È la contraddizione con la trascrizione.

Codice: `soluzioni/es02_cosa_stampa_heap.c` (identico allo starter).
</details>

### es03 — Duplicare una stringa nello heap (strdup fatta a mano)  ·  Base
**Fonte:** Ispirato a: Appunti Unità 4, par. 1.11 (funzione che alloca e restituisce il puntatore) e par. 1.4 (calcolo della dimensione).
**Testo:** completa `char *duplica(const char *s)`. Deve allocare **esattamente** i byte che servono, copiare la stringa e restituire il nuovo blocco. Il `main` mette la copia in maiuscolo e mostra che l'originale non cambia.
```text
Input:
ciao mondo
Output:
originale: [ciao mondo]
copia:     [CIAO MONDO]
blocchi distinti: si
byte allocati: 11
```
Caso limite: una riga vuota deve allocare 1 byte (solo il `'\0'`).
**File:** `es03_duplica_stringa.c` · **Test:** `make test T=12 E=es03`

<details><summary>💡 Suggerimento</summary>
`strlen("ciao")` vale 4, ma la stringa in memoria occupa 5 byte. Copia anche il terminatore.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. `len = strlen(s)` conta i caratteri **senza** il `'\0'`.
2. `copia = (char *) malloc(len + 1);` Il +1 è il punto chiave. Senza, la copia non avrebbe spazio per il terminatore: scrivendolo si andrebbe un byte oltre il blocco (ASan: `heap-buffer-overflow`). Non serve `* sizeof(char)`, che vale 1 per definizione.
3. Controllo `NULL`.
4. `for (i = 0; i <= len; i++) copia[i] = s[i];` Il `<=` copia anche il `'\0'`. In alternativa: `strcpy(copia, s)`.
5. **Perché non basta `char *c = riga;`?** Così copieresti solo l'indirizzo, e i due puntatori indicherebbero lo stesso blocco: mettendo in maiuscolo `c`, cambierebbe anche `riga`. La riga "blocchi distinti: si" confronta i due indirizzi.
6. Il `main` fa `free(c)`: chi riceve memoria da `duplica` deve restituirla.

La `strdup` della libreria fa la stessa cosa, ma non fa parte del C11 standard. Per questo la scriviamo a mano. Codice in `soluzioni/es03_duplica_stringa.c`.
</details>

### es04 — Trova e correggi gli errori di memoria  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 4, par. 1.9 ("la memoria deve essere liberata una sola volta", "dopo la chiamata a free il puntatore non deve essere utilizzato", memory leak) e trascrizione 4.1 ("dopo la free il puntatore punta ancora all'area ma non è più allocata").
**Testo:** il programma legge n interi in un vettore dinamico, stampa il massimo con la sua posizione e poi i numeri al contrario (usando un secondo vettore dinamico). Ci sono **quattro errori di memoria**. Lanciando il test, ASan ne fa "esplodere" uno alla volta (**CRASH**): correggi, rilancia e leggi il messaggio successivo. Il quarto il test **non** lo vede. gcc dà anche un avviso: è un indizio.
```text
Input:
5
4 -2 9 7 9
Output atteso:
massimo: 9 (posizione 2)
al contrario: 9 7 9 -2 4
```
**File:** `es04_trova_errore_memoria.c` · **Test:** `make test T=12 E=es04`

<details><summary>💡 Suggerimento</summary>
Leggi il rapporto di ASan dall'alto: la prima riga dice *che cosa* (overflow, use-after-free, double free), le righe `#… in main …es04_trova_errore_memoria.c:NN` dicono *dove*. Per il quarto errore conta le malloc e le free.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Errore 1: `malloc(n)`.** ASan risponde:
   `ERROR: AddressSanitizer: heap-buffer-overflow ... WRITE of size 4 ... in main es04_trova_errore_memoria.c:45` e `located 0 bytes after 5-byte region`. Tradotto: la `scanf` ha scritto 4 byte (un int) subito dopo la fine di un blocco di 5 byte. malloc vuole i byte, non gli elementi. Correzione: `malloc(n * sizeof(int))`.
2. **Errore 2: `free(v)` prima di `printf(... *pmax ...)`.** `pmax` punta *dentro* il blocco di `v`. Dopo la free è un dangling pointer. ASan:
   `ERROR: AddressSanitizer: heap-use-after-free ... READ of size 4`, seguito da `freed by thread T0 here:` (dove è stato liberato) e `previously allocated by thread T0 here:` (dove era stato allocato). Correzione: prima si usa, poi si libera. Nota: questo è l'errore che ti fa vedere un CRASH anche se il programma "sembra" stampare il numero giusto. Senza ASan potrebbe stampare 9 per caso, perché la memoria liberata spesso non viene subito sovrascritta.
3. **Errore 3: due `free(v)`.** Il compilatore lo segnala: `warning: pointer 'v' used after 'free' [-Wuse-after-free]`. ASan: `ERROR: AddressSanitizer: attempting double-free`. Correzione: una sola free.
4. **Errore 4: `inverso` non viene mai liberato (memory leak).** Il test non lo vede, perché il runner spegne il controllo dei leak. Su Linux puoi vederlo con `ASAN_OPTIONS=detect_leaks=1 ./programma`: `ERROR: LeakSanitizer: detected memory leaks ... Direct leak of 20 byte(s) in 1 object(s)` (5 int = 20 byte). Correzione: `free(inverso)`.
5. In più la soluzione, se una `scanf` o la seconda malloc falliscono, libera ciò che aveva già allocato prima di uscire.

Codice corretto in `soluzioni/es04_trova_errore_memoria.c`.
</details>

### es05 — Funzioni che creano vettori: con `return` e con `int **`  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 4, par. 1.11 (`int *creavettore(int n)`) e 1.12 (`void creavettore(int **pV, int n)`); trascrizione 4.1 ("ho passato l'indirizzo del puntatore e poi alloco la zona di memoria").
**Testo:** completa `crea_inverso(v, n)`, che **restituisce** un nuovo vettore dinamico con gli elementi in ordine inverso. Completa poi `crea_fibonacci(&f, n)`, che alloca il vettore **scrivendo nel puntatore del chiamante** e lo riempie con i primi n numeri di Fibonacci (0, 1, 1, 2, 3, 5, …: ognuno è la somma dei due precedenti). Ritorna 0, oppure −1 se l'allocazione fallisce.
```text
Input:
6
1 2 3 4 5 6
Output:
inverso: 6 5 4 3 2 1
fibonacci(6): 0 1 1 2 3 5
```
**File:** `es05_crea_vettori.c` · **Test:** `make test T=12 E=es05`

<details><summary>💡 Suggerimento</summary>
Dentro `crea_fibonacci`, `pV` è l'indirizzo della variabile `fib` del `main`. Il vettore si assegna a `*pV`, e per l'elemento i si scrive `(*pV)[i]`, con le parentesi.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Modo a (return):** `r = calloc(n, sizeof(int)); ... return r;`. È lecito restituire `r` perché punta allo heap. Restituire un `int r[100]` locale sarebbe un errore (Errore tipico 5): al `return` quella memoria sparisce.
2. **Modo b (`int **`):** il C passa tutto per valore. Se la funzione ricevesse `int *pV` e facesse `pV = calloc(...)`, cambierebbe solo la sua copia e `fib` nel `main` resterebbe NULL. Ricevendo l'indirizzo di `fib` (`&fib`, di tipo `int **`), con `*pV = calloc(...)` scrive dentro `fib`. È la stessa idea di `f(&i)` della lezione 3.6.
3. **Le parentesi:** `[]` ha precedenza su `*`. `*pV[i]` significherebbe `*(pV[i])`: tratterebbe `pV` come un vettore di puntatori e leggerebbe fuori dalla memoria. Quello che serve è `(*pV)[i]`.
4. Fibonacci: `(*pV)[0] = 0; (*pV)[1] = 1;` poi `(*pV)[i] = (*pV)[i-1] + (*pV)[i-2]`. Con n = 1 il ciclo scrive solo il primo elemento (test 2).
5. Il `main` fa tre free, una per ogni allocazione. `free(NULL)` è permessa e non fa nulla: è comodo nei percorsi di errore.

Codice in `soluzioni/es05_crea_vettori.c`.
</details>

### es06 — Un vettore che cresce con `realloc` fino alla sentinella  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 4, par. 1.7 (realloc: "se ciò non è possibile, viene allocata una nuova area … e il contenuto della vecchia area viene copiato") e trascrizione 4.1 (limiti dei vettori dinamici: "se voglio allargarli devo comunque riallocare memoria").
**Testo:** si leggono interi fino allo 0 (la **sentinella**, cioè il valore speciale che segnala la fine) o fino alla fine dell'input. Il vettore parte con capacità 2 e raddoppia quando è pieno. Completa `aggiungi(&v, &n, &cap, x)`: ritorna 1 se ha fatto una realloc, 0 se no, −1 se la realloc è fallita.
```text
Input:
3 1 4 1 5 9 2 0
Output:
letti 7 numeri, capacita' 8, riallocazioni 2
al contrario: 2 9 5 1 4 1 3
```
**File:** `es06_cresce_sentinella.c` · **Test:** `make test T=12 E=es06`

<details><summary>💡 Suggerimento</summary>
La funzione deve poter cambiare tre variabili del `main` (il puntatore, il numero di elementi, la capacità): per questo riceve tre indirizzi. Per la realloc usa un puntatore temporaneo.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché raddoppiare e non aggiungere 1 alla volta?** Ogni realloc può copiare tutto il vettore. Crescendo di 1 si copierebbe a ogni numero. Raddoppiando le copie sono poche: con 9 numeri, solo 3 riallocazioni (2 → 4 → 8 → 16).
2. ```c
   if (*n == *cap) {
       int *tmp = (int *) realloc(*pv, *cap * 2 * sizeof(int));
       if (tmp == NULL) return -1;   /* il vecchio blocco e' intatto */
       *pv = tmp;                    /* il blocco puo' essersi spostato */
       *cap *= 2;
   }
   (*pv)[*n] = x;
   (*n)++;
   ```
3. **Perché `*pv = tmp` è indispensabile?** realloc può spostare il blocco. Se il `main` tenesse il vecchio indirizzo, avrebbe un dangling pointer (use-after-free). Per questo `aggiungi` riceve `int **`.
4. **Perché `(*n)++` e non `*n++`?** Il secondo incrementerebbe il puntatore `n`, non il contatore.

Simulazione con `3 1 4 1 5 9 2 0`:

| x | n prima | cap prima | realloc? | cap dopo |
|---|---|---|---|---|
| 3 | 0 | 2 | no | 2 |
| 1 | 1 | 2 | no | 2 |
| 4 | 2 | 2 | **sì** | 4 |
| 1 | 3 | 4 | no | 4 |
| 5 | 4 | 4 | **sì** | 8 |
| 9, 2 | 5, 6 | 8 | no | 8 |

Lo 0 ferma il ciclo e non viene memorizzato. Test 3 (`-7 0 99 98`): i numeri dopo la sentinella vengono ignorati. Test 4: nessuna sentinella, il ciclo finisce perché finisce l'input. Codice in `soluzioni/es06_cresce_sentinella.c`.
</details>

### es07 — Tipo esame: matrice dinamica, eliminare una riga  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 4, par. 1.10 "Matrici dinamiche" (`int **A`, calloc delle righe, liberazione "prima ogni riga e successivamente il vettore di puntatori") e trascrizione 4.1 ("è un vettore di vettori … un vettore di puntatori").
**Testo:** completa `crea_matrice(r, c)`, `libera_matrice(m, r)` ed `elimina_riga(m, r, k)`. `elimina_riga` libera la riga k, sposta in su i puntatori alle righe successive (senza copiare i numeri) e restituisce il nuovo numero di righe. Se k non esiste, restituisce r e non tocca nulla. Input: `r c`, la matrice, poi `k`.
```text
Input:
3 4
1 2 3 4
5 6 7 8
9 10 11 12
1
Output:
riga 0: 1 2 3 4 | somma 10
riga 1: 9 10 11 12 | somma 42
```
Eliminando l'unica riga: `matrice vuota`. Con k fuori range: `riga 5 inesistente, matrice invariata` e la matrice stampata intera.
**File:** `es07_matrice_dinamica.c` · **Test:** `make test T=12 E=es07`

<details><summary>💡 Suggerimento</summary>
In `crea_matrice`, se la calloc della riga i fallisce, le righe da 0 a i−1 esistono già: puoi riusare `libera_matrice(m, i)`. In `elimina_riga` il ciclo di spostamento è `m[i] = m[i + 1]` per i da k a r − 2.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Creazione:** `m = (int **) calloc(r, sizeof(int *));` Ogni casella contiene un *indirizzo*, quindi serve `sizeof(int *)` (8), non `sizeof(int)` (4). Con 4 il blocco sarebbe grande la metà e ASan segnalerebbe un overflow. Poi `m[i] = (int *) calloc(c, sizeof(int))` per ogni riga.
2. **Fallimento a metà:** se la riga i non si alloca, si liberano le i righe già create e il vettore (`libera_matrice(m, i)`), poi si restituisce NULL. Così niente leak anche nel caso d'errore.
3. **Liberazione:** prima `free(m[i])` per ogni riga, poi `free(m)`. Nell'ordine inverso, dopo `free(m)` leggere `m[i]` sarebbe un use-after-free.
4. **Eliminazione:**
   ```c
   free(m[k]);
   for (i = k; i < r - 1; i++) m[i] = m[i + 1];
   m[r - 1] = NULL;
   return r - 1;
   ```
   Si spostano solo gli indirizzi (8 byte ciascuno), qualunque sia la lunghezza delle righe. È il vantaggio del vettore di puntatori, lo stesso dell'ordinamento di stringhe della cartella 11. L'ultima casella viene messa a NULL perché ora è un doppione della penultima: senza, una `libera_matrice(m, r)` farebbe un double free.
5. **Liberazione finale nel main:** `libera_matrice(m, nuove)`. Il vettore di puntatori era stato allocato per r caselle, ma `free(m)` libera comunque tutto il blocco.

Simulazione (test 1, k = 1): `m[0]→{1,2,3,4}`, `m[1]→{5,6,7,8}`, `m[2]→{9,…}`. Dopo `free(m[1])` e lo spostamento: `m[0]→{1,2,3,4}`, `m[1]→{9,10,11,12}`, `m[2]=NULL`. Codice in `soluzioni/es07_matrice_dinamica.c`.
</details>

### es08 — Tipo esame: parole nello heap e concatenazione in nuova memoria  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 4, par. 1.10 (vettore di puntatori allocato con calloc), par. 1.11 (funzione che restituisce memoria allocata) e cap. 3.2 (array di stringhe come vettore di `char *`).
**Testo:** il programma legge n parole e un carattere separatore. Completa:
- `leggi_parole(n)`: crea un vettore dinamico di n `char *` e, per ogni parola, un blocco della misura esatta (lettura con `scanf("%30s", buf)` in un buffer d'appoggio);
- `concatena(parole, n, sep)`: crea una **nuova** stringa con le parole separate da `sep`, allocando esattamente i byte necessari (con n = 0 restituisce `""`, comunque allocata);
- `libera_parole(parole, n)`.
```text
Input:
3
latte uova farina
,
Output:
parole: [latte] [uova] [farina]
risultato: [latte,uova,farina]
byte allocati per il risultato: 18
```
**File:** `es08_concatena.c` · **Test:** `make test T=12 E=es08`

<details><summary>💡 Suggerimento</summary>
Byte necessari = somma delle lunghezze + (n − 1) separatori + 1 terminatore. Per riempire la stringa usa un secondo puntatore `dove` che avanza, e lascia fermo quello restituito da malloc: servirà alla `free`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Vettore di parole:** `calloc(caselle, sizeof(char *))`. Con calloc le caselle partono a NULL, quindi `libera_parole` può liberare anche un vettore riempito a metà (`free(NULL)` non fa nulla). Si chiede almeno 1 casella perché `calloc(0, …)` può restituire NULL anche senza errori, e allora NULL non direbbe più "errore".
2. **Ogni parola:** `buf` (31 byte nello stack) serve solo da appoggio. `parole[i] = malloc(strlen(buf) + 1); strcpy(parole[i], buf);` È es03 applicato n volte.
3. **Dimensione del risultato** (test 1): 5 + 4 + 6 = 15 caratteri, + 2 virgole, + 1 `'\0'` = 18 byte.
4. **Riempimento:**
   ```c
   dove = ris;
   for (i = 0; i < n; i++) {
       memcpy(dove, parole[i], len); dove += len;
       if (i < n - 1) *dove++ = sep;
   }
   *dove = '\0';
   ```
   `*dove++ = sep` scrive `sep` nella casella puntata e poi sposta `dove` avanti di un char. `ris` resta sull'inizio: passare a `free` il puntatore spostato sarebbe un errore grave (vedi le contraddizioni).
5. **Liberazione:** `free(frase)` e poi `libera_parole`: prima ogni parola, poi il vettore. In tutto n + 2 free per n + 2 allocazioni.

Casi limite: n = 1 (nessun separatore, test 2) e n = 0 (stringa vuota da 1 byte, test 3). Codice in `soluzioni/es08_concatena.c`.
</details>

## Prompt pronti per questo argomento
1. "Interrogami con 6 domande, una alla volta, su malloc, calloc, realloc e free (cartella 12-memoria-dinamica della mia repo esercizi-c): differenze, valori restituiti, quando si controlla NULL. Aspetta la mia risposta e correggimi spiegando il perché."
2. "Ho scritto questa soluzione per es06 di 12-memoria-dinamica: [incolla codice]. Dimmi se è corretta e perché, senza riscrivermela tutta. Controlla in particolare l'uso di realloc e dei puntatori a puntatore."
3. "Ecco il rapporto di AddressSanitizer che ho ottenuto: [incolla]. Spiegami riga per riga che cosa dice e quale riga del mio codice devo guardare, senza darmi direttamente la correzione."
4. "Generami 3 esercizi nuovi tipo es07/es08 della cartella 12 (matrici dinamiche, vettori di stringhe nello heap), con testo, input e output di esempio. Non darmi le soluzioni."
5. "Disegnami in ASCII stack e heap durante l'esecuzione di `crea_fibonacci(&fib, 4)` di es05, prima e dopo la calloc, e spiegami perché serve `int **`."

## Riepilogo
- Lo heap ospita memoria chiesta a runtime con malloc/calloc/realloc, che resta valida finché non chiami free. Si usa quando la dimensione dipende dall'input o quando una funzione deve restituire un vettore.
- Sempre: `n * sizeof(tipo)`, controllo di NULL, realloc tramite un puntatore temporaneo, `+1` per il `'\0'` delle stringhe.
- Ogni allocazione ha esattamente una free, con l'indirizzo originale. Dopo la free il puntatore va messo a NULL: usarlo è un use-after-free, liberarlo di nuovo è un double free, non liberarlo è un memory leak.
- Matrice dinamica = vettore di puntatori (`int **`): si crea prima il vettore e poi le righe, si libera prima le righe e poi il vettore. Spostare righe vuol dire spostare indirizzi.

## Glossario
- **heap** — zona di memoria da cui il programma chiede blocchi durante l'esecuzione; restano validi fino alla free.
- **stack** — zona dove vivono le variabili locali; si libera da sola quando la funzione termina.
- **malloc** — alloca un blocco di N byte, dal contenuto casuale; restituisce `void *` oppure NULL.
- **calloc** — alloca N elementi da M byte e li azzera.
- **realloc** — cambia la dimensione di un blocco, eventualmente spostandolo e copiando i dati.
- **free** — restituisce al sistema un blocco ottenuto con malloc/calloc/realloc.
- **void \*** — puntatore "generico", senza tipo; va convertito prima di usarlo.
- **size_t** — tipo intero senza segno usato per le dimensioni in byte.
- **sizeof** — operatore che dà il numero di byte di un tipo o di una variabile.
- **padding** — byte vuoti che il compilatore inserisce in una struct per allineare i campi.
- **sentinella** — valore speciale che segnala la fine dei dati (qui lo 0).
- **capacità** — numero di elementi che il blocco può contenere, diverso dal numero di elementi usati.
- **memory leak** — memoria allocata e mai liberata.
- **dangling pointer** — puntatore che contiene ancora l'indirizzo di un blocco già liberato.
- **use-after-free** — lettura o scrittura attraverso un dangling pointer.
- **double free** — chiamare free due volte sullo stesso blocco.
- **heap-buffer-overflow** — accesso oltre la fine (o prima dell'inizio) di un blocco nello heap.
- **puntatore a puntatore (`int **`)** — indirizzo di una variabile puntatore; serve per modificarla da una funzione o per costruire matrici dinamiche.
- **comportamento indefinito** — situazione in cui lo standard C non garantisce niente: può funzionare, crollare o dare risultati casuali.
- **AddressSanitizer (ASan)** — strumento attivato dal runner che ferma il programma al primo errore di memoria e dice dove è avvenuto.
- **LeakSanitizer** — parte di ASan che elenca i leak a fine programma; nel runner è spenta.
