/*
 * es01 — Lunghezza a mano e il '\n' di fgets  (SOLUZIONE)
 *
 * Input:  una riga di testo (può contenere spazi).
 * Output: la lunghezza contata a mano PRIMA e DOPO aver tolto l'a capo
 *         che fgets lascia nella stringa, il confronto con strlen e la riga
 *         tra parentesi quadre (così si vedono eventuali spazi).
 *
 * Come testarlo: make sol T=06 E=es01
 */
#include <stdio.h>
#include <string.h>

#define DIM 100

/* Conta i caratteri prima del terminatore '\0'.
 * Funziona perché OGNI stringa C finisce con '\0': è l'unico modo
 * che abbiamo per sapere dove finisce (il vettore può essere più lungo). */
int mia_strlen(char s[])
{
    int i = 0;
    while (s[i] != '\0')   /* ci fermiamo SUL terminatore, senza contarlo */
        i++;
    return i;              /* i = indice del '\0' = numero di caratteri prima */
}

/* fgets mette nella stringa anche il '\n' (il tasto Invio), se c'è.
 * Lo sostituiamo con '\0': così la stringa "finisce un carattere prima". */
void togli_a_capo(char s[])
{
    int n = mia_strlen(s);
    /* n > 0: con la stringa vuota s[n-1] sarebbe s[-1], fuori dal vettore.
     * Il controllo su '\n' serve perché l'ultima riga di un file potrebbe
     * non avere l'a capo (oppure la riga era più lunga di DIM-1). */
    if (n > 0 && s[n - 1] == '\n')
        s[n - 1] = '\0';
}

int main(void)
{
    char s[DIM];

    /* fgets legge al massimo DIM-1 caratteri e aggiunge sempre '\0':
     * non può uscire dal vettore. Restituisce NULL se non c'è niente da leggere. */
    if (fgets(s, DIM, stdin) == NULL) {
        printf("nessuna riga\n");
        return 1;
    }
    printf("con a capo: %d\n", mia_strlen(s));
    togli_a_capo(s);
    printf("senza a capo: %d\n", mia_strlen(s));
    /* strlen restituisce size_t (un intero senza segno): si stampa con %zu */
    printf("strlen: %zu\n", strlen(s));
    printf("[%s]\n", s);
    return 0;
}
