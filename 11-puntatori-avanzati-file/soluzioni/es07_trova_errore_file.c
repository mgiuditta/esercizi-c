/*
 * Esercizio 07 — Trova e correggi gli errori: media dei voti da file  (Tipo esame)
 * SOLUZIONE: gli errori corretti sono segnalati con "ERRORE n".
 *
 * Come testarlo: make sol T=11 E=es07
 */
#include <stdio.h>

int main(void)
{
    char nome[100];
    FILE *fp;
    int voto = 0, somma = 0, quanti = 0;

    if (scanf("%99s", nome) != 1)
        return 1;

    /* ERRORE 1: la modalita' era "w+". Il "+" permette anche di leggere, ma
       la "w" SVUOTA il file appena lo apre (o lo crea vuoto se non esiste):
       i voti venivano cancellati prima ancora di leggerli! Per leggere serve "r". */
    fp = fopen(nome, "r");

    /* ERRORE 2: mancava il controllo di NULL. Con "r", se il file non esiste,
       fopen restituisce NULL e la prima fscanf/feof su NULL fa crollare il
       programma (Segmentation fault / AddressSanitizer: SEGV). */
    if (fp == NULL) {
        printf("Errore: file %s non trovato\n", nome);
        fprintf(stderr, "Errore: file %s non trovato\n", nome); /* canale degli errori */
        return 1;
    }

    /* ERRORE 3: il ciclo era while (!feof(fp)). feof diventa vero solo DOPO
       una lettura fallita: l'ultimo voto veniva sommato due volte e contato
       una volta di troppo. Si controlla invece il valore restituito da fscanf. */
    while (fscanf(fp, "%d", &voto) == 1) {
        somma += voto;
        quanti++;
    }

    /* ERRORE 4 (di stile, il test non lo vede): mancava fclose. */
    fclose(fp);

    if (quanti == 0) {   /* evita la divisione per zero con un file vuoto */
        printf("nessun voto\n");
        return 0;
    }
    printf("letti %d voti, media %.2f\n", quanti, (double)somma / quanti);
    return 0;
}
