/*
 * pila.h — interfaccia del modulo "pila di caratteri"  (SOLUZIONE di es07)
 * Una pila (stack) è come una pila di piatti: si aggiunge e si toglie solo in cima.
 * L'ultimo inserito è il primo a uscire.
 */
#ifndef PILA_H
#define PILA_H

void pila_svuota(void);          /* riporta la pila a vuota */
int  pila_vuota(void);           /* 1 se vuota, 0 altrimenti */
int  pila_dimensione(void);      /* quanti elementi contiene */
int  pila_push(char c);          /* mette c in cima; 1 se riuscito, 0 se la pila è piena */
int  pila_pop(char *c);          /* toglie la cima e la scrive in *c; 1 se riuscito, 0 se vuota */

#endif
