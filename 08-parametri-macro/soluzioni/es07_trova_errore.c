/* =====================================================================
 * es07 — Trova e correggi l'errore: statistiche di un appello
 * Tipo esame  ·  SOLUZIONE
 * Legge n voti (0 = assente) e stampa presenti, promossi (voto >= 18),
 * voto massimo e media dei presenti. I 3 bug dello starter sono
 * segnalati con "BUG n" nei commenti.
 * Come testarlo: make sol T=08 E=es07
 * ===================================================================== */
#include <stdio.h>

#define MAXN 50
/* BUG 1 (macro): era  #define MEDIA(tot, n) (double)tot / n
 * Con MEDIA(somma, n - assenti) diventava (double)somma / n - assenti,
 * cioè (somma / n) - assenti per la precedenza degli operatori.
 * Corretto: parentesi intorno a OGNI parametro e a tutta l'espressione. */
#define MEDIA(tot, n) ((double)(tot) / (n))

int promossi = 0;    /* globale: la riempie conta_promossi */

void conta_promossi(const int v[], int n);
void trova_max(const int v[], int n, int *max);

int main(void) {
    int v[MAXN];
    int n, i, m, somma = 0, assenti = 0;

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
    /* BUG 3 (parametro): era trova_max(v, n, m) con "int max" per valore:
     * la funzione calcolava il massimo nella sua copia e m restava 0.
     * Corretto: passo l'indirizzo di m. */
    trova_max(v, n, &m);

    printf("presenti: %d\n", n - assenti);
    printf("promossi: %d\n", promossi);
    printf("voto massimo: %d\n", m);
    if (n - assenti > 0)
        printf("media dei presenti: %.2f\n", MEDIA(somma, n - assenti));
    else
        printf("media dei presenti: nessuno\n");   /* evito la divisione per 0 */
    return 0;
}

void conta_promossi(const int v[], int n) {
    int i;
    /* BUG 2 (shadowing): qui c'era "int promossi = 0;". Quella locale
     * faceva ombra alla globale: il conteggio finiva nella locale, che
     * moriva al return. gcc 13 non dice nulla; clang può segnalare
     * "variable 'promossi' set but not used". Corretto: niente
     * dichiarazione, azzero la GLOBALE. */
    promossi = 0;
    for (i = 0; i < n; i++)
        if (v[i] >= 18)
            promossi++;
}

void trova_max(const int v[], int n, int *max) {
    int i;
    *max = v[0];
    for (i = 1; i < n; i++)
        if (v[i] > *max)
            *max = v[i];
}
