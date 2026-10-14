# 10 — Strutture e union

> Lezioni di riferimento: trascrizione 3.5 (Strutture dati e Union), Appunti Unità 3 (cap. 5 "Strutture e Union", par. 5.1–5.11, e par. 6.10 "Passaggio di strutture"), LEZ 17.
> Tempo stimato: ~4 ore.

## Teoria flash

**Perché servono.** Un vettore raccoglie tanti dati *dello stesso tipo*. Spesso però un "oggetto" è fatto di dati *diversi*: uno studente ha un cognome (stringa), una matricola (intero) e dei voti (vettore). Una **struttura** (`struct`, in teoria detta anche **record**) li raggruppa sotto un solo nome. Pensala come una scheda anagrafica con più caselle. Le caselle si chiamano **campi** o **membri**. Se conosci Java/TypeScript: è come una classe con soli attributi pubblici, senza metodi.

**Tre modi di dichiararla** (tutti e tre nelle fonti):
```c
struct datiMeteo {            /* 1) con TAG (nome della struttura): */
    double temperatura;       /*    poi si dichiara "struct datiMeteo oggi;" */
    double pressione;
};

struct { int id; int eta; } persona;   /* 2) anonima: definisce subito la variabile */

typedef struct {              /* 3) con typedef: crea un NUOVO NOME DI TIPO */
    double x, y;
} Punto;                      /*    poi basta "Punto p;" (senza la parola struct) */
```
Il `;` dopo la graffa chiusa è obbligatorio. Il **tipo** da solo non occupa memoria: è uno stampo. La memoria la occupano le **variabili** di quel tipo.

**Accesso ai campi: l'operatore punto.** `p.x` = "il campo x della struttura p". Un campo si usa come una variabile normale: si legge, si assegna, gli si passa l'indirizzo (`scanf("%lf", &p.x)`, perché il punto lega più forte di `&`). I nomi dei campi sono *locali* alla struttura: `persona.id` e `luogo.id` possono convivere.

**Inizializzazione.** Tra graffe, nell'ordine dei campi: `Esame a = {"PA1", 30};`. Oppure per nome, con l'**inizializzatore designato** di C99/C11: `Magazzino m = { .n = 0 };`. I campi non nominati valgono 0.

**Strutture annidate e vettori di strutture** (Appunti par. 5.6–5.7):
```c
typedef struct { char nome[20]; char cognome[20]; } Persona;
typedef struct { long matricola; Persona identita; } Studente;
Studente classe[100];
classe[12].identita.nome     /* vettore → indice → campo → campo */
```

**Assegnamento.** `oggi = ieri;` copia *tutti* i campi, **compresi i vettori** dentro la struttura (una cosa che con due vettori "nudi" non puoi fare). Se un campo è un **puntatore**, però, si copia solo l'indirizzo: le due strutture finiscono per puntare *alla stessa* memoria (esempio del *nickname* del prof). Questa si chiama **copia superficiale**. Non si possono invece confrontare due strutture con `==`: va fatto campo per campo.

**Strutture e funzioni.** Una struttura passata a una funzione viene **copiata** (passaggio per valore): la funzione lavora su una copia e le modifiche si perdono al `return`. Per modificare l'originale, o per evitare di copiare strutture grandi, si passa il suo **indirizzo**. Con un puntatore a struttura si usa l'operatore **freccia** `->`:
```c
void azzera(Orario *o) {
    o->ore = 0;        /* identico a (*o).ore = 0;  le parentesi servono perché */
    o->minuti = 0;     /* il punto lega più forte di *: *o.ore vorrebbe dire *(o.ore) */
}
azzera(&t);
```
Regola pratica: a sinistra c'è una struttura → **punto**; a sinistra c'è un puntatore a struttura → **freccia**. Se la funzione deve solo leggere, scrivi `const Orario *o`.

**Union.** Si scrive come una struct, ma tutti i campi **condividono la stessa memoria**, a partire dallo stesso indirizzo. Quindi la union è grande quanto il campo più grande (più un eventuale arrotondamento, vedi sotto) e contiene *un solo valore alla volta*: scrivere un campo sovrascrive gli altri. Analogia: una sola lavagna su cui scrivi o un numero o una parola, non entrambi.
```c
union Valore { int i; double d; char c[8]; };   /* sizeof = 8, non 4+8+8 */
```
Serve a risparmiare memoria quando un dato può avere *uno* tra più tipi. Ma la union da sola non "sa" quale campo è valido. Per questo si usa la **union etichettata**: una struct con un campo **etichetta** (di solito un `enum`, cioè un tipo con valori dai nomi leggibili come `INTERO`, `REALE`, `TESTO`) e la union. Chi scrive aggiorna anche l'etichetta; chi legge controlla prima l'etichetta (con uno `switch`) e poi legge solo il campo giusto.

