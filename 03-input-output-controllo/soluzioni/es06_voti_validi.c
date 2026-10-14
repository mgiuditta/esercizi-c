/*
 * es06 — Validazione dell'input con do-while  (Intermedio)
 * La funzione leggi_voto() chiede un voto finche' non ne arriva uno valido
 * (intero fra 18 e 30). Scarta l'input non numerico. Restituisce -1 se l'input finisce.
 * Il main legge 3 voti e stampa la media con 2 decimali.
 * Come testarlo: make test T=03 E=es06
 */
#include <stdio.h>

/* Restituisce un voto valido (18..30), oppure -1 se l'input e' finito (EOF). */
int leggi_voto(void) {
    int v = 0;
    int valido = 0;     /* "flag": 0 = falso, 1 = vero (in C non c'e' un bool di base) */

    /* do-while: il corpo va eseguito ALMENO una volta (devo leggere prima di
       poter controllare), quindi il controllo va in fondo. */
    do {
        int r = scanf("%d", &v);
        if (r == EOF) {
            return -1;                      /* niente piu' input: inutile insistere */
        } else if (r == 0) {
            /* scanf non ha consumato i caratteri sbagliati: restano nel buffer.
               Se non li togliamo, la prossima scanf li ritrova e fallisce di nuovo
               -> ciclo infinito. Li scartiamo fino a fine riga. */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                /* corpo vuoto: ci interessa solo consumare i caratteri */
            }
            printf("Input non numerico, riprova\n");
        } else if (v < 18 || v > 30) {
            printf("Voto %d fuori intervallo (18-30), riprova\n", v);
        } else {
            valido = 1;
        }
    } while (!valido);                      /* ripeti finche' NON e' valido */

    return v;
}

int main(void) {
    int somma = 0;
    for (int i = 0; i < 3; i++) {
        int v = leggi_voto();
        if (v == -1) {
            printf("Input terminato prima di 3 voti\n");
            return 1;
        }
        somma += v;
    }
    /* somma / 3 sarebbe una divisione INTERA (73/3 = 24). Il cast a double
       forza la divisione reale (24.333...). */
    printf("Media: %.2f\n", (double)somma / 3);
    return 0;
}
