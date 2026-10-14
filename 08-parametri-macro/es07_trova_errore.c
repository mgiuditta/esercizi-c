/* =====================================================================
 * es07 — Trova e correggi l'errore: statistiche di un appello  ·  Tipo esame
 * Il programma legge n voti (0 = studente assente) e deve stampare:
 *   presenti: ...          (voti diversi da 0)
 *   promossi: ...          (voti >= 18)
 *   voto massimo: ...
 *   media dei presenti: ... (con %.2f, oppure "nessuno" se 0 presenti)
 * Esempio con input "6" e "25 0 30 15 0 29":
 *   presenti: 4
 *   promossi: 3
 *   voto massimo: 30
 *   media dei presenti: 24.75
 * Ci sono 3 errori: uno in una macro, uno di scope, uno di passaggio dei
 * parametri. gcc non segnala nulla; clang (macOS) potrebbe avvisarti
 * con "variable 'promossi' set but not used": se lo fa, è un indizio.
 * Come testarlo: make test T=08 E=es07
 * ===================================================================== */
#include <stdio.h>

#define MAXN 50
#define MEDIA(tot, n) (double)tot / n

int promossi = 0;

void conta_promossi(const int v[], int n);
void trova_max(const int v[], int n, int max);

int main(void) {
    int v[MAXN];
    int n, i, m = 0, somma = 0, assenti = 0;

    if (scanf("%d", &n) != 1 || n < 1 || n > MAXN) {
        printf("n non valido\n");
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (scanf("%d", &v[i]) != 1) {
            printf("input non valido\n");
            return 0;
        }
        if (v[i] == 0)
            assenti++;
        else
            somma += v[i];
    }

    conta_promossi(v, n);
    trova_max(v, n, m);

    printf("presenti: %d\n", n - assenti);
    printf("promossi: %d\n", promossi);
    printf("voto massimo: %d\n", m);
    if (n - assenti > 0)
        printf("media dei presenti: %.2f\n", MEDIA(somma, n - assenti));
    else
        printf("media dei presenti: nessuno\n");
    return 0;
}

void conta_promossi(const int v[], int n) {
    int i;
    int promossi = 0;
    for (i = 0; i < n; i++)
        if (v[i] >= 18)
            promossi++;
}

void trova_max(const int v[], int n, int max) {
    int i;
    max = v[0];
    for (i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];
}
