/*
 * es06 — Trova e correggi l'errore: la rubrica  (Intermedio)  — SOLUZIONE
 *
 * Testo: una Rubrica contiene un vettore di Contatto e il numero di voci n.
 * Comandi da input (fino alla fine dell'input):
 *    A nome telefono   -> aggiunge un contatto
 *    C nome            -> cerca e stampa il telefono
 * Alla fine stampa quanti contatti ci sono.
 * Lo starter ha DUE errori sulle strutture. Questa e' la versione corretta.
 *
 * Come testarlo: make sol T=10 E=es06
 */
#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char nome[20];
    char telefono[16];
} Contatto;

typedef struct {
    Contatto voci[MAX];
    int n;
} Rubrica;

/* CORRETTO (errore 1): Rubrica *r invece di Rubrica r.
 * Per valore la funzione riceveva una COPIA dell'intera rubrica (oltre 1800
 * byte!), aggiungeva il contatto alla copia e la copia spariva al return. */
int aggiungi(Rubrica *r, const char *nome, const char *tel)
{
    if (r->n == MAX)
        return 0;                          /* piena */
    strcpy(r->voci[r->n].nome, nome);      /* i campi vettore si riempiono con strcpy, */
    strcpy(r->voci[r->n].telefono, tel);   /* non con = */
    r->n++;                                /* -> lega piu' forte di ++: e' (r->n)++ */
    return 1;
}

const char *cerca(const Rubrica *r, const char *nome)
{
    int i;
    for (i = 0; i < r->n; i++)
        /* CORRETTO (errore 2): strcmp confronta i CARATTERI. Con == si
         * confrontavano due INDIRIZZI (il vettore nella rubrica e la stringa
         * letta), che sono sempre diversi: "non trovato" anche se c'era. */
        if (strcmp(r->voci[i].nome, nome) == 0)
            return r->voci[i].telefono;
    return NULL;
}

int main(void)
{
    Rubrica rub;
    char cmd;
    char nome[20], tel[16];
    const char *t;

    rub.n = 0;   /* una struct locale non e' inizializzata: azzero il contatore */

    while (scanf(" %c", &cmd) == 1) {
        if (cmd == 'A') {
            if (scanf("%19s %15s", nome, tel) != 2)
                break;
            if (!aggiungi(&rub, nome, tel))
                printf("rubrica piena\n");
        } else if (cmd == 'C') {
            if (scanf("%19s", nome) != 1)
                break;
            t = cerca(&rub, nome);
            if (t != NULL)
                printf("%s: %s\n", nome, t);
            else
                printf("%s: non trovato\n", nome);
        } else {
            printf("comando sconosciuto: %c\n", cmd);
            break;
        }
    }
    printf("contatti: %d\n", rub.n);
    return 0;
}
