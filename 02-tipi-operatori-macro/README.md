# 02 — Tipi di dato, operatori e macro

> Lezioni di riferimento: trascrizione 2.2 (e 2.1 per divisione e promozioni; 3.2 per le macro con parametri), Appunti Unità 2 (cap. 1: §1.5.1 Macro, §1.7 Tipi, §1.8 Costanti, §1.11 Operatori, §1.12–1.15 Assegnamenti e ++/--, §1.16 Conversioni, §1.19 Overflow; cap. 2: §2.19 sizeof), Dispensa 2.2.2 (tipi primitivi, limiti), LEZ 08.
> Tempo stimato: ~3 ore.

## Teoria flash

**Tipo.** Per il prof il tipo di una variabile dice quattro cose: quali valori può avere, come sono scritti in binario, quanto spazio occupano, quali operazioni si possono fare. Il tipo serve anche al compilatore per scegliere *quale* operazione fare: `a / b` è una divisione diversa se `a` e `b` sono interi o reali.

| tipo | cosa contiene | byte (macOS Apple Silicon e Linux 64 bit) | `printf` |
|---|---|---|---|
| `char` | un carattere, cioè un piccolo intero (codice ASCII: `'A'` = 65) | 1 | `%c` (carattere) o `%d` (numero) |
| `short` / `int` / `long` | interi con segno | 2 / 4 / 8 | `%hd` / `%d` / `%ld` |
| `unsigned int` | interi senza segno (solo ≥ 0) | 4 | `%u` |
| `float` / `double` | numeri reali (in realtà approssimati) | 4 / 8 | `%f` (printf usa `%f` per entrambi) |

- **Byte e bit**: un *bit* è una cifra binaria (0 o 1); un *byte* sono 8 bit. Con n bit e il segno rappresenti da −2^(n−1) a 2^(n−1) − 1 (un `int` a 32 bit: da −2147483648 a 2147483647). Senza segno (`unsigned`): da 0 a 2^n − 1.
- **`sizeof(tipo)`** o **`sizeof(espressione)`** è un *operatore* (non una funzione) che dà i byte occupati. Il risultato è di tipo `size_t` (un intero senza segno), da stampare con `%zu`. Le costanti `INT_MAX`, `SCHAR_MAX`… stanno in `<limits.h>`.
- **Costanti letterali** (*letterale* = valore scritto direttamente nel codice): `5` è `int`, `1.4` è `double`, `1.4f` è `float`, `1L` è `long`, `'A'` è un carattere (in C ha tipo `int`, valore 65).
- **Overflow**: il risultato non ci sta nei bit del tipo. Per gli interi **con segno** il C lo considera *comportamento indefinito* (UB, *undefined behavior*: lo standard non dice cosa succede, il programma può fare qualsiasi cosa). Per gli `unsigned` invece è definito: si "riparte da 0" come un contachilometri. Per evitarlo si controlla **prima** di fare il calcolo.

**Operatori aritmetici.** `+ - * / %`. Il prof insiste: "l'operatore guarda gli operandi", non dove finisce il risultato.
```c
int a = 7, b = 2;
double r = a / b;          /* 3.0 : divisione INTERA, poi convertita */
r = (double)a / b;         /* 3.5 : a diventa double, b viene promosso */
r = (double)(a / b);       /* 3.0 : il cast arriva troppo tardi */
```
- `%` (resto) esiste **solo tra interi**. Con i negativi, dal C99 la divisione tronca verso lo zero: `-7 / 2` = −3 e `-7 % 2` = −1.
- **Conversione implicita (promozione)**: in un'operazione tra tipi diversi, il "più piccolo" viene convertito nel "più grande" (`char` → `int` → `float` → `double`), senza perdere informazione. Nell'**assegnamento** invece il valore viene convertito nel tipo di sinistra, anche se perde informazione: `int b = 4.3;` mette 4 (tronca).
- **Cast (conversione esplicita)**: `(tipo) espressione`. È un operatore *unario* (agisce su un solo operando) ad alta priorità: si applica a ciò che segue subito, non a tutta l'espressione.

**Assegnamento, ++ e --.** In C `x = 5` è un'*espressione*: ha un valore (5) e un *side effect* (effetto collaterale: cambia `x`). Gli assegnamenti composti: `a += b` equivale a `a = a + (b)` — nota la parentesi: `c *= 2 + 1` moltiplica per 3.
- `++b` (*prefisso*): incrementa, e il valore dell'espressione è quello **nuovo**.
- `b++` (*postfisso*): il valore dell'espressione è quello **vecchio**; l'incremento avviene comunque prima dell'istruzione successiva.
- Mai modificare la stessa variabile due volte nella stessa espressione (`i = i++ + 1;`): è UB.

