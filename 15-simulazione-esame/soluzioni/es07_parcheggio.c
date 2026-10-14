/*
 * es07 — Parcheggio: enum, switch, struct e menu'  (Tipo esame) — SOLUZIONE
 *
 * Un parcheggio ha N_POSTI posti. Comandi da stdin (uno per riga):
 *   1 T TARGA HH:MM   entrata: T = A (auto), M (moto), F (furgone)
 *   2 TARGA HH:MM     uscita: calcola e incassa il costo
 *   3                 stampa lo stato dei posti
 *   0                 fine: stampa l'incasso totale (anche a fine input)
 * Tariffe orarie in centesimi: auto 200, moto 100, furgone 350.
 * Ogni ora iniziata si paga intera (minimo 1 ora); dalla quarta ora in poi
 * ogni ora costa la meta'.
 *
 * Come testarlo: make sol T=15 E=es07
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

/* Converte il carattere letto nell'enum. Ritorna 1 se valido, 0 se no.
 * Il risultato esce dal parametro puntatore perche' il return dice "valido o no". */
int tipo_da_carattere(char c, TipoVeicolo *t)
{
    switch (c) {
    case 'A': *t = AUTO;    return 1;   /* il return esce dalla funzione: niente break */
    case 'M': *t = MOTO;    return 1;
    case 'F': *t = FURGONE; return 1;
    default:  return 0;
    }
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
    switch (t) {
    case AUTO:    return 200;
    case MOTO:    return 100;
    case FURGONE: return 350;
    }
    return 0;
}

/* Costo in centesimi per una sosta di "minuti" minuti. */
int costo(TipoVeicolo t, int minuti)
{
    int ore = (minuti + 59) / 60;       /* divisione intera "per eccesso": 61 min -> 2 ore */
    int tar = tariffa_oraria(t);

    if (ore == 0)
        ore = 1;                        /* minimo un'ora */
    if (ore <= 3)
        return ore * tar;
    return 3 * tar + (ore - 3) * (tar / 2);
}

/* Cerca la targa tra i posti OCCUPATI. Ritorna l'indice o -1. */
int cerca_targa(const Posto p[], int n, const char *targa)
{
    int i;
    for (i = 0; i < n; i++)
        if (p[i].stato == OCCUPATO && strcmp(p[i].targa, targa) == 0)
            return i;
    return -1;
}

/* Parcheggia nel primo posto libero. Ritorna l'indice del posto,
 * -1 se il parcheggio e' pieno, -2 se la targa e' gia' dentro. */
int entra(Posto p[], int n, TipoVeicolo t, const char *targa, int minuti)
{
    int i;

    if (cerca_targa(p, n, targa) >= 0)
        return -2;
    for (i = 0; i < n; i++)
        if (p[i].stato == LIBERO) {
            p[i].stato = OCCUPATO;
            p[i].tipo = t;
            strcpy(p[i].targa, targa);  /* le stringhe si copiano con strcpy, non con = */
            p[i].ingresso = minuti;
            return i;
        }
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
