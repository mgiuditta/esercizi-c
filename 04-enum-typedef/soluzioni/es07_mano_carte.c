/*
 * es07 — Punteggio di una mano di carte  (Tipo esame)
 * Legge carte fino a fine input, nel formato VALORE SEME (es. "1 C", "13 p"):
 *   valore 1..13, seme P/C/Q/F (picche, cuori, quadri, fiori), maiuscolo o minuscolo.
 * Punti: asso(1)=11, tre=10, re(13)=4, regina(12)=3, fante(11)=2, le altre 0.
 * Stampa le carte non valide, una tabella per seme e il seme con piu' punti.
 * Come testarlo: make test T=04 E=es07
 */
#include <stdio.h>

/* Un valore negativo "sentinella" per i semi sbagliati: con un valore negativo
   l'enum diventa un tipo CON segno (come "intero" nell'esempio del prof),
   quindi possiamo fare confronti e cicli senza sorprese da unsigned. */
typedef enum {SEME_NON_VALIDO = -1, PICCHE, CUORI, QUADRI, FIORI} seme;

seme seme_da_char(char c) {
    switch (c) {
    case 'P': case 'p': return PICCHE;
    case 'C': case 'c': return CUORI;
    case 'Q': case 'q': return QUADRI;
    case 'F': case 'f': return FIORI;
    default:            return SEME_NON_VALIDO;
    }
}

/* const char * = un testo costante (lo vedremo con le stringhe). */
const char *nome_seme(seme s) {
    switch (s) {
    case PICCHE: return "PICCHE";
    case CUORI:  return "CUORI";
    case QUADRI: return "QUADRI";
    case FIORI:  return "FIORI";
    default:     return "?";
    }
}

int punti_carta(int valore) {
    switch (valore) {
    case 1:  return 11;
    case 3:  return 10;
    case 13: return 4;
    case 12: return 3;
    case 11: return 2;
    default: return 0;   /* 2, 4..10: nessun punto */
    }
}

int main(void) {
    /* Senza vettori (arrivano nella lezione 2.5) servono 8 contatori. */
    int carte_p = 0, carte_c = 0, carte_q = 0, carte_f = 0;
    int punti_p = 0, punti_c = 0, punti_q = 0, punti_f = 0;
    int valide = 0;
    int v;
    char ch;

    /* " %c": lo spazio salta spazi e a capo prima della lettera del seme. */
    while (scanf("%d %c", &v, &ch) == 2) {
        seme s = seme_da_char(ch);
        if (s == SEME_NON_VALIDO || v < 1 || v > 13) {
            printf("Carta non valida: %d %c\n", v, ch);
            continue;
        }
        int p = punti_carta(v);
        valide++;
        switch (s) {                /* lo switch smista sul contatore giusto */
        case PICCHE: carte_p++; punti_p += p; break;
        case CUORI:  carte_c++; punti_c += p; break;
        case QUADRI: carte_q++; punti_q += p; break;
        case FIORI:  carte_f++; punti_f += p; break;
        default: break;             /* SEME_NON_VALIDO: gia' escluso sopra */
        }
    }

    if (valide == 0) {
        printf("Nessuna carta valida\n");
        return 0;
    }

    seme migliore = SEME_NON_VALIDO;
    int max_punti = -1;
    int totale = 0;
    /* Ciclo sull'enum: funziona perche' i valori sono interi CONSECUTIVI. */
    for (seme s = PICCHE; s <= FIORI; s++) {
        int carte = 0, punti = 0;
        switch (s) {
        case PICCHE: carte = carte_p; punti = punti_p; break;
        case CUORI:  carte = carte_c; punti = punti_c; break;
        case QUADRI: carte = carte_q; punti = punti_q; break;
        case FIORI:  carte = carte_f; punti = punti_f; break;
        default: break;
        }
        printf("%-7s carte=%d punti=%d\n", nome_seme(s), carte, punti);
        totale += punti;
        if (punti > max_punti) {    /* > e non >=: a parita' vince il primo seme */
            max_punti = punti;
            migliore = s;
        }
    }
    printf("Totale: %d punti in %d carte\n", totale, valide);
    printf("Seme migliore: %s (%d punti)\n", nome_seme(migliore), max_punti);
    return 0;
}