**Padding (spazio di riempimento).** Su questi processori un `int` deve iniziare a un indirizzo multiplo di 4 e un `double` a un multiplo di 8 (**allineamento**). Per rispettarlo il compilatore può inserire byte vuoti tra i campi e in fondo. Per questo `struct { char c; int n; }` occupa 8 byte e non 5. Non è nelle fonti del corso, ma serve per capire i `sizeof`.

> Assunzioni di questa cartella (vere su macOS arm64 e Linux x86-64): `sizeof(int)` = 4, `sizeof(long)` = 8, `sizeof(double)` = 8, puntatori da 8 byte, `enum` grande come un `int`. Entrambi i sistemi sono **little-endian** (il byte meno significativo di un numero sta all'indirizzo più basso). Gli esercizi però usano valori scelti apposta per non dipendere da questo.

### Contraddizioni e imprecisioni nelle fonti
- **Dimensione della union.** Appunti (par. 5.9) e trascrizione dicono "pari alla dimensione del campo più grande". È vero *quasi* sempre. Per l'allineamento la union può essere più grande: `union { char s[12]; double d; }` occupa 16 byte, non 12 (12 non è multiplo di 8). Lo vedi nell'es07.
- **Il libro nella union.** Nella trascrizione il prof dice che dopo `prezzo = 250` il titolo "viene in parte sovrascritto" e si stampano "caratteri sbagliati". Più precisamente, su un computer little-endian i primi 4 byte del titolo diventano `250, 0, 0, 0`: `printf("%s")` stampa *un solo* carattere strano (il codice 250) e si ferma subito al byte 0. Il resto del titolo è ancora in memoria, ma invisibile.
- **Leggere un campo diverso dall'ultimo scritto.** Gli Appunti dicono che il vecchio campo "non è più valido". In C11 la lettura è permessa: rilegge gli stessi byte con un altro tipo, e il risultato dipende da come la macchina rappresenta i dati. Per questo serve l'etichetta. (In C++ invece è vietato.)
- **Operatore `->` e union etichettata.** Non compaiono né nella trascrizione 3.5 né nel cap. 5 degli Appunti. Gli Appunti (par. 6.10) consigliano di passare "l'indirizzo della struttura" senza mostrare la sintassi. Li trovi nella LEZ 17 e qui sopra.
- **Errori di trascrizione:** "l'Extract" / "Extract" = `struct`; "type def" = `typedef`; "string copy" = `strcpy`; "union int k e double i" = `union { int k; double i; }`.

### Errori tipici
1. **Punto e virgola dimenticato** dopo la graffa: `struct punto { int x; int y; }` → gcc: `error: expected ';', identifier or '(' before 'int'` (clang, più chiaro: `expected ';' after struct`).
2. **Tag usato senza `struct`**: `punto a;` → gcc: `error: unknown type name 'punto'; use 'struct' keyword to refer to the type`. Soluzione: `struct punto a;` oppure un `typedef`.
3. **Assegnare una stringa a un campo vettore**: `p.nome = "Mario";` → gcc: `error: assignment to expression with array type` (clang: `array type 'char[20]' is not assignable`). Si usa `strcpy(p.nome, "Mario");`.
4. **Punto e freccia scambiati**: `pp.eta` con `pp` puntatore → `error: 'pp' is a pointer; did you mean to use '->'?`. Al contrario, `p->eta` con `p` struttura → `error: invalid type argument of '->' (have 'Persona')`.
5. **Confrontare strutture con `==`**: → `error: invalid operands to binary == (have 'struct punto' and 'struct punto')`. Si confronta campo per campo (per le stringhe con `strcmp`).
6. **Struttura passata per valore "che non cambia"**: compila senza avvisi, ma le modifiche fatte nella funzione si perdono. È l'errore dell'es04 e dell'es06.

## Esercizi

### es01 — Punto 2D e distanza  ·  Base
**Fonte:** Ispirato a: Trascrizione 3.5 e Appunti Unità 3 par. 5.5 (`typedef struct` stile `datiMeteo`), par. 5.4 (operatore punto).
**Testo:** dato `typedef struct { double x; double y; } Punto;`, implementa `double distanza(Punto a, Punto b)`, che restituisce √((bx−ax)² + (by−ay)²). Il `main` legge due punti e stampa la distanza con 2 decimali.
```text
input:   0 0 3 4
output:  P = (0.00, 0.00)
         Q = (3.00, 4.00)
         distanza: 5.00
```
**File:** `es01_punto_distanza.c` · **Test:** `make test T=10 E=es01`

<details><summary>💡 Suggerimento</summary>

Calcola prima `dx = b.x - a.x` e `dy = b.y - a.y`, poi usa `sqrt` di `<math.h>`. Per elevare al quadrato basta `dx * dx`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché una struct?** Un punto *è* una coppia (x, y). Con la struct passi "un punto" alla funzione invece di quattro `double` sparsi, ed è più difficile scambiare per sbaglio una x con una y.
2. **Per valore va bene**: la funzione legge soltanto, e una copia di 16 byte non costa nulla.
3. `b.x - a.x` usa l'operatore punto per prendere i campi. Con `dx * dx` hai il quadrato. Esiste anche `pow(dx, 2)`, ma per un quadrato è inutilmente più lento.
4. `sqrt` sta nella libreria matematica: su Linux va collegata con `-lm` (il runner lo fa già).

```c
double distanza(Punto a, Punto b)
{
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}
```
Verifica a mano con P(−1, −1) e Q(2, 3): dx = 3, dy = 4, √(9 + 16) = 5. Codice completo: `soluzioni/es01_punto_distanza.c`.
</details>

### es02 — Studente con media  ·  Base
**Fonte:** Ispirato a: Appunti Unità 3 par. 5.2 (lo studente con nome, cognome, età, matricola); Trascrizione 3.5 (campi vettore dentro la struttura).
**Testo:** dato il tipo `Studente` (cognome, matricola, vettore `voti[5]`, `nvoti`), implementa `double media(Studente s)`, che restituisce la media dei primi `nvoti` voti (0.0 se non ce ne sono).
```text
input:   Rossi 12345 3
         27 30 25
output:  Rossi (matricola 12345): media 27.33
```
**File:** `es02_studente_media.c` · **Test:** `make test T=10 E=es02`

<details><summary>💡 Suggerimento</summary>

Il voto i-esimo è `s.voti[i]`. Attento alla divisione: tra due `int` è intera.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **`nvoti`**: il vettore ha 5 caselle, ma solo le prime `nvoti` contengono voti veri. Le altre hanno valori casuali (la struct non è inizializzata) e non vanno toccate. È lo schema "vettore + riempimento" della LEZ 11, solo che qui i due pezzi viaggiano insieme nella stessa struttura.
2. **Divisione per zero**: con `nvoti == 0` restituisco subito 0.0.
3. **Divisione intera**: `82 / 3` fa 27, perché tra due `int` il C tronca. Converto prima: `(double)somma / s.nvoti` = 27.333...
4. Lo studente arriva per valore: viene copiato tutto, vettore `voti` compreso (sono circa 50 byte). Qui va bene; per strutture grandi si preferisce `const Studente *`.

```c
double media(Studente s)
{
    int i, somma = 0;
    if (s.nvoti == 0)
        return 0.0;
    for (i = 0; i < s.nvoti; i++)
        somma += s.voti[i];
    return (double)somma / s.nvoti;
}
```
Nel `main`, `scanf("%19s", s.cognome)` non ha `&`: `s.cognome` è un vettore, quindi vale già l'indirizzo del suo primo carattere. Codice completo: `soluzioni/es02_studente_media.c`.
</details>

### es03 — Cosa stampa? struct, union e copie  ·  Base
**Fonte:** Ispirato a: Trascrizione 3.5 (assegnamento campo per campo, esempio del *nickname* condiviso, union che alloca "solo per il tipo più capiente"), Appunti Unità 3 par. 5.8–5.10 e 6.10.
**Testo:** il file è **già completo**. Leggilo e, **prima di eseguirlo**, scrivi la tua previsione per ogni riga numerata (attenzione: c'è anche una riga stampata *dentro* una funzione). Poi lancia il test, che passa già, e confronta con `tests/es03_cosa_stampa_struct_union.out`.
```text
La mia previsione:
1) sizeof(Esame) = ...
2) sizeof(union Valore) = ...
3) sizeof(struct Sbilanciata) = ...
4) a = ..., b = ...
5) p1 = ..., p2 = ...
   (dentro boccia: ...)
6) dopo boccia: ...
7) dopo boccia_davvero: ...
8) u.c[0] = ..., u.c[3] = ...
9) u.i = ...
10) stesso indirizzo? ... ...
11) byte tra &a e &a.voto = ...
```
**File:** `es03_cosa_stampa_struct_union.c` · **Test:** `make test T=10 E=es03`

<details><summary>💡 Suggerimento</summary>

Per ogni assegnamento chiediti: "si copia il *dato* o solo un *indirizzo*?". Per ogni funzione: "riceve la struttura o il suo indirizzo?". Per la union: "tutti i campi partono dallo stesso byte".
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output atteso:
```text
1) sizeof(Esame) = 8
2) sizeof(union Valore) = 8
3) sizeof(struct Sbilanciata) = 8
4) a = PA1 30, b = MAT 18
5) p1 = 1 Teo, p2 = 2 Teo
   (dentro boccia: 0)
6) dopo boccia: 30
7) dopo boccia_davvero: 0
8) u.c[0] = 1, u.c[3] = 1
9) u.i = 0
10) stesso indirizzo? 1 1
11) byte tra &a e &a.voto = 4
```
- **1)** `char sigla[4]` (4 byte) + `int voto` (4 byte). `voto` parte dal byte 4, che è già multiplo di 4: niente padding. Totale 8.
- **2)** Nella union i campi si *sovrappongono*: conta il più grande (`double` e `char[8]`, 8 byte). Non 4 + 8 + 8 = 20.
- **3)** `char c` occupa il byte 0. `int n` deve partire da un multiplo di 4, quindi i byte 1–3 restano vuoti (padding). 1 + 3 + 4 = 8, non 5.
- **4)** `b = a` copia tutto, **anche il vettore** `sigla` (Appunti 5.8). Dopo, `a` e `b` sono indipendenti: cambiare `b` non tocca `a`.
- **5)** La trappola del *nickname* del prof. `Persona` contiene un **puntatore**. `p2 = p1` copia l'indirizzo, non la stringa. Quindi `p2.nickname[0] = 'T'` modifica l'unica stringa `nick`, che è condivisa: anche `p1` vede "Teo". `id` invece è un numero ed è stato copiato: `p2.id = 2` non tocca `p1`.
- **riga "dentro boccia"** e **6)** `boccia(a)` riceve una *copia* di `a`. Dentro, la copia vale 0 (lo stampa); fuori, `a.voto` è ancora 30.
- **7)** `boccia_davvero(&a)` riceve l'**indirizzo** e scrive con `e->voto = 0` nella struttura originale.
- **8)** `u.i = 0x01010101` scrive 4 byte che valgono tutti 1 (in esadecimale ogni coppia di cifre è un byte). `u.c` parte dallo stesso indirizzo, quindi `u.c[0]` … `u.c[3]` sono quei 4 byte. Siccome sono tutti uguali, l'ordine dei byte (endianness) non conta.
- **9)** `u.d = 0.0` scrive 8 byte. Nel formato dei `double` (standard IEEE 754) lo zero è "tutti i bit a 0". `u.i` rilegge i primi 4 di quei byte: 0. Abbiamo appena scritto `d` e letto `i`: ecco perché nella union conta *quale* campo hai scritto per ultimo.
- **10)** Tutti i campi di una union iniziano allo stesso indirizzo: entrambi i confronti valgono 1. Il cast a `void *` (puntatore "generico", senza tipo puntato) serve per poter confrontare puntatori di tipi diversi.
- **11)** In `Esame`, `voto` viene dopo i 4 byte di `sigla`: è a 4 byte dall'inizio. In una struct, a differenza della union, ogni campo ha il suo spazio.
</details>

