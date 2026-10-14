/* =====================================================================
 * es06 — Trova e correggi l'errore: la funzione che "non fa niente"
 * Intermedio  ·  SOLUZIONE
 * Il programma legge a e b, li mette in ordine crescente e stampa il
 * doppio del minore. Nella versione con bug, scambia() e raddoppia()
 * lavoravano su COPIE (passaggio per valore) e il main non cambiava.
 * Correzione SENZA puntatori: funzioni che RESTITUISCONO il risultato.
 * Come testarlo: make sol T=07 E=es06
 * ===================================================================== */
#include <stdio.h>

int minimo(int x, int y);
int massimo(int x, int y);
int raddoppia(int x);

int main(void) {
    int a, b, m, M;
    if (scanf("%d %d", &a, &b) != 2) {
        printf("input non valido\n");
        return 1;
    }
    printf("prima: a=%d b=%d\n", a, b);

    /* PRIMA (bug): if (a > b) scambia(a, b);
     * scambia riceveva copie di a e b: scambiava le copie e basta.
     * ORA: calcolo minimo e massimo (valori restituiti) e li riassegno
     * IO, nel main, alle MIE variabili. */
    m = minimo(a, b);
    M = massimo(a, b);
    a = m;
    b = M;
    printf("dopo: a=%d b=%d\n", a, b);

    /* PRIMA (bug): raddoppia(a);  -> il valore calcolato andava perso.
     * ORA: raddoppia restituisce il risultato e io lo assegno. */
    a = raddoppia(a);
    printf("doppio del minimo: %d\n", a);
    return 0;
}

int minimo(int x, int y) {
    return x < y ? x : y;    /* operatore ternario: "se x<y allora x altrimenti y" */
}

int massimo(int x, int y) {
    return x > y ? x : y;
}

int raddoppia(int x) {
    return x * 2;            /* il risultato esce dalla funzione con return */
}

/* Nota: una vera funzione scambia(a, b) che modifica le variabili del
 * chiamante NON si può scrivere con il solo passaggio per valore.
 * Serve passare gli INDIRIZZI: void scambia(int *x, int *y).
 * Lo fai in 08-parametri-macro (es02) e lo approfondisci in 09. */
