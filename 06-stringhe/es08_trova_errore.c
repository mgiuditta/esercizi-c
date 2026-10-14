/*
 * es08 — Trova e correggi l'errore: "Cognome, Nome"  ·  Tipo esame
 *
 * Input:  coppie "nome cognome" (una per riga), fino alla fine dell'input.
 *         Ogni parola ha al massimo DIM-1 = 19 caratteri.
 * Output: per ogni persona "Cognome, Nome (L)" dove L è la lunghezza.
 *     Ada Lovelace  ->  Lovelace, Ada (13)
 *     Alan Turing   ->  Turing, Alan (12)
 *
 * Il codice COMPILA ma contiene DUE errori legati alle stringhe:
 * uno fa uscire testo "sporco", l'altro fa scrivere fuori da un vettore
 * (con nomi lunghi). Trovali, correggili e rilancia il test.
 *
 * Come testarlo: make test T=06 E=es08
 */
#include <stdio.h>
#include <string.h>

#define DIM 20

/* Copia orig in dest, come strcpy. */
void mia_copia(char dest[], char orig[])
{
    int i = 0;
    while (orig[i] != '\0') {
        dest[i] = orig[i];
        i++;
    }
}

/* Aggiunge orig in fondo a dest, come strcat. */
void mia_accoda(char dest[], char orig[])
{
    int i = (int)strlen(dest);
    int j = 0;
    while (orig[j] != '\0') {
        dest[i] = orig[j];
        i++;
        j++;
    }
    dest[i] = '\0';
}

int main(void)
{
    char nome[DIM], cognome[DIM];
    char completo[DIM];

    while (scanf("%19s %19s", nome, cognome) == 2) {
        mia_copia(completo, cognome);
        mia_accoda(completo, ", ");
        mia_accoda(completo, nome);
        printf("%s (%zu)\n", completo, strlen(completo));
    }
    return 0;
}
