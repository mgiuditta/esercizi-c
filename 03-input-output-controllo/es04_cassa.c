/*
 * es04 — TROVA E CORREGGI L'ERRORE: la cassa con lo switch  (Intermedio)
 * Comandi (uno per riga):
 *   v IMPORTO   vendita: aggiunge l'importo al totale
 *   r IMPORTO   reso: toglie l'importo dal totale
 *   s oppure S  stampa il totale corrente
 *   q           chiude la cassa (sentinella)
 * Qualunque altro carattere: "Comando sconosciuto: X".
 * Il programma compila ma da' risultati sbagliati: trova e correggi gli errori.
 * (Suggerimento: leggi bene i warning del compilatore.)
 * Come testarlo: make test T=03 E=es04
 */
#include <stdio.h>

int main(void) {
    char cmd;
    double imp = 0.0;
    double totale = 0.0;
    int vendite = 0, resi = 0;

    while (scanf(" %c", &cmd) == 1 && cmd != 'q') {
        if (cmd == 'v' || cmd == 'r') {
            if (scanf("%lf", &imp) != 1) {
                printf("Importo mancante\n");
                break;
            }
        }

        switch (cmd) {
        case 'v':
            totale += imp;
            vendite++;
        case 'r':
            totale -= imp;
            resi++;
            break;
        case 's':
        case 'S':
            printf("Totale: %.2f (vendite: %d, resi: %d)\n", totale, vendite, resi);
        default:
            printf("Comando sconosciuto: %c\n", cmd);
        }
    }

    printf("Cassa chiusa. Totale finale: %.2f\n", totale);
    return 0;
}
