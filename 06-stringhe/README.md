# 06 — Stringhe

> Lezioni di riferimento: trascrizione 2.6 (Stringhe), Appunti di fine Unità 2 (capitolo 4 "Stringhe nel linguaggio C", paragrafi 4.1–4.11), LEZ 12.
> Tempo stimato: ~4 ore.

## Teoria flash

**Cos'è una stringa in C.** Una **stringa** è una sequenza di caratteri (una parola, una frase). In Java o JavaScript esiste un tipo `String` apposta; in C **no**. In C una stringa è un **vettore di `char`** che finisce con un carattere speciale: il **terminatore** `'\0'` (si legge "backslash zero"). È il carattere con codice 0, non la cifra `'0'` (che ha codice 48).
```c
char s[] = "abc";   /* in memoria: 'a' 'b' 'c' '\0'  -> 4 celle, non 3 */
```
**Perché serve il terminatore?** Abbiamo visto nella cartella 05 che un vettore non "sa" quanto è lungo. Il `'\0'` è il segnale "la stringa finisce qui", come il punto alla fine di una frase. Tutte le funzioni sulle stringhe (`printf("%s")`, `strlen`, `strcpy`...) avanzano cella per cella finché lo trovano. Se manca, continuano a leggere la memoria che segue, fuori dal vettore.

**Lunghezza e dimensione sono due numeri diversi.** La **lunghezza** è quanti caratteri ci sono prima del `'\0'` (`strlen`). La **dimensione** è quante celle ha il vettore (`sizeof`). Una stringa lunga 10 ha bisogno di almeno 11 celle:
```c
#define LUNGHEZZA 10
char s[LUNGHEZZA + 1];   /* +1 per il terminatore */
```
La stringa finisce al **primo** `'\0'`: se il vettore contiene `'c' 'i' 'a' 'o' '\0' 'm' 'o' 'n' 'd' 'o' '\0'`, la stringa è `"ciao"` (esempio del prof).

**Carattere e stringa.** `'a'` (apici singoli) è **un** carattere: una cella, il numero 97 in codice ASCII (*American Standard Code for Information Interchange*, la tabella che associa a ogni carattere un numero). `"a"` (doppi apici) è una **stringa**: due celle, `'a'` e `'\0'`. `""` è la **stringa vuota**: una cella, solo `'\0'`.

**Inizializzazione.** `char s[10] = "ciao";` riempie le prime 5 celle (con `'\0'`) e le altre valgono 0. `char t[] = "ciao";` lascia scegliere la dimensione al compilatore: 5. Trappola: `char u[4] = "ciao";` compila **senza warning** in C, ma non c'è posto per il `'\0'`: `u` non è una stringa valida.

**Stampa.** `printf("%s", s)` stampa da `s[0]` fino al `'\0'` escluso. `%c` stampa un solo carattere; `%d` su un `char` stampa il suo codice numerico.

**Il nome del vettore è un indirizzo.** Scrivendo `s` (senza quadre) si ottiene l'indirizzo di `s[0]`. Per questo in `scanf("%s", s)` **non** si mette `&`: `s` è già un indirizzo. Lo approfondirai con i puntatori.

**Lettura con `scanf("%s")`.** Salta gli spazi iniziali, poi legge **una parola**: si ferma al primo spazio, tabulazione o a capo, e aggiunge il `'\0'`. **Non conosce la dimensione del vettore**: se l'utente scrive una parola troppo lunga, scrive fuori. La soluzione è indicare il massimo di caratteri: con `char s[20];` si scrive `scanf("%19s", s);` (19 caratteri + `'\0'` = 20 celle).

