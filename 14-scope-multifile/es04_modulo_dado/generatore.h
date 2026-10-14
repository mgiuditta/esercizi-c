/*
 * generatore.h — interfaccia del modulo "generatore di lanci di dado"  ·  file 1 di 3
 * Chi usa il modulo vede SOLO queste tre funzioni. Il seme e la funzione interna
 * restano nascosti in generatore.c (static).
 */
#ifndef GENERATORE_H
#define GENERATORE_H

void gen_seme(unsigned int s);   /* imposta il punto di partenza della sequenza */
int  gen_dado(void);             /* restituisce un lancio da 1 a 6 */
int  gen_estrazioni(void);       /* quanti lanci sono stati fatti finora */

#endif
