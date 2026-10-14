/*
 * es05 — Trova e correggi gli errori: elenco di parole nello heap  (Tipo esame)
 *
 * Input: n, poi n parole. Il programma copia ogni parola nello heap,
 * calcola la lunghezza media e stampa le parole lunghe ALMENO quanto la media.
 *
 * Il codice compila senza avvisi, ma contiene 4 ERRORI di tipo diverso:
 * uno sui puntatori, uno di logica e due sulla memoria dinamica.
 * Trovali, correggili e rilancia il test finche' passa.
 * Consiglio: correggi un errore alla volta e leggi il messaggio di
 * AddressSanitizer (il "sanitizer" che il test attiva): dice la riga.
 *
 * Esempio corretto:
 *   input:  4  casa lampadina re sole
 *   output: parole lette: 4
 *           media lunghezza: 4.75
 *           almeno lunghe come la media: lampadina
 *           totale: 1
 *
 * Come testarlo: make test T=15 E=es05
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPAROLA 32

/* Copia s in un blocco nuovo nello heap (una strdup fatta a mano). */
char *duplica(const char *s)
{
    char *copia = (char *) malloc(strlen(s));
    if (copia != NULL)
        strcpy(copia, s);
    return copia;
}

/* Crea un vettore di n puntatori a char, tutti a NULL, per il main. */
int crea_elenco(char **v, int n)
{
    int i;
    v = (char **) malloc((size_t) n * sizeof(char *));
    if (v == NULL)
        return 0;
    for (i = 0; i < n; i++)
        v[i] = NULL;
    return 1;
}

double lunghezza_media(char **v, int n)
{
    int i, totale = 0;
    for (i = 0; i < n; i++)
        totale += (int) strlen(v[i]);
    return totale / n;
}

void libera_elenco(char **v, int n)
{
    int i;
    free(v);
    for (i = 0; i < n; i++)
        free(v[i]);
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
    if (!crea_elenco(elenco, n))
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
        if (strlen(elenco[i]) >= media) {
            printf(" %s", elenco[i]);
            quante++;
        }
    printf("\ntotale: %d\n", quante);

    libera_elenco(elenco, n);
    return 0;
}