**Lettura con `fgets`.** `fgets(s, DIM, stdin)` legge **una riga intera**, spazi compresi, da `stdin` (lo *standard input*, cioè la tastiera o il file passato con `<`). Legge al massimo `DIM - 1` caratteri e aggiunge sempre il `'\0'`: non può uscire dal vettore. Due dettagli importanti:
1. **Tiene il `'\n'`** (l'Invio) dentro la stringa, se c'è spazio. Con l'input `ciao` la stringa diventa `"ciao\n"`, lunghezza 5. Di solito lo si toglie:
   ```c
   size_t n = strlen(s);
   if (n > 0 && s[n - 1] == '\n')
       s[n - 1] = '\0';
   ```
2. Restituisce `NULL` (un valore speciale che significa "niente") quando l'input è finito. Così `while (fgets(s, DIM, stdin) != NULL)` legge tutte le righe.

**La libreria `string.h`.** Una *libreria* è un insieme di funzioni già scritte; si usa con `#include <string.h>`.
| Funzione | Cosa fa | Attenzione |
|---|---|---|
| `strlen(s)` | lunghezza (caratteri prima di `'\0'`); restituisce `size_t` (intero senza segno), si stampa con `%zu` | conta fino al `'\0'`: se manca, legge fuori |
| `strcpy(dest, orig)` | copia `orig` in `dest`, `'\0'` compreso | non controlla se `dest` è abbastanza grande |
| `strcat(dest, add)` | aggiunge `add` in fondo a `dest` | `dest` deve avere posto per entrambe + `'\0'` |
| `strcmp(s1, s2)` | confronta: `< 0` se `s1` viene prima, `0` se uguali, `> 0` se dopo | è garantito solo il **segno**, non il valore |
| `strncpy`, `strncat` | come sopra, con un massimo di `n` caratteri | vedi le note sotto |

**Perché non si usa `=` e `==` con le stringhe.** `s1 = s2;` è un errore di compilazione: un vettore non si assegna in blocco (cartella 05). `s1 == s2` compila, ma confronta gli **indirizzi** dei due vettori, non il contenuto: due vettori diversi hanno sempre indirizzi diversi, quindi il risultato è falso anche se contengono la stessa parola. Per il contenuto si usa `strcmp(s1, s2) == 0`.

**Ordine lessicografico.** È l'ordine del dizionario: si confrontano i caratteri uno a uno e decide il **primo diverso**. `strcmp` usa i codici ASCII, quindi le maiuscole (65–90) vengono **prima** delle minuscole (97–122): `"Zebra"` viene prima di `"ape"`. Se una stringa è l'inizio dell'altra (`"cas"` e `"casa"`), la più corta viene prima, perché il suo `'\0'` (0) è minore di qualunque carattere.

**La libreria `ctype.h`.** Funzioni sui singoli caratteri: `isalpha(c)` (è una lettera?), `isdigit(c)` (è una cifra?), `isalnum(c)` (lettera o cifra?), `isspace(c)` (spazio, tab, a capo?), `toupper(c)` / `tolower(c)` (converte in maiuscolo/minuscolo; se non è una lettera lo lascia com'è). Si scrive `toupper((unsigned char)s[i])`: queste funzioni vogliono un valore da 0 a 255, e le lettere accentate in UTF-8 (la codifica dei file di testo moderni) danno `char` negativi. Passare un valore negativo è comportamento indefinito.

**Buffer overflow.** Un **buffer** è un vettore usato come deposito temporaneo (per esempio per il testo digitato). Il **buffer overflow** è scrivere oltre la sua fine: con le stringhe succede con `scanf("%s")` senza larghezza, `strcpy`, `strcat` su un `dest` troppo piccolo, o un `'\0'` dimenticato. ASan (AddressSanitizer, lo strumento dei test che controlla gli accessi alla memoria) lo segnala con `ERROR: AddressSanitizer: stack-buffer-overflow`. Senza ASan, gcc su Linux a volte ferma il programma alla fine con `*** stack smashing detected ***: terminated` (rilevato sfondamento dello stack, la zona di memoria delle variabili locali).

**Imprecisioni e contraddizioni nelle fonti:**
- **Trascrizione, `strcmp`**: la trascrizione automatica dice "se è nullo dice che le stringhe sono terminate, se è negativo ci dice che S1 è terminato". È un errore di trascrizione: la versione corretta è quella della dispensa (4.10): 0 = uguali, negativo = `s1` viene prima, positivo = `s1` viene dopo.
- **`BUFSIZ`**: nella trascrizione ("Buff Size") viene descritto come la dimensione del buffer della tastiera (quello che "suona" quando è pieno). In realtà `BUFSIZ` è una costante di `stdio.h` che indica la dimensione dei buffer interni di input/output: vale 8192 su Linux (glibc) e 1024 su macOS. Inoltre `char str[BUFSIZ]; scanf("%s", str);` (dispensa 4.8.1) **non** è sicuro: `scanf` non conosce la dimensione, e un input più lungo la sfonda comunque. Meglio `scanf("%99s", s)` con `char s[100]`, oppure `fgets`.
- **fgets e il `'\n'`**: la dispensa (4.8.2) dice che `fgets` legge "fino al ritorno a capo", ma non dice che il `'\n'` **resta nella stringa**. La trascrizione lo accenna ("considera o non considera il ritorno a capo"). La regola esatta: `fgets` lo tiene, `scanf("%s")` no (lo lascia nell'input).
- **`strncpy` e `strncat` "per evitare sforamenti"** (trascrizione e dispensa 4.9.4): aiutano, ma con due insidie. `strncpy(dest, orig, n)` **non aggiunge il `'\0'`** se `orig` ha `n` o più caratteri: va messo a mano (`dest[n - 1] = '\0';`). In `strncat(dest, add, n)` il numero `n` è il massimo di caratteri **aggiunti**, non la dimensione di `dest`: `dest` deve avere posto per `strlen(dest) + n + 1` caratteri.
- **Dispensa 4.11.1 contro 4.11.2**: il primo paragrafo dice correttamente che con `char s[5]` una stringa "più lunga di quattro caratteri" sfonda il vettore; il secondo dice "più lunga di cinque". Ha ragione il primo: 5 caratteri + `'\0'` = 6 celle, già troppe.
- **Trascrizione automatica**: "strcopy" = `strcpy`; "str con per" = `strcmp`; "per cento S" = `%s`; "l'aggett s" = probabilmente `fgets`; "Buff Size" = `BUFSIZ`.

### Errori tipici
1. **Confrontare con `==`**: `if (a == b)` (con `a`, `b` vettori di char) →
   `warning: comparison between two arrays [-Warray-compare]`. Usa `strcmp(a, b) == 0`.
2. **Assegnare con `=`**: `b = "ciao";` →
   `error: assignment to expression with array type`. Usa `strcpy(b, "ciao");`.
3. **`&` davanti al nome del vettore in scanf**: `scanf("%9s", &a);` →
   `warning: format '%s' expects argument of type 'char *', but argument 2 has type 'char (*)[10]' [-Wformat=]`.
4. **Confondere `'a'` e `"a"`**: `char c = "a";` →
   `warning: initialization of 'char' from 'char *' makes integer from pointer without a cast [-Wint-conversion]`.
5. **Dimenticare `#include <string.h>`**: `strlen(a)` →
   `warning: implicit declaration of function 'strlen' [-Wimplicit-function-declaration]` (con gcc 14 e clang recenti è un **errore**).
6. **Nessuno spazio per `'\0'`**: `char t[3] = "ciao";` → `warning: initializer-string for array of 'char' is too long`; ma `char s[4] = "ciao";` non dà **nessun** warning ed è comunque sbagliato. Copiando a mano, dimenticare `dest[i] = '\0';` produce testo "sporco" (es08).

## Esercizi

### es01 — Lunghezza a mano e il '\n' di fgets  ·  Base
**Fonte:** Ispirato a: trascrizione 2.6 ("strlen... mi ritorna da quanti caratteri è composta partendo dall'inizio finché non trovo il primo terminatore"; fgets "considera o non considera il ritorno a capo"); Appunti Unità 2, par. 4.2, 4.8.2, 4.9.1. Variante di LEZ 12 es. 1: qui si legge una riga intera con fgets e si gestisce l'a capo.
**Testo:** leggi una riga con `fgets` (già scritto). Completa `mia_strlen` (senza usare `strlen`) e `togli_a_capo`. Il main stampa la lunghezza prima e dopo aver tolto l'a capo, il valore di `strlen` e la riga tra quadre.
```text
input:  ciao mondo
output: con a capo: 11
        senza a capo: 10
        strlen: 10
        [ciao mondo]
```
**File:** `es01_lunghezza_fgets.c` · **Test:** `make test T=06 E=es01`

<details><summary>💡 Suggerimento</summary>
In mia_strlen il contatore stesso può fare da indice: quando s[i] è '\0', i è già la risposta. In togli_a_capo guarda la cella n-1, ma solo se n > 0. Il terzo test ha una riga SENZA a capo finale: non devi togliere nulla.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **`mia_strlen`**: `i` parte da 0 e avanza finché `s[i] != '\0'`. Quando il ciclo si ferma, `i` è l'indice del terminatore, cioè proprio il numero di caratteri che lo precedono.
2. **Perché "con a capo" vale 11?** `fgets` ha messo nella stringa anche il `'\n'`: `"ciao mondo\n"` = 10 + 1 caratteri.
3. **`togli_a_capo`**: calcola `n` (lunghezza). Se `n > 0` e `s[n-1] == '\n'`, scrive `'\0'` al suo posto: la stringa ora finisce un carattere prima. Il controllo `n > 0` evita `s[-1]` (fuori dal vettore) con la stringa vuota. Il controllo `== '\n'` serve perché l'ultima riga di un file può non avere l'a capo (test 3: `"  abc"`), e allora toglieremmo la `c`.
4. **Riga vuota** (test 2): `fgets` legge solo `"\n"` → lunghezza 1, poi 0.

```c
int mia_strlen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}
```
Simulazione con `"ab\n"`: `s[0]`='a' → i=1; `s[1]`='b' → i=2; `s[2]`='\n' → i=3; `s[3]`='\0' → stop, restituisce 3.
Codice completo: `soluzioni/es01_lunghezza_fgets.c`.
</details>

### es02 — Conta ogni vocale separatamente  ·  Base
**Fonte:** Ispirato a: Appunti Unità 2, par. 4.5 ("il carattere può essere interpretato come un numero intero corrispondente al codice ASCII"); LEZ 12, par. 3.18 (ctype.h). Variante di LEZ 12 es. 2: qui ogni vocale ha il suo contatore, in un vettore.
**Testo:** leggi una riga. Completa `conta_vocali`: riempie `cont[0..4]` con quante `a`, `e`, `i`, `o`, `u` ci sono (maiuscole comprese) e restituisce quante **altre lettere** ci sono. Spazi, cifre e punteggiatura non contano. Nei test non ci sono lettere accentate.
```text
input:  Programmare In C e Bello
output: a: 2
        e: 3
        i: 1
        o: 2
        u: 0
        vocali: 8
        altre lettere: 12
```
**File:** `es02_conta_vocali.c` · **Test:** `make test T=06 E=es02`

<details><summary>💡 Suggerimento</summary>
Converti ogni carattere in minuscolo prima di confrontarlo: così 'I' e 'i' diventano la stessa cosa. Per sapere QUALE contatore incrementare, puoi confrontare il carattere con le celle di una stringa "aeiou": la posizione k in cui lo trovi è l'indice giusto di cont.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Azzerare `cont`**: il vettore arriva dal main con spazzatura.
2. **Scorrere la stringa** con `for (i = 0; s[i] != '\0'; i++)`: la condizione è il terminatore, non una lunghezza.
3. **`c = tolower((unsigned char)s[i])`**: `'P'` diventa `'p'`, il resto non cambia. Il cast a `unsigned char` evita valori negativi (vedi Teoria flash).
4. **`if (!isalpha(c)) continue;`**: `continue` salta al giro successivo del ciclo. Così spazi e cifre non finiscono tra le "altre lettere".
5. **Quale vocale?** `char vocali[] = "aeiou";` è usata come tabella: se `c == vocali[k]`, incrementa `cont[k]`. Se nessuna `k` corrisponde, è una consonante: `altre++`.

```c
c = tolower((unsigned char)s[i]);
if (!isalpha(c))
    continue;
vocale = 0;
for (k = 0; k < 5; k++)
    if (c == vocali[k]) {
        cont[k]++;
        vocale = 1;
    }
if (!vocale)
    altre++;
```
Controllo a mano: Programmare (o, a, a, e + 7 consonanti), In (i + n), C (1 consonante), e, Bello (e, o + B, l, l). Vocali: a=2, e=3, i=1, o=2 → 8. Consonanti: 7 + 1 + 1 + 3 = 12.
Codice completo: `soluzioni/es02_conta_vocali.c`.
</details>

### es03 — Cosa stampa?  ·  Base
**Fonte:** Ispirato a: trascrizione 2.6 (stringa `"abc"` di 4 celle; "ciao mondo" con il terminatore in mezzo; `str == str2` confronta gli indirizzi); Appunti Unità 2, par. 4.4, 4.5, 4.7, 4.9, 4.10.
**Testo:** apri `es03_cosa_stampa.c` e, **senza eseguirlo**, prevedi le righe A–I. Il test passa già: l'output vero è in `tests/es03_cosa_stampa.out`. Ipotesi: codici ASCII (`'a'` = 97, `'A'` = 65).
```text
A: ? ? ?
...
I: ? ?
```
**File:** `es03_cosa_stampa.c` · **Test:** `make test T=06 E=es03`

<details><summary>💡 Suggerimento</summary>
Distingui sempre sizeof (celle del vettore) da strlen (caratteri prima del primo '\0'). Un confronto come `x < 0` in C vale 1 se è vero e 0 se è falso.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output corretto:
```text
A: 10 5 4
B: 6 2
C: ok|no
D: 105 0
E: Cp
F: ciao-ciao 9
G: 0 1
H: ci 2 0
I: 1 1
```
1. **A**: `s` è dichiarato con 10 celle → `sizeof(s)` = 10. `t[] = "ciao"`: il compilatore conta 4 caratteri + `'\0'` → 5. `strlen(s)` = 4: conta solo i caratteri prima del terminatore.
2. **B**: `u` ha 6 celle (le abbiamo elencate tutte). Ma la stringa finisce al **primo** `'\0'` (cella 2): `strlen(u)` = 2. È l'esempio "ciao mondo" del prof in piccolo.
3. **C**: `%s` con `u` stampa `ok`. `&u[3]` è l'indirizzo della cella 3: `%s` parte da lì e stampa `no` fino al secondo `'\0'`.
4. **D**: `s[1]` è `'i'`, che con `%d` mostra il suo codice ASCII: 105. `s[4]` è il terminatore: 0.
5. **E**: `s[0] - 32` = `'c'` (99) − 32 = 67 = `'C'`. È il "trucco" ASCII: maiuscola e minuscola distano 32. `t[3] + 1` = `'o'` (111) + 1 = 112 = `'p'`. Risultato `Cp`.
6. **F**: `strcpy` → `"ciao"`, `strcat` con `"-"` → `"ciao-"`, `strcat` con `t` → `"ciao-ciao"`: 9 caratteri. `w` ha 20 celle: c'è spazio.
7. **G**: `&s[0] == &t[0]` confronta gli indirizzi di due vettori diversi: falso, 0. È quello che farebbe `s == t`. `strcmp(s, t) == 0` confronta il contenuto: `"ciao"` e `"ciao"` sono uguali → 1.
8. **H**: `s[2] = '\0'` "taglia" la stringa dopo `ci`: stampa `ci`, lunghezza 2, e `strcmp(s, "ci")` = 0 (uguali). Le celle `'a'`, `'o'` sono ancora nel vettore, ma non fanno più parte della stringa.
9. **I**: `"abc"` e `"abd"` differiscono al terzo carattere: `'c'` < `'d'` → negativo → `< 0` vale 1. `"casa"` e `"cas"`: al quarto carattere `'a'` (97) contro `'\0'` (0) → positivo → `> 0` vale 1.

Codice commentato: `soluzioni/es03_cosa_stampa.c`.
</details>

### es04 — Inverti ogni parola, lasciando le parole al loro posto  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 2, par. 4.1 ("una stringa è semplicemente un array di elementi di tipo char"): stesso algoritmo di es04 della cartella 05 (inversione di un tratto) applicato ai caratteri. Variante di LEZ 12 es. 4: qui si inverte ogni parola di una riga, non una parola sola.
**Testo:** leggi una riga. Completa `inverti_tratto` (inverte `s[a]..s[b]` sul posto) e `inverti_parole` (trova ogni parola e la inverte). Spazi e ordine delle parole non cambiano. Il main stampa il risultato tra quadre.
```text
input:  ciao mondo crudele
output: [oaic odnom eledurc]
```
**File:** `es04_inverti_parole.c` · **Test:** `make test T=06 E=es04`

<details><summary>💡 Suggerimento</summary>
Con un indice i: salta gli spazi, ricorda dove inizia la parola, avanza finché non trovi uno spazio o '\0'. Ora la parola va da inizio a i-1. Ripeti finché s[i] non è '\0'. Non invertire mai il '\0'.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **`inverti_tratto`** è identica a quella per i vettori di `int`: due indici che si vengono incontro e scambio con variabile d'appoggio (qui di tipo `char`).
2. **Trovare le parole**: un ciclo esterno finché `s[i] != '\0'`. Dentro: (a) salta gli spazi con `isspace`; (b) `inizio = i`; (c) avanza finché il carattere non è uno spazio e non è `'\0'`. A questo punto la parola occupa `inizio .. i-1`.
3. **Perché `i - 1`?** `i` è il primo carattere *dopo* la parola (uno spazio o il `'\0'`). Se passassimo `i`, sposteremmo lo spazio o, peggio, il terminatore all'inizio della parola: la stringa diventerebbe vuota.
4. **Riga vuota o solo spazi**: alla fine `inizio == i`, quindi `inverti_tratto(s, i, i - 1)` riceve `a > b` e non fa nulla.

```c
while (s[i] != '\0') {
    while (s[i] != '\0' && isspace((unsigned char)s[i]))
        i++;
    inizio = i;
    while (s[i] != '\0' && !isspace((unsigned char)s[i]))
        i++;
    inverti_tratto(s, inizio, i - 1);
}
```
Simulazione su `"  x  ab"`: salta 2 spazi, parola `x` (0 scambi), salta 2 spazi, parola `ab` da 5 a 6 → scambio → `"  x  ba"`.
Codice completo: `soluzioni/es04_inverti_parole.c`.
</details>

### es05 — Frase palindroma  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 2, par. 4.5 (caratteri come numeri) e 4.8.2 (fgets); LEZ 12, par. 3.18 (ctype.h). Variante di LEZ 12 es. 5: qui si analizzano frasi intere, ignorando spazi, punteggiatura e maiuscole.
**Testo:** leggi righe fino alla fine dell'input. Per ognuna stampa `SI: riga` se è **palindroma** (si legge uguale da sinistra e da destra), `NO: riga` altrimenti. Conta solo lettere e cifre (`isalnum`), senza distinguere maiuscole e minuscole. Una riga senza lettere né cifre è palindroma.
```text
input:  I topi non avevano nipoti
        Ciao
        Ai lati d'Italia
output: SI: I topi non avevano nipoti
        NO: Ciao
        SI: Ai lati d'Italia
```
**File:** `es05_frase_palindroma.c` · **Test:** `make test T=06 E=es05`

<details><summary>💡 Suggerimento</summary>
Due indici: i dall'inizio, j dall'ultimo carattere (strlen - 1). A ogni giro, se s[i] non è lettera/cifra sposta solo i; se s[j] non lo è sposta solo j; altrimenti confronta i due caratteri resi minuscoli. Una coppia diversa basta per rispondere 0.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Indici**: `i = 0`, `j = strlen(s) - 1`. Con la stringa vuota `j` vale -1: il ciclo `while (i < j)` non parte e la risposta è 1 (nessuna prova contraria). Attenzione: `strlen` restituisce `size_t`, senza segno; `0 - 1` in `size_t` diventa un numero enorme. Per questo si converte prima in `int`: `(int)strlen(s) - 1`.
2. **Saltare i caratteri inutili**: se `s[i]` non è `isalnum`, `i++` e si ricomincia il giro (`continue`); lo stesso per `j`. Spazi e apostrofi così non contano.
3. **Confronto**: `tolower(s[i]) != tolower(s[j])` → `return 0`. Altrimenti `i++`, `j--`.
4. **Fine del ciclo**: se `i` e `j` si sono incontrati senza differenze, `return 1`.

```c
while (i < j) {
    if (!isalnum((unsigned char)s[i])) { i++; continue; }
    if (!isalnum((unsigned char)s[j])) { j--; continue; }
    if (tolower((unsigned char)s[i]) != tolower((unsigned char)s[j]))
        return 0;
    i++;
    j--;
}
return 1;
```
"Ai lati d'Italia" ridotta a sole lettere minuscole è `ailatiditalia`, che letta al contrario è identica. "12 31" diventa `1231` → NO.
Codice completo: `soluzioni/es05_frase_palindroma.c`.
</details>

### es06 — Confronta due stringhe a mano (la tua strcmp)  ·  Intermedio
**Fonte:** Ispirato a: trascrizione 2.6 ("non le posso confrontare con l'uguale uguale perché... confronto gli indirizzi"; strcmp "scorre in parallelo le due stringhe partendo dall'indice 0... quando trova caratteri diversi si ferma"); Appunti Unità 2, par. 4.10.
**Testo:** leggi coppie di parole fino alla fine dell'input (`scanf("%49s %49s")`, già scritto). Completa `mia_strcmp` (senza usare `strcmp`) e `segno` (riduce un intero a -1, 0 o 1). Il main stampa anche il segno della `strcmp` vera e il risultato di `==` sugli indirizzi.
```text
input:  abc abd
        casa cas
        Zebra ape
output: abc abd -> mia: -1, strcmp: -1, ==: 0
        casa cas -> mia: 1, strcmp: 1, ==: 0
        Zebra ape -> mia: -1, strcmp: -1, ==: 0
```
**File:** `es06_confronta.c` · **Test:** `make test T=06 E=es06`

<details><summary>💡 Suggerimento</summary>
Avanza con un unico indice finché s1[i] == s2[i] e s1[i] non è '\0'. Quando ti fermi, la risposta dipende solo da s1[i] e s2[i]: la loro differenza ha già il segno giusto.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Scorrere in parallelo** (come dice il prof): `while (s1[i] != '\0' && s1[i] == s2[i]) i++;`.
2. **Perché basta controllare `s1[i] != '\0'`?** Se `s2` finisse prima, `s2[i]` sarebbe `'\0'` e `s1[i]` no: sarebbero diversi e il ciclo si fermerebbe comunque. Se finiscono insieme, ci fermiamo su due `'\0'`.
3. **Il risultato** è `s1[i] - s2[i]`: negativo se il carattere di `s1` ha codice più basso, 0 se sono entrambi `'\0'` (stringhe uguali). Con `"casa"` e `"cas"`: `'a'` (97) − `'\0'` (0) = 97 > 0. Il cast `(unsigned char)` imita la `strcmp` vera.
4. **Perché `segno`?** Lo standard garantisce solo il segno del risultato di `strcmp`, non il valore: su una macchina può dare -1, su un'altra -32. Per confrontare la tua funzione con quella vera in modo affidabile riduciamo entrambi a -1/0/1.
5. **`==: 0` sempre**: `a` e `b` sono due vettori distinti, quindi i loro indirizzi sono diversi anche quando contengono la stessa parola (`ciao ciao`). Per questo `==` non serve a confrontare stringhe.
6. **`Zebra` prima di `ape`**: `'Z'` = 90, `'a'` = 97. L'ordine di `strcmp` non è quello "umano" del dizionario: le maiuscole vengono tutte prima.

```c
int mia_strcmp(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] != '\0' && s1[i] == s2[i])
        i++;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}
```
Codice completo: `soluzioni/es06_confronta.c`.
</details>

### es07 — Analisi di una frase: parole, parola più lunga, maiuscolo  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 2, par. 4.4 (la stringa finisce al primo terminatore: serve per costruire una sottostringa) e 4.9.2 (copia carattere per carattere); LEZ 12, par. 3.18 (`isspace`, `toupper`). Variante di LEZ 12 es. 6: oltre a contare le parole si estrae la più lunga e si converte la riga.
**Testo:** leggi una riga. Completa `conta_parole`, `parola_piu_lunga` (copia in `out` la parola più lunga, terminata da `'\0'`, e ne restituisce la lunghezza; a parità vince la prima) e `maiuscolo`. Le parole possono essere separate da più spazi.
```text
input:  oggi studio   la programmazione in C
output: parole: 6
        piu lunga: programmazione (14)
        maiuscolo: [OGGI STUDIO   LA PROGRAMMAZIONE IN C]
```
**File:** `es07_analisi_frase.c` · **Test:** `make test T=06 E=es07`

<details><summary>💡 Suggerimento</summary>
Per contare non contare gli spazi (con spazi doppi sbaglieresti): conta gli INIZI di parola, usando una variabile che ricorda se sei "dentro" una parola. Per la più lunga ricordati l'indice di inizio e la lunghezza della migliore; alla fine copiala in out e aggiungi tu il '\0'.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **`conta_parole`**: una variabile `dentro` (vale 1 se siamo in mezzo a una parola). Per ogni carattere: se è uno spazio, `dentro = 0`; se non lo è e `dentro` era 0, stiamo **entrando** in una parola: `parole++` e `dentro = 1`. Così spazi multipli, iniziali o finali non creano parole fantasma.
2. **`parola_piu_lunga`**: stessa scansione di es04 (salta spazi, `inizio = i`, avanza). `len = i - inizio`. Se `len > best_len`, ricordiamo `best_inizio` e `best_len`. Con `>` (e non `>=`) a parità resta la prima: nel test `tre due uno` vince `tre`.
3. **Copiare la sottostringa**: `for (k = 0; k < best_len; k++) out[k] = s[best_inizio + k];` e poi **`out[best_len] = '\0';`**. Senza il terminatore, `printf("%s", out)` continuerebbe a stampare spazzatura.
4. **`maiuscolo`**: `s[i] = toupper((unsigned char)s[i])` per ogni carattere. `toupper` lascia invariati spazi e lettere già maiuscole.
5. **Ordine nel main**: prima si cerca la parola più lunga, poi si converte in maiuscolo, perché `maiuscolo` modifica `s` sul posto.

```c
for (i = 0; s[i] != '\0'; i++) {
    if (isspace((unsigned char)s[i]))
        dentro = 0;
    else if (!dentro) {
        dentro = 1;
        parole++;
    }
}
```
Caso limite nei test: riga di soli spazi → `parole: 0`, `piu lunga: nessuna (0)`.
Codice completo: `soluzioni/es07_analisi_frase.c`.
</details>

### es08 — Trova e correggi l'errore: "Cognome, Nome"  ·  Tipo esame
**Fonte:** Ispirato a: trascrizione 2.6 ("se la destinazione è più corta la copia eccede i limiti e sporca altri dati"); Appunti Unità 2, par. 4.9.2, 4.9.3, 4.11 (buffer overflow, funzioni non sicure).
**Testo:** il programma legge coppie `nome cognome` e stampa `Cognome, Nome (lunghezza)` usando due funzioni scritte a mano, `mia_copia` (come `strcpy`) e `mia_accoda` (come `strcat`). Contiene **due** errori: uno produce testo sporco (test 1), l'altro scrive fuori da un vettore con nomi lunghi (test 2, CRASH di AddressSanitizer). Correggili.
```text
input:  Ada Lovelace
        Alan Turing
output: Lovelace, Ada (13)
        Turing, Alan (12)
uscita attuale (sbagliata), seconda riga: Turingce, Ada, Alan (19)
```
**File:** `es08_trova_errore.c` · **Test:** `make test T=06 E=es08`

<details><summary>💡 Suggerimento</summary>
"Turingce, Ada": da dove vengono "ce, Ada"? Sono avanzi della persona precedente: qualcosa non dice alla stringa dove finire. Per il secondo errore conta quante celle servono, nel caso peggiore, per cognome + ", " + nome + '\0'.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Errore 1 — `mia_copia` non copia il `'\0'`.** Il ciclo `while (orig[i] != '\0')` si ferma *prima* di copiare il terminatore. Alla prima persona `completo` era (forse) pieno di zeri e tutto sembrava andare; alla seconda contiene ancora `"Lovelace, Ada"`. Copiando `"Turing"` sopra le prime 6 celle resta `"Turingce, Ada"`, e `mia_accoda` aggiunge dopo. **Correzione:** dopo il ciclo, `dest[i] = '\0';`. Nota che `mia_accoda` invece lo fa già.
2. **Errore 2 — `char completo[DIM]` è troppo piccolo.** Nel caso peggiore servono 19 (cognome) + 2 (`", "`) + 19 (nome) + 1 (`'\0'`) = 41 celle. Con `"Rita Levi-Montalcini"` il risultato `"Levi-Montalcini, Rita"` ha 21 caratteri + `'\0'` = 22 > 20: `mia_accoda` scrive oltre la fine. ASan: `ERROR: AddressSanitizer: stack-buffer-overflow ... WRITE of size 1 ... in mia_accoda`. **Correzione:** `#define DIM_COMPLETO (2 * DIM + 1)` e `char completo[DIM_COMPLETO];`.
3. **Perché `%19s` nello scanf?** Con `char nome[20]` al massimo 19 caratteri + `'\0'`. Senza il 19, un nome lungo sfonderebbe `nome` stesso: è il primo esempio di buffer overflow della dispensa (4.11.1).
4. **Lezione generale**: chi scrive una funzione che costruisce una stringa è responsabile del `'\0'`; chi dichiara il vettore di destinazione è responsabile della sua dimensione. Il C non controlla nessuna delle due cose.

```c
void mia_copia(char dest[], char orig[])
{
    int i = 0;
    while (orig[i] != '\0') {
        dest[i] = orig[i];
        i++;
    }
    dest[i] = '\0';   /* la riga mancante */
}
```
Codice corretto: `soluzioni/es08_trova_errore.c`.
</details>

## Prompt pronti per questo argomento
- "Interrogami con 5 domande sulle stringhe in C (terminatore, sizeof contro strlen, scanf contro fgets, perché non si usa ==, strcmp), una alla volta. Aspetta la mia risposta e correggimi spiegando il perché."
- "Ho scritto questa soluzione per es07 di 06-stringhe: [incolla codice]. Dimmi se è corretta e perché, quali casi limite (riga vuota, spazi multipli, parole di pari lunghezza) potrebbe sbagliare, senza riscrivermela tutta."
- "Scrivimi a mano, passo per passo, cosa fa `strcat(dest, add)` sulla memoria se `dest = \"ciao\"` in un vettore di 6 celle e `add = \"!!\"`. Disegna le celle e dimmi dove avviene il buffer overflow."
- "Generami 3 esercizi nuovi sulle stringhe di livello tipo esame (prof Anisetti), con input/output di esempio e senza soluzione: uno con fgets, uno con ctype.h, uno che costruisce una stringa a mano."
- "Dammi 4 frammenti di codice C con stringhe, ognuno con un errore diverso (terminatore, dimensione, ==, & in scanf). Io trovo l'errore, tu mi dici se ho ragione."

## Riepilogo
- In C una stringa è un vettore di `char` che termina con `'\0'`: servono lunghezza + 1 celle. La stringa finisce al primo `'\0'`; `strlen` conta i caratteri prima di esso, `sizeof` conta le celle del vettore.
- `scanf("%Ns")` legge una parola (metti sempre la larghezza N); `fgets` legge una riga intera e tiene il `'\n'`, che di solito si toglie.
- Stringhe si copiano, si accodano e si confrontano con `strcpy`, `strcat`, `strcmp` (o a mano), mai con `=` e `==`. Nessuna di queste funzioni controlla la dimensione della destinazione.
- `ctype.h` lavora sui singoli caratteri (`isalpha`, `isspace`, `toupper`...); si passa sempre `(unsigned char)c`.

## Glossario
- **stringa** — sequenza di caratteri; in C, vettore di `char` terminato da `'\0'`.
- **terminatore `'\0'`** — carattere con codice 0 che segna la fine di una stringa.
- **lunghezza** — numero di caratteri prima del `'\0'` (`strlen`).
- **dimensione** — numero di celle del vettore (`sizeof`).
- **ASCII** — tabella che associa un numero a ogni carattere (`'a'` = 97, `'A'` = 65).
- **stringa vuota** — `""`, contiene solo il `'\0'`.
- **`%s`** — segnaposto di printf/scanf per le stringhe.
- **`stdin`** — standard input: da dove il programma legge (tastiera o file passato con `<`).
- **`fgets`** — legge una riga intera (massimo DIM-1 caratteri), tiene il `'\n'`, aggiunge `'\0'`.
- **`NULL`** — valore speciale che significa "nessun indirizzo"; `fgets` lo restituisce a fine input.
- **`BUFSIZ`** — costante di `stdio.h` con la dimensione dei buffer di input/output (8192 su Linux, 1024 su macOS).
- **libreria** — insieme di funzioni già scritte, incluse con `#include`.
- **`string.h`** — libreria con `strlen`, `strcpy`, `strcat`, `strcmp`, `strncpy`, `strncat`.
- **`ctype.h`** — libreria con funzioni sui caratteri: `isalpha`, `isdigit`, `isalnum`, `isspace`, `toupper`, `tolower`.
- **`size_t`** — tipo intero senza segno usato per dimensioni e lunghezze; si stampa con `%zu`.
- **ordine lessicografico** — ordine "da dizionario" basato sul primo carattere diverso (con i codici ASCII).
- **palindromo** — che si legge uguale da sinistra a destra e da destra a sinistra.
- **buffer** — vettore usato come deposito temporaneo di dati.
- **buffer overflow** — scrittura oltre la fine di un buffer, che sporca la memoria vicina.
- **ASan (AddressSanitizer)** — strumento del compilatore che ferma il programma se accede a memoria non sua.
- **stack** — zona di memoria dove vivono le variabili locali delle funzioni.
- **cast** — conversione esplicita di tipo, es. `(unsigned char)c`.
