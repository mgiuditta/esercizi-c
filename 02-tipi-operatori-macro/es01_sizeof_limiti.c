/*
 * 02 — es01: sizeof e limiti dei tipi  (Base)
 *
 * Testo:
 *  1) nel main, al posto degli 0 segnati TODO, scrivi sizeof(tipo) giusto;
 *  2) completa bit_da_byte(byte): quanti bit ci sono in quei byte (1 byte = 8 bit);
 *  3) completa massimo_con_segno(bit): il piu' grande intero con segno
 *     rappresentabile con quel numero di bit, cioe' 2^(bit-1) - 1.
 *     Calcola la potenza con un ciclo (niente pow). Il main confronta il tuo
 *     risultato con le costanti di <limits.h> (SCHAR_MAX, SHRT_MAX, INT_MAX).
 *
 * Nota: le dimensioni attese sono quelle di macOS su Apple Silicon e di
 * Linux a 64 bit (int = 4 byte, long = 8 byte). Su Windows long e' 4 byte.
 *
 * Come testarlo: make test T=02 E=es01
 */
#include <stdio.h>
#include <limits.h>

int bit_da_byte(size_t byte)
{
    /* TODO: restituisci il numero di bit */
    (void)byte;
    return 0;
}

long long massimo_con_segno(int bit)
{
    long long potenza = 1;
    /* TODO: moltiplica potenza per 2 per (bit - 1) volte,
             poi restituisci potenza - 1 */
    (void)bit;
    return potenza;
}

void stampa_tipo(const char *nome, size_t byte)
{
    /* %zu e' il segnaposto per size_t, il tipo restituito da sizeof */
    printf("%-7s %zu byte = %2d bit\n", nome, byte, bit_da_byte(byte));
}

int main(void)
{
    stampa_tipo("char", 0);   /* TODO: sizeof(char)   */
    stampa_tipo("short", 0);  /* TODO: sizeof(short)  */
    stampa_tipo("int", 0);    /* TODO: sizeof(int)    */
    stampa_tipo("long", 0);   /* TODO: sizeof(long)   */
    stampa_tipo("float", 0);  /* TODO: sizeof(float)  */
    stampa_tipo("double", 0); /* TODO: sizeof(double) */

    printf("max con segno a  8 bit: %lld (SCHAR_MAX = %d)\n", massimo_con_segno(8), SCHAR_MAX);
    printf("max con segno a 16 bit: %lld (SHRT_MAX  = %d)\n", massimo_con_segno(16), SHRT_MAX);
    printf("max con segno a 32 bit: %lld (INT_MAX   = %d)\n", massimo_con_segno(32), INT_MAX);
    return 0;
}
