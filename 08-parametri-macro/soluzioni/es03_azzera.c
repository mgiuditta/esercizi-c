/* =====================================================================
 * es03 — Azzera i primi k elementi di un vettore  ·  Base  ·  SOLUZIONE
 * Un vettore passato a una funzione NON viene copiato: arriva l'indirizzo
 * del primo elemento, quindi la funzione modifica il vettore del main.
 * La funzione non sa quanto è lungo: la lunghezza va passata a parte.
 * Come testarlo: make sol T=08 E=es03
 * ===================================================================== */
#include <stdio.h>

#define MAXN 100

void azzera(int v[], int k);
void stampa(const char *etichetta, const int v[], int n);

int main(void) {
    int v[MAXN];
    int n, k, i;

    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) {
        printf("n non valido\n");
        return 0;
    }
    for (i = 0; i < n; i++)
        if (scanf("%d", &v[i]) != 1) {
            printf("input non valido\n");
            return 0;
        }
    if (scanf("%d", &k) != 1 || k < 0 || k > n) {   /* k > n: scriverei fuori dal vettore */
        printf("k non valido\n");
        return 0;
    }
    stampa("prima", v, n);
    azzera(v, k);          /* passo il NOME del vettore = indirizzo del primo elemento */
    stampa("dopo", v, n);  /* v è cambiato: la funzione ha lavorato sull'originale */
    return 0;
}

/* int v[] nel parametro è in realtà un puntatore (int *v): dentro la
 * funzione sizeof(v) darebbe 8 (la dimensione di un indirizzo), non la
 * dimensione del vettore. Per questo serve il parametro k. */
void azzera(int v[], int k) {
    int i;
    for (i = 0; i < k; i++)
        v[i] = 0;          /* scrivo nella memoria del vettore del main */
}

/* const: prometto di NON modificare v (il compilatore mi blocca se ci provo) */
void stampa(const char *etichetta, const int v[], int n) {
    int i;
    printf("%s:", etichetta);
    for (i = 0; i < n; i++)
        printf(" %d", v[i]);
    printf("\n");
}
