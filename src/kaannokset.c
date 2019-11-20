#include <stdio.h>

#include "kaannokset.h"

/* Grafiikat geeg for geeks.
   https://www.geeksforgeeks.org/avl-tree-set-1-insertion/ */

/* Kaikki tämän tiedoston aliohjelmat suorittavat tarvittavat käännökset mahdollisimman
   tehokkaasti kuvissa esitetyllä tavalla. */

void vasen_vasen_kaannos(Solmu **isanta, Solmu *korjattava) {
/*
T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
*/
    Solmu *T3 = korjattava->vasen->oikea;
    Solmu *Y = korjattava->vasen;
    *isanta = Y;
    korjattava->vasen->oikea = korjattava;
    korjattava->vasen = T3;
    korjaa_painot(Y);
}

void vasen_oikea_kaannos(Solmu **isanta, Solmu *korjattava) {
/*
     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2
*/
    Solmu *T2 = korjattava->vasen->oikea->vasen;
    Solmu *T3 = korjattava->vasen->oikea->oikea;
    Solmu *X = korjattava->vasen->oikea;
    *isanta = X;
    X->vasen = korjattava->vasen;
    X->oikea = korjattava;
    X->vasen->oikea = T2;
    X->oikea->vasen = T3;
    korjaa_painot(X);
}

void oikea_oikea_kaannos(Solmu **isanta, Solmu *korjattava) {
/*
  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
*/
    Solmu *T2 = korjattava->oikea->vasen;
    Solmu *Y = korjattava->oikea;
    *isanta = Y;
    korjattava->oikea->vasen = korjattava;
    korjattava->oikea = T2;
    korjattava->paino = 0;
    korjaa_painot(Y);
}

void oikea_vasen_kaannos(Solmu **isanta, Solmu *korjattava) {
/*
   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4
*/
    Solmu *T2 = korjattava->oikea->vasen->vasen;
    Solmu *T3 = korjattava->oikea->vasen->oikea;
    Solmu *X = korjattava->oikea->vasen;
    *isanta = X;
    X->vasen = korjattava;
    X->oikea = korjattava->oikea;
    X->vasen->oikea = T2;
    X->oikea->vasen = T3;
    korjaa_painot(X);
}

void korjaa_painot(Solmu *solmu) {
    /* Laskee uudelleen muuteltujen solmujen painot. Ei ehkä tehokkain, mutta toiminta varma. */
    solmu->paino = 0;
    laske_solmu(solmu->vasen);
    laske_solmu(solmu->oikea);
}

void laske_solmu(Solmu *solmu) {
    /* Jos ei alisolmuja. */
    if (solmu->oikea == NULL && solmu->vasen == NULL) solmu->paino = 0;
    /* Jos vain oikea alisolmu. */
    else if (solmu->oikea != NULL && solmu->vasen == NULL) solmu->paino = 1;
    /* Jos vain vasen alisolmu. */
    else if (solmu->oikea == NULL && solmu->vasen != NULL) solmu->paino = -1;
    /* Jos molemmat alisolmut 0, myös isäntäsolmun oltava 0. */
    else if (solmu->oikea->paino == 0 && solmu->vasen->paino == 0) solmu->paino = 0;
    /* Jos mikään erityistapaukset eivät päde lasketaan arvot suoraan solmujen arvojen perusteella. */
    else {
        /* Muutoin. */
        if (solmu->paino == 2) solmu->paino = 0;
        if (solmu->paino == -2) solmu->paino = 0;
    }
}