**Relazionali e logici.** `< > <= >= == !=` danno 1 (vero) o 0 (falso), e questi numeri si possono usare nei calcoli. Logici: `!` (NOT), `&&` (AND), `||` (OR). **Cortocircuito** (*short-circuit*): si valuta da sinistra e ci si ferma appena il risultato è certo. `0 && ...` è 0 senza guardare il resto; `1 || ...` è 1 senza guardare il resto. Se la parte saltata conteneva `j++` o una chiamata di funzione, quell'effetto **non avviene** (il prof avverte: anche problemi di sicurezza). Lo si sfrutta per proteggere: `q > 0 && x / q > 3` non divide mai per 0.

**Precedenza e associatività.** La *precedenza* dice quale operatore si applica prima (`*` prima di `+`); l'*associatività* decide tra operatori con la stessa precedenza (`* / %` da sinistra a destra: `b * 3 % 4` = `(b * 3) % 4`; `=` da destra: `a = b = 5` = `a = (b = 5)`). Ordine a grandi linee, dal più forte: `++ -- ! cast` → `* / %` → `+ -` → `< > <= >=` → `== !=` → `&&` → `||` → `= += -=…`. Nel dubbio: parentesi.

**Macro (`#define`).** Il preprocessore fa una **sostituzione di testo** prima della compilazione. Non calcola nulla e non conosce i tipi.
```c
#define LUNGHEZZA 20              /* costante simbolica: MAIUSCOLO per convenzione */
#define DIFFERENZA 3-2            /* 10 * DIFFERENZA  ->  10 * 3-2  = 28 (!) */
#define MOLTIPLICA(a, b) a * b    /* MOLTIPLICA(x-1, y)  ->  x-1 * y          */
#define MOLTIPLICA_OK(a, b) ((a) * (b))   /* regola: parentesi su ogni parametro e su tutto */
```
Il prof (lezione 3.2): una macro con parametri "sembra" una funzione ma non lo è: non c'è chiamata né salto, il codice viene copiato al suo posto (*macro-espansione*). Vantaggio: niente costo di chiamata. Rischi: precedenza (servono le parentesi) e side effect ripetuti (`QUADRATO(i++)` incrementa due volte). Vedi l'espansione con `cc -E file.c`.

**Operatori bit a bit** (`&`, `|`, `^`, `~`, `<<`, `>>`, che lavorano sui singoli bit): nelle fonti di questo blocco il prof non li tratta. Dice solo che `&` singola "è un'altra cosa, lo vedremo più avanti". Per questo qui non ci sono esercizi su di loro.

**Imprecisioni e contraddizioni nelle fonti.**
- **Postfisso "alla fine dell'istruzione"**: la trascrizione 2.2 dice che `b++` "viene eseguito alla fine della istruzione". Gli Appunti (§1.15.1) dicono "produce prima il valore corrente e solo successivamente applica l'incremento". Conta la seconda: il *valore* usato è quello vecchio; *quando* esattamente avviene la scrittura non è fissato, basta che sia prima dell'istruzione successiva. Per questo `i = i++ + 1` è indefinito.
- **Intervallo degli interi**: la trascrizione dice "da 2 alla n−1 a 2 alla n−1 −1". Manca un meno: è da **−**2^(n−1) a 2^(n−1) − 1.
- **Esempi di macro**: la trascrizione usa `lunghezza 20` e `differenza 3-2`, gli Appunti `LARGHEZZA 20` e `SOMMA 3+2`. È lo stesso concetto con nomi diversi (qui usiamo quelli della trascrizione).
- **"Una macro è una costante simbolica"** (Appunti §1.5.1): è vero solo per le macro senza parametri. Le macro con parametri arrivano nella lezione 3.2 e qui le anticipiamo.
- **Conversioni "indefinite"**: gli Appunti (§1.16.1) dicono che assegnare un intero troppo grande a un tipo più piccolo "può diventare indefinito". Per precisione: verso un tipo con segno il risultato dipende dal compilatore (*implementation-defined*), verso un `unsigned` è definito (riparte da 0). È UB solo da reale a intero quando il valore non ci sta.
- **Divisione con negativi**: gli Appunti parlano di "troncare la parte decimale". In C89 (lo standard citato dagli Appunti) il verso dell'arrotondamento con i negativi dipendeva dal compilatore; dal C99 in poi (e quindi con il nostro `-std=c11`) è sempre verso lo zero.
- **Dimensioni**: la dispensa 2.2.2 dà `int` = 16 bit e `double` = 32 bit. Sulle macchine di oggi sono 32 e 64 bit (vedi es01).

