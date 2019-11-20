#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>

#include "puu.h"
#include "tulostus.h"
#include "tiedoston_kasittely.h"
#include "valikko.h"

void tulosta_valikko(void)
{
    printf("\nValikko:\n");
    printf("1) Lue avaimet tiedostosta.\n");
    printf("2) Tulosta tämän hetkinen puu.\n");
    printf("3) Lisää yksi uusi avain.\n");
    printf("4) Nouda arvo avaimella.\n");
    printf("5) Vaihda tulostus tilaa.\n");
    printf("0) Lopeta ohjelma.\n");
}

int kysy_valintaa(void)
{
    char puskuri[2];
    puskuri[0] = '\0';
    printf("Anna valinta: ");
    fgets(puskuri, 2, stdin);
    tyhjenna_puskuri(puskuri);
    return muuta_numeroksi(puskuri);
}

void kysy_tiedoston_nimea(char *tiedoston_nimi)
{
    printf("Anna luettavan tiedoston nimi: ");
    fgets(tiedoston_nimi, PATH_MAX, stdin);
    tyhjenna_puskuri(tiedoston_nimi);
    tiedoston_nimi[strlen(tiedoston_nimi) - 1] = '\0';
}

void lue_avaimia_tiedostosta(Puu *puu, char *tiedoston_nimi, int tulostus_tila)
{
    FILE *tiedosto;
    int avain = 0;
    int kaannos = 0;
    if ((tiedosto = avaa_tiedosto(tiedoston_nimi)) == NULL)
    {
        return;
    }
    /* Lue tiedosto riveittäin ja lisää uusi avain puuhun. */
    while ((avain = lue_ja_tarkista(tiedosto)) != -1)
    {
        kaannos = lisaa_uusi_solmu(puu, avain, 0);
        tulosta_puu(puu, avain, kaannos, tulostus_tila);
    }
    sulje_tiedosto(tiedosto);
}

void kysy_ja_lisaa_avain(Puu *puu, int tulostus_tila)
{
    int avain = 0;
    int kaannos = 0;
    printf("Anna uusi avain: ");
    avain = kysy_numero();
    if (avain < 0)
    {
        printf("Virhe avainta lisätessä.\n");
        return;
    }
    kaannos = lisaa_uusi_solmu(puu, avain, 0);
    tulosta_puu(puu, avain, kaannos, tulostus_tila);
}

void nouda_arvo_avaimella(Puu *puu)
{
    int avain = 0;
    int arvo = 0;
    printf("Anna haettava avain: ");
    avain = kysy_numero();
    if (avain < 0)
    {
        printf("Avain ei voi olla negatiivinen.\n");
        return;
    }
    arvo = nouda_avaimella(puu, avain);
    if (arvo != -1)
    {
        printf("Avain %i löydettiin ja sen arvo oli %i.\n", avain, arvo);
    }
    else
    {
        printf("Avaimella %i ei löytynyt arvoa.\n", avain);
    }
}

int vaihda_tulostus_tilaa(int nykyinen)
{
    int valinta = 0;
    printf("\nNykyinen tila: %i\n", nykyinen);
    printf("Valitse seuraavista tulostustiloista:\n");
    printf("1) Vain avaimet.\n");
    printf("2) Avaimet ja painot.\n");
    printf("3) Avaimet ja arvot.\n");
    printf("4) Ei mitään.\n");
    printf("5) Pidä nykyinen.\n");
    printf("Anna valintasi: ");
    valinta = kysy_numero();
    switch (valinta)
    {
    case 1:
        return VAIN_AVAIMET;
        break;
    case 2:
        return AVAIMET_JA_PAINOT;
        break;
    case 3:
        return AVAIMET_JA_ARVOT;
        break;
    case 4:
        return EI_MITAAN;
        break;
    case 5:
        return nykyinen;
        break;
    default:
        printf("Valintaa ei tunnistettu. Pidetään aikaisempi tila.");
        return nykyinen;
        break;
    }
}

int kysy_numero(void)
{
    char puskuri[12];
    puskuri[0] = '\0';
    fgets(puskuri, 12, stdin);
    tyhjenna_puskuri(puskuri);
    return muuta_numeroksi(puskuri);
}

int muuta_numeroksi(char *merkkijono)
{
    /* Varmista, että käyttäjän syöte oli numero. */
    int numero = 0;
    if (merkkijono[0] != '0')
    {
        numero = atoi(merkkijono);
        if (numero != 0)
        {
            return numero;
        }
    }
    else
    {
        return 0;
    }
    return -1;
}

void tyhjenna_puskuri(char *viimeinen)
{
    if (viimeinen[strlen(viimeinen) - 1] == '\n')
    {
        return;
    }
    int results = 0;
    while (results != EOF && results != '\n')
    {
        results = fgetc(stdin);
    }
}