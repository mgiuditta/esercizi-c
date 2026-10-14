/*
 * punteggio.h — interfaccia del modulo "punteggio"  (SOLUZIONE di es03)
 *
 * Un header (file .h) contiene DICHIARAZIONI: dice agli altri file "queste cose esistono".
 * Non contiene definizioni (niente memoria allocata, niente corpi di funzione).
 */
#ifndef PUNTEGGIO_H          /* include guard: se PUNTEGGIO_H non è ancora definita...  */
#define PUNTEGGIO_H          /* ...la definisco, così una seconda #include salta tutto  */

/* DICHIARAZIONE con extern: "esiste un int punteggio_totale, ma la sua memoria
 * è allocata in un altro file (punteggio.c)". Si può ripetere in più file. */
extern int punteggio_totale;

/* Prototipo: per le funzioni extern è implicito, non serve scriverlo. */
void aggiungi_punti(int p);

#endif
