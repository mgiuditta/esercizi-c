/*
 * es08 — Trova e correggi l'errore: "Cognome, Nome"  (SOLUZIONE)
 *
 * Input:  coppie "nome cognome" (una per riga), fino alla fine dell'input.
 *         Ogni parola ha al massimo DIM-1 = 19 caratteri.
 * Output: per ogni persona "Cognome, Nome (L)" dove L è la lunghezza.
 *
 * Come testarlo: make sol T=06 E=es08
 */
#include <stdio.h>
#include <string.h>

#define DIM 20
/* CORREZIONE 2: il risultato contiene cognome (max 19) + ", " (2)
 * + nome (max 19) + '\0' (1) = 41 caratteri = 2*DIM + 1.
 * Prima era char completo[DIM]: con "Rita Levi-Montalcini" servono
 * 21 + 1 celle e strcat/mia_accoda scrivevano fuori dal vettore. */
#define DIM_COMPLETO (2 * DIM + 1)

/* Copia orig in dest, come strcpy. */
void mia_copia(char dest[], char orig[])
{
    int i = 0;
    while (orig[i] != '\0') {
        dest[i] = orig[i];
        i++;
    }
    /* CORREZIONE 1: mancava questa riga. Il ciclo si ferma PRIMA di copiare
     * il '\0', quindi va scritto a mano. Senza, dest non "finisce" dove
     * dovrebbe: restano i caratteri di prima (es. "Turingce, Ada"). */
    dest[i] = '\0';
}

/* Aggiunge orig in fondo a dest, come strcat. */
void mia_accoda(char dest[], char orig[])
{
    int i = (int)strlen(dest);   /* si parte dal '\0' di dest e lo si sovrascrive */
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
    char completo[DIM_COMPLETO];

    /* %19s: al massimo 19 caratteri + '\0' = 20 = DIM celle */
    while (scanf("%19s %19s", nome, cognome) == 2) {
        mia_copia(completo, cognome);
        mia_accoda(completo, ", ");
        mia_accoda(completo, nome);
        printf("%s (%zu)\n", completo, strlen(completo));
    }
    return 0;
}
