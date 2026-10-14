/*
 * es05 — argc/argv e una tabella di puntatori a funzione  ·  Intermedio
 * Ispirato a: Appunti Unità 4 cap. 3 (par. 3.4 argc/argv, 3.6 atoi, 3.7 valore di ritorno,
 * 3.12 array di puntatori a funzione, 3.13 funzioni come parametri), LEZ 21 par. 3.16-3.19.
 *
 * Programma simulato:  conta <criterio> <numeri...>
 * 1) conta_se(v, n, cond): quanti elementi di v soddisfano cond (puntatore a funzione).
 * 2) esegui(argc, argv): fa ciò che farebbe main(argc, argv):
 *    - argc < 3            -> stampa "Uso: conta <criterio> <numeri...>"  e restituisce 1
 *    - criterio sconosciuto -> stampa "Criterio sconosciuto: X"            e restituisce 2
 *    - altrimenti converte i numeri con atoi e stampa "pari: 3 su 5"        e restituisce 0
 * Il main (già scritto) trasforma ogni riga di input in un finto argv.
 *
 * Come testarlo: make test T=14 E=es05
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARG 32

int pari(int x)     { return x % 2 == 0; }
int dispari(int x)  { return x % 2 != 0; }
int positivo(int x) { return x > 0; }
int primo(int x)
{
    int d;
    if (x < 2)
        return 0;
    for (d = 2; d * d <= x; d++)
        if (x % d == 0)
            return 0;
    return 1;
}

static const char *nomi_criteri[] = {"pari", "dispari", "positivi", "primi"};
static int (*criteri[])(int) = {pari, dispari, positivo, primo};
#define N_CRITERI 4

int conta_se(const int v[], int n, int (*cond)(int))
{
    /* TODO: scorri v e conta gli elementi per cui cond(v[i]) è vero */
    (void)v;
    (void)n;
    (void)cond;
    return 0;
}

int esegui(int argc, char *argv[])
{
    /* TODO: controlla argc, cerca argv[1] in nomi_criteri con strcmp,
       converti argv[2..argc-1] con atoi in un vettore, chiama conta_se con criteri[k] */
    (void)argc;
    (void)argv;
    (void)nomi_criteri;
    (void)criteri;
    return 0;
}

int main(void)
{
    char riga[512];
    char *argv[MAX_ARG + 2];
    int argc;
    char *parola;

    while (fgets(riga, sizeof riga, stdin) != NULL) {
        riga[strcspn(riga, "\n")] = '\0';
        printf("> conta %s\n", riga);
        argc = 0;
        argv[argc++] = "conta";
        parola = strtok(riga, " ");
        while (parola != NULL && argc < MAX_ARG + 1) {
            argv[argc++] = parola;
            parola = strtok(NULL, " ");
        }
        argv[argc] = NULL;
        printf("codice di uscita: %d\n", esegui(argc, argv));
    }
    return 0;
}