### Errori tipici
1. **Divisione intera inattesa**: `double m = (a + b) / 2;` → nessun avviso, risultato troncato. Rimedio: `2.0` oppure un cast *prima* della divisione.
2. **`%` con un reale** → errore. clang: `error: invalid operands to binary expression ('double' and 'int')`; gcc: `invalid operands to binary % (have 'double' and 'int')`.
3. **`=` o `;` dentro una `#define`** (`#define N = 10;`) → l'errore appare dove la macro è *usata*. clang: `error: expected expression` con la nota `expanded from macro 'N'`.
4. **Overflow e valori troppo grandi** → `int a = 2147483647 + 1;` dà `warning: overflow in expression; result is -2147483648 with type 'int' [-Winteger-overflow]`; `char c = 300;` dà `implicit conversion from 'int' to 'char' changes value from 300 to 44`. Il compilatore se ne accorge solo con le costanti; con valori letti da scanf no.
5. **Segnaposto sbagliato**: `printf("%d", m)` con `m` double → `warning: format specifies type 'int' but the argument has type 'double'` (e stampa un numero senza senso).
6. **Confronto tra con segno e senza segno**: `int a = -1; unsigned b = 1; a < b` è **falso**, perché `a` viene convertito in unsigned (diventa 4294967295). Avviso (con `-Wextra`): `comparison of integers of different signs: 'int' and 'unsigned int' [-Wsign-compare]`. Doppia modifica: `i = i++ + 1;` → clang `multiple unsequenced modifications to 'i'`.

## Esercizi

### es01 — sizeof e limiti dei tipi  ·  Base
**Fonte:** Ispirato a: Appunti Unità 2, §2.19 "Operatore sizeof" e §1.7.4 (interi con e senza segno); Dispensa 2.2.2 "Limiti" (`INT_MAX` in `limits.h`); trascrizione 2.2 (intervallo con n bit).
**Testo:** sostituisci gli `0` nel `main` con il `sizeof` giusto, completa `bit_da_byte` e `massimo_con_segno(bit)` = 2^(bit−1) − 1 calcolato con un ciclo. Nessun input.
```text
char    1 byte =  8 bit
...
max con segno a 32 bit: 2147483647 (INT_MAX   = 2147483647)
```
I valori attesi valgono su macOS (Apple Silicon) e Linux a 64 bit: `sizeof(int)` = 4, `sizeof(long)` = 8.
**File:** `es01_sizeof_limiti.c` · **Test:** `make test T=02 E=es01`

