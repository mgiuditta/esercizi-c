/*
 * 02 — es01: sizeof e limiti dei tipi  (Base) — SOLUZIONE
 * Come testarlo: make sol T=02 E=es01
 */
#include <stdio.h>
#include <limits.h>

int bit_da_byte(size_t byte)
{
    /* CHAR_BIT (da limits.h) = bit in un byte, cioe' 8.
       Lo uso invece di scrivere 8 "a mano": e' la costante ufficiale.
       Il cast (int) converte size_t (intero senza segno) nel tipo restituito. */
    return (int)byte * CHAR_BIT;
}

long long massimo_con_segno(int bit)
{
    long long potenza = 1;   /* long long: almeno 64 bit, cosi' 2^31 ci sta */
    int i = 1;

    /* Con n bit e il segno, un bit "se ne va" per il segno:
       i valori vanno da -2^(n-1) a 2^(n-1) - 1 (il -1 perche' c'e' anche lo 0). */
    while (i < bit) {        /* ripeto (bit - 1) volte */
        potenza = potenza * 2;
        i = i + 1;
    }
    return potenza - 1;
}

void stampa_tipo(const char *nome, size_t byte)
{
    printf("%-7s %zu byte = %2d bit\n", nome, byte, bit_da_byte(byte));
}

int main(void)
{
    /* sizeof e' un OPERATORE (non una funzione): il compilatore lo calcola
       guardando solo il tipo, prima che il programma parta. */
    stampa_tipo("char", sizeof(char));     /* sempre 1, per definizione */
    stampa_tipo("short", sizeof(short));
    stampa_tipo("int", sizeof(int));
    stampa_tipo("long", sizeof(long));
    stampa_tipo("float", sizeof(float));
    stampa_tipo("double", sizeof(double));

    printf("max con segno a  8 bit: %lld (SCHAR_MAX = %d)\n", massimo_con_segno(8), SCHAR_MAX);
    printf("max con segno a 16 bit: %lld (SHRT_MAX  = %d)\n", massimo_con_segno(16), SHRT_MAX);
    printf("max con segno a 32 bit: %lld (INT_MAX   = %d)\n", massimo_con_segno(32), INT_MAX);
    return 0;
}
