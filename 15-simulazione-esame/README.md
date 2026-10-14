# 15 — Simulazione d'esame: esercizi misti su tutto il C

> Lezioni di riferimento: tutte le trascrizioni dei blocchi 2, 3 e 4 (in particolare 2.4, 3.1, 3.2, 3.4, 3.5, 3.6, 4.1, 4.2, 4.4), le E-tivity 2.1, 3.4 e 3.6 (MatriciePuntatori, ParametriePuntatoribis, 2ParametriePuntatoriTRIS), Appunti di fine Unità 2, 3 e 4, Dispensa Stream, LEZ 07–21, e i README delle cartelle 01–14.
> Tempo stimato: ~6 ore (circa 5 ore di esercizi a tempo, più la correzione).

## Come usare questa simulazione

Questa cartella non introduce argomenti nuovi. Mette insieme **tutto** quello che hai visto nelle cartelle 01–14, come succede in un compito d'esame: ogni esercizio combina almeno tre argomenti. Tutti gli otto esercizi sono di livello **Tipo esame**.

**Il metodo, in quattro passi.**
1. **Fai l'esercizio a tempo, senza aiuti.** Ogni esercizio ha un campo **Tempo indicativo**: è il tempo che dovresti metterci all'esame. Fai partire un timer. Non aprire il suggerimento, non aprire la soluzione, non guardare le cartelle precedenti. Lavora solo con il testo, il file di partenza (lo *starter*, cioè il file `.c` con le parti `TODO` da completare) e la carta. Se il tempo scade, annota dove sei arrivato e vai avanti: anche questo è un dato utile.
2. **Testa.** Lancia `make test T=15 E=es01` (cambia `es01` con l'esercizio). Il *test* è un programma che dà al tuo eseguibile un input preparato e confronta l'output con quello atteso. Se una riga non coincide vedi `FAIL` e le differenze. I test attivano anche **AddressSanitizer** (abbreviato ASan, cioè uno strumento del compilatore che controlla ogni accesso alla memoria e ferma il programma con un messaggio chiaro se leggi o scrivi fuori da un vettore o usi memoria già liberata). Se lo vedi intervenire, il runner scrive `CRASH`: leggi il messaggio, dice la riga.
3. **Correggi da solo, poi con il suggerimento.** Solo se resti bloccato più di 10 minuti apri **💡 Suggerimento**. Solo quando tutti i test sono `OK` (o hai davvero esaurito le idee) apri **✅ Soluzione**, e confrontala con la tua riga per riga: spesso funzionano entrambe, ma la soluzione spiega il *perché* di ogni scelta.
4. **Fatti correggere con i prompt.** In fondo trovi dei **Prompt pronti**: incolla la tua soluzione e chiedi una correzione "da professore", con il voto e gli errori di stile, senza farti riscrivere il codice.

Ogni esercizio ha anche il campo **Ripassa: cartelle NN, NN**. Se un esercizio va male, il problema non è l'esercizio: è uno degli argomenti che lo compongono. Torna alle cartelle indicate, rifai il loro esercizio *Tipo esame*, poi riprova questo.

**Ordine consigliato.** Gli esercizi non sono in ordine di difficoltà: sono tutti di livello esame. Puoi farli in ordine, oppure simulare un appello vero: scegline tre a caso e datti 2 ore in tutto.

**Ipotesi sulla macchina.** Come nel resto della repo: `sizeof(int)` = 4 e `sizeof(char *)` = 8, valori veri su macOS con processore Apple (arm64) e su Linux x86-64. Nessun esercizio stampa indirizzi: gli output sono sempre identici a ogni esecuzione.

### Contraddizioni e imprecisioni nelle fonti (utili da sapere all'esame)
- **Copia di matrici con `<=`** (Appunti Unità 2, par. 3.11): l'esempio scrive `for (i = 0; i <= M; i++) for (j = 0; j <= N; j++) B[i][j] = A[i][j];`. Con `<=` si arriva a `B[M][N]`, che è **fuori** dalla matrice. Le stesse dispense, al par. 3.8 e al par. 2.16.2 (errori *off-by-one*, cioè "sbagliati di uno"), spiegano che gli indici vanno da 0 a N−1. La versione corretta usa `<`.
- **Stampare gli indirizzi con `%d`** (Appunti Unità 2, par. 3.3): l'esempio usa `printf("%d", &a)`. Gli Appunti Unità 3 (par. 4.3) usano invece `printf("%p", (void *)&x)`, che è il modo corretto. Nella E-tivity "Matrici e puntatori" il prof stesso dice che con `%d` "mi darebbe un warning".
- **C89 o C99?** Gli Appunti Unità 2 (par. 1.2) dicono che il corso usa l'ANSI C (C89). Però molti esempi degli Appunti Unità 3 e 4 scrivono `for (int i = 0; ...)`, che in C89 non è ammesso (è stato introdotto dal C99). La repo compila con `-std=c11`, quindi entrambe le forme funzionano; all'esame, se il prof chiede C89, dichiara le variabili all'inizio del blocco (come fa nelle trascrizioni: "subito all'inizio del blocco dichiarazione di tutto quello che serve").
- **`main()` senza `int`** (Appunti Unità 2, par. 2.1): dal C99 in poi il tipo restituito non si può omettere. Scrivi sempre `int main(void)`.
- **`p = realloc(p, ...)`** (Appunti Unità 4, par. 1.3 e 1.7): se `realloc` fallisce restituisce `NULL` e il vecchio blocco resta allocato; scrivendo il risultato direttamente in `p` perdi l'unico indirizzo del blocco. Si usa un puntatore temporaneo (es01, e cartella 12 es06).
- **Il cast su `malloc`** (Appunti Unità 4, par. 1.2: "è necessario effettuare un cast"): in C la conversione da `void *` è automatica, quindi il cast non è obbligatorio (lo è in C++). Non è un errore metterlo: la repo lo mette per seguire lo stile del prof.
- **Refusi nella Dispensa Stream:** `int *fputs(...)` e `int *puts(...)` restituiscono in realtà un `int`, non un `int *`; "fpritnf" è `fprintf`.

### Errori tipici da compito (messaggi veri di `cc`)
1. **Dimenticare `&` in `scanf`:** `warning: format '%d' expects argument of type 'int *', but argument 2 has type 'int' [-Wformat=]`. È un *warning* (avviso), non un errore: il programma compila lo stesso, ma poi crolla.
2. **Confrontare stringhe con `==`:** `warning: comparison with string literal results in unspecified behavior [-Waddress]`. `==` confronta gli indirizzi; per il contenuto serve `strcmp(a, b) == 0`.
3. **`*n++` al posto di `(*n)++`:** `warning: value computed is not used [-Wunused-value]`. Il `++` ha la precedenza: sposta il puntatore invece di incrementare il valore puntato.
4. **Passare una matrice `int a[3][3]` a un parametro `int **`:** `warning: passing argument 1 of 'f' from incompatible pointer type [-Wincompatible-pointer-types]`. Una matrice "decade" in un puntatore a riga, `int (*)[3]`, non in un puntatore a puntatore (es03).
5. **Liberare il vettore prima dei suoi elementi:** `warning: pointer 'v' may be used after 'free' [-Wuse-after-free]` (solo con gcc recenti; clang su macOS non lo segnala, ma ASan sì: `heap-use-after-free`). Lo trovi in es05.

## Checklist pre-esame

Prima dell'appello devi saper fare tutte queste cose **senza guardare gli appunti**. Se un punto ti fa esitare, ripassa la cartella indicata.

- [ ] Tradurre un algoritmo scritto con `goto` (l'MCD della E-tivity 2.1) in un ciclo `while` equivalente — **01**
- [ ] Prevedere il valore di espressioni con `++`/`--` prefissi e postfissi, cast, divisione intera e cortocircuito di `&&`/`||` — **02**
- [ ] Scrivere macro con parametri con tutte le parentesi giuste e spiegare perché `#define DOPPIO(x) x + x` sbaglia — **02, 08**
- [ ] Leggere input con `scanf` controllando il valore restituito, anche fino alla fine dell'input (EOF, *End Of File*) — **03**
- [ ] Usare `switch` con `break` (e sapere cosa succede senza) e un `do-while` per validare l'input — **03**
- [ ] Definire tipi con `enum` e `typedef` e usarli come `case` di uno `switch` — **04**
- [ ] Scorrere un vettore senza uscire dai limiti; scrivere a memoria l'ordinamento per selezione — **05**
- [ ] Usare una matrice: `m[i][j]`, `*(*(m + i) + j)`, e passarla a una funzione indicando il numero di colonne — **05, 11**
- [ ] Lavorare con le stringhe: terminatore `'\0'`, spazio `n + 1`, `strlen`, `strcpy`, `strcmp`, il `'\n'` lasciato da `fgets` — **06**
- [ ] Spiegare passaggio per valore e record di attivazione disegnando lo stack di una chiamata annidata — **07**
- [ ] "Restituire" più risultati con parametri puntatore (`scambia`, min e max, radici dell'equazione) — **08**
- [ ] Usare l'aritmetica dei puntatori, la differenza `q - p` e spiegare il ruolo del tipo puntato — **09**
- [ ] Definire `typedef struct`, vettori di struct, usare `.` e `->` e passare una struct per indirizzo — **10**
- [ ] Usare una `union` con un campo "etichetta" che dice quale membro è valido — **10**
- [ ] Aprire, leggere (`fscanf` con il suo valore di ritorno, `fgets`), scrivere (`fprintf`), riavvolgere (`rewind`) e chiudere un file — **11**
- [ ] Usare `malloc`, `calloc`, `realloc` con puntatore temporaneo e `free`; scrivere funzioni che creano un vettore (con `return` o con `int **`) — **12**
- [ ] Allocare e liberare una matrice dinamica nell'ordine giusto (prima le righe, poi il vettore di puntatori) — **12**
- [ ] Scrivere una funzione ricorsiva con caso base e riduzione, e simularne lo stack a mano (fattoriale, MCD, Hanoi) — **13**
- [ ] Usare `static` (locale e globale), `extern` su più file, puntatori a funzione e `argc`/`argv` — **14**
- [ ] Leggere un messaggio di AddressSanitizer e trovare la riga colpevole — **12, 15**

## Esercizi

### es01 — Libretto universitario: record da stdin, realloc e ordinamento  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 4, par. 1.7 (`realloc`), 1.8 (`NULL`) e 3.13 ("Passare funzioni come parametri", la `wrapper(fun1)`); Appunti Unità 3, par. 5.7–5.8 (vettori di struct, assegnamento tra struct). Variante d'esame che unisce cartella 12 es06 (vettore che cresce con `realloc`), cartella 05 es06 (ordinamento per selezione) e cartella 14 es05 (funzione passata come parametro).
**Ripassa:** cartelle 05, 10, 12, 14
**Tempo indicativo:** 40 minuti
**Testo:** la prima riga dell'input è il criterio di ordinamento: `voto`, `nome` oppure `crediti`. Poi, fino alla fine dell'input, c'è un esame per riga: `nome voto crediti`. Il main (già scritto) scarta gli esami con voto fuori da 18..30 o con crediti ≤ 0. Completa:
- `aggiungi_esame(&v, &n, &cap, e)`: aggiunge `e` in fondo al vettore dinamico; se è pieno **raddoppia** la capacità con `realloc` (la capacità iniziale è 1). Restituisce 1 se ha fatto la `realloc`, 0 se no, −1 se fallisce;
- `per_voto`, `per_nome`, `per_crediti`: rispondono 1 se `a` deve stare **prima** di `b` (voto più alto prima; più crediti prima; a parità, e per `nome`, ordine alfabetico);
- `ordina(v, n, precede)`: ordinamento per selezione che usa il criterio ricevuto come **puntatore a funzione**;
- `medie(...)`: media aritmetica, media ponderata (somma di voto × crediti diviso somma dei crediti) e crediti totali (CFU, cioè Crediti Formativi Universitari).
```text
input:
voto
Analisi 28 9
Programmazione 30 12
Fisica 24 6
Inglese 30 3
output:
letti 4 esami (capacita' 4, riallocazioni 2)
ordine: voto
1) Inglese 30 (3 CFU)
2) Programmazione 30 (12 CFU)
3) Analisi 28 (9 CFU)
4) Fisica 24 (6 CFU)
media aritmetica: 28.00
media ponderata: 28.20
CFU totali: 30
```
Casi di test: questo; ordine per `nome` con tre esami scartati (voto 15, voto 31, 0 crediti); nessun esame (solo il criterio); criterio sconosciuto; un esame solo.
**File:** `es01_libretto_ordina.c` · **Test:** `make test T=15 E=es01`

<details><summary>💡 Suggerimento</summary>
In `aggiungi_esame` lavori su `*pv` (il puntatore del main) e su `*n`, `*cap`: scrivi `(*pv)[*n] = e;` e `(*n)++`. Per la `realloc` usa `Esame *tmp = realloc(*pv, ...)` e assegna `*pv = tmp` solo se `tmp != NULL`. Nell'ordinamento, al posto di `v[j] < v[min]` scrivi `precede(&v[j], &v[scelto])`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché un vettore dinamico.** Non sappiamo quanti esami arriveranno. Un vettore statico grande "abbastanza" spreca memoria o non basta. Con `realloc` il vettore cresce quando serve. Raddoppiare (e non aggiungere 1 posto alla volta) riduce il numero di `realloc`: con 1000 esami ne servono circa 10 invece di 1000.
2. **Perché `Esame **pv`.** `realloc` può **spostare** il blocco in un'altra zona dello heap (lo *heap* è la zona di memoria dove vivono i blocchi allocati con `malloc`/`calloc`/`realloc`). Il main deve ricevere il nuovo indirizzo: quindi la funzione deve modificare il puntatore del main, e per farlo le serve il suo indirizzo (Appunti Unità 4, par. 1.12).
3. **Il puntatore temporaneo.** `*pv = realloc(*pv, ...)` sembra più corto, ma se `realloc` fallisce scrive `NULL` in `*pv` e il vecchio blocco resta allocato senza che nessuno ne conosca più l'indirizzo: un *memory leak* (memoria persa fino alla fine del programma).
   ```c
   if (*n == *cap) {
       Esame *tmp = (Esame *) realloc(*pv, (size_t)(*cap * 2) * sizeof(Esame));
       if (tmp == NULL) return -1;
       *pv = tmp;
       *cap = *cap * 2;
       rialloc = 1;
   }
   (*pv)[*n] = e;     /* assegnamento tra struct: copia anche l'array nome */
   (*n)++;
   ```
4. **I criteri.** Ognuno risponde alla domanda "a va prima di b?". Il confronto tra stringhe si fa con `strcmp`: restituisce un numero negativo se la prima viene prima nell'ordine alfabetico.
   ```c
   int per_voto(const Esame *a, const Esame *b)
   {
       if (a->voto != b->voto) return a->voto > b->voto;
       return strcmp(a->nome, b->nome) < 0;
   }
   ```
5. **L'ordinamento riceve il criterio.** `int (*precede)(const Esame *, const Esame *)` si legge "precede è un puntatore a una funzione che riceve due `const Esame *` e restituisce un `int`". L'algoritmo è sempre lo stesso; cambia solo la funzione chiamata nel confronto. Senza puntatori a funzione dovresti scrivere tre ordinamenti quasi identici.
6. **Le medie.** `(double) somma_voti / n`: il cast va **prima** della divisione, altrimenti `int / int` tronca (cartella 02).

Crescita del vettore nel primo test:

| esame | n prima | cap prima | realloc? | cap dopo | n dopo |
|---|---|---|---|---|---|
| Analisi | 0 | 1 | no | 1 | 1 |
| Programmazione | 1 | 1 | sì | 2 | 2 |
| Fisica | 2 | 2 | sì | 4 | 3 |
| Inglese | 3 | 4 | no | 4 | 4 |

Ordinamento per voto, partendo da `[Analisi 28, Programmazione 30, Fisica 24, Inglese 30]`:

| i | elemento scelto | vettore dopo lo scambio |
|---|---|---|
| 0 | Inglese 30 (pari voto con Programmazione, ma "I" < "P") | Inglese, Programmazione, Fisica, Analisi |
| 1 | Programmazione 30 | invariato |
| 2 | Analisi 28 | Inglese, Programmazione, Analisi, Fisica |

Media ponderata: (28·9 + 30·12 + 24·6 + 30·3) / 30 = 846 / 30 = 28.20.

Codice completo: `soluzioni/es01_libretto_ordina.c`.
</details>

### es02 — Calcolatrice a comandi: tabella di puntatori a funzione  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 4, par. 3.12 (`fun_ptr_arr` con `add`, `sub`, `mul`: "sostituire strutture di controllo come switch con una tabella di funzioni"), par. 2.8 (potenza ricorsiva), par. 4.6 (`static int c` di `contatore`); E-tivity 2.1 (MCD di Euclide); trascrizione 2.4 (enum). Diverso da cartella 14 es05: qui il comando si cerca per nome in una tabella di struct e ogni operazione porta con sé un vincolo.
**Ripassa:** cartelle 04, 06, 13, 14
**Tempo indicativo:** 35 minuti
**Testo:** ogni riga è un comando: `<operazione> a b` (operazioni `somma diff prod div mod pot mcd`), oppure `stat` (stampa i conteggi), oppure `fine`. Le operazioni sono in una **tabella**: un vettore di `struct Comando { nome, puntatore alla funzione, vincolo }`, dove il vincolo è un `enum` (`NESSUNO`, `B_NON_ZERO`, `B_NON_NEGATIVO`). Completa:
- `pot(a, b)` e `mcd(a, b)` **ricorsive**;
- `cerca(nome)`: restituisce l'indirizzo della riga della tabella, o `NULL`;
- `esegui(c, a, b, &ris)`: con uno `switch` sul vincolo restituisce 1 (divisione per zero) o 2 (esponente negativo); se va tutto bene calcola tramite `c->calcola` e restituisce 0;
- `statistiche(ev)`: conta operazioni riuscite e fallite con due variabili **static locali**; con `STAMPA` stampa la riga `stat: ...`.
```text
input:
div 7 0
pot 2 -1
radice 16 2
pot 5 0
mcd -12 18
div -7 2
stat
output:
div 7 0 -> errore: divisione per zero
pot 2 -1 -> errore: esponente negativo
radice: comando sconosciuto
pot 5 0 = 1
mcd -12 18 = 6
div -7 2 = -3
stat: 3 riuscite, 3 fallite
finale stat: 3 riuscite, 3 fallite
```
Casi di test: tutte le operazioni + `fine` con righe dopo (ignorate); errori, comando sconosciuto, `pot 0 0`, `mcd 0 0`, numeri negativi; input vuoto; operandi mancanti.
**File:** `es02_calcolatrice_comandi.c` · **Test:** `make test T=15 E=es02`

<details><summary>💡 Suggerimento</summary>
`cerca` restituisce `&tabella[i]` (un indirizzo, non una copia). In `esegui` il `case NESSUNO:` serve comunque, anche vuoto, così il compilatore sa che hai considerato tutti i valori dell'enum. Per `mcd`: `mcd(a, b) = mcd(b, a % b)`, caso base `b == 0` (restituisci il valore assoluto di `a`).
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché una tabella.** Con uno `switch` su sette stringhe dovresti scrivere sette `if (strcmp(...) == 0)` e, per ognuno, il controllo del vincolo. Con la tabella i **dati** (nome, funzione, vincolo) sono separati dalla **logica** (cerca, controlla, calcola): aggiungere un'operazione significa aggiungere una riga. È l'idea della `fun_ptr_arr` degli Appunti, con in più il nome per cercarla.
2. **`cerca`:** ricerca lineare. Restituisce un puntatore `const Comando *` così il chiamante legge la riga senza copiarla e senza poterla modificare.
   ```c
   for (i = 0; i < N_COMANDI; i++)
       if (strcmp(tabella[i].nome, nome) == 0)
           return &tabella[i];
   return NULL;
   ```
   `N_COMANDI` è `sizeof tabella / sizeof tabella[0]`: byte totali diviso byte di una riga = numero di righe. Funziona solo perché `tabella` è un vero vettore e non un puntatore (cartella 09).
3. **`esegui`:** prima il vincolo, poi la chiamata. L'ordine è essenziale: se calcolassi `a / b` prima di controllare `b == 0`, il programma si fermerebbe con un errore di divisione.
   ```c
   switch (c->vincolo) {
   case B_NON_ZERO:     if (b == 0) return 1; break;
   case B_NON_NEGATIVO: if (b < 0)  return 2; break;
   case NESSUNO:        break;
   }
   *ris = c->calcola(a, b);
   ```
   `c->calcola(a, b)` chiama la funzione il cui indirizzo è nella riga: `esegui` non sa se è `somma` o `pot`.
4. **`pot` ricorsiva veloce.** Caso base `b == 0` → 1. Caso ricorsivo: calcolo `meta = pot(a, b / 2)` **una volta sola** e restituisco `meta * meta` (b pari) o `a * meta * meta` (b dispari). La versione degli Appunti (`i * potenza(i, n - 1)`) è corretta e accettata, ma fa b chiamate invece di circa log₂ b.
5. **`mcd` ricorsivo:** è l'MCD della E-tivity 2.1 scritto senza `goto`: il ciclo "r = x % y; x = y; y = r" diventa la chiamata `mcd(b, a % b)`.
6. **`statistiche`:** le due `static int` vengono inizializzate una volta sola e ricordano il valore tra le chiamate; nessun'altra funzione può toccarle (cartella 14). Una globale funzionerebbe, ma sarebbe modificabile da tutto il file.
7. **`div -7 2 = -3`:** in C la divisione intera tronca **verso zero** (−3.5 → −3), non verso il basso.

Simulazione di `pot(2, 10)` (discesa, poi risalita):

| chiamata | b | meta | restituisce |
|---|---|---|---|
| pot(2,10) | 10 | pot(2,5) = 32 | 32·32 = 1024 |
| pot(2,5) | 5 | pot(2,2) = 4 | 2·4·4 = 32 |
| pot(2,2) | 2 | pot(2,1) = 2 | 2·2 = 4 |
| pot(2,1) | 1 | pot(2,0) = 1 | 2·1·1 = 2 |
| pot(2,0) | 0 | — | 1 (caso base) |

`mcd(-12, 18)` → `mcd(18, -12)` → `mcd(-12, 6)` (18 % −12 = 6) → `mcd(6, 0)` → 6.

Codice completo: `soluzioni/es02_calcolatrice_comandi.c`.
</details>

### es03 — Campo minato: matrici, puntatori e funzioni  ·  Tipo esame
**Fonte:** Ispirato a: E-tivity 3.6 "Matrici e puntatori" (`*(*(ar + i) + j)` e il puntatore a riga `int (*p)[3]`), Appunti Unità 3, par. 6.5 (restituzione di più risultati), 6.7 (array multidimensionali come parametri: "è necessario specificare la dimensione delle colonne"), 6.8–6.9 (puntatori ad array).
**Ripassa:** cartelle 05, 08, 11
**Tempo indicativo:** 35 minuti
**Testo:** l'input è `R C` (da 1 a 10) e poi R righe di C caratteri: `*` è una mina, `.` una cella libera. Il programma stampa la griglia in cui ogni cella libera diventa il numero di mine tra le sue (fino a) 8 vicine, il numero di mine e la cella libera "più pericolosa" (a parità, la prima per riga e poi per colonna). Completa:
- `conta_vicine(m, R, C, i, j)` leggendo le celle con la notazione `*(*(m + r) + c)`;
- `calcola(m, num, R, C)`: riempie `num` (−1 per le mine) e restituisce il numero di mine;
- `piu_pericolosa(num, R, C, &ri, &rj)`: restituisce il massimo (−1 se ci sono solo mine) e la posizione tramite i puntatori, scorrendo le righe con il puntatore a riga `int (*p)[MAXC]`.
```text
input:
3 4
*..*
.*..
....
output:
*22*
2*21
1110
mine: 3
piu' pericolosa: riga 0 colonna 1 (2 mine vicine)
```
Casi di test: questo; griglia 1×1 libera; griglia di sole mine; dimensioni non valide (`0 5`); mina circondata da otto mine (il caso 8).
**File:** `es03_campo_minato.c` · **Test:** `make test T=15 E=es03`

<details><summary>💡 Suggerimento</summary>
Prima di leggere `*(*(m + r) + c)` controlla che `r` e `c` siano dentro la griglia: usa `continue` per saltare le celle fuori e la cella `(i, j)` stessa. In `piu_pericolosa` usa `>` e non `>=`, così a parità resta la prima trovata.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Come si passa una matrice.** `char m[][MAXC]` è in realtà un parametro di tipo `char (*)[MAXC]`, cioè "puntatore a un vettore di MAXC char" (un puntatore a **riga**). Il compilatore deve conoscere MAXC: per arrivare alla riga r deve saltare r · MAXC caratteri (Appunti Unità 3, par. 6.7). Per questo non si può scrivere `char m[][]`, e per questo `char **` non va bene (vedi Errori tipici 4).
2. **La notazione a puntatori, come nella E-tivity.** `m + r` è l'indirizzo della riga r; `*(m + r)` è la riga, che "decade" (si converte da sola) nell'indirizzo del suo primo carattere; `+ c` si sposta di c caratteri; l'ultimo `*` legge il carattere. Quindi `*(*(m + r) + c)` è esattamente `m[r][c]`.
3. **I bordi.** Una cella in un angolo ha solo 3 vicine. Senza il controllo `r < 0 || r >= righe || ...` leggeresti `m[-1][...]` o una riga oltre l'ultima: memoria che non appartiene alla griglia (comportamento indefinito, cioè il C non garantisce il risultato; ASan lo segnalerebbe).
   ```c
   for (r = i - 1; r <= i + 1; r++)
       for (c = j - 1; c <= j + 1; c++) {
           if (r < 0 || r >= righe || c < 0 || c >= colonne) continue;
           if (r == i && c == j) continue;
           if (*(*(m + r) + c) == '*') conta++;
       }
   ```
4. **Due risultati da una funzione.** `piu_pericolosa` deve dare il massimo **e** la sua posizione. Il massimo esce con `return`, riga e colonna con `*pi` e `*pj` (cartella 08).
5. **Il puntatore a riga `p`.** `p = num` punta alla riga 0; `p++` avanza di una riga intera (MAXC int = 40 byte); `(*p)[j]` è l'elemento j della riga puntata. Le parentesi in `int (*p)[MAXC]` sono essenziali: `int *p[MAXC]` sarebbe un vettore di MAXC puntatori (Appunti Unità 3, par. 6.8).
6. **Stampa.** `putchar('0' + num[i][j])` trasforma il numero 3 nel carattere `'3'`: le cifre hanno codici consecutivi nella tabella ASCII (la tabella che associa a ogni carattere un numero).

Simulazione di `conta_vicine` per la cella (0, 1) del primo test:

| (r, c) | dentro? | è (i, j)? | carattere | conta |
|---|---|---|---|---|
| (−1, 0..2) | no | — | — | 0 |
| (0, 0) | sì | no | `*` | 1 |
| (0, 1) | sì | sì | — | 1 |
| (0, 2) | sì | no | `.` | 1 |
| (1, 0) | sì | no | `.` | 1 |
| (1, 1) | sì | no | `*` | 2 |
| (1, 2) | sì | no | `.` | 2 |

Codice completo: `soluzioni/es03_campo_minato.c`.
</details>

### es04 — Espandere stringhe compresse con la ricorsione  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 4, cap. 2 (par. 2.5 "caso base e caso ricorsivo", 2.7 "riduzione del problema", 2.14 "relazioni di ricorrenza e strutture dati") e par. 1.12 (puntatore a puntatore); Appunti Unità 2, par. 4.2 (terminatore) e 4.11 (buffer overflow: controllare sempre lo spazio prima di scrivere); Appunti Unità 2, par. 2.7 (la stringa di formato di `scanf` descritta con una grammatica).
**Ripassa:** cartelle 06, 09, 12, 13
**Tempo indicativo:** 45 minuti
**Testo:** in una stringa compressa `k[...]` significa "ripeti k volte il contenuto", anche annidato: `2[ab]3[x]c` → `ababxxxc`, `2[a3[b]]` → `abbbabbb`. La regola (la *grammatica*, cioè la descrizione formale di com'è fatta una stringa valida) è `sequenza := { lettera | numero '[' sequenza ']' }`. Completa la funzione **ricorsiva** `espandi(p, out, pos, max)`:
- `*p` è il cursore sulla stringa compressa: la funzione lo fa avanzare, per questo riceve `const char **p`;
- scrive i caratteri espansi in `out` dalla posizione `pos`;
- si ferma, **senza consumarli**, su `'\0'` o `']'`;
- restituisce la nuova posizione libera, oppure `ERR_FORMATO` o `ERR_LUNGA` (il risultato supererebbe 64 caratteri).
```text
input:
2[ab]3[x]c 2[a3[b]] 2[ab ab] 2[] 0[abc]d 8[8[x]] 9[9[x]]
output:
2[ab]3[x]c -> "ababxxxc" (lunghezza 8)
2[a3[b]] -> "abbbabbb" (lunghezza 8)
2[ab -> errore di formato
ab] -> errore di formato
2[] -> "" (lunghezza 0)
0[abc]d -> "d" (lunghezza 1)
8[8[x]] -> "xxxx...x" (lunghezza 64)
9[9[x]] -> troppo lunga
```
(nel test vero la riga di `8[8[x]]` contiene 64 `x`). Casi di test: espansioni normali e numeri a più cifre (`10[z]`); errori di formato (`2[ab`, `ab]`, `3a`, `[ab]`, `x-y`), contenuto vuoto e zero ripetizioni; limite esatto di 64 caratteri e superamento.
**File:** `es04_espandi_ricorsivo.c` · **Test:** `make test T=15 E=es04`

<details><summary>💡 Suggerimento</summary>
Ciclo `while (**p != '\0' && **p != ']')`. Se `**p` è una lettera: controlla `pos < max`, scrivi, avanza. Se è una cifra: leggi tutto il numero k, pretendi `'['`, ricordati `inizio = pos`, chiama `espandi(p, out, pos, max)`, pretendi `']'`. A quel punto il contenuto è già scritto **una** volta tra `inizio` e `pos`: ricopialo altre k−1 volte.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché la ricorsione.** Una stringa compressa contiene altre stringhe compresse dentro le parentesi: la struttura è ricorsiva, quindi la funzione lo è. **Caso base:** la sequenza è finita (`'\0'` o `']'`), e la funzione restituisce `pos` senza chiamarsi. **Riduzione:** ogni chiamata ricorsiva lavora sul contenuto di una coppia di parentesi, che è più corto della stringa intera.
2. **Perché `const char **p`.** Dopo che la chiamata ricorsiva ha letto `3[b`, il chiamante deve ripartire **dopo** quello che lei ha consumato. Se `espandi` ricevesse `const char *p`, avanzerebbe solo la sua copia locale (passaggio per valore, cartella 08). Con `const char **p` avanza il cursore del chiamante: `(*p)++`. Attenzione: `*p++` sposterebbe `p` stesso, non il cursore.
3. **Leggere un numero di più cifre:** `k = k * 10 + (**p - '0')` (per "12": 0·10 + 1 = 1, poi 1·10 + 2 = 12). `**p - '0'` trasforma il carattere cifra nel suo valore.
4. **Ripetere senza memoria extra.** La chiamata ricorsiva scrive il contenuto una volta in `out[inizio..pos-1]`. Poi lo copio dietro se stesso k−1 volte. Con k = 0 rimetto `pos = inizio`, cioè "cancello".
   ```c
   inizio = pos;
   pos = espandi(p, out, pos, max);
   if (pos < 0) return pos;                 /* l'errore risale */
   if (**p != ']') return ERR_FORMATO;
   (*p)++;
   lun = pos - inizio;
   if (k == 0) pos = inizio;
   else for (r = 1; r < k; r++) {
       if (pos + lun > max) return ERR_LUNGA;
       for (i = 0; i < lun; i++) out[pos + i] = out[inizio + i];
       pos += lun;
   }
   ```
5. **Mai scrivere fuori.** `out` ha MAXOUT + 1 posti (l'ultimo è per `'\0'`). Ogni scrittura è preceduta da un controllo: è la regola anti *buffer overflow* (scrittura oltre la fine di un vettore) degli Appunti Unità 2, par. 4.11.
6. **Gli errori risalgono.** Se una chiamata profonda restituisce un valore negativo, ogni chiamata sopra lo restituisce subito: l'errore arriva al chiamante iniziale senza fare altro lavoro.
7. **`ab]`.** `espandi` si ferma sulla `]` e restituisce 2: per lei è tutto regolare. È `decodifica` (già scritta) a notare che il cursore non è arrivato a `'\0'` e a segnalare l'errore.
8. **`isdigit((unsigned char) **p)`:** le funzioni di `<ctype.h>` vogliono un valore non negativo; con lettere accentate un `char` può essere negativo, e il cast evita il comportamento indefinito.

Simulazione di `2[a3[b]]` (livello = profondità della ricorsione):

| livello | legge | azione | out | pos |
|---|---|---|---|---|
| 0 | `2[` | k = 2, inizio = 0, chiama livello 1 | | 0 |
| 1 | `a` | scrive | a | 1 |
| 1 | `3[` | k = 3, inizio = 1, chiama livello 2 | a | 1 |
| 2 | `b` | scrive | ab | 2 |
| 2 | `]` | si ferma, restituisce 2 | ab | 2 |
| 1 | `]` | salta; lun = 1, copia 2 volte | abbb | 4 |
| 1 | `]` | si ferma, restituisce 4 | abbb | 4 |
| 0 | `]` | salta; lun = 4, copia 1 volta | abbbabbb | 8 |
| 0 | `\0` | restituisce 8 | abbbabbb | 8 |

Codice completo: `soluzioni/es04_espandi_ricorsivo.c`.
</details>

### es05 — Trova e correggi gli errori: elenco di parole nello heap  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 4, par. 1.9 ("la memoria deve essere liberata una sola volta", "dopo la chiamata a free il puntatore non deve essere utilizzato") e 1.12 (allocazione tramite puntatore a puntatore); Appunti Unità 2, par. 4.2 ("una stringa di lunghezza n occupa n + 1 posizioni") e 1.16.2 (`r = a / b` contro `r = (double) a / b`); Appunti Unità 3, par. 6.4 (modificare il puntatore copia non modifica quello del chiamante).
**Ripassa:** cartelle 02, 06, 08, 12
**Tempo indicativo:** 30 minuti
**Testo:** il programma legge n parole, ne copia ognuna nello heap, calcola la lunghezza media e stampa le parole lunghe **almeno** quanto la media. Ci sono **quattro errori** di tipo diverso: uno sui **puntatori**, uno di **logica** e due sulla **memoria dinamica**. Il programma compila; con gcc compare un solo avviso, che è già un indizio.
```text
input:
4
casa lampadina re sole
output corretto:
parole lette: 4
media lunghezza: 4.75
almeno lunghe come la media: lampadina
totale: 1
```
Casi di test: questo; tre parole uguali di lunghezza (media intera); una parola sola; n = 0; cinque parole con media 4.80 (`mare sole vento neve pioggia`).
**File:** `es05_trova_errore.c` · **Test:** `make test T=15 E=es05`

<details><summary>💡 Suggerimento</summary>
Correggi un errore alla volta e rilancia il test: ASan si ferma al primo problema che incontra. Le domande da farti: quanti byte servono per copiare una stringa? Chi riceve davvero il blocco allocato in `crea_elenco`? Che tipo ha `totale / n`? In che ordine si liberano un vettore di puntatori e i blocchi a cui punta?
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Gli errori compaiono in quest'ordine mentre li correggi.

**Errore 1 — memoria: manca lo spazio per `'\0'`.** ASan:
```text
ERROR: AddressSanitizer: heap-buffer-overflow ...
WRITE of size 5 at ...
    #0 ... in strcpy
    #1 ... in duplica es05_trova_errore.c:33
```
"WRITE of size 5" per la parola `casa`: `strcpy` scrive 4 lettere **più** il terminatore, ma `malloc(strlen(s))` ha riservato 4 byte. Correzione: `malloc(strlen(s) + 1)`.

**Errore 2 — puntatori: il vettore allocato non arriva al main.**
```text
ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000
    #0 ... in main es05_trova_errore.c:82
```
*SEGV* (*segmentation violation*) vuol dire accesso a un indirizzo non valido: qui l'indirizzo 0, cioè `NULL`. `crea_elenco(char **v, ...)` riceve una **copia** del puntatore del main; `v = malloc(...)` cambia solo la copia, e il main resta con `elenco = NULL`. È lo stesso caso di "modificare il puntatore" contro "modificare il valore puntato" (Appunti Unità 3, par. 6.4). Correzione, come in Appunti Unità 4, par. 1.12:
```c
int crea_elenco(char ***pv, int n)
{
    *pv = (char **) malloc((size_t) n * sizeof(char *));
    ...
        (*pv)[i] = NULL;     /* parentesi: prima *pv, poi [i] */
}
/* nel main */ crea_elenco(&elenco, n)
```

**Errore 3 — logica: divisione intera.** Ora il programma stampa `media lunghezza: 4.00` e include anche `casa` e `sole`. `totale / n` è `int / int` = 19 / 4 = 4: la parte decimale si perde **prima** che il risultato diventi `double`. Correzione: `return (double) totale / n;` (Appunti Unità 2, par. 1.16.2). Il test con cinque parole lo conferma: media 4.80, non 4.00.

**Errore 4 — memoria: ordine di deallocazione.**
```text
ERROR: AddressSanitizer: heap-use-after-free ...
    #0 ... in libera_elenco es05_trova_errore.c:62
```
`free(v)` libera il vettore dei puntatori; subito dopo `free(v[i])` **legge** `v[i]` da quel blocco già liberato. Correzione: prima il ciclo `free(v[i])`, poi `free(v)`. È la stessa regola della matrice dinamica (Appunti Unità 4, par. 1.10): "prima ogni riga e successivamente il vettore di puntatori". gcc lo segnala già in compilazione: `warning: pointer 'v' may be used after 'free' [-Wuse-after-free]`.

| errore | tipo | sintomo | correzione |
|---|---|---|---|
| 1 | memoria | heap-buffer-overflow in `strcpy` | `strlen(s) + 1` |
| 2 | puntatori | SEGV su indirizzo 0 | `char ***pv` e `&elenco` |
| 3 | logica | media 4.00 invece di 4.75 | `(double) totale / n` |
| 4 | memoria | heap-use-after-free | liberare prima gli elementi |

Codice completo: `soluzioni/es05_trova_errore.c` (righe marcate `CORRETTO`).
</details>

### es06 — Cosa stampa? Puntatori, static, ricorsione e macro  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 2, par. 1.5.1 (`#define SOMMA 3+2` e `a = 5 * SOMMA`); Appunti Unità 4, par. 3.8–3.10 (`MAX(x,y)`, macro e precedenza), par. 4.6 (static locale), par. 2.9 (record di attivazione nelle chiamate ricorsive); E-tivity 3.4 (aritmetica dei puntatori, "il tipo determina la dimensione della memoria riferita"); Appunti Unità 3, par. 6.4.
**Ripassa:** cartelle 02, 08, 09, 13, 14
**Tempo indicativo:** 25 minuti
**Testo:** apri `es06_cosa_stampa.c` (è **già completo**). Senza eseguirlo, scrivi su carta le **22 righe** che stampa. Poi lancia il test e confronta con `tests/es06_cosa_stampa.out`.
```text
La mia previsione:
A: ?
B: ?
C: m=? i=?
D: m=? i=?
E: ? ?
F: ? ?
G: ? ? ?
H: ? ? ?
I: ? ?
J: ?
giu(5) profondita=?
... (le righe di giu e su)
K: m=? acc=?
giu(0) profondita=?
su(0) r=?
L: m=?
```
**File:** `es06_cosa_stampa.c` · **Test:** `make test T=15 E=es06`

<details><summary>💡 Suggerimento</summary>
Per ogni macro scrivi a mano l'espansione **testuale** prima di calcolare. In `MAX(i++, j)` conta quante volte compare `a` nell'espansione e quali parti di `? :` vengono davvero valutate. Per `giu`, ricorda che `profondita` è una sola per tutte le chiamate, mentre `n` e `r` sono una per chiamata.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

Output reale:
```text
A: 8
B: 9
C: m=4 i=4
D: m=5 i=6
E: 11 20
F: 30 2
G: 99 40 99
H: e a me
I: Esame 6
J: 3
giu(5) profondita=1
giu(3) profondita=2
giu(1) profondita=3
giu(-1) profondita=4
su(-1) r=9
su(1) r=10
su(3) r=11
su(5) r=12
K: m=12 acc=9
giu(0) profondita=1
su(0) r=9
L: m=9
```

1. **A.** `3 * DOPPIO(2)` diventa `3 * 2 + 2`: la moltiplicazione ha la precedenza, quindi 6 + 2 = **8**, non 12. È l'esempio `5 * SOMMA` degli Appunti Unità 2.
2. **B.** `QUADRATO(1 + 2)` diventa `((1 + 2) * (1 + 2))` = **9**. Senza parentesi sarebbe `1 + 2 * 1 + 2` = 5.
3. **C.** `MAX(i++, j)` diventa `((i++) > (j) ? (i++) : (j))`. Con i = 3: `3 > 4` è falso; dopo il confronto i vale 4. Si valuta **solo** il ramo scelto, `(j)` = 4. Quindi m = 4, i = 4. L'operatore `? :` ha un *punto di sequenza* (un punto in cui tutti gli effetti precedenti sono completati) dopo la condizione: il comportamento è definito.
4. **D.** `MAX(i++, j - 1)`: `4 > 3` è vero, i diventa 5; ora si valuta il ramo vero, **un altro** `i++`: vale 5 e i diventa 6. Quindi m = 5, i = 6. È il motivo per cui le macro con parametri "doppi" sono pericolose: una funzione `max` incrementerebbe i una volta sola (Appunti Unità 4, par. 3.10).
5. **E.** `*p + 1`: prima `*p` (10), poi + 1 = **11**. `*(p + 1)` è `v[1]` = **20**.
6. **F.** `sposta(&p, 2)` riceve l'indirizzo di p e fa `*pp += 2`: modifica **p del main**, che ora punta a `v[2]`. `*p` = 30; `q - p` = indice 4 − indice 2 = **2** (la differenza tra puntatori conta elementi, non byte).
7. **G.** `*p++ = 99`: il `++` postfisso si applica a p, ma l'espressione vale il **vecchio** p. Quindi scrive 99 in `v[2]` e poi p passa a `v[3]`. `p[-1]` è `*(p - 1)` = `v[2]` = 99.
8. **H.** `*c` = `'e'`; `*(c + 2)` = `'a'` (e-s-**a**-m-e); `c + 3` è l'indirizzo di `"me"`, e `%s` stampa da lì fino a `'\0'`.
9. **I.** `c[0] = 'E'` modifica **s**, perché c punta a s. `sizeof s` = 6: 5 lettere più `'\0'`. `s` è un vero vettore, non un puntatore (con `sizeof c` avresti 8).
10. **J.** `prossimo()` ha una static: 1, 2, 3. Le prime due chiamate scartano il valore. (Non è scritto `printf("%d %d", prossimo(), prossimo())` apposta: l'ordine di valutazione degli argomenti non è stabilito dal C.)
11. **giu/su.** Ogni chiamata ha il suo record di attivazione con la sua `n` e la sua `r`, ma `profondita` è static: una sola cella condivisa. Scendendo sale 1, 2, 3, 4; risalendo ogni chiamata la riporta giù di 1. `acc` è una sola variabile del main, raggiunta tramite il puntatore: accumula 5 + 3 + 1 = 9.

| chiamata | profondita all'ingresso | acc dopo | r restituito |
|---|---|---|---|
| giu(5) | 1 | 5 | giu(3) + 1 = 12 |
| giu(3) | 2 | 8 | giu(1) + 1 = 11 |
| giu(1) | 3 | 9 | giu(−1) + 1 = 10 |
| giu(−1) | 4 | 9 | caso base: *acc = 9 |

12. **K, giu(0), L.** Dopo la prima discesa `profondita` è tornata a 0, quindi `giu(0)` stampa `profondita=1`. Non è perché la static si "riazzera": è perché ogni chiamata ha fatto `profondita--` prima di uscire. `giu(0)` è caso base e restituisce `*acc` = 9.

Il file della soluzione è identico allo starter.
</details>

### es07 — Parcheggio: enum, switch, struct e menù  ·  Tipo esame
**Fonte:** Ispirato a: Appunti Unità 2, par. 2.18 (tipi enumerativi, `typedef enum`, "uso degli enumerativi nei cicli e nello switch") e 2.10 (switch con `break`); trascrizione 2.4 (enum e typedef); Appunti Unità 3, par. 5.5–5.7 (`typedef struct`, vettori di struct); Appunti Unità 2, par. 2.6 (`scanf("%2d/%2d/%4d", ...)`: separatori nella stringa di formato). Diverso da cartella 10 es08 (magazzino): qui conta la logica degli stati e delle tariffe con gli enum.
**Ripassa:** cartelle 03, 04, 06, 10
**Tempo indicativo:** 40 minuti
**Testo:** un parcheggio ha 3 posti. Comandi: `1 T TARGA HH:MM` (entrata; T = `A` auto, `M` moto, `F` furgone), `2 TARGA HH:MM` (uscita), `3` (stato), `0` (fine: incasso totale). Tariffe orarie in centesimi: auto 200, moto 100, furgone 350. Ogni ora iniziata si paga intera, minimo 1 ora; **dalla quarta ora in poi** ogni ora costa la metà. Il `main` con il menù è già scritto. Completa con degli `switch`: `tipo_da_carattere`, `tariffa_oraria`, `costo`, e poi `cerca_targa` (solo tra i posti `OCCUPATO`) ed `entra` (−2 se la targa è già dentro, −1 se è tutto pieno, altrimenti il primo posto libero).
```text
input:
1 A AB123CD 08:30
1 F FUR99 07:10
2 AB123CD 10:31
2 FUR99 13:00
0
output:
entrata AB123CD (auto): posto 0
entrata FUR99 (furgone): posto 1
uscita AB123CD: posto 0, 121 min, 6.00 euro
uscita FUR99: posto 1, 350 min, 15.75 euro
incasso: 21.75 euro, veicoli usciti: 2
```
Casi di test: flusso completo con stampa dello stato; parcheggio pieno, targa duplicata, tipo non valido, targa inesistente, orario d'uscita prima dell'entrata, sosta di 0 minuti, comando non valido; solo `0`; sosta di quasi 24 ore e sosta di esattamente 60 minuti.
**File:** `es07_parcheggio.c` · **Test:** `make test T=15 E=es07`

<details><summary>💡 Suggerimento</summary>
Le "ore iniziate" si calcolano con la sola divisione intera: `(minuti + 59) / 60` (61 minuti → 2 ore, 60 minuti → 1 ora). In uno `switch` dove ogni `case` fa `return`, il `break` non serve. Le targhe si confrontano con `strcmp` e si copiano con `strcpy`.
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché gli enum.** `AUTO`, `MOTO`, `FURGONE` al posto di 0, 1, 2 rendono il codice leggibile, e lo `switch` diventa un elenco di casi con un nome. Gli enum sono interi (Appunti Unità 2, par. 2.18.2): per questo funzionano come `case` e il main può scrivere `case ENTRATA:` facendo lo `switch` su un `int`.
2. **Conversione carattere → enum.** Il risultato esce dal parametro puntatore, perché il `return` serve a dire "valido o no" (cartella 08):
   ```c
   switch (c) {
   case 'A': *t = AUTO;    return 1;
   case 'M': *t = MOTO;    return 1;
   case 'F': *t = FURGONE; return 1;
   default:  return 0;
   }
   ```
3. **Il costo, in centesimi.** Usare interi evita gli errori di arrotondamento dei `double` sui soldi.
   ```c
   int ore = (minuti + 59) / 60;
   if (ore == 0) ore = 1;
   if (ore <= 3) return ore * tar;
   return 3 * tar + (ore - 3) * (tar / 2);
   ```
   Furgone, 350 minuti: (350 + 59) / 60 = 6 ore → 3·350 + 3·175 = 1575 centesimi = 15.75 euro.
4. **`cerca_targa` solo sui posti occupati.** Un posto libero può contenere ancora la targa dell'ultimo veicolo uscito (non la cancelliamo): senza il controllo `stato == OCCUPATO` troveresti un'auto già uscita.
5. **`entra`.** Prima il controllo del duplicato, poi il primo posto libero. Le stringhe non si assegnano con `=` (Appunti Unità 2, par. 4.9.2): `strcpy(p[i].targa, targa)`. La targa è letta con `%7s`, quindi sta sempre in `char targa[8]`.
6. **Il menù nel main.** `while (scanf("%d", &cmd) == 1 && cmd != FINE)`: termina con `0` **oppure** a fine input. `scanf(" %c ...")`: lo spazio prima di `%c` salta gli spazi rimasti nel *buffer* di input (la zona di memoria dove aspetta il testo letto da tastiera, Appunti Unità 2, par. 2.6); senza, `%c` leggerebbe lo spazio. `%d:%d` legge l'orario perché i caratteri fuori dagli specificatori devono comparire uguali nell'input.

| comando | posti dopo (0, 1, 2) | incasso |
|---|---|---|
| `1 A AB123CD 08:30` | AB123CD, –, – | 0 |
| `1 F FUR99 07:10` | AB123CD, FUR99, – | 0 |
| `2 AB123CD 10:31` (121 min → 3 h) | –, FUR99, – | 600 |
| `2 FUR99 13:00` (350 min → 6 h) | –, –, – | 2175 |

Codice completo: `soluzioni/es07_parcheggio.c`.
</details>

### es08 — Spese da file: struct, vettore dinamico, categorie e report  ·  Tipo esame
**Fonte:** Ispirato a: Dispensa Stream (`fopen` con `"r"` e `"w"`, valore di ritorno di `fscanf`, `rewind`, `fprintf`, `fgets`, `fclose`); Appunti Unità 4, par. 1.6 (`calloc`), 1.11 (funzioni che restituiscono vettori dinamici: "è responsabilità della funzione chiamante liberare la memoria"); Appunti Unità 3, par. 5.7 (vettori di struct); Appunti Unità 4, par. 5.6 (ricerca lineare). Diverso da cartella 11 es07/es08: qui il vettore ha la misura esatta grazie alla doppia lettura con `rewind`.
**Ripassa:** cartelle 06, 10, 11, 12
**Tempo indicativo:** 45 minuti
**Testo:** dallo standard input arriva il nome di un file. Ogni riga del file è una spesa: `GG/MM categoria importo`. La lettura si ferma alla prima riga non valida. Completa:
- `conta_spese(fp)`: quante righe valide;
- `carica_spese(nome, &n)`: apre il file (se non si apre → `NULL` e n = −1), conta, `rewind`, `calloc` della misura **esatta**, seconda lettura, chiusura; con 0 spese → `NULL` e n = 0;
- `indice_massima`, `raggruppa` (categorie nell'ordine di prima comparsa) e `scrivi_report` (una riga per categoria nel file `report.txt`).
Il main stampa totale, media e spesa più alta, poi rilegge `report.txt` e lo stampa.
```text
input:
spese.txt
contenuto di tests/fixtures/spese.txt:
03/01 cibo 12.50
05/01 trasporti 35.00
07/01 cibo 27.90
12/01 casa 45.00
15/01 svago 18.40
20/01 cibo 9.60
output:
spese lette: 6
totale: 148.40 euro, media: 24.73 euro
spesa piu' alta: 45.00 euro il 12/01 (casa)
--- report.txt ---
cibo: 50.00 euro (33.7%), spese: 3
trasporti: 35.00 euro (23.6%), spese: 1
casa: 45.00 euro (30.3%), spese: 1
svago: 18.40 euro (12.4%), spese: 1
```
Casi di test: questo; file con una spesa sola (100.0%); file vuoto; file inesistente; file con una riga rotta a metà (`02/03 cibo dieci`: si leggono solo le righe prima).
**File:** `es08_spese_file.c` · **Test:** `make test T=15 E=es08` (i file da leggere sono in `tests/fixtures/`)

<details><summary>💡 Suggerimento</summary>
`fscanf(fp, "%d/%d %19s %lf", ...)` restituisce 4 solo se ha letto la riga intera: usalo come condizione del `while`. Dopo il conteggio il file è "in fondo": `rewind(fp)` lo riporta all'inizio. In `raggruppa`, dopo il ciclo di ricerca, `k == nc` vuol dire "non trovata".
</details>

<details><summary>✅ Soluzione spiegata passo passo</summary>

1. **Perché due letture.** Per allocare un vettore della misura esatta devo sapere quante spese ci sono, ma lo so solo dopo aver letto il file. Soluzione: una prima lettura che **conta** e basta, `rewind` per tornare all'inizio, `calloc(n, sizeof(Spesa))`, seconda lettura che **riempie**. È l'alternativa alla `realloc` di es01: più letture del file, ma una sola allocazione.
2. **Il valore di ritorno di `fscanf`.** È il numero di campi assegnati (Dispensa Stream). Con `02/03 cibo dieci` assegna 3 campi e il conteggio si ferma; a fine file restituisce `EOF`. In entrambi i casi `!= 4` chiude il ciclo.
   ```c
   while (fscanf(fp, "%d/%d %19s %lf", &s.giorno, &s.mese, s.categoria, &s.importo) == 4)
       n++;
   ```
   `%19s` perché `categoria` ha 20 posti (19 caratteri + `'\0'`); `%lf` perché `importo` è `double` (con `%f` si leggerebbe un `float`, e il valore sarebbe sbagliato).
3. **Tre esiti distinti con un solo puntatore.** `carica_spese` restituisce il vettore e usa `*n` per distinguere "file non apribile" (−1) da "file vuoto" (0). Il chiamante controlla `n`, non solo il puntatore. Con n = 0 evito `calloc(0, ...)`, il cui risultato dipende dalla libreria (può essere `NULL` o un blocco da non usare).
4. **La memoria sopravvive alla funzione.** `v` vive nello heap, non nel record di attivazione di `carica_spese`, quindi resta valido dopo il `return` (Appunti Unità 4, par. 1.11). La `free` la fa il main.
5. **Raggruppare.** Per ogni spesa una ricerca lineare tra le categorie già viste (`strcmp`); se non c'è, la aggiungo in fondo con `strcpy`.
   ```c
   for (k = 0; k < nc; k++)
       if (strcmp(c[k].nome, v[i].categoria) == 0) break;
   if (k == nc) { /* nuova */ strcpy(c[nc].nome, v[i].categoria); c[nc].quante = 0; c[nc].totale = 0.0; nc++; }
   c[k].quante++;
   c[k].totale += v[i].importo;
   ```
6. **Scrivere e rileggere.** `fopen("report.txt", "w")` crea il file (o lo svuota). In `fprintf` il carattere `%` si scrive `%%`. `fclose` è necessario **prima** di rileggerlo: svuota il buffer di scrittura sul disco (Dispensa Stream, "Buffering"). Il main rilegge con `fgets`, che tiene il `'\n'` di ogni riga: per questo stampa con `printf("%s", riga)` senza aggiungere `\n`.

Verifica a mano: totale 12.50 + 35.00 + 27.90 + 45.00 + 18.40 + 9.60 = 148.40; media 148.40 / 6 = 24.733 → 24.73; cibo 12.50 + 27.90 + 9.60 = 50.00, che è il 33.69 % → 33.7.

| fase | posizione nel file | n | v |
|---|---|---|---|
| dopo `fopen` | inizio | – | – |
| dopo `conta_spese` | fine | 6 | – |
| dopo `rewind` | inizio | 6 | – |
| dopo `calloc` | inizio | 6 | 6 struct azzerate |
| dopo la seconda lettura | fine | 6 | 6 spese |

Codice completo: `soluzioni/es08_spese_file.c`.
</details>

## Prompt pronti per questo argomento
1. "Sono uno studente di Programmazione e Algoritmi I (C, prof. Anisetti, UniMi). Ho svolto l'esercizio esNN della simulazione d'esame: [incolla testo e codice]. Correggilo come all'esame: dammi un voto in trentesimi, elenca gli errori (correttezza, memoria, stile) con la riga, e dimmi quali argomenti devo ripassare. Non riscrivermi il codice."
2. "Generami una nuova simulazione d'esame di C con 3 esercizi da svolgere in 2 ore, ognuno che combina almeno tre argomenti tra: struct, memoria dinamica, file, stringhe, ricorsione, puntatori a funzione, static, matrici. Per ognuno dammi testo, esempio di input/output e 3 casi di test, senza soluzione."
3. "Interrogami come all'orale su questi 20 punti, uno alla volta, partendo dai più difficili: [incolla la Checklist pre-esame]. Se rispondo male spiegami il perché con un esempio di codice di massimo 10 righe."
4. "Scrivimi un 'Cosa stampa?' in C come es06 della simulazione (puntatori, static, ricorsione, macro), di massimo 40 righe, senza comportamento indefinito. Aspetta la mia previsione prima di darmi l'output e la spiegazione riga per riga."
5. "Scrivimi un programma C di circa 60 righe con 4 errori nascosti di tipo diverso (uno di memoria, uno sui puntatori, uno di logica, uno sui file o sulle stringhe), come es05 della simulazione. Dammi solo il codice e l'output atteso; le soluzioni solo quando te le chiedo."

## Riepilogo
- All'esame gli argomenti non arrivano da soli: un esercizio unisce struct, memoria dinamica, puntatori, stringhe, file, ricorsione. Quando sbagli, il campo **Ripassa** ti dice quale "mattone" ripassare.
- Le stesse regole tornano ovunque: controlla il valore di ritorno di `scanf`/`fscanf`/`fopen`/`malloc`; riserva sempre `n + 1` byte per una stringa; usa un puntatore temporaneo con `realloc`; libera la memoria nell'ordine inverso a come l'hai costruita.
- Per far modificare qualcosa a una funzione le passi il suo **indirizzo**: un `int *` per un `int`, un `Esame **` per un puntatore, un `const char **` per un cursore su una stringa.
- AddressSanitizer è il tuo correttore automatico: impara a leggere la prima riga (`heap-buffer-overflow`, `SEGV`, `heap-use-after-free`) e la riga del tuo file nello stack delle chiamate.

## Glossario
- **Simulazione d'esame** — esercizi svolti a tempo e senza aiuti, nelle condizioni dell'appello.
- **Starter** — il file di partenza con le parti `TODO` da completare.
- **Test** — confronto automatico tra l'output del tuo programma e quello atteso, su un input preparato.
- **AddressSanitizer (ASan)** — strumento del compilatore che ferma il programma a ogni accesso sbagliato alla memoria.
- **Heap** — zona di memoria dei blocchi allocati con `malloc`/`calloc`/`realloc`, che restano finché non chiami `free`.
- **realloc** — cambia la dimensione di un blocco; può spostarlo e, se fallisce, restituisce `NULL` lasciando valido il vecchio.
- **Memory leak** — memoria allocata di cui hai perso l'indirizzo: non puoi più liberarla.
- **heap-buffer-overflow** — lettura o scrittura oltre la fine di un blocco dello heap.
- **heap-use-after-free** — uso di un blocco dopo averlo liberato con `free`.
- **SEGV (segmentation violation)** — accesso a un indirizzo non valido, per esempio `NULL`.
- **Puntatore a funzione** — variabile che contiene l'indirizzo di una funzione e permette di chiamarla.
- **Tabella di dispatch** — vettore di righe (nome, funzione, ...) usato per scegliere quale funzione chiamare al posto di uno `switch`.
- **Puntatore a riga** — `int (*p)[N]`: punta a un intero vettore di N elementi; `p++` salta una riga.
- **Puntatore a puntatore** — `T **`: l'indirizzo di un puntatore; serve a una funzione per modificare il puntatore del chiamante.
- **Cursore** — puntatore che indica il punto di una stringa a cui si è arrivati a leggere.
- **Grammatica** — insieme di regole che descrivono com'è fatta una stringa valida.
- **Caso base / caso ricorsivo** — il caso risolto senza chiamate / il caso ridotto a uno più piccolo dello stesso tipo.
- **Static locale** — variabile locale che esiste per tutto il programma e ricorda il valore tra le chiamate.
- **Enum** — tipo con un insieme finito di nomi, che il C rappresenta come interi.
- **Divisione intera** — `int / int`: tronca verso zero (`-7 / 2` = −3).
- **Punto di sequenza** — punto dell'esecuzione in cui tutti gli effetti delle espressioni precedenti sono completati (per esempio dopo la condizione di `? :`).
- **rewind** — riporta all'inizio la posizione di lettura di un file aperto.
- **Off-by-one** — errore "di uno" nei limiti di un ciclo, tipico con `<=` al posto di `<`.
- **Buffer overflow** — scrittura oltre la fine di un vettore, che sovrascrive altra memoria.
