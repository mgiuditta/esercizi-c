/*
 * es06 — Confronta due stringhe a mano (la tua strcmp)  (SOLUZIONE)
 *
 * Input:  coppie di parole (due per riga), fino alla fine dell'input.
 * Output: per ogni coppia: le due parole, il segno del confronto fatto con
 *         mia_strcmp (-1, 0, 1), il segno di strcmp (deve coincidere) e
 *         il risultato di == sugli indirizzi (sempre 0).
 *
 * Come testarlo: make sol T=06 E=es06
 */
#include <stdio.h>
#include <string.h>

#define DIM 50

/* Come strcmp: <0 se s1 viene prima di s2 in ordine lessicografico,
 * 0 se sono uguali, >0 se viene dopo.
 * Ordine lessicografico = l'ordine del dizionario, ma usando i codici
 * ASCII: per questo 'Z' (90) viene prima di 'a' (97). */
int mia_strcmp(char s1[], char s2[])
{
    int i = 0;
    /* Avanza finché i caratteri sono uguali E non siamo alla fine.
     * Basta controllare s1[i] != '\0': se s2[i] fosse '\0' e s1[i] no,
     * sarebbero diversi e il ciclo si fermerebbe comunque. */
    while (s1[i] != '\0' && s1[i] == s2[i])
        i++;
    /* Primo carattere diverso (o i due terminatori, se uguali).
     * Se s1 = "cas" e s2 = "casa": confronto '\0' (0) con 'a' (97) -> negativo:
     * la parola più corta viene prima. Il cast a unsigned char fa come
     * la strcmp vera, che confronta i caratteri come valori 0..255. */
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

/* Riduce qualunque intero a -1, 0 o 1. Serve perché strcmp garantisce solo
 * il SEGNO del risultato, non il valore esatto (può essere -1, -32, ...). */
int segno(int x)
{
    if (x < 0)
        return -1;
    if (x > 0)
        return 1;
    return 0;
}

int main(void)
{
    char a[DIM], b[DIM];

    /* %49s: legge al massimo 49 caratteri, così resta posto per '\0'.
     * Senza il 49 una parola lunga sfonderebbe il vettore (buffer overflow). */
    while (scanf("%49s %49s", a, b) == 2) {
        printf("%s %s -> mia: %d, strcmp: %d, ==: %d\n",
               a, b,
               segno(mia_strcmp(a, b)),
               segno(strcmp(a, b)),
               &a[0] == &b[0]);   /* confronta INDIRIZZI: a e b sono vettori diversi */
    }
    return 0;
}
