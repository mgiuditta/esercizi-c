/*
 * Esercizio 07 — Trova e correggi gli errori: media dei voti da file  (Tipo esame)
 *
 * Questo programma dovrebbe:
 *   1. leggere da tastiera il nome di un file di voti (interi);
 *   2. aprirlo in lettura;
 *   3. se il file non esiste, stampare "Errore: file NOME non trovato"
 *      su stdout e su stderr, e terminare con codice 1;
 *   4. altrimenti leggere tutti i voti e stampare
 *      "letti N voti, media M" (M con due decimali).
 *
 * Ci sono TRE errori sugli stream (piu' uno "di stile" che il test non vede).
 * Il programma compila senza avvisi, ma i test falliscono o crollano.
 * Trovali, correggili e spiega a te stesso PERCHE' erano errori.
 *
 * Come testarlo: make test T=11 E=es07
 */
#include <stdio.h>

int main(void)
{
    char nome[100];
    FILE *fp;
    int voto = 0, somma = 0, quanti = 0;

    if (scanf("%99s", nome) != 1)
        return 1;

    fp = fopen(nome, "w+");

    while (!feof(fp)) {
        fscanf(fp, "%d", &voto);
        somma += voto;
        quanti++;
    }

    printf("letti %d voti, media %.2f\n", quanti, (double)somma / quanti);
    return 0;
}
