/*
 * es02 — Leggere una data con scanf e controllarne il valore di ritorno  (Base)
 * Legge una data nel formato gg/mm/aaaa con scanf("%2d/%2d/%4d", ...)
 * (esempio del prof negli Appunti Unita' 2, par. 2.6) e la ristampa come gg-mm-aaaa.
 * Come testarlo: make test T=03 E=es02
 */
#include <stdio.h>

int main(void) {
    int giorno, mese, anno;

    /* scanf restituisce QUANTE variabili e' riuscita a riempire,
       oppure EOF (un numero negativo) se l'input e' finito prima di leggere qualcosa.
       Le / nella stringa di formato devono comparire IDENTICHE nell'input. */
    int letti = scanf("%2d/%2d/%4d", &giorno, &mese, &anno);

    if (letti == EOF) {
        /* Nessun carattere disponibile: le variabili NON sono state toccate. */
        printf("Errore: nessun input (EOF)\n");
    } else if (letti != 3) {
        /* Lettura parziale: solo i primi 'letti' campi sono validi. */
        printf("Errore: letti %d campi su 3\n", letti);
    } else if (mese < 1 || mese > 12 || giorno < 1 || giorno > 31) {
        /* scanf controlla la FORMA, non il SIGNIFICATO: 31/13 per lei va benissimo. */
        printf("Errore: data fuori intervallo\n");
    } else {
        /* %02d = intero in almeno 2 colonne, riempite con 0 a sinistra (6 -> 06). */
        printf("Data: %02d-%02d-%04d\n", giorno, mese, anno);
    }
    return 0;
}
