/*
 * es05 — Trova e correggi gli errori: elenco di parole nello heap  (Tipo esame) — SOLUZIONE
 *
 * Input: n, poi n parole. Il programma copia ogni parola nello heap,
 * calcola la lunghezza media e stampa le parole lunghe ALMENO quanto la media.
 * Nello starter c'erano 4 errori di tipo diverso; qui sono corretti e
 * marcati con "CORRETTO".
 *
 * Come testarlo: make sol T=15 E=es05
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPAROLA 32

/* Copia s in un blocco nuovo nello heap (una strdup fatta a mano). */
char *duplica(const char *s)
{
    /* CORRETTO (errore 1, memoria): servono strlen(s) + 1 byte, perche'
     * strcpy copia anche il terminatore '\0'. */
    char *copia = (char *) malloc(strlen(s) + 1);
    if (copia != NULL)
        strcpy(copia, s);
    return copia;
}

/* Crea un vettore di n puntatori a char, tutti a NULL.
 * CORRETTO (errore 2, puntatori): la funzione deve modificare il puntatore
 * del main, quindi riceve il SUO INDIRIZZO (char ***). Prima riceveva una
 * copia (char **) e il main restava con NULL. */
int crea_elenco(char ***pv, int n)
{
    int i;
    *pv = (char **) malloc((size_t) n * sizeof(char *));
    if (*pv == NULL)
        return 0;
    for (i = 0; i < n; i++)
        (*pv)[i] = NULL;
    return 1;
}

double lunghezza_media(char **v, int n)
{
    int i, totale = 0;
    for (i = 0; i < n; i++)
        totale += (int) strlen(v[i]);
    /* CORRETTO (errore 3, logica): int / int tronca (19 / 4 = 4).
     * Il cast PRIMA della divisione la rende reale: 19.0 / 4 = 4.75. */
    return (double) totale / n;
}

void libera_elenco(char **v, int n)
{
    int i;
    /* CORRETTO (errore 4, memoria): PRIMA si liberano le parole, POI il
     * vettore che contiene i loro indirizzi. Al contrario, dopo free(v) la
     * lettura di v[i] e' un uso di memoria gia' liberata (use-after-free). */
    for (i = 0; i < n; i++)
        free(v[i]);
    free(v);
}

int main(void)
{
    char **elenco = NULL;
    char parola[MAXPAROLA];
    int n, i, quante = 0;
    double media;

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("nessuna parola\n");
        return 0;
    }
    if (!crea_elenco(&elenco, n))           /* CORRETTO: &elenco */
        return 1;

    for (i = 0; i < n; i++) {
        if (scanf("%31s", parola) != 1)
            parola[0] = '\0';               /* input troppo corto: parola vuota */
        elenco[i] = duplica(parola);
        if (elenco[i] == NULL) {
            libera_elenco(elenco, i);
            return 1;
        }
    }

    media = lunghezza_media(elenco, n);
    printf("parole lette: %d\n", n);
    printf("media lunghezza: %.2f\n", media);
    printf("almeno lunghe come la media:");
    for (i = 0; i < n; i++)
        if (strlen(elenco[i]) >= media) {   /* size_t confrontato con double: diventa double */
            printf(" %s", elenco[i]);
            quante++;
        }
    printf("\ntotale: %d\n", quante);

    libera_elenco(elenco, n);
    return 0;
}