### es04 — Aggiorna un orario tramite puntatore  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 3 par. 6.10 (passare l'indirizzo della struttura) e 6.2 (passaggio di indirizzi); Trascrizione 3.5 (campi a sinistra degli assegnamenti, priorità del punto in `qui.id++`).
**Testo:** dato `typedef struct { int ore; int minuti; } Orario;`, implementa `void aggiungi_minuti(Orario *o, int m)`. La funzione aggiunge `m` minuti (anche negativi) all'orario puntato, **usando `->`**, e lo riporta tra 00:00 e 23:59, girando oltre la mezzanotte come un orologio. Il `main` chiama prima `aggiungi_per_valore` (già scritta), per mostrarti che non cambia nulla.
```text
input:   23 50 20
output:  per valore:    23:50
         per indirizzo: 00:10
```
**File:** `es04_orario_puntatore.c` · **Test:** `make test T=10 E=es04`

<details><summary>💡 Suggerimento</summary>

Converti tutto in minuti dalla mezzanotte, usa `% 1440` e poi riconverti in ore e minuti. Con i negativi `%` dà un resto negativo: correggilo aggiungendo 1440.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché un puntatore?** `aggiungi_per_valore` riceve una copia: modifica la copia e la butta via. Con `Orario *o` la funzione riceve l'indirizzo della struttura del `main` e può scriverci dentro.
2. **Perché `->`?** `o` è un puntatore, non una struttura: `o.ore` non compila. `o->ore` vuol dire `(*o).ore`, "il campo ore della struttura puntata da o".
3. **Normalizzazione.** Lavorare con ore e minuti separati obbliga a gestire tanti casi (minuti > 59, ore > 23, negativi...). Convertendo in un solo numero di minuti (`totale`) basta il resto della divisione per 1440 (i minuti in un giorno).
4. **Negativi.** In C `-20 % 1440` vale `-20` (il resto ha il segno del dividendo), non 1420. Quindi, se esce negativo, aggiungo 1440.

