/*
 * 01 — es05: trova e correggi l'errore  (Intermedio) — SOLUZIONE
 * Come testarlo: make sol T=01 E=es05
 */
#include <stdio.h>

int main(void)
{
    int a = 0;
    int b = 0;
    int distanza = 0;
    double media = 0.0;

    if (scanf("%d", &a) != 1)
        return 1;
    /* ERRORE 1: mancava la & davanti a b.
       scanf deve sapere DOVE scrivere il numero letto, cioe' l'indirizzo
       della variabile (&b). Senza &, passavamo il VALORE di b (0) e scanf
       provava a scrivere all'indirizzo 0: crash. */
    if (scanf("%d", &b) != 1)
        return 1;

    /* ERRORE 2: (a + b) / 2 e' una divisione tra INTERI: 9 / 2 fa 4,
       la parte decimale si perde PRIMA di finire nel double.
       Con 2.0 (costante double) l'intero viene promosso a double e la
       divisione diventa reale: 9 / 2.0 = 4.5. */
    media = (a + b) / 2.0;

    distanza = a - b;
    /* ERRORE 3: c'era un ';' subito dopo la condizione dell'if.
       Quel ';' e' un'istruzione vuota: era LEI il ramo "then".
       La riga dopo veniva quindi eseguita SEMPRE (l'indentazione inganna,
       il compilatore la ignora). */
    if (distanza < 0)
        distanza = -distanza;

    printf("Media = %.2f\n", media);
    printf("Distanza = %d\n", distanza);
    return 0;
}
