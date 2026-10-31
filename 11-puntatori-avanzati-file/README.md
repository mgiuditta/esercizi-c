# 11 — Approfondimento puntatori, matrici e stream (file)

> Lezioni di riferimento: trascrizione 3.6 (Approfondimento puntatori) e le sue tre E-tivity (ParametriePuntatoribis, 2ParametriePuntatoriTRIS, MatriciePuntatori), Dispensa 3.6.4 Stream, Appunti Unità 3 (cap. 6 "Approfondimenti sui Puntatori", par. 6.2–6.10), Appunti Unità 4 (cap. 3.2–3.4, solo per vettori di stringhe e argc/argv), LEZ 18.
> Tempo stimato: ~5 ore.

## Teoria flash

**1. Il C passa SEMPRE per valore, anche i puntatori.** Quando chiami `f(&i)`, la funzione riceve una *copia* dell'indirizzo di `i`. Con quella copia può però andare a scrivere nella cella originale: `(*p)++` cambia `i` del chiamante. `p++` invece sposta solo la copia locale e fuori non cambia niente (trascrizione 3.6 e Appunti 6.4). Pensa a un biglietto con scritto un indirizzo di casa: se fotocopi il biglietto, tutte e due le copie portano alla stessa casa.
Così una funzione può "restituire" più risultati: è il caso di `scompone(double d, long *pi, double *pf)` del prof. Questi puntatori si chiamano **parametri di output** (parametri in cui la funzione scrive il risultato). Nella E-tivity delle radici, `coefficienti(float *c1, float *c2, float *c3)` fa `scanf("%f", c1)` **senza &**, perché `c1` è già un indirizzo.

**2. Puntatore a puntatore (`char **`, `int **`).** È una variabile che contiene l'indirizzo di *un'altra variabile puntatore*. Serve quando una funzione deve modificare un puntatore del chiamante. Esempio: per scambiare due caselle di `char *nomi[]` passo `&nomi[i]`, che è di tipo `char **`:
```c
void scambia(char **a, char **b) { char *tmp = *a; *a = *b; *b = tmp; }
```

**3. Matrici e puntatori (E-tivity MatriciePuntatori, Appunti 6.9).** Una matrice `int ar[2][3]` in memoria è una fila di 6 interi: prima riga, poi seconda. Il nome `ar`, usato in un'espressione, **decade** (cioè viene convertito automaticamente) in un *puntatore alla prima riga*, di tipo `int (*)[3]`.

| Espressione | Equivale a | Tipo | Cos'è |
|---|---|---|---|
| `ar + i` | `&ar[i]` | `int (*)[3]` | indirizzo della riga i (salta i righe intere) |
| `*(ar + i)` | `ar[i]` | decade a `int *` | indirizzo del primo intero della riga i |
| `*(ar + i) + j` | `&ar[i][j]` | `int *` | indirizzo dell'elemento (i, j) |
| `*(*(ar + i) + j)` | `ar[i][j]` | `int` | il valore |

`ar + i` e `*(ar + i)` hanno **lo stesso indirizzo** ma "puntano a cose diverse" (una riga intera o un intero): cambia di quanto si salta con `+ 1`.
`int (*p)[3]` è un **puntatore a vettore**: un solo puntatore che punta a una riga di 3 interi. `int *p[3]` (senza parentesi) è invece un **vettore di 3 puntatori**: le `[]` hanno precedenza sull'asterisco.

**4. Passare una matrice a una funzione.** Si DEVE scrivere il numero di colonne: `void f(int m[][3], int righe)` oppure `void f(int (*m)[3], int righe)`. Il motivo: per trovare `m[i][j]` il compilatore calcola "inizio + i·colonne + j", quindi deve sapere quante colonne ha una riga. Una matrice **non** è un `int **` (vedi Errori tipici).