```c
void aggiungi_minuti(Orario *o, int m)
{
    int totale = o->ore * 60 + o->minuti + m;
    totale %= MINUTI_GIORNO;
    if (totale < 0)
        totale += MINUTI_GIORNO;
    o->ore = totale / 60;
    o->minuti = totale % 60;
}
```
| caso | totale iniziale | dopo `%` | dopo correzione | risultato |
|---|---|---|---|---|
| 23:50 + 20 | 1450 | 10 | 10 | 00:10 |
| 00:10 − 20 | −10 | −10 | 1430 | 23:50 |
| 08:15 − 3000 | −2505 | −1065 | 375 | 06:15 |

Codice completo: `soluzioni/es04_orario_puntatore.c`.
</details>

### es05 — Vettore di studenti e strutture annidate  ·  Intermedio
**Fonte:** Ispirato a: Trascrizione 3.5 e Appunti Unità 3 par. 5.6–5.7 (strutture `persona`/`studente` con campo `identita`, vettore `classe[100]`, accesso `classe[12].matricola`).
**Testo:** con `Persona` (nome, cognome) annidata in `Studente` (matricola, identita, media), implementa:
- `const Studente *migliore(const Studente classe[], int n)`: **puntatore** allo studente con la media più alta (a parità, il primo);
- `int conta_sopra(const Studente classe[], int n, double soglia)`: quanti hanno media ≥ soglia.
```text
input:   4
         1001 Luca Rossi 26.5
         1002 Anna Verdi 29.5
         1003 Marco Neri 24
         1004 Sara Blu 29.5
         27
output:  migliore: Anna Verdi (matricola 1002, media 29.50)
         indice del migliore: 1
         media >= 27.00: 2
```
**File:** `es05_classe_migliore.c` · **Test:** `make test T=10 E=es05`