<details><summary>💡 Suggerimento</summary>
Per la potenza parti da 1 e raddoppia (bit − 1) volte. Usa <code>long long</code> (almeno 64 bit): 2^31 non ci sta in un <code>int</code>.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. `sizeof(char)` … `sizeof(double)`: il compilatore conosce le dimensioni e le scrive al posto dell'operatore. `sizeof(char)` è 1 per definizione.
2. `bit_da_byte`: `byte * CHAR_BIT`. `CHAR_BIT` (in `limits.h`) vale 8: meglio della costante "magica" 8, perché dice cosa significa.
3. `massimo_con_segno`: con n bit, uno serve per il segno, quindi restano n − 1 bit per il valore: massimo 2^(n−1) − 1 (il −1 perché tra i positivi c'è anche lo 0).
```c
long long potenza = 1;
int i = 1;
while (i < bit) { potenza = potenza * 2; i = i + 1; }
return potenza - 1;
```
4. **Perché `long long`?** Per bit = 32 la potenza arriva a 2^31 = 2147483648, che supera `INT_MAX` di 1: con un `int` andrebbe in overflow (UB).

| bit | potenza finale | risultato |
|---|---|---|
| 8 | 128 | 127 |
| 16 | 32768 | 32767 |
| 32 | 2147483648 | 2147483647 |

Codice: `soluzioni/es01_sizeof_limiti.c`.
</details>

### es02 — Cambio in monete con / e %  ·  Base
**Fonte:** Ispirato a: Trascrizione 2.1 e Appunti §1.11.1 (divisione intera, `%` solo tra interi); trascrizione 2.2 (promozione int → double).
**Testo:** dato un importo in centesimi, stampa il valore in euro e quante monete di ogni taglio servono (dalla più grande). Completa `in_euro`, `quante`, `avanzo`. Importo negativo → `Importo non valido`.
```text
input:  388
output: 388 centesimi = 3.88 euro
        2 euro: 1
        1 euro: 1
        ... (una moneta per ogni taglio)
        Resto non cambiato: 0
```
**File:** `es02_monete.c` · **Test:** `make test T=02 E=es02`

<details><summary>💡 Suggerimento</summary>
"Quante monete da 50 stanno in 88?" è una divisione intera. "Quanto resta?" è il resto. Per gli euro serve invece una divisione reale.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. `quante`: `importo / taglio`. Qui il troncamento della divisione intera è proprio quello che vuoi: 88 / 50 = 1 moneta.
2. `avanzo`: `importo % taglio` = 88 % 50 = 38 centesimi ancora da cambiare.
3. `in_euro`: `centesimi / 100` sarebbe intera (388 / 100 = 3 → 3.00). Con `centesimi / 100.0` l'`int` viene promosso a `double`: 3.88.
4. Il `main` passa il resto da un taglio all'altro: 388 → (200) 188 → (100) 88 → (50) 38 → (20) 18 → (10) 8 → (5) 3 → (2) 1 → (1) 0.

Caso limite `0`: tutte le divisioni danno 0 e i resti 0. Codice: `soluzioni/es02_monete.c`.
</details>

### es03 — Cifrario di Cesare su un carattere  ·  Base
**Fonte:** Ispirato a: Dispensa 2.2.2 "Operazioni sui caratteri" (`printf("%c %d", 'A' + 1, 'B')`), trascrizione 2.2 (char = numero interpretato con la tabella ASCII), Appunti §1.7.6.
**Testo:** completa `cifra(c, k)`: se `c` è una minuscola, la sposta di `k` posizioni nell'alfabeto ricominciando dopo la `z` (k può essere negativo o > 26); altrimenti la restituisce invariata.
```text
input:  z 1          input:  a -1
output: z + 1 -> a   output: a + -1 -> z
        codici ASCII: 122 -> 97
```
**File:** `es03_cifrario_cesare.c` · **Test:** `make test T=02 E=es03`

<details><summary>💡 Suggerimento</summary>
Trasforma la lettera in un numero da 0 a 25 (<code>c - 'a'</code>), lavora lì con <code>% 26</code>, poi torna a lettera. Prova a mano quanto fa <code>-1 % 26</code> in C.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Filtro**: `if (c < 'a' || c > 'z') return c;`. Le lettere minuscole hanno codici consecutivi (97…122), quindi si confrontano come numeri.
2. **Posizione**: `pos = c - 'a'`. Il `char` viene promosso a `int`: `'z' - 'a'` = 25.
3. **Spostamento circolare**: `pos = (pos + k) % 26`. Il resto "riavvolge" come un orologio: 25 + 1 = 26 → 0.
4. **Il tranello dei negativi**: in C `-1 % 26` vale **−1**, non 25, perché la divisione tronca verso lo zero. Quindi: `if (pos < 0) pos = pos + 26;`.
5. **Ritorno**: `(char)('a' + pos)`. `'a' + pos` è un `int`; il cast dice esplicitamente "lo voglio come char".

| input | pos | pos + k | % 26 | corretto | lettera |
|---|---|---|---|---|---|
| a 3 | 0 | 3 | 3 | 3 | d |
| z 1 | 25 | 26 | 0 | 0 | a |
| a −1 | 0 | −1 | −1 | 25 | z |
| x 55 | 23 | 78 | 0 | 0 | a |

La seconda riga dell'output mostra lo stesso valore letto come numero (`%d`): un `char` è un numero. Codice: `soluzioni/es03_cifrario_cesare.c`.
</details>

### es04 — Cosa stampa? ++/--, precedenza, cast, cortocircuito  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 2.2 (esempi `a = ++b` / `a = b++`, `a += i * j`, cast `(double) a / b`, cortocircuito `1 || (a+b)`), Appunti §1.11.2, §1.11.4, §1.14–1.16.
**Testo:** senza eseguirlo, scrivi qui l'output di `es04_cosa_stampa_operatori.c`. Poi esegui il test.
```text
La mia previsione:
1) ...
```
**File:** `es04_cosa_stampa_operatori.c` · **Test:** `make test T=02 E=es04` (passa già)

<details><summary>💡 Suggerimento</summary>
Per ogni riga chiediti: il ++ è prima o dopo? Di che tipo sono gli operandi della divisione? Quale operatore ha la precedenza? La parte destra di && / || viene valutata davvero?
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

```text
1) a = 8, b = 2, c = 9
2) c = 10
3) c = 2
4) r = 3.00
5) r = 3.00
6) r = 3.50
7) -3 -1
8) c = 1, j = 1
9) c = 0, j = 1
10) c = 1, j = 2
11) c = 15
12) c = 13
```
1. `c = a++ + --b`: `a++` vale 7 (vecchio), poi `a` diventa 8; `--b` porta `b` a 2 e vale 2 (nuovo). c = 7 + 2 = 9.
2. `a + b * 3 % 4`: `*` e `%` hanno la stessa precedenza e si associano da sinistra: `(2 * 3) % 4` = 2; poi 8 + 2 = 10.
3. `(a + b) * 3 % 4` = `(10 * 3) % 4` = 30 % 4 = 2.
4. `p / q` = 7 / 2 tra interi = 3, poi convertito in 3.0.
5. `(double)(p / q)`: le parentesi fanno prima la divisione intera (3), il cast arriva dopo: 3.00.
6. `(double)p / q`: il cast ha alta priorità e si applica solo a `p`. 7.0 / 2 → `q` promosso → 3.5.
7. Troncamento verso lo zero: −7 / 2 = −3 (non −4); −7 % 2 = −1. Controllo: (−3) · 2 + (−1) = −7.
8. `(i > 0)` è 1 → con `||` il risultato è già certo: `j++` **non** viene eseguito. j resta 1.
9. `(i < 0)` è 0 → con `&&` il risultato è già 0: `j++` saltato di nuovo.
10. `(i < 0)` è 0 → con `||` serve la parte destra: `j++ > 0` usa il vecchio j (1 > 0, vero) e poi j diventa 2. c = 1.
11. `c -= 2 + 3` → `c = 10 - (5)` = 5; `c *= 2 + 1` → `c = 5 * (3)` = 15, non 5 · 2 + 1 = 11.
12. `(7 > 2)` vale 1: un confronto è un numero. 3 + 1 · 10 = 13.
</details>

### es05 — Cosa stampa? Macro con e senza parentesi  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 2.2 (`#define lunghezza 20`, `#define differenza 3-2`), Appunti §1.5.1 (`SOMMA 3+2` → `5 * 3 + 2`), Trascrizione 3.2 (`moltiplica(a - c, b)` → `a - c * b`).
**Testo:** espandi a mano ogni macro (scrivi il testo che il preprocessore mette al suo posto), poi calcola. Scrivi qui la previsione, poi esegui il test.
```text
La mia previsione:
1) ...
```
**File:** `es05_cosa_stampa_macro.c` · **Test:** `make test T=02 E=es05` (passa già)

<details><summary>💡 Suggerimento</summary>
Non calcolare il valore della macro prima di sostituirla: copia il testo così com'è, parentesi comprese (o assenti). Solo dopo applica le precedenze.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Ecco cosa produce il preprocessore (`cc -E es05_cosa_stampa_macro.c`) e il risultato, con x = 4 e y = 3:

| # | espansione | calcolo | stampa |
|---|---|---|---|
| 1 | `20 * 2` | | 40 |
| 2 | `10 * 3-2` | (10 · 3) − 2 | **28** (non 10) |
| 3 | `10 * (3-2)` | | 10 |
| 4 | `x - 1 * y` | 4 − (1 · 3) | **1** (non 9) |
| 5 | `((x - 1) * (y))` | 3 · 3 | 9 |
| 6 | `x + 6 / 2` | 4 + 3 | **7** (non 5) |
| 7 | `100 / (5) * (5)` | (100 / 5) · 5 | **100** (non 4) |
| 8 | `100 / ((5) * (5))` | 100 / 25 | 4 |
| 9 | `y * y - 3-2` | 9 − 3 − 2 | **4** (non 8) |

1. Righe 2 e 9: `3-2` senza parentesi si "scioglie" nell'espressione intorno.
2. Riga 4: mancano le parentesi **sui parametri**: `a` diventa il testo `x - 1`, e `*` lega solo l'`1`.
3. Riga 7: le parentesi sui parametri ci sono, ma manca quella **esterna**: `/` e `*` si associano da sinistra, quindi si divide solo per il primo `(5)`.
4. Regola pratica (Appunti §1.5.1 e lezione 3.2): parentesi attorno a ogni parametro **e** attorno all'intera definizione. Anche così resta un pericolo: `QUADRATO_OK(i++)` diventa `((i++) * (i++))`, due modifiche nella stessa espressione → UB. Con le macro, passa solo variabili o valori semplici.
</details>

### es06 — Trova e correggi l'errore: media di tre voti  ·  Intermedio
**Fonte:** Ispirato a: Appunti §1.5.1 (macro senza parentesi), §1.11.3 (`&&` e `||`), §1.11.5 (risultati logici come numeri); Trascrizione 2.1 (divisione intera).
**Testo:** il programma legge tre voti (0–30); deve stampare `Voto non valido` se uno è fuori intervallo, altrimenti media (2 decimali) e quanti voti sono ≥ 18. Ci sono **3 errori**: uno nella macro, uno nella funzione, uno nel conteggio.
```text
input:  30 25 18      input:  24 18 31
output: Media = 24.33          output: Voto non valido
        Sufficienti: 3 su 3
```
**File:** `es06_trova_errore_voti.c` · **Test:** `make test T=02 E=es06`

<details><summary>💡 Suggerimento</summary>
Espandi a mano <code>MEDIA(v1 + v2 + v3, NUM_VOTI)</code>. Prova la funzione di validità con 31: deve dire "non valido". Rileggi i tre confronti con <code>SOGLIA</code>: sono tutti uguali?
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Macro**: `MEDIA(v1 + v2 + v3, NUM_VOTI)` si espande in `v1 + v2 + v3 / 3`: si divide solo `v3`! In più è una divisione tra interi. Con 30 25 18 esce 30 + 25 + 6 = 61.00. Correzione: `#define MEDIA(somma, n) ((double)(somma) / (n))`. Le parentesi su `somma` fanno sommare tutto prima; il cast rende la divisione reale.
2. **Validità**: `v >= 0 || v <= 30` è vero per **qualsiasi** numero (31 è ≥ 0; −1 è ≤ 30). "Tra 0 e 30" vuol dire *entrambe* le condizioni: `v >= 0 && v <= 30`. clang lo segnala: `overlapping comparisons always evaluate to true`.
3. **Conteggio**: per `v3` c'era `> SOGLIA`, quindi un 18 non contava (30 25 18 → 2 invece di 3). Con `>=` tutti e tre i confronti sono uguali. Il trucco del conteggio è corretto: ogni confronto vale 1 o 0, e la somma conta i veri.

Codice: `soluzioni/es06_trova_errore_voti.c`.
</details>

### es07 — Equazione di secondo grado  ·  Tipo esame
**Fonte:** Ispirato a: l'esempio del prof delle radici dell'equazione di secondo grado (blocco 1), Trascrizione 2.2 (conversioni implicite ed esplicite, cast a double), Appunti §1.16.2 (`(double) a / b`).
**Testo:** legge `a b c` interi e stampa le soluzioni reali di a·x² + b·x + c = 0 con 2 decimali. Completa `calcola_delta`, `soluzione_doppia` (−b / 2a) e `soluzione` ((−b ± √delta) / 2a). Casi: a = 0, delta < 0, delta = 0, delta > 0.
```text
input:  1 -3 2     ->  Delta = 1: x1 = 1.00, x2 = 2.00
input:  4 4 1      ->  Delta = 0: x = -0.50
input:  2 2 5      ->  Delta = -36: nessuna soluzione reale
input:  0 2 1      ->  Non e' di secondo grado
```
**File:** `es07_secondo_grado.c` · **Test:** `make test T=02 E=es07`

<details><summary>💡 Suggerimento</summary>
<code>-b / (2 * a)</code> con a = 4 e b = 4 fa 0, non −0.5: chiediti perché. La funzione <code>sqrt</code> (in <code>&lt;math.h&gt;</code>) prende e restituisce un <code>double</code>.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **delta** può restare intero: `b * b - 4 * a * c` (prima le moltiplicazioni, poi la sottrazione). Con coefficienti piccoli non c'è overflow.
2. **a = 0** va escluso *prima*: si dividerebbe per 2a = 0. Lo fa già il `main`.
3. **Soluzione doppia**: `-b / (2 * a)` è tutta tra `int`: −4 / 8 = 0 (troncato). Scrivendo `2.0 * a` il denominatore diventa `double` e la divisione è reale: −0.5.
4. **Due soluzioni**: `(-b + segno * sqrt((double)delta)) / (2.0 * a)`. `sqrt` restituisce un `double`, quindi il numeratore è già reale; il cast `(double)delta` rende esplicita una conversione che avverrebbe comunque.
5. **Linker**: `sqrt` sta nella *libreria matematica*. Su Linux va collegata con `-lm` (il runner lo fa già); su macOS non serve.

Simulazione `2 -1 -1`: delta = 1 − 4 · 2 · (−1) = 9, √9 = 3; x1 = (1 − 3) / 4 = −0.50; x2 = (1 + 3) / 4 = 1.00. Codice: `soluzioni/es07_secondo_grado.c`.
</details>

### es08 — Scontrino con sconto e IVA  ·  Tipo esame
**Fonte:** Ispirato a: Trascrizione 2.2 (macro come parametri del programma: "se voglio cambiarli li cambio in un punto"; cortocircuito), Trascrizione 3.2 (macro con parametri e parentesi), Appunti §1.16 (cast e troncamento), §1.19 (overflow).
**Testo:** legge prezzo in centesimi, quantità e sconto %. Stampa imponibile, sconto, netto, IVA 22% e totale, arrotondando al centesimo. Completa la macro `ARROTONDA(x)`, `percentuale(cent, perc)` e `ordine_valido(...)`, che deve rifiutare quantità ≤ 0, prezzo ≤ 0, sconto fuori da 0–100 e imponibile oltre `MAX_IMPORTO` (senza causare overflow né divisioni per zero).
```text
input:  1999 3 10
output: Imponibile: 59.97 euro
        Sconto 10%: -6.00 euro
        Netto: 53.97 euro
        IVA 22%: 11.87 euro
        Totale: 65.84 euro

input:  500 0 0   ->  Ordine non valido
```
**File:** `es08_scontrino_macro.c` · **Test:** `make test T=02 E=es08`

<details><summary>💡 Suggerimento</summary>
Arrotondare un numero ≥ 0 = aggiungere 0.5 e troncare con un cast a <code>int</code>. Per il limite, invece di <code>prezzo * quantita &lt;= MAX</code> confronta <code>prezzo &lt;= MAX / quantita</code>, e metti il controllo <code>quantita &gt; 0</code> PRIMA, sfruttando il cortocircuito di <code>&amp;&amp;</code>.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché i centesimi interi?** I `double` approssimano: 0.1 non ha una rappresentazione binaria esatta. Con gli interi i conti sui soldi sono esatti; si passa ai reali solo per la percentuale.
2. **Macro**: `#define ARROTONDA(x) ((int)((x) + 0.5))`. Parentesi su `x` perché le passeremo un'espressione intera (`cent * perc / 100.0`); parentesi esterne perché la macro può finire dentro un'espressione più grande. 599.7 + 0.5 = 600.2 → 600; 1187.34 + 0.5 = 1187.84 → 1187.
3. **`percentuale`**: `ARROTONDA(cent * perc / 100.0)`. Con `/ 100` intera, 599.7 diventerebbe 599 *prima* di arrotondare.
4. **`ordine_valido`**: `quantita > 0 && prezzo > 0 && prezzo <= MAX_IMPORTO / quantita && sconto >= 0 && sconto <= 100`. Grazie al cortocircuito, se `quantita` è 0 ci si ferma subito e `MAX_IMPORTO / 0` non viene mai calcolato. Si confronta con una divisione perché `prezzo * quantita` potrebbe già andare in overflow (UB per gli `int`): 99999999 · 2 non supera `INT_MAX`, ma con quantità più grandi sì.
5. **Stampa in euro**: `cent / 100` = parte intera, `cent % 100` = centesimi, `%02d` stampa sempre due cifre (5 → `05`).

| voce | calcolo | centesimi |
|---|---|---|
| imponibile | 1999 · 3 | 5997 |
| sconto | 5997 · 10 / 100.0 = 599.7 → | 600 |
| netto | 5997 − 600 | 5397 |
| IVA | 5397 · 22 / 100.0 = 1187.34 → | 1187 |
| totale | 5397 + 1187 | 6584 |

Codice: `soluzioni/es08_scontrino_macro.c`.
</details>

## Prompt pronti per questo argomento
1. "Interrogami con 6 domande, una alla volta, su: divisione intera vs reale, posizione del cast, ++ prefisso e postfisso, cortocircuito di && e ||, precedenza. Per ogni domanda dammi un'espressione C e chiedimi il valore; correggimi spiegando il perché."
2. "Scrivimi 5 macro `#define` 'trappola' (senza parentesi o con side effect) e per ognuna un'istruzione che le usa. Chiedimi l'espansione del preprocessore e il valore, uno alla volta."
3. "Ho scritto questa soluzione per es08 di 02-tipi-operatori-macro: [incolla codice]. Dimmi se è corretta e perché, se ci sono rischi di overflow, divisione per zero o arrotondamento sbagliato, senza riscrivermela tutta."
4. "Generami 3 esercizi nuovi tipo es07 di 02-tipi-operatori-macro, dove il tranello sia una divisione intera o un cast nel posto sbagliato. Dammi input/output attesi ma non le soluzioni."
5. "Spiegami con un esempio a 8 bit perché `int a = -1; unsigned b = 1; a < b` è falso in C, e cosa vuol dire che l'overflow degli int con segno è comportamento indefinito."

## Riepilogo
- Il tipo decide spazio, valori e operazione: `/` tra interi tronca, `%` esiste solo tra interi, e il cast va messo **prima** dell'operazione che vuoi cambiare.
- `++x` dà il valore nuovo, `x++` quello vecchio; `&&` e `||` si fermano appena il risultato è certo, e saltano gli effetti della parte non valutata.
- Precedenza e associatività decidono l'ordine (`* / %` prima di `+ -`, poi i confronti, poi `&&`, `||`, `=`); nel dubbio servono le parentesi.
- `#define` è sostituzione di testo: le macro vogliono parentesi su ogni parametro e attorno a tutto, e niente argomenti con side effect.

## Glossario
- **tipo** — insieme dei valori, codifica binaria, spazio occupato e operazioni ammesse per un dato.
- **bit / byte** — una cifra binaria / un gruppo di 8 bit.
- **sizeof** — operatore che dà i byte occupati da un tipo o da un'espressione (risultato `size_t`).
- **size_t** — tipo intero senza segno usato per le dimensioni; si stampa con `%zu`.
- **unsigned** — versione senza segno di un tipo intero: solo valori ≥ 0, intervallo doppio verso l'alto.
- **letterale** — valore scritto direttamente nel codice (`5`, `1.4f`, `'A'`).
- **ASCII** — tabella che associa un numero a ogni carattere (`'A'` = 65, `'a'` = 97).
- **overflow** — risultato troppo grande per il tipo; per gli `int` con segno è comportamento indefinito.
- **UB (undefined behavior, comportamento indefinito)** — situazione in cui lo standard C non garantisce nulla sul risultato.
- **implementation-defined** — comportamento che dipende dal compilatore, ma che il compilatore deve documentare.
- **divisione intera** — `/` tra interi: tronca verso lo zero.
- **modulo (`%`)** — resto della divisione intera; con dividendo negativo è negativo.
- **promozione (conversione implicita)** — conversione automatica verso un tipo più capiente in un'operazione mista.
- **cast (conversione esplicita)** — `(tipo) espressione`: forza la conversione; si applica solo all'operando che segue.
- **operatore unario** — operatore con un solo operando (`-x`, `!x`, `++x`, cast).
- **side effect (effetto collaterale)** — modifica dello stato (es. di una variabile) prodotta da un'espressione.
- **assegnamento composto** — `+=`, `-=`, `*=`, `/=`: `a op= b` equivale a `a = a op (b)`.
- **prefisso / postfisso** — `++x` restituisce il valore nuovo; `x++` restituisce il vecchio e poi incrementa.
- **operatore relazionale** — `< > <= >= == !=`: dà 1 (vero) o 0 (falso).
- **operatore logico** — `!` (NOT), `&&` (AND), `||` (OR).
- **cortocircuito (short-circuit)** — `&&`/`||` smettono di valutare appena il risultato è certo.
- **precedenza** — regola che dice quale operatore si applica prima.
- **associatività** — regola per operatori con la stessa precedenza (da sinistra o da destra).
- **preprocessore** — fase prima della compilazione che esegue le direttive `#` (include, define).
- **macro** — nome definito con `#define` che il preprocessore sostituisce con un testo; può avere parametri.
- **macro-espansione** — la sostituzione del testo della macro al posto del suo uso.
- **libreria matematica** — libreria con `sqrt`, `pow`…; su Linux si collega con `-lm`.