**5. Vettori di stringhe (Appunti Unità 4, 3.2).** `char *nomi[] = {"zanzara", "barca", "casa"};` è un vettore di puntatori a carattere. Per ordinarlo si scambiano i puntatori (8 byte l'uno), non i caratteri. Passato a una funzione decade a `char **`.
`argc`/`argv`: `int main(int argc, char *argv[])` riceve le parole scritte dopo il nome del programma (`./prog par1 par2` → `argc = 3`, `argv[1] = "par1"`). Il nostro runner di test non passa argomenti, quindi nessun esercizio lo usa: è solo teoria. I **puntatori a funzione** non sono nelle fonti di questa unità (arrivano con il blocco 4).

**6. Stream (Dispensa 3.6.4).** Uno **stream** è qualsiasi sorgente o destinazione di dati (tastiera, video, file). In `stdio.h` ogni stream è un `FILE *`, cioè un puntatore a una struttura che il sistema usa per ricordare a che punto sei del file. Tre stream esistono già aperti: `stdin` (tastiera), `stdout` (video), `stderr` (video, ma riservato ai messaggi di errore). Con `./prog < dati.txt` il sistema operativo fa leggere a `stdin` il file al posto della tastiera: è proprio così che il runner di test dà l'input ai tuoi programmi.

```c
FILE *fp = fopen("voti.txt", "r");   /* "r" leggi, "w" scrivi (SVUOTA!), "a" accoda */
if (fp == NULL) {                    /* file inesistente o non apribile */
    fprintf(stderr, "Errore\n");
    return 1;
}
while (fscanf(fp, "%d", &x) == 1) { /* fscanf restituisce quanti valori ha letto */
    ...
}
fclose(fp);                          /* chiude e svuota il buffer */
```
- `fprintf(fp, ...)` è `printf` su un file; `fscanf(fp, ...)` è `scanf` da un file e restituisce il numero di valori assegnati, oppure **EOF** (End Of File, una costante negativa che vuol dire "non c'è più niente da leggere").
- `fgets(s, n, fp)` legge una riga intera, `'\n'` compreso, al massimo `n - 1` caratteri; restituisce `NULL` a fine file. `gets` non va usata: non conosce la dimensione di `s` ed è stata tolta dal C11.
- `getc(fp)` / `putc(c, fp)`: un carattere alla volta. `getc` restituisce un **`int`**, non un `char`, perché deve poter restituire anche EOF.
- **Buffer**: le scritture vengono accumulate in memoria e scritte sul disco a blocchi. `fclose` (o `fflush`) le scrive davvero. Se dimentichi `fclose` e rileggi il file subito, potresti trovarlo vuoto.
- `feof(fp)` diventa vero solo **dopo** una lettura fallita. Per questo `while (!feof(fp))` sbaglia l'ultimo giro: controlla invece il valore di ritorno di `fscanf`/`fgets`/`getc`.

**Assunzioni sui tipi:** `sizeof(int)` = 4 e `sizeof(char *)` = 8 su macOS arm64 e Linux x86-64. Gli esercizi stampano differenze di indirizzi in byte, mai indirizzi assoluti (cambiano a ogni esecuzione).

**Imprecisioni nelle fonti (trascrizioni automatiche e dispense):**
- Trascrizione 3.6: "par uguale a r" va letto `parr = &arr;`. Per un vettore semplice `int arr[5]` serve la `&` per ottenere il tipo `int (*)[5]`. Per una matrice invece `p = ar;` è già corretto, senza `&`, perché `ar` decade proprio a puntatore alla prima riga.
- Trascrizione 3.6: "passare v di lunghezza quello è un errore". In realtà `void f(int v[10])` compila: il 10 viene semplicemente **ignorato** (il parametro è comunque un `int *`). Non è un errore, è inutile.
- E-tivity MatriciePuntatori: "per 100p" = `%p`; "array più 1, scusate più i" = il prof si corregge da solo, l'indice è la variabile `i`.
- Dispensa Stream: `fputs` e `puts` sono scritte con tipo di ritorno `int *`. In realtà restituiscono `int`. Ci sono anche refusi: "nomele" = nomefile, "fpritnf" = fprintf.

### Errori tipici
1. **Matrice passata come `int **`.** Il compilatore (gcc) avvisa:
   `warning: passing argument 1 of 'stampa' from incompatible pointer type [-Wincompatible-pointer-types]` … `note: expected 'int **' but argument is of type 'int (*)[3]'`. Se lo esegui va in crash: dentro la matrice ci sono interi, non indirizzi. Correzione: `int m[][3]` oppure `int (*m)[3]`.
2. **`*righe++` invece di `(*righe)++`.** Il `++` viene applicato al puntatore, non al valore: `warning: value computed is not used [-Wunused-value]`. Il contatore del chiamante resta 0.
3. **`fopen` senza controllo di NULL.** Il compilatore non dice niente (non può sapere se il file esisterà). In esecuzione: `AddressSanitizer: SEGV on unknown address 0x000000000000 ... Hint: address points to the zero page` oppure, con UBSan, `runtime error: null pointer passed as argument 1, which is declared to never be null`.
4. **Modalità tra apici singoli:** `fopen(nome, 'r')` → `warning: passing argument 2 of 'fopen' makes pointer from integer without a cast [-Wint-conversion]`. `'r'` è un carattere (un numero), mentre serve la stringa `"r"`.
5. **`fprintf` senza il FILE \*:** `fprintf("x vale %d\n", x)` → `warning: passing argument 1 of 'fprintf' from incompatible pointer type` … `expected 'FILE * restrict' but argument is of type 'char *'`.
6. **`while (!feof(fp))`**: nessun avviso, ma l'ultimo valore viene contato due volte (es07).

## Esercizi

### es01 — Cosa stampa? Matrici e puntatori  ·  Base
**Fonte:** Ispirato a: E-tivity 3.6 MatriciePuntatori (matrice `{11,22,33},{44,55,66}`, `int (*p)[3]`, `*(*(p+i)+j)`) e Appunti Unità 3, par. 6.8–6.9.
**Testo:** il file `es01_cosa_stampa_matrice.c` è già completo. Leggilo e, **prima di eseguirlo**, scrivi qui sotto cosa stampa ogni riga (A–H). Il prof stampava gli indirizzi con `%p`; qui si stampano le differenze in byte, così l'output è uguale su ogni computer. Con `i = 1` e `j = 1`.
```text
A: ?
B: ?
C: ?
D: ? ?
E: ? ?
F: ?
G: ? ?
H: ?
```
**File:** `es01_cosa_stampa_matrice.c` · **Test:** `make test T=11 E=es01`

<details><summary>💡 Suggerimento</summary>
Chiediti sempre "a che cosa punta?". Se punta a una riga di 3 int, `+ 1` salta 3 × 4 = 12 byte. Se punta a un int, `+ 1` salta 4 byte.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

```text
A: 12
B: 0
C: 4
D: 12 4
E: 55 55
F: 55
G: 44 66
H: 11
```
1. **A = 12.** `ar` decade a `int (*)[3]`, un puntatore a riga. `ar + 1` salta una riga intera: 3 int × 4 byte = 12 byte.
2. **B = 0.** `ar + 1` (indirizzo della riga 1) e `*(ar + 1)` (indirizzo del primo intero della riga 1) sono **lo stesso indirizzo**. È la frase del prof: "ha lo stesso indirizzo ma cambia quello che viene puntato".
3. **C = 4.** `*(ar + 1)` è un `int *`, quindi `+ 1` salta un solo int (4 byte). È il "posto 1 dell'i-esima riga".
4. **D = 12 4.** `sizeof` dice quanto è grande la cosa puntata. `*(ar + 1)` è la riga intera (12 byte). `**(ar + 1)` è un singolo int (4 byte).
5. **E = 55 55.** `*(*(ar + 1) + 1)` è `ar[1][1]`, cioè 55, come nell'output della E-tivity.
6. **F = 55.** `p = ar` è un assegnamento corretto senza `&`: `ar` ha già il tipo di `p`. Allora `p` si comporta come il nome della matrice.
7. **G = 44 66.** `p++` salta una riga intera, quindi ora `p` punta alla riga 1. `(*p)[0]` è il primo elemento della riga 1 (44). `p[0][2]` è il terzo (66).
8. **H = 11.** `p--` torna alla riga 0. `*p` è la riga 0, che decade a `int *`. Il secondo `*` legge il suo primo intero: 11.

Codice: `soluzioni/es01_cosa_stampa_matrice.c` (identico allo starter).
</details>

### es02 — Somma delle diagonali con l'aritmetica dei puntatori  ·  Base
**Fonte:** Ispirato a: E-tivity 3.6 MatriciePuntatori (`*(*(ar+i)+j)`) e Appunti Unità 3, par. 6.7 (matrice come parametro con il numero di colonne).
**Testo:** completa `somma_principale` e `somma_secondaria`. Ricevono una matrice quadrata n×n (n ≤ 10) come `int (*m)[N]`. Dentro le funzioni è vietato scrivere `m[i][j]`: usa solo `*(*(m + i) + j)`. La diagonale secondaria va dall'angolo in alto a destra a quello in basso a sinistra.
```text
Input:
3
1 2 3
4 5 6
7 8 9
Output:
principale = 15
secondaria = 15
```
**File:** `es02_somma_diagonale.c` · **Test:** `make test T=11 E=es02`

<details><summary>💡 Suggerimento</summary>
Sulla diagonale principale riga e colonna coincidono (i, i). Sulla secondaria, alla riga i corrisponde la colonna n − 1 − i.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché `int (*m)[N]` con N = 10 fisso?** Il compilatore deve sapere quante colonne ha una riga *in memoria* per saltare da una riga all'altra. La matrice del `main` è `int mat[10][10]`, anche se ne usiamo solo n×n. Quindi la riga in memoria è lunga 10, non n. Se scrivessi `int (*m)[3]` per una matrice 3×3 dentro una 10×10, i salti sarebbero sbagliati.
2. `m + i` → riga i. `*(m + i)` → la riga, che decade a `int *`. `+ i` → colonna i. `*(...)` → il valore.
3. Ciclo unico da 0 a n − 1: non serve un doppio ciclo, perché per ogni riga c'è un solo elemento di diagonale.
```c
for (i = 0; i < n; i++)
    s += *(*(m + i) + i);              /* principale */
for (i = 0; i < n; i++)
    s += *(*(m + i) + (n - 1 - i));    /* secondaria */
```
Simulazione con l'esempio 3×3 (secondaria):

| i | colonna n−1−i | valore | s |
|---|---|---|---|
| 0 | 2 | 3 | 3 |
| 1 | 1 | 5 | 8 |
| 2 | 0 | 7 | 15 |

Caso limite n = 1: le due diagonali sono lo stesso elemento (test 2, con un numero negativo). Codice in `soluzioni/es02_somma_diagonale.c`.
</details>

### es03 — Contare righe e parole di un file  ·  Base
**Fonte:** Ispirato a: Dispensa 3.6.4 Stream (fopen/fclose, `getc` "restituisce EOF se incontra la fine del file") e trascrizione 3.6 (funzione `scompone` con parametri di output).
**Testo:** completa `analizza_file(nome, &righe, &parole, &maxlen)`. La funzione apre il file, lo legge carattere per carattere con `getc` e restituisce con i parametri di output: il numero di righe, il numero di parole (sequenze di caratteri che non sono spazi, tab o a capo) e la lunghezza della riga più lunga (senza `'\n'`). Ritorna `-1` se il file non si apre. Attenzione: l'ultima riga può non avere `'\n'` finale ma va contata lo stesso. I file di prova sono in `tests/fixtures/` (`dante.txt`, `codice.txt`, `vuoto.txt`).
```text
Input:
dante.txt
Output:
righe: 3
parole: 19
riga piu' lunga: 35 caratteri
```
Con un file inesistente: `Errore: impossibile aprire non_esiste.txt`.
**File:** `es03_conta_righe_parole.c` · **Test:** `make test T=11 E=es03`

<details><summary>💡 Suggerimento</summary>
Usa una variabile `dentro` (0/1) che ricorda se sei in mezzo a una parola: una parola nuova inizia quando trovi un carattere non-spazio e `dentro` vale 0. Per la riga più lunga tieni un contatore `lung` che riparte da 0 a ogni `'\n'`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. `fp = fopen(nome, "r"); if (fp == NULL) return -1;` Senza il controllo, con un file inesistente il programma crolla alla prima `getc`.
2. Azzera i tre risultati **attraverso i puntatori**: `*righe = 0;`. Sono le variabili `r`, `p`, `m` del `main`.
3. `int c;` e **non** `char c;`. `getc` restituisce un `int` perché EOF (di solito −1) deve essere distinguibile da tutti i 256 caratteri possibili.
4. Ciclo `while ((c = getc(fp)) != EOF)`:
   - se `c == '\n'`: `(*righe)++`, aggiorna il massimo, `lung = 0`. Le parentesi sono obbligatorie: `*righe++` sposterebbe il puntatore (Errore tipico 2);
   - altrimenti `lung++`;
   - `isspace(c)` (da `ctype.h`) è vero per spazio, tab e a capo: se è vero metti `dentro = 0`, altrimenti, se `dentro` era 0, è iniziata una parola: `(*parole)++`.
5. Dopo il ciclo: se `lung > 0` l'ultima riga non aveva `'\n'`, quindi va contata e confrontata con il massimo. Succede in `codice.txt`, che finisce con `}` senza a capo.
6. `fclose(fp)`.

Simulazione su `codice.txt` (`"  int main(void)   {\n\n\treturn 0;\n}"`): riga 1 = 20 caratteri e 3 parole (`int`, `main(void)`, `{`); riga 2 vuota; riga 3 = 10 caratteri (il tab conta) e 2 parole; `}` senza `'\n'` → righe 4, parole 6, max 20. Codice in `soluzioni/es03_conta_righe_parole.c`.
</details>

### es04 — Ordinare un vettore di stringhe scambiando i puntatori  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 4, cap. 3.2 "Array di stringhe" (esempio `{"zanzara", "barca", "casa"}`, "è sufficiente scambiare i puntatori") e Appunti Unità 3, par. 6.2 (passaggio di indirizzi per valore).
**Testo:** il `main` legge n parole nel vettore `char testo[20][31]` e fa puntare `nomi[i]` a `testo[i]`. Completa `scambia(char **a, char **b)` e `ordina(char **v, int n)` (ordinamento per selezione con `strcmp`). L'output mostra le parole ordinate e poi `testo` nell'ordine originale: se i caratteri non si sono mossi, hai scambiato solo i puntatori.
```text
Input:
3
zanzara barca casa
Output:
ordinate: barca casa zanzara
originali: zanzara barca casa
```
**File:** `es04_ordina_nomi.c` · **Test:** `make test T=11 E=es04`

<details><summary>💡 Suggerimento</summary>
`strcmp(s1, s2)` restituisce un numero negativo se `s1` viene prima di `s2` in ordine alfabetico. Le maiuscole vengono prima delle minuscole (codice ASCII: 'B' = 66, 'b' = 98). Per scambiare due caselle di `v` devi passare a `scambia` i loro indirizzi: `&v[i]`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché `char **`?** `nomi` è un vettore di `char *`. Passato a `ordina` decade a puntatore al primo elemento, cioè puntatore a `char *` = `char **`.
2. **Perché `scambia` riceve `char **`?** Deve modificare due caselle del vettore del chiamante. Per modificare una variabile da dentro una funzione serve il suo indirizzo. Le caselle sono `char *`, quindi il loro indirizzo è `char **`. È la stessa regola di `f(&i)` della lezione 3.6, applicata a una variabile che è essa stessa un puntatore.
```c
void scambia(char **a, char **b) { char *tmp = *a; *a = *b; *b = tmp; }
```
3. **Selezione:** per ogni posizione i, cerca l'indice `min` della stringa "più piccola" tra i e n − 1, poi scambia `v[i]` e `v[min]`.
4. Il vettore `testo` non viene toccato: per ogni scambio si spostano 8 byte (un puntatore), invece dei 31 di una riga di caratteri.

Simulazione con zanzara/barca/casa: i = 0 → minimo "barca" (indice 1), scambio → `barca zanzara casa`; i = 1 → minimo "casa" (indice 2), scambio → `barca casa zanzara`. Il test 3 contiene maiuscole e doppioni: `Banana Mela banana kiwi mela mela`. Codice in `soluzioni/es04_ordina_nomi.c`.
</details>

### es05 — Copiare un file in maiuscolo e poi stamparlo  ·  Intermedio
**Fonte:** Ispirato a: Dispensa 3.6.4 Stream (modi "r"/"w", `getc`/`putc`, `fgets`, `fputs` "senza aggiungere '\n'", buffering e `fclose`).
**Testo:** completa `copia_maiuscolo(sorgente, destinazione)`: apre la sorgente in `"r"` e la destinazione in `"w"` e copia carattere per carattere con `toupper`. Ritorna quanti caratteri ha copiato, oppure −1. Completa poi `stampa_file(nome)`, che rilegge il file creato con `fgets` e lo stampa con `fputs(riga, stdout)`.
```text
Input:
teresa.txt teresa_maiuscola.txt
Output:
copiati 71 caratteri
--- contenuto di teresa_maiuscola.txt ---
LA VISPA TERESA
AVEA TRA L'ERBETTA
A VOLO SORPRESA
GENTIL FARFALLETTA.
--- fine ---
```
Nel test 2 (`formula.txt`) l'ultima riga non ha `'\n'`: per questo `--- fine ---` finisce attaccato all'ultima riga. È voluto, perché `fputs` non aggiunge l'a capo.
**File:** `es05_copia_maiuscolo.c` · **Test:** `make test T=11 E=es05`

<details><summary>💡 Suggerimento</summary>
Se la seconda `fopen` fallisce, prima di uscire chiudi la prima. In `stampa_file` riapri il file **dopo** aver chiuso quello di scrittura: è la `fclose` che scrive davvero il buffer sul disco.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. Apertura con controllo: `in = fopen(sorgente, "r")`. Se è NULL, ritorna −1. Poi `out = fopen(destinazione, "w")`; se è NULL, `fclose(in)` e ritorna −1. Così il primo file non resta aperto: un file aperto occupa risorse del sistema.
2. Copia: `while ((c = getc(in)) != EOF) { putc(toupper(c), out); quanti++; }`. `toupper` trasforma solo le lettere minuscole e lascia invariati spazi, cifre e punteggiatura.
3. `fclose(in); fclose(out);` La seconda è fondamentale: i caratteri scritti con `putc` stanno nel **buffer** (una zona di memoria di appoggio) finché non viene svuotato. Se rileggessi il file senza chiuderlo, potresti trovarlo vuoto.
4. `stampa_file`: `while (fgets(riga, sizeof riga, fp) != NULL) fputs(riga, stdout);`. `fgets` tiene il `'\n'` dentro `riga`, quindi `fputs` (che non ne aggiunge) riproduce il file identico.
5. Caso limite `vuoto.txt`: la prima `getc` dà subito EOF, si copiano 0 caratteri e il file destinazione esiste ma è vuoto.

Codice in `soluzioni/es05_copia_maiuscolo.c`.
</details>

### es06 — Leggere numeri da file e scrivere le statistiche  ·  Intermedio
**Fonte:** Ispirato a: Dispensa 3.6.4 Stream ("fscanf … restituisce il numero di oggetti assegnati", `fprintf`) e trascrizione 3.6 ("funzioni con risultati multipli" tramite parametri passati per indirizzo).
**Testo:** completa `statistiche(in, &min, &max, &media)`: legge con `fscanf` tutti gli interi dallo stream già aperto e ritorna quanti sono. Completa `scrivi_report(nome, n, min, max, media)`: scrive su file quattro righe:
```text
numeri letti: N
minimo: MIN
massimo: MAX
media: M        (due decimali)
```
Il `main` scrive il report in `statistiche.txt` e poi lo rilegge a video.
```text
Input:
misure.txt          (contiene: 12 7 -3 / 5 / 1)
Output:
numeri letti: 5
minimo: -3
massimo: 12
media: 4.40
```
Con `vuoto.txt`: `nessun numero in vuoto.txt`. Con `sporco.txt` (`10 20 30 ciao 40`) la lettura si ferma a "ciao": 3 numeri.
**File:** `es06_statistiche_file.c` · **Test:** `make test T=11 E=es06`

<details><summary>💡 Suggerimento</summary>
Il primo numero letto è sia il minimo sia il massimo: usa la condizione `n == 0 || x < *min`. Per la media fai un cast a `double` prima di dividere.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. `while (fscanf(in, "%d", &x) == 1)`: si continua finché `fscanf` riesce ad assegnare 1 valore. A fine file restituisce EOF. Davanti a "ciao" restituisce 0 (non riesce a interpretarlo come intero) e il ciclo si ferma anche lì. È il motivo per cui si confronta con `== 1` e non con `!= EOF`: con `!= EOF`, davanti a "ciao" il ciclo non finirebbe mai, perché `fscanf` restituirebbe 0 per sempre senza avanzare.
2. Minimo e massimo si scrivono attraverso i puntatori (`*min = x`): sono le variabili del `main`, come `*pi` e `*pf` in `scompone`.
3. `*media = (double)somma / n;` Senza cast, `22 / 5` darebbe 4 (divisione intera). La media si calcola solo se `n > 0`, altrimenti sarebbe una divisione per zero.
4. `scrivi_report`: `fopen(nome, "w")`, quattro `fprintf(out, ...)` e `fclose`.

Simulazione su `misure.txt`:

| x | min | max | somma | n |
|---|---|---|---|---|
| 12 | 12 | 12 | 12 | 1 |
| 7 | 7 | 12 | 19 | 2 |
| −3 | −3 | 12 | 16 | 3 |
| 5 | −3 | 12 | 21 | 4 |
| 1 | −3 | 12 | 22 | 5 |

Media = 22 / 5 = 4.40. Codice in `soluzioni/es06_statistiche_file.c`.
</details>

### es07 — Trova e correggi gli errori: media dei voti da file  ·  Tipo esame
**Fonte:** Ispirato a: Dispensa 3.6.4 Stream (modi di apertura; "se il file non esiste, in lettura restituisce NULL"; "feof restituisce vero dopo il fallimento di un'operazione di lettura").
**Testo:** il programma legge il nome di un file di voti e dovrebbe stampare `letti N voti, media M`. Se il file non esiste deve stampare `Errore: file NOME non trovato` (su stdout e su stderr) e uscire con 1. Compila senza avvisi, ma contiene **tre errori** sugli stream (più uno "di stile" che il test non rileva). Trovali e correggili.
```text
Input:
voti.txt          (contiene 28 30 18 27)
Output atteso:
letti 4 voti, media 25.75
Output dello starter:
letti 1 voti, media 0.00
```
**File:** `es07_trova_errore_file.c` · **Test:** `make test T=11 E=es07`

<details><summary>💡 Suggerimento</summary>
Guarda la modalità di `fopen`: che cosa fa la "w" a un file esistente? Poi chiediti cosa succede quando il file non esiste. Infine conta a mano i giri del ciclo `while (!feof(fp))` con 4 voti.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Errore 1, `"w+"` invece di `"r"`.** La "w", anche con il "+" che permette di leggere, **svuota** il file appena lo apre, o lo crea vuoto se non esiste. I voti spariscono prima di essere letti: per questo lo starter legge "1 voto da 0". Correzione: `"r"`.
2. **Errore 2, nessun controllo di NULL.** Dopo aver messo `"r"`, con un file inesistente `fopen` restituisce NULL e `feof(NULL)` fa crollare il programma. Il runner mostra **CRASH** oppure **FAIL** con l'output vuoto: dipende dal sistema e da quale strumento ferma il programma per primo. Su Linux UBSan (UndefinedBehaviorSanitizer, cioè lo strumento che segnala le operazioni vietate dal linguaggio) scrive `runtime error: null pointer passed as argument 1, which is declared to never be null`. ASan (AddressSanitizer, cioè lo strumento che controlla gli accessi alla memoria) scrive `SEGV on unknown address 0x000000000000 ... address points to the zero page`. "Zero page" vuol dire che si è provato a leggere all'indirizzo 0, cioè NULL. Correzione:
   ```c
   if (fp == NULL) {
       printf("Errore: file %s non trovato\n", nome);
       fprintf(stderr, "Errore: file %s non trovato\n", nome);
       return 1;
   }
   ```
3. **Errore 3, `while (!feof(fp))`.** Corretti i primi due, otterresti `letti 5 voti, media 26.00`. Dopo aver letto 27, `fscanf` si ferma prima del `'\n'` finale e non ha ancora "toccato" la fine del file, quindi `feof` è ancora falso. Si entra una quinta volta: `fscanf` fallisce, `voto` vale ancora 27 e viene sommato di nuovo (130 / 5 = 26). Correzione: `while (fscanf(fp, "%d", &voto) == 1)`.
4. **Errore 4 (stile), manca `fclose(fp)`.** Il test non lo vede, perché il sistema chiude i file a fine programma. In un programma che apre molti file, però, si esaurirebbero i file apribili.
5. In più la soluzione gestisce il file vuoto (test 3): senza voti stampa `nessun voto` invece di dividere per zero.

Codice corretto e commentato in `soluzioni/es07_trova_errore_file.c`.
</details>

### es08 — Tipo esame: equazioni di secondo grado da file a file  ·  Tipo esame
**Fonte:** Ispirato a: E-tivity 3.6 ParametriePuntatoribis e 2ParametriePuntatoriTRIS (funzioni `coefficienti`, `discriminante`, `radici`; "se a è 0 non è un'equazione di secondo grado"), Appunti Unità 3, par. 6.10 (passaggio di strutture tramite indirizzo) e Dispensa Stream.
**Testo:** il file d'ingresso contiene un'equazione per riga, `a b c` (numeri reali). Con `typedef struct { double a, b, c; } Equazione;` completa:
- `leggi_equazioni(nome, v, max)`: legge al massimo `max` equazioni nel vettore di struct e ritorna quante, oppure −1 se il file non si apre;
- `radici(&e, &x1, &x2)`: ritorna −1 se a = 0, 0 se non ci sono radici reali, 1 se sono coincidenti (solo `*x1`), 2 se sono distinte (`*x1` con +√Δ, `*x2` con −√Δ);
- `scrivi_soluzioni(nome_out, v, n)`: scrive una riga per equazione nel formato qui sotto.

Il `main` scrive `soluzioni.txt`, lo rilegge a video e aggiunge un riepilogo.
```text
Input:
equazioni.txt     (contiene: 1 -3 2 / 1 2 1 / 1 0 1 / 0 2 1 / 2 -6 0)
Output:
1) a=1.00 b=-3.00 c=2.00: x1=2.00 x2=1.00
2) a=1.00 b=2.00 c=1.00: radici coincidenti x=-1.00
3) a=1.00 b=0.00 c=1.00: nessuna radice reale
4) a=0.00 b=2.00 c=1.00: non e' di secondo grado
5) a=2.00 b=-6.00 c=0.00: x1=3.00 x2=0.00
equazioni: 5, con radici reali: 3
```
**File:** `es08_esame_equazioni.c` · **Test:** `make test T=11 E=es08`

<details><summary>💡 Suggerimento</summary>
Con un puntatore a struct si accede ai campi con `e->a`, che equivale a `(*e).a`. In `fscanf` i double si leggono con `%lf` (con `%f` leggeresti dei float) e servono gli indirizzi: `&v[n].a`. Ricordati il controllo `n < max` per non scrivere oltre il vettore.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Lettura:** `while (n < max && fscanf(fp, "%lf %lf %lf", &v[n].a, &v[n].b, &v[n].c) == 3) n++;`. L'ordine delle condizioni conta: se `n == max`, l'operatore `&&` non valuta la `fscanf`, quindi non si scrive in `v[max]`, che non esiste.
2. **Perché `const Equazione *e`?** Passare l'indirizzo evita di copiare la struct (Appunti 6.10). `const` promette che la funzione non la modifica.
3. **`radici`** riproduce il flusso della E-tivity: se `a == 0` ritorna −1 ("non ha senso andare avanti"); poi Δ = b² − 4ac; Δ < 0 → 0; Δ == 0 → `*x1 = -b / (2a)` e ritorna 1; altrimenti `*x1 = (-b + sqrt(Δ)) / (2a)`, `*x2 = (-b - sqrt(Δ)) / (2a)` e ritorna 2. Rispetto alla E-tivity c'è una differenza voluta: lì `radici` stampava con `printf` ("sarebbe più elegante mantenere le stampe nel main", dice il prof). Qui restituisce i valori con i parametri di output e la stampa la fa chi la chiama.
4. **Scrittura:** per ogni equazione si scrive la parte `"%d) a=%.2f b=%.2f c=%.2f: "`, poi si chiama `radici(&v[i], &x1, &x2)` e si completa la riga in base al valore restituito.
5. `fclose(out)` prima che il `main` rilegga il file.

Verifica a mano dell'equazione 5: 2x² − 6x = 0 → Δ = 36 − 0 = 36, √Δ = 6 → x1 = (6 + 6) / 4 = 3, x2 = (6 − 6) / 4 = 0.
Attenzione: se b = 0 e le radici sono coincidenti, `-0.0 / (2a)` vale "meno zero" e `printf` stampa `-0.00`. I test evitano questo caso, ma è bene saperlo.
Codice in `soluzioni/es08_esame_equazioni.c`.
</details>

## Prompt pronti per questo argomento
1. "Interrogami con 6 domande, una alla volta, su `ar + i`, `*(ar + i)`, `*(*(ar + i) + j)` e `int (*p)[3]` (cartella 11 della mia repo esercizi-c). Aspetta la mia risposta prima di passare alla successiva e correggimi spiegando il perché."
2. "Ho scritto questa soluzione per es06 di 11-puntatori-avanzati-file: [incolla codice]. Dimmi se è corretta e perché, senza riscrivermela tutta. Controlla in particolare come gestisco la fine del file e i parametri di output."
3. "Generami 3 esercizi nuovi tipo es08 della cartella 11 (file + struct + parametri di output), con il testo, un file di input di esempio e l'output atteso. Non darmi le soluzioni."
4. "Scrivimi 4 frammenti di codice C con errori sugli stream (modalità di fopen, NULL, feof, fclose, fgets) e chiedimi di trovare l'errore in ognuno, uno alla volta."
5. "Spiegami con un disegno ASCII della memoria la differenza tra `int (*p)[5]`, `int *p[5]` e `char **v` quando passo `char *nomi[]` a una funzione."

## Riepilogo
- Il C passa sempre per valore: passando un indirizzo, la funzione può modificare le variabili del chiamante (parametri di output). `(*p)++` cambia il valore puntato, `p++` sposta solo la copia locale.
- In una matrice, `ar + i` punta a una riga e `*(ar + i)` al primo intero della riga: stesso indirizzo, salti diversi. Le funzioni che ricevono matrici devono conoscere il numero di colonne. Una matrice non è un `int **`.
- Un vettore di stringhe è un vettore di `char *`: si ordina scambiando i puntatori, con funzioni che ricevono `char **`.
- Con i file: `fopen` → controllo NULL → leggi/scrivi controllando il valore restituito (`== 1`, `!= NULL`, `!= EOF`) → `fclose`. Non usare `while (!feof(fp))` e non usare gets.

## Glossario
- **parametro di output** — puntatore passato a una funzione perché ci scriva un risultato (es. `long *pi` in `scompone`).
- **puntatore a puntatore (`char **`, `int **`)** — variabile che contiene l'indirizzo di un'altra variabile puntatore.
- **decadimento** — conversione automatica del nome di un vettore in puntatore al suo primo elemento quando lo usi in un'espressione.
- **puntatore a vettore (`int (*p)[3]`)** — un solo puntatore che punta a un'intera riga di 3 interi; `p + 1` salta la riga.
- **vettore di puntatori (`int *p[3]`)** — un vettore di 3 caselle, ognuna contenente un indirizzo.
- **vettore di stringhe** — vettore di `char *`, ognuno puntato al primo carattere di una stringa.
- **argc / argv** — parametri di `main`: numero di parole della riga di comando e vettore di stringhe con quelle parole.
- **stream** — sorgente o destinazione di dati (tastiera, video, file), rappresentata in C da un `FILE *`.
- **FILE \*** — puntatore alla struttura con cui la libreria tiene traccia di un file aperto.
- **stdin / stdout / stderr** — stream sempre aperti: tastiera, video, video per gli errori.
- **reindirizzamento** — `prog < file` o `prog > file`: il sistema operativo collega stdin o stdout a un file.
- **fopen / fclose** — aprono un file (restituendo un `FILE *` oppure NULL) e lo chiudono (svuotando il buffer).
- **modalità di apertura** — `"r"` lettura, `"w"` scrittura che svuota il file, `"a"` scrittura in coda; il `+` aggiunge anche l'altra direzione.
- **NULL** — indirizzo speciale "nessun oggetto"; `fopen` lo restituisce se fallisce.
- **EOF** — End Of File, costante negativa restituita dalle funzioni di lettura quando il file è finito.
- **buffer** — zona di memoria dove le scritture si accumulano prima di andare sul disco.
- **fscanf / fprintf** — `scanf` e `printf` su uno stream qualsiasi.
- **fgets / fputs** — leggono e scrivono una riga intera; `fgets` conserva il `'\n'`.
- **getc / putc** — leggono e scrivono un carattere alla volta; `getc` restituisce un `int`.
- **AddressSanitizer (ASan)** — strumento attivato dal runner che ferma il programma quando accede a memoria non valida.
- **UBSan (UndefinedBehaviorSanitizer)** — strumento che ferma il programma quando esegue un'operazione che il C vieta, come passare NULL a `feof`.