<details><summary>💡 Suggerimento</summary>

`classe[i]` è una struttura, quindi `classe[i].media`. `best` è un puntatore, quindi `best->media`. Aggiorna con `>` (non `>=`) per tenere il primo a parità.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché restituire un puntatore** e non una copia dello `Studente`? Perché una copia costa (oltre 50 byte) e, soprattutto, il puntatore ti dice *quale* elemento è. Il `main` infatti ricava l'indice con `b - classe` (differenza tra puntatori, cartella 09).
2. **`const`**: la ricerca non modifica la classe; restituisco `const Studente *` perché punta dentro un vettore ricevuto come `const`.
3. **Accesso annidato**: `b->identita.nome` si legge da sinistra: "la struttura puntata da b → il suo campo identita (una Persona) → il campo nome". Freccia perché `b` è un puntatore; punto perché `identita` è una struttura.
4. **Parità**: Anna e Sara hanno 29.5. Con `>`, Sara non supera Anna, quindi resta Anna.

```c
const Studente *migliore(const Studente classe[], int n)
{
    const Studente *best = &classe[0];
    int i;
    for (i = 1; i < n; i++)
        if (classe[i].media > best->media)
            best = &classe[i];
    return best;
}
```
| i | classe[i].media | best->media prima | aggiorno? |
|---|---|---|---|
| 1 | 29.5 | 26.5 | sì → Anna |
| 2 | 24.0 | 29.5 | no |
| 3 | 29.5 | 29.5 | no (non è `>`) |

Codice completo: `soluzioni/es05_classe_migliore.c`.
</details>

### es06 — Trova e correggi l'errore: la rubrica  ·  Intermedio
**Fonte:** Ispirato a: Appunti Unità 3 par. 6.10 (struttura passata per valore = copia); Trascrizione 3.5 (campi stringa riempiti con `strcpy`, come `strcpy(qui.nome, "Milano")`).
**Testo:** la rubrica accetta comandi `A nome telefono` (aggiungi) e `C nome` (cerca) fino alla fine dell'input, poi stampa quanti contatti ci sono. Il codice **compila senza avvisi**, ma ha **due errori**: i contatti aggiunti "spariscono" e la ricerca non trova mai niente. Correggili cambiando il meno possibile.
```text
input:   A mario 3331112222
         A anna 3204445555
         C anna
         C luca
output:  anna: 3204445555
         luca: non trovato
         contatti: 2
```
**File:** `es06_trova_errore_rubrica.c` · **Test:** `make test T=10 E=es06`

