#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <linux/limits.h>

/* Omat kirjastot. */
#include "puu.h"
#include "valikko.h"
#include "tulostus.h"
#include "harjoitustyo.h"

int main(int argc, char *argv[])
{
    /* Alusta puu. */
    Puu puu;
    puu.juuri = NULL;
    puu.koko = 0;
    if (argc > 3)
    {
        printf("Ohjelma hyväksyy 0-2 argumentin. Argumentti on nimi tiedostoon,\njoka sisältää avaimia puuhun rivinvaihdolla eroteltuna.\n \
                Toinen argumentti voi olla t, jolloin ainoastaan luodaan puu testaus mielessä.\n");
        return 1;
    }
    else if (argc == 2)
    {
        /* Alusta puu argumentti tiedoston tiedoilla. */
        lue_avaimia_tiedostosta(&puu, argv[1], OLETUS_TULOSTUS);
        printf("Tiedoston lukeminen onnistui!\n");
    }
    else if (argc == 3)
    {
        if (argv[2][0] == 't') {
            lue_avaimia_tiedostosta(&puu, argv[1], EI_MITAAN);
            tyhjenna_puu(puu.juuri);
            return 0;
        } else {
            printf("Toinen argumentti voi olla ainoastaan \"t\".\n");
            return 1;
        }
    }
    paa_valikko(&puu);
    tyhjenna_puu(puu.juuri);
    return 0;
}

void paa_valikko(Puu *puu)
{
    int valinta = 0;
    int tulostus_tila = OLETUS_TULOSTUS;
    char tiedoston_nimi[PATH_MAX];
    while (true)
    {
        tulosta_valikko();
        valinta = kysy_valintaa();
        switch (valinta)
        {
        case 1:
            kysy_tiedoston_nimea(tiedoston_nimi);
            lue_avaimia_tiedostosta(puu, tiedoston_nimi, tulostus_tila);
            printf("Tiedoston lukeminen onnistui!\n");
            break;
        case 2:
            tulosta_puu(puu, -1, NN, tulostus_tila);
            break;
        case 3:
            kysy_ja_lisaa_avain(puu, tulostus_tila);
            break;
        case 4:
            nouda_arvo_avaimella(puu);
            break;
        case 5:
            tulostus_tila = vaihda_tulostus_tilaa(tulostus_tila);
            break;
        case 0:
            return;
            break;
        default:
            printf("Valintaa ei tunnistettu.\n");
            break;
        }
    }
}