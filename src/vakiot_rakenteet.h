#ifndef VAKIO_RAKENTEET_H
#define VAKIO_RAKENTEET_H

/* Puu rakenteeseen liittyvät vakiot. */
#define MAKSIMI_KORKEUS 100
#define NN 0
#define LL 1
#define LR 2
#define RL 3
#define RR 4

/* Tulostukseen liittyvät vakiot. */
#define VAIN_AVAIMET 1
#define AVAIMET_JA_PAINOT 2
#define AVAIMET_JA_ARVOT 3
#define EI_MITAAN 4

#define OLETUS_TULOSTUS 2

#define OIKEA 0
#define VASEN 1

/* AVL-puun yksittäinen solmu */
typedef struct Solmu
{
    int avain;
    /* Arvo on tässä työssä aina 0. */
    int arvo;
    short paino;
    struct Solmu *vasen;
    struct Solmu *oikea;
} Solmu;

/* AVL-puuta ylläpitävä tietorakenne */
typedef struct Puu
{
    Solmu *juuri;
    int koko;
} Puu;
#endif