<details><summary>💡 Suggerimento</summary>

(1) Che cosa riceve `aggiungi`: la rubrica del `main` o una sua copia? (2) Che cosa confronta `==` tra due vettori di `char`: i caratteri o gli indirizzi?
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

**Errore 1 — rubrica passata per valore.** `int aggiungi(Rubrica r, ...)` riceve una **copia** di tutta la rubrica (50 contatti, oltre 1800 byte copiati a ogni chiamata!). Aggiunge il contatto alla copia e incrementa `r.n` della copia. Al `return` la copia sparisce, quindi nel `main` resta `rub.n == 0`. Correzione: passare l'indirizzo e usare la freccia.
```c
int aggiungi(Rubrica *r, const char *nome, const char *tel)
{
    if (r->n == MAX) return 0;
    strcpy(r->voci[r->n].nome, nome);
    strcpy(r->voci[r->n].telefono, tel);
    r->n++;
    return 1;
}
/* nel main: aggiungi(&rub, nome, tel) */
```
**Errore 2 — stringhe confrontate con `==`.** `r->voci[i].nome == nome` confronta due **indirizzi**: quello del vettore dentro la rubrica e quello del vettore `nome` del `main`. Sono due zone di memoria diverse, quindi il confronto è sempre falso, anche se contengono le stesse lettere. Per confrontare il *contenuto* serve `strcmp`, che restituisce 0 quando le stringhe sono uguali:
```c
if (strcmp(r->voci[i].nome, nome) == 0)
```
Il compilatore non avvisa, perché confrontare due puntatori a `char` è un'operazione lecita: è solo quella sbagliata per questo scopo. Con l'Errore 1 corretto ma non il 2, il test mostra `contatti: 3` e tutti `non trovato`. Correggendo entrambi passa. Codice completo: `soluzioni/es06_trova_errore_rubrica.c`.
</details>

### es07 — Misure dei sensori con una union etichettata  ·  Tipo esame
**Fonte:** Ispirato a: Trascrizione 3.5 (union: "una variabile può assumere uno dei tipi e uno solo in un certo istante", "deve avere senso la cosa"), Appunti Unità 3 par. 5.11 ("il programmatore deve assicurarsi di utilizzare il campo corretto"); enum dalla lezione 2.4.
**Testo:** ogni `Misura` ha il nome del sensore, un'**etichetta** `TipoMisura` (`INTERO`, `REALE`, `TESTO`) e una union `dato` con `conteggio` (int), `valore` (double) o `stato` (stringa). Implementa:
- `int leggi_misura(Misura *m)`: legge `sensore lettera dato` con lettera `I`, `D` o `S`. Imposta etichetta e campo giusto e restituisce 1; restituisce 0 se la lettera è sconosciuta o la lettura fallisce;
- `void stampa_misura(const Misura *m)`: con uno `switch` sull'etichetta;
- `double somma_numeriche(const Misura v[], int n)`: somma conteggi e valori, ignora i testi.
```text
input:   4
         porta I 42
         temp D 21.5
         luce S acceso
         umid D -0.25
output:  porta: 42 (intero)
         temp: 21.50 (reale)
         luce: acceso (testo)
         umid: -0.25 (reale)
         totale numerico: 63.25
         byte di una Misura: 32
```
**File:** `es07_misure_union.c` · **Test:** `make test T=10 E=es07`

<details><summary>💡 Suggerimento</summary>

La regola d'oro della union etichettata: **chi scrive** un campo imposta anche l'etichetta; **chi legge** guarda prima l'etichetta. Per arrivare al dato scendi di due livelli: `m->dato.conteggio`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché una union?** Una misura è *o* un numero intero, *o* un reale, *o* uno stato, mai due insieme. Con una struct sprecheresti spazio per tutti e tre i campi. Con la union lo spazio è uno solo.
2. **Perché l'etichetta?** Gli stessi byte possono essere letti come `int`, `double` o testo. Se leggi `dato.valore` dopo aver scritto `dato.stato`, ottieni un numero senza senso. L'`enum` ricorda quale campo è "vivo".
3. **`leggi_misura`**: legge nome e lettera, poi uno `switch` sceglie *insieme* l'etichetta e il formato di `scanf`. `scanf(...) == 1` vale 1 se la lettura del dato è riuscita, 0 altrimenti: è proprio il valore da restituire. Nota `&m->dato.conteggio`: `->` e `.` legano più forte di `&`, quindi è l'indirizzo del campo.
4. **`stampa_misura`**: lo `switch` sull'etichetta legge solo il campo giusto.
5. **`somma_numeriche`**: un `int` sommato a un `double` viene convertito automaticamente.
6. **32 byte?** `sensore` 12 + `tipo` 4 = 16. La union è grande quanto `stato[12]`, ma contiene un `double` e quindi deve essere multiplo di 8: 16 byte (vedi "Contraddizioni"). 16 + 16 = 32.

