/*
 * es03 — Cosa stampa? struct, union e copie  (Base)  — SOLUZIONE
 *
 * Questo esercizio e' un "Cosa stampa?": il codice e' gia' completo.
 * Leggi il README, scrivi la tua previsione riga per riga, POI esegui.
 *
 * Assunzioni (vere su macOS arm64 e Linux x86-64): sizeof(int) = 4,
 * sizeof(double) = 8, un int deve stare a un indirizzo multiplo di 4 e un
 * double a un multiplo di 8. I valori scelti per la union NON dipendono
 * dall'ordine dei byte (endianness).
 *
 * Come testarlo: make sol T=10 E=es03
 */
#include <stdio.h>
#include <string.h>

typedef struct {
    char sigla[4];   /* 4 byte */
    int voto;        /* 4 byte */
} Esame;

typedef struct {
    long id;
    char *nickname;  /* PUNTATORE: la struct contiene solo un indirizzo */
} Persona;

union Valore {
    int i;           /* 4 byte */
    double d;        /* 8 byte */
    char c[8];       /* 8 byte */
};

struct Sbilanciata {
    char c;          /* 1 byte... */
    int n;           /* ...ma n deve partire da un multiplo di 4 */
};

void boccia(Esame e)             /* e e' una COPIA dell'argomento */
{
    e.voto = 0;
    printf("   (dentro boccia: %d)\n", e.voto);
}

void boccia_davvero(Esame *e)    /* e e' l'INDIRIZZO dell'originale */
{
    e->voto = 0;
}

int main(void)
{
    Esame a = {"PA1", 30};
    Esame b;
    char nick[] = "teo";
    Persona p1 = {1, nick};
    Persona p2;
    union Valore u;

    printf("1) sizeof(Esame) = %zu\n", sizeof(Esame));
    printf("2) sizeof(union Valore) = %zu\n", sizeof(union Valore));
    printf("3) sizeof(struct Sbilanciata) = %zu\n", sizeof(struct Sbilanciata));

    b = a;                    /* copia campo per campo, vettore sigla compreso */
    b.voto = 18;
    strcpy(b.sigla, "MAT");
    printf("4) a = %s %d, b = %s %d\n", a.sigla, a.voto, b.sigla, b.voto);

    p2 = p1;                  /* copia il PUNTATORE, non la stringa puntata */
    p2.id = 2;
    p2.nickname[0] = 'T';
    printf("5) p1 = %ld %s, p2 = %ld %s\n", p1.id, p1.nickname, p2.id, p2.nickname);

    boccia(a);
    printf("6) dopo boccia: %d\n", a.voto);
    boccia_davvero(&a);
    printf("7) dopo boccia_davvero: %d\n", a.voto);

    u.i = 0x01010101;         /* tutti e 4 i byte valgono 1 */
    printf("8) u.c[0] = %d, u.c[3] = %d\n", u.c[0], u.c[3]);
    u.d = 0.0;                /* 0.0 in un double = 8 byte tutti a zero */
    printf("9) u.i = %d\n", u.i);
    printf("10) stesso indirizzo? %d %d\n",
           (void *)&u.i == (void *)&u.d, (void *)&u.d == (void *)u.c);
    printf("11) byte tra &a e &a.voto = %d\n", (int)((char *)&a.voto - (char *)&a));
    return 0;
}
