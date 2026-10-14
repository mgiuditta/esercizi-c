/*
 * es06 — Trova e correggi l'errore: la rubrica  (Intermedio)
 *
 * Testo: una Rubrica contiene un vettore di Contatto e il numero di voci n.
 * Comandi da input (fino alla fine dell'input):
 *    A nome telefono   -> aggiunge un contatto
 *    C nome            -> cerca e stampa il telefono
 * Alla fine stampa quanti contatti ci sono.
 * Questo codice compila senza avvisi, ma ha DUE errori legati alle
 * strutture: i contatti "spariscono" e la ricerca non trova mai nulla.
 * Trovali e correggili cambiando il meno possibile.
 *
 * Input:  A mario 3331112222 / A anna 3204445555 / C anna / C luca
 * Output: anna: 3204445555
 *         luca: non trovato
 *         contatti: 2
 *
 * Come testarlo: make test T=10 E=es06
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

int aggiungi(Rubrica r, const char *nome, const char *tel)
{
    if (r.n == MAX)
        return 0;
    strcpy(r.voci[r.n].nome, nome);
    strcpy(r.voci[r.n].telefono, tel);
    r.n++;
    return 1;
}

const char *cerca(const Rubrica *r, const char *nome)
{
    int i;
    for (i = 0; i < r->n; i++)
        if (r->voci[i].nome == nome)
            return r->voci[i].telefono;
    return NULL;
}

int main(void)
{
    Rubrica rub;
    char cmd;
    char nome[20], tel[16];
    const char *t;

    rub.n = 0;

    while (scanf(" %c", &cmd) == 1) {
        if (cmd == 'A') {
            if (scanf("%19s %15s", nome, tel) != 2)
                break;
            if (!aggiungi(rub, nome, tel))
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