```c
int leggi_misura(Misura *m)
{
    char t;
    if (scanf("%11s %c", m->sensore, &t) != 2) return 0;
    switch (t) {
    case 'I': m->tipo = INTERO; return scanf("%d", &m->dato.conteggio) == 1;
    case 'D': m->tipo = REALE;  return scanf("%lf", &m->dato.valore) == 1;
    case 'S': m->tipo = TESTO;  return scanf("%11s", m->dato.stato) == 1;
    default:  return 0;
    }
}
```
Con una lettera sconosciuta (test 3: `boh X 1`) il `main` stampa `misura 2 non valida: mi fermo` e lavora sulle misure lette fino a lì. Codice completo: `soluzioni/es07_misure_union.c`.
</details>

### es08 — Gestione magazzino con vettore di struct e menù  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 3 par. 5.7 (strutture e array) e 6.10 (passare l'indirizzo delle strutture grandi); Trascrizione 3.5 (record come "insieme di dati eterogenei che viaggiano insieme"). Struttura a menù tipica degli esercizi d'esame.
**Testo:** `Articolo` ha `codice`, `nome`, `quantita`, `prezzo`. `Magazzino` contiene un vettore di `MAX_ART` (= 4) articoli e il contatore `n`. Implementa:
- `int cerca(const Magazzino *m, int codice)`: indice o −1;
- `int aggiungi(Magazzino *m, int codice, const char *nome, int q, double prezzo)`: se il codice esiste somma `q` e restituisce 1; se è nuovo e c'è posto lo aggiunge in fondo e restituisce 2; se il magazzino è pieno restituisce 0;
- `int preleva(Magazzino *m, int codice, int q)`: 0 se ok, −1 se il codice non esiste, −2 se la quantità non basta (e in quel caso non cambia nulla);
- `double valore_totale(const Magazzino *m)`: somma di quantità × prezzo.

Il menù (già scritto) legge: `1 codice nome q prezzo` · `2 codice q` · `3` (stampa) · `4` (valore) · `0` (esci).
```text
input:   1 101 viti 150 0.10
         1 102 bulloni 40 0.25
         2 101 30
         2 102 100
         4
         0
output:  Comandi: 1=aggiungi 2=preleva 3=stampa 4=valore 0=esci
         aggiunto 101 viti
         aggiunto 102 bulloni
         prelevati 30 di 101: restano 120
         quantita insufficiente per 102 (disponibili 40)
         valore totale: 22.00
         ciao!
```
**File:** `es08_magazzino.c` · **Test:** `make test T=10 E=es08`

<details><summary>💡 Suggerimento</summary>

Scrivi prima `cerca`: `aggiungi` e `preleva` la usano. In `aggiungi`, la prima cella libera è `m->art[m->n]`. Incrementa `m->n` solo dopo averla riempita.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché tutto per indirizzo?** Un `Magazzino` contiene un vettore di strutture: copiarlo a ogni chiamata è uno spreco. Soprattutto, `aggiungi` e `preleva` *devono* modificare quello del `main`. `cerca` e `valore_totale` ricevono `const Magazzino *`: niente copia e niente modifiche.
2. **`cerca`**: ricerca lineare sui primi `m->n` elementi. `m->art[i].codice` si legge: "struttura puntata da m → vettore art → elemento i → campo codice".
3. **`aggiungi`**: prima controllo se l'articolo esiste (così non creo doppioni). Poi controllo lo spazio. Poi riempio la cella `m->art[m->n]`. Il nome si copia con `strcpy`, perché un vettore non si assegna con `=`. Uso un puntatore d'appoggio `Articolo *a = &m->art[m->n];` per scrivere `a->codice` invece di ripetere `m->art[m->n].codice` quattro volte.
4. **`preleva`**: i controlli vengono **prima** della modifica. Così, se la quantità non basta, il magazzino resta com'era.
5. **Codici di ritorno**: la funzione non stampa nulla, restituisce un numero, e il `main` decide il messaggio. Separare "logica" e "dialogo con l'utente" rende le funzioni riutilizzabili e testabili.

