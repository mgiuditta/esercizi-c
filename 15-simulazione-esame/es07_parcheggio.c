/*
 * es07 — Parcheggio: enum, switch, struct e menu'  (Tipo esame)
 *
 * Un parcheggio ha N_POSTI posti. Comandi da stdin (uno per riga):
 *   1 T TARGA HH:MM   entrata: T = A (auto), M (moto), F (furgone)
 *   2 TARGA HH:MM     uscita: calcola e incassa il costo
 *   3                 stampa lo stato dei posti
 *   0                 fine: stampa l'incasso totale (anche a fine input)
 * Il main (gia' scritto) gestisce il menu' con uno switch.
 *
 * Completa (con uno switch dove ha senso):
 *   - tipo_da_carattere: 'A' -> AUTO, 'M' -> MOTO, 'F' -> FURGONE, mette il
 *     risultato in *t e ritorna 1; per ogni altro carattere ritorna 0.
 *   - tariffa_oraria: centesimi all'ora: auto 200, moto 100, furgone 350.
 *   - costo: ogni ora iniziata si paga intera (minimo 1 ora); dalla quarta
 *     ora in poi ogni ora costa la meta' della tariffa. Risultato in centesimi.
 *     Esempio: furgone per 350 minuti = 6 ore = 3*350 + 3*175 = 1575.
 *   - cerca_targa: indice del posto OCCUPATO con quella targa, -1 se non c'e'.
 *   - entra: -2 se la targa e' gia' dentro, -1 se e' tutto pieno, altrimenti
 *     occupa il PRIMO posto libero e ritorna il suo indice.
 *
 * Come testarlo: make test T=15 E=es07
 */
#include <stdio.h>
#include <string.h>

#define N_POSTI 3
#define MAXTARGA 8                      /* 7 caratteri + '\0' */

typedef enum { AUTO, MOTO, FURGONE } TipoVeicolo;
typedef enum { LIBERO, OCCUPATO } StatoPosto;
typedef enum { FINE, ENTRATA, USCITA, STATO } Comando;

typedef struct {
    StatoPosto stato;
    TipoVeicolo tipo;
    char targa[MAXTARGA];
    int ingresso;                       /* minuti dalla mezzanotte: 08:30 -> 510 */
} Posto;

int tipo_da_carattere(char c, TipoVeicolo *t)
{
    /* TODO: switch (c) { case 'A': ... default: ... } */
    (void)c; (void)t;
    return 0;
}

const char *nome_tipo(TipoVeicolo t)
{
    switch (t) {
    case AUTO:    return "auto";
    case MOTO:    return "moto";
    case FURGONE: return "furgone";
    }
    return "?";                         /* non ci si arriva, ma il compilatore vuole un return */
}

int tariffa_oraria(TipoVeicolo t)
{
    /* TODO: switch (t) */
    (void)t;
    return 0;
}

int costo(TipoVeicolo t, int minuti)
{
    /* TODO: ore "per eccesso" con la sola divisione intera, minimo 1 */
    (void)t; (void)minuti;
    return 0;
}

int cerca_targa(const Posto p[], int n, const char *targa)
{
    /* TODO: confronta le stringhe con strcmp, solo sui posti OCCUPATI */
    (void)p; (void)n; (void)targa;
    return -1;
}

int entra(Posto p[], int n, TipoVeicolo t, const char *targa, int minuti)
{
    /* TODO: usa cerca_targa; la targa si copia con strcpy */
    (void)p; (void)n; (void)t; (void)targa; (void)minuti;
    return -1;
}

int main(void)
{
    Posto posti[N_POSTI];
    int cmd, hh, mm, i, minuti, durata, c, incasso = 0, usciti = 0;
    char tc, targa[MAXTARGA];
    TipoVeicolo t;

    for (i = 0; i < N_POSTI; i++)
        posti[i].stato = LIBERO;

    while (scanf("%d", &cmd) == 1 && cmd != FINE) {
        switch (cmd) {                 /* le costanti enum sono int: vanno bene come case */
        case ENTRATA:
            /* " %c": lo spazio salta gli spazi bianchi prima del carattere */
            if (scanf(" %c %7s %d:%d", &tc, targa, &hh, &mm) != 4)
                return 1;
            if (!tipo_da_carattere(tc, &t)) {
                printf("tipo non valido: %c\n", tc);
                break;
            }
            i = entra(posti, N_POSTI, t, targa, hh * 60 + mm);
            if (i == -1)
                printf("pieno: %s non entra\n", targa);
            else if (i == -2)
                printf("targa gia' presente: %s\n", targa);
            else
                printf("entrata %s (%s): posto %d\n", targa, nome_tipo(t), i);
            break;

        case USCITA:
            if (scanf("%7s %d:%d", targa, &hh, &mm) != 3)
                return 1;
            i = cerca_targa(posti, N_POSTI, targa);
            if (i < 0) {
                printf("targa non trovata: %s\n", targa);
                break;
            }
            minuti = hh * 60 + mm;
            durata = minuti - posti[i].ingresso;
            if (durata < 0) {
                printf("orario non valido per %s\n", targa);
                break;
            }
            c = costo(posti[i].tipo, durata);
            incasso += c;
            usciti++;
            posti[i].stato = LIBERO;
            printf("uscita %s: posto %d, %d min, %d.%02d euro\n",
                   targa, i, durata, c / 100, c % 100);
            break;

        case STATO:
            for (i = 0; i < N_POSTI; i++) {
                if (posti[i].stato == LIBERO)
                    printf("posto %d: libero\n", i);
                else
                    printf("posto %d: %s %s dalle %02d:%02d\n", i,
                           nome_tipo(posti[i].tipo), posti[i].targa,
                           posti[i].ingresso / 60, posti[i].ingresso % 60);
            }
            break;

        default:
            printf("comando non valido: %d\n", cmd);
            break;
        }
    }
    printf("incasso: %d.%02d euro, veicoli usciti: %d\n", incasso / 100, incasso % 100, usciti);
    return 0;
}
