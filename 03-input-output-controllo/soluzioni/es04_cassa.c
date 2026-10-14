/*
 * es04 — TROVA E CORREGGI L'ERRORE: la cassa con lo switch  (Intermedio)
 * Comandi (uno per riga):
 *   v IMPORTO   vendita: aggiunge l'importo al totale
 *   r IMPORTO   reso: toglie l'importo dal totale
 *   s oppure S  stampa il totale corrente
 *   q           chiude la cassa (sentinella)
 * Qualunque altro carattere: "Comando sconosciuto: X".
 * Questa e' la versione CORRETTA.
 * Come testarlo: make test T=03 E=es04
 */
#include <stdio.h>

int main(void) {
    char cmd;
    double imp = 0.0;
    double totale = 0.0;
    int vendite = 0, resi = 0;

    /* Ciclo con sentinella: si continua finche' scanf legge un comando
       (== 1) E il comando non e' 'q'. Se l'input finisce (EOF) si esce lo stesso. */
    while (scanf(" %c", &cmd) == 1 && cmd != 'q') {
        /* Solo v e r sono seguiti da un importo. */
        if (cmd == 'v' || cmd == 'r') {
            if (scanf("%lf", &imp) != 1) {
                printf("Importo mancante\n");
                break;              /* input rovinato: inutile continuare */
            }
        }

        switch (cmd) {
        case 'v':
            totale += imp;
            vendite++;
            break;                  /* CORREZIONE 1: senza break si "cade" nel case 'r'
                                       e la vendita viene subito annullata dal reso. */
        case 'r':
            totale -= imp;
            resi++;
            break;
        case 's':                   /* Raggruppamento LEGITTIMO: 's' e 'S' fanno la stessa cosa. */
        case 'S':
            printf("Totale: %.2f (vendite: %d, resi: %d)\n", totale, vendite, resi);
            break;                  /* CORREZIONE 2: senza break si cade nel default
                                       e dopo il totale compare "Comando sconosciuto". */
        default:
            printf("Comando sconosciuto: %c\n", cmd);
        }
    }

    printf("Cassa chiusa. Totale finale: %.2f\n", totale);
    return 0;
}