```c
int aggiungi(Magazzino *m, int codice, const char *nome, int q, double prezzo)
{
    int i = cerca(m, codice);
    Articolo *a;
    if (i >= 0) { m->art[i].quantita += q; return 1; }
    if (m->n == MAX_ART) return 0;
    a = &m->art[m->n];
    a->codice = codice;
    strcpy(a->nome, nome);
    a->quantita = q;
    a->prezzo = prezzo;
    m->n++;
    return 2;
}
```
I test coprono il magazzino vuoto, l'aggiornamento di un articolo esistente, il magazzino pieno (5° articolo con `MAX_ART` = 4), il prelievo che azzera, il codice inesistente, la scelta non valida e la quantità ≤ 0. Codice completo: `soluzioni/es08_magazzino.c`.
</details>

## Prompt pronti per questo argomento
1. `Interrogami con 6 domande su struct e union in C (typedef, operatore punto e freccia, assegnamento tra strutture, copia superficiale dei puntatori, sizeof della union), una alla volta. Aspetta la mia risposta e correggimi spiegando il perché.`
2. `Disegnami in testo, byte per byte, la memoria di questa struct e di questa union, indicando dove c'è padding: [incolla dichiarazioni]. Assumi macOS arm64 (int 4 byte, double 8, puntatori 8).`
3. `Ho scritto questa soluzione per es08 di 10-strutture-union (magazzino): [incolla codice]. Dimmi se è corretta e perché, segnalami dove copio strutture inutilmente, senza riscrivermela tutta.`
4. `Generami un esercizio d'esame nuovo tipo es08 di 10-strutture-union (vettore di struct + menù + funzioni che ricevono un puntatore alla struttura), con input/output d'esempio e 3 casi limite da testare.`
5. `Dammi 4 mini-programmi "Cosa stampa?" su struct passate per valore vs per indirizzo e su union, con output che non dipende dall'endianness. Non darmi le soluzioni finché non rispondo.`

## Riepilogo
- Una `struct` raggruppa dati di tipo diverso. Si accede ai campi con `.` sulla struttura e con `->` sul puntatore alla struttura (`p->x` è `(*p).x`).
- L'assegnamento tra strutture copia tutto, vettori compresi, ma dei puntatori copia solo l'indirizzo (copia superficiale). Passata a una funzione, una struttura viene copiata: per modificarla o per non sprecare memoria si passa il suo indirizzo.
- In una `union` tutti i campi condividono la stessa memoria: è grande quanto il campo più grande (più l'eventuale allineamento) e contiene un solo valore alla volta.
- La union etichettata (struct con `enum` + union) dice sempre quale campo è valido; si legge con uno `switch` sull'etichetta.

## Glossario
- **struttura (`struct`) / record** — tipo che raggruppa campi di tipo diverso sotto un solo nome.
- **campo / membro** — una delle "caselle" di una struttura o union.
- **tag** — il nome dopo `struct` (`struct punto`); per usarlo serve ripetere `struct`.
- **`typedef`** — crea un nuovo nome per un tipo (`typedef struct {...} Punto;`).
- **operatore punto `.`** — accede a un campo di una struttura o union.
- **operatore freccia `->`** — accede a un campo tramite un puntatore: `p->x` equivale a `(*p).x`.
- **struttura annidata** — struttura che contiene un campo che è a sua volta una struttura.
- **inizializzatore designato** — inizializzazione per nome di campo: `{ .n = 0 }`.
- **copia superficiale** — copia che duplica il puntatore ma non i dati puntati.
- **passaggio per valore / per indirizzo** — la funzione riceve una copia / l'indirizzo dell'originale.
- **union** — tipo i cui campi condividono la stessa memoria; contiene un solo valore alla volta.
- **union etichettata** — struct con un campo `enum` che indica quale campo della union è valido.
- **`enum`** — tipo con un elenco di valori dai nomi leggibili (`INTERO`, `REALE`, ...).
- **padding** — byte vuoti inseriti dal compilatore per rispettare l'allineamento.
- **allineamento** — regola per cui un dato di N byte deve stare a un indirizzo multiplo di N (per i tipi base).
- **endianness / little-endian** — ordine dei byte di un numero in memoria; little-endian = byte meno significativo per primo.
- **`strcmp`** — confronta il contenuto di due stringhe; restituisce 0 se sono uguali.
- **`void *`** — puntatore generico, senza tipo puntato; usato qui per confrontare indirizzi di tipi diversi.
