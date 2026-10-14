/*
 * es06 — Trova e correggi l'errore: static e scope  (SOLUZIONE)
 * Ispirato a: Trascrizione 4.4 (static locale inizializzata una sola volta), Trascrizione 3.1
 * (variabile globale modificata da una funzione), LEZ 21 par. 5.8.
 */
#include <stdio.h>

int totale_vendite = 0;          /* globale: il totale di tutta la giornata */

/* Numero di ricevuta progressivo: 1, 2, 3, ... */
int nuova_ricevuta(void)
{
    static int numero = 0;       /* CORRETTO: INIZIALIZZAZIONE (avviene una volta sola).
                                    Prima c'era "numero = 0;" come ASSEGNAMENTO separato,
                                    eseguito a ogni chiamata: il contatore ripartiva sempre da 0 */
    numero++;
    return numero;
}

/* Aggiunge un incasso al totale globale. */
void registra(int importo)
{
    totale_vendite += importo;   /* CORRETTO: prima c'era "int totale_vendite = 0;" qui dentro:
                                    una variabile LOCALE con lo stesso nome nascondeva la globale */
}

/* Variazione rispetto all'incasso precedente (il primo si confronta con 0). */
int variazione(int importo)
{
    static int precedente = 0;   /* CORRETTO: serve static, altrimenti "precedente"
                                    nasce a 0 a ogni chiamata e dimentica il valore vecchio */
    int diff = importo - precedente;
    precedente = importo;        /* lo ricordo per la prossima chiamata */
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
