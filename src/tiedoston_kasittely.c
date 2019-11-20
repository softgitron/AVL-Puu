#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PUSKURI 100

FILE *avaa_tiedosto(char *nimi)
{
    FILE *tiedosto = fopen(nimi, "r");
    if (tiedosto == NULL)
    {
        printf("Tiedoston avaaminen epäonnistui. Onko tiedoston nimi oikein?\n");
    }
    return tiedosto;
}

int lue_ja_tarkista(FILE *tiedosto)
{
    /* Lukee tiedoston rivin, tarkistaa että se on luku ja palauttaa arvon. */
    char rivi[PUSKURI];
    int numero;
    /* Palauta tiedsoton seuraava rivi */
    if (fgets(rivi, PUSKURI, tiedosto) == NULL)
    {
        /* Viimeisen rivin tilanne. */
        return -1;
    }
    if (rivi[0] != '0')
    {
        numero = atoi(rivi);
        if (numero < 0)
        {
            printf("Avaimen arvo ei voi olla negatiivinen.\n");
        }
        return numero;
    }
    else
    {
        printf("Tiedosto sisältää epäsopivia rivejä, joilla ei ole kokonaislukuja.\n");
        exit(2);
    }
}

void sulje_tiedosto(FILE *tiedosto)
{
    fclose(tiedosto);
}