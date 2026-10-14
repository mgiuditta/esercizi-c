/*
 * Esercizio 04 — Ordinare un vettore di stringhe scambiando i puntatori  (Intermedio)
 *
 * Le parole lette restano FERME nel vettore "testo". Il vettore di puntatori
 * "nomi" (char *nomi[]) contiene gli indirizzi delle parole. Per ordinarle in
 * ordine alfabetico si scambiano SOLO i puntatori, mai i caratteri
 * (Appunti Unita' 4, cap. 3.2 "Array di stringhe").
 *
 * Completa:
 *   - scambia(char **a, char **b): scambia i due puntatori a stringa
 *   - ordina(char **v, int n): ordinamento a selezione con strcmp
 *
 * Input: n (0..20), poi n parole (max 30 caratteri ciascuna).
 * Output: le parole ordinate, poi le parole nell'ordine originale
 *         (per dimostrare che i caratteri non si sono mossi).
 *
 * Come testarlo: make test T=11 E=es04
 */
#include <stdio.h>
#include <string.h>

#define MAXN 20
#define MAXL 31 /* 30 caratteri + il terminatore '\0' */

/* a e b sono "puntatori a puntatore a char": l'indirizzo di due caselle
   del vettore nomi. Ci servono per modificare le caselle del chiamante. */
void scambia(char **a, char **b)
{
    char *tmp = *a;   /* *a e' il puntatore contenuto nella prima casella */
    *a = *b;
    *b = tmp;
}

/* v punta alla prima casella del vettore di puntatori (char *nomi[] decade a char **) */
void ordina(char **v, int n)
{
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (strcmp(v[j], v[min]) < 0)   /* < 0: v[j] viene prima in ordine alfabetico */
                min = j;
        if (min != i)
            scambia(&v[i], &v[min]);        /* passo gli INDIRIZZI delle caselle */
    }
}

int main(void)
{
    char testo[MAXN][MAXL]; /* qui stanno davvero i caratteri */
    char *nomi[MAXN];       /* qui solo gli indirizzi (8 byte l'uno) */
    int n, i;

    if (scanf("%d", &n) != 1 || n < 0 || n > MAXN) {
        printf("numero non valido\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        if (scanf("%30s", testo[i]) != 1)
            return 1;
        nomi[i] = testo[i];   /* la casella i punta alla parola i */
    }

    ordina(nomi, n);

    printf("ordinate:");
    for (i = 0; i < n; i++)
        printf(" %s", nomi[i]);
    printf("\n");

    printf("originali:");
    for (i = 0; i < n; i++)
        printf(" %s", testo[i]);
    printf("\n");
    return 0;
}
