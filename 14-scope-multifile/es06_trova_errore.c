/*
 * es06 — Trova e correggi l'errore: static e scope  ·  Intermedio
 * Ispirato a: Trascrizione 4.4 (static locale inizializzata una sola volta), Trascrizione 3.1
 * (variabile globale modificata da una funzione), LEZ 21 par. 5.8.
 *
 * Una cassa registra gli incassi. Ci sono TRE errori, tutti legati a static e scope.
 * Output corretto con input 100 150 120:
 *   ricevuta 1: importo 100, variazione +100
 *   ricevuta 2: importo 150, variazione +50
 *   ricevuta 3: importo 120, variazione -30
 *   totale vendite: 370
 * Indizio: compila a mano con  cc -Wall -Wshadow es06_trova_errore.c  e leggi il warning.
 *
 * Come testarlo: make test T=14 E=es06
 */
#include <stdio.h>

int totale_vendite = 0;

/* Numero di ricevuta progressivo: 1, 2, 3, ... */
int nuova_ricevuta(void)
{
    static int numero;
    numero = 0;
    numero++;
    return numero;
}

/* Aggiunge un incasso al totale globale. */
void registra(int importo)
{
    int totale_vendite = 0;
    totale_vendite += importo;
}

/* Variazione rispetto all'incasso precedente (il primo si confronta con 0). */
int variazione(int importo)
{
    int precedente = 0;
    int diff = importo - precedente;
    precedente = importo;
    return diff;
}

int main(void)
{
    int importo, r;

    while (scanf("%d", &importo) == 1) {
        r = nuova_ricevuta();
        registra(importo);
        printf("ricevuta %d: importo %d, variazione %+d\n", r, importo, variazione(importo));
    }
    printf("totale vendite: %d\n", totale_vendite);
    return 0;
}
