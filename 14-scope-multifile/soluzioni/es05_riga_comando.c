/*
 * es05 — argc/argv e una tabella di puntatori a funzione  (SOLUZIONE)
 * Ispirato a: Appunti Unità 4 cap. 3 (par. 3.4 argc/argv, 3.6 atoi, 3.7 valore di ritorno,
 * 3.12 array di puntatori a funzione, 3.13 funzioni come parametri), LEZ 21 par. 3.16-3.19.
 *
 * Il programma simulato si chiama "conta":  conta <criterio> <numeri...>
 * e stampa quanti numeri soddisfano il criterio.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ARG 32

/* ---- I criteri: tutte con la STESSA firma  int nome(int)  ---- */
int pari(int x)     { return x % 2 == 0; }
int dispari(int x)  { return x % 2 != 0; }
int positivo(int x) { return x > 0; }
int primo(int x)
{
    int d;
    if (x < 2)
        return 0;
    for (d = 2; d * d <= x; d++)   /* basta provare i divisori fino alla radice di x */
        if (x % d == 0)
            return 0;
    return 1;
}

/* Tabella: nomi e funzioni nella stessa posizione (come fun_ptr_arr degli Appunti).
 * static: servono solo in questo file. */
static const char *nomi_criteri[] = {"pari", "dispari", "positivi", "primi"};
static int (*criteri[])(int) = {pari, dispari, positivo, primo};   /* vettore di puntatori a funzione */
#define N_CRITERI 4

/* Conta gli elementi di v che soddisfano cond.
 * cond è un PUNTATORE A FUNZIONE: chi chiama decide QUALE controllo fare. */
int conta_se(const int v[], int n, int (*cond)(int))
{
    int i, c = 0;
    for (i = 0; i < n; i++)
        if (cond(v[i]))        /* chiamata tramite puntatore (equivale a (*cond)(v[i])) */
            c++;
    return c;
}

/* Fa il lavoro che in un programma vero farebbe main(argc, argv).
 * argv[0] = nome del programma, argv[1] = criterio, argv[2..argc-1] = numeri (come STRINGHE). */
int esegui(int argc, char *argv[])
{
    int v[MAX_ARG], n, i, k;

    if (argc < 3) {                         /* controllo argc PRIMA di toccare argv[1] e argv[2] */
        printf("Uso: %s <criterio> <numeri...>\n", argv[0]);
        return 1;                           /* valore di ritorno != 0: "qualcosa è andato storto" */
    }
    for (k = 0; k < N_CRITERI; k++)         /* cerco il nome del criterio nella tabella */
        if (strcmp(argv[1], nomi_criteri[k]) == 0)
            break;
    if (k == N_CRITERI) {
        printf("Criterio sconosciuto: %s\n", argv[1]);
        return 2;
    }
    n = argc - 2;                           /* quanti numeri ci sono dopo il criterio */
    for (i = 0; i < n; i++)
        v[i] = atoi(argv[i + 2]);           /* "42" (stringa) -> 42 (int) */
    printf("%s: %d su %d\n", argv[1], conta_se(v, n, criteri[k]), n);
    return 0;                               /* 0 = tutto bene (EXIT_SUCCESS) */
}

/* main GIÀ SCRITTO: il runner dei test non può passare argomenti al programma,
 * quindi ogni riga di input viene trasformata in un finto argv. */
int main(void)
{
    char riga[512];
    char *argv[MAX_ARG + 2];
    int argc;
    char *parola;

    while (fgets(riga, sizeof riga, stdin) != NULL) {
        riga[strcspn(riga, "\n")] = '\0';        /* tolgo l'a capo finale */
        printf("> conta %s\n", riga);
        argc = 0;
        argv[argc++] = "conta";                  /* argv[0]: il nome del programma */
        parola = strtok(riga, " ");              /* spezzo la riga sugli spazi */
        while (parola != NULL && argc < MAX_ARG + 1) {
            argv[argc++] = parola;
            parola = strtok(NULL, " ");
        }
        argv[argc] = NULL;                       /* come nel vero argv: argv[argc] vale NULL */
        printf("codice di uscita: %d\n", esegui(argc, argv));
    }
    return 0;
}
