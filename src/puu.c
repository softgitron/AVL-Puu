#include <stdio.h>
#include <stdlib.h>

#include "puu.h"
#include "kaannokset.h"

Solmu *varaa_muistia(void)
{
    /* Varaa muistia yhdelle solmulle ja palauttaa tämän solmun osoitteen. */
    Solmu *uusi_solmu;
    if ((uusi_solmu = (Solmu *)malloc(sizeof(Solmu))) == 0)
    {
        printf("Muistin varaaminen epäonnistui!\n");
        exit(5);
    }
    return uusi_solmu;
}

int lisaa_uusi_solmu(Puu *puu, int avain, int arvo)
{
    /* Valmistele uusi solmu ja alusta sen arvot. */
    Solmu *solmu = varaa_muistia();
    solmu->arvo = arvo;
    solmu->avain = avain;
    solmu->paino = 0;
    solmu->oikea = NULL;
    solmu->vasen = NULL;
    /* Lista lisäysreitistä. */
    Solmu *seuranta[MAKSIMI_KORKEUS];
    int maara = 0;
    int kohta = 0;
    short kaannos = NN;
    Solmu **isanta;
    /* Käsittele tyhjä puu poikkeustapauksena. */
    if (puu->koko == 0)
    {
        puu->juuri = solmu;
        puu->koko = 1;
        return NN;
    }
    /* Suoritetaan binäärinen lisäys samalla laskien uudet painot. */
    maara = binaarinen_lisays(puu->juuri, solmu, seuranta);
    if (maara == -1) {
        free(solmu);
        return NN;
    }
    /* Tutkitaan, onko jokin kohta puusta epätasapainossa. */
    kohta = tutki_tasapaino(seuranta, maara);
    if (kohta != -1)
    {
        /* Selvitetään mikä epätasapainon tyyppi on kysessä. */
        kaannos = selvita_tasapaino(seuranta, kohta);
        /* Selvitetään epätasapainoisen solmun isäntä. */
        isanta = selvita_isanta(seuranta, kohta, puu);
        /* Suoritetaan käännös yllä saatujen tietojen pohjalta. */
        suorita_kaannokset(kaannos, isanta, seuranta[kohta]);
    }
    puu->koko++;
    return kaannos;
}

int binaarinen_lisays(Solmu *solmu, Solmu *lisattava, Solmu **seuranta)
{
    /* Perus binääripuu lisäys sekä lisäksi epätasapainon laskeminen. */
    Solmu *liukuri = solmu;
    int maara = 0;
    short suunta = 0;
    while (liukuri != NULL)
    {
        seuranta[maara] = liukuri;
        /* Mene vasemmalle, jos arvo on pienempi. */
        if (lisattava->avain < liukuri->avain)
        {
            suunta = VASEN;
            liukuri = liukuri->vasen;
        }
        /* Mene oikealle, jos arvo on suurempi. */
        else if (lisattava->avain > liukuri->avain)
        {
            suunta = OIKEA;
            liukuri = liukuri->oikea;
        }
        else
        {
            printf("Lisättävällä ei voi olla samaa avainta kuin aikaisemmilla solmuilla.\n");
            return -1;
        }
        maara++;
        if (maara == MAKSIMI_KORKEUS)
        {
            printf("Puun maksimi koko saavutettu.\n");
            exit(5);
        }
    }
    /* Lisää uusi solmu oikeaan kohtaan. */
    if (suunta == VASEN)
    {
        seuranta[maara - 1]->vasen = lisattava;
    }
    else
    {
        seuranta[maara - 1]->oikea = lisattava;
    }
    seuranta[maara] = lisattava;
    return maara;
}

int tutki_tasapaino(Solmu **seuranta, int maara)
{
    /* Päivittää tasapaino tietoja siihen asti, kunnes tulee vastaan
       ensimmäinen solmu, joka ei enää päivityksen jälkeen täytä tasapaino ehtoa.
       palauttaa kohdan takaisinseuranta listasta. */
    Solmu *vertailtava = seuranta[maara];
    int kohta;
    for (kohta = maara - 1; kohta >= 0; kohta--)
    {
        if (seuranta[kohta]->vasen == vertailtava)
        {
            seuranta[kohta]->paino--;
        }
        else
        {
            seuranta[kohta]->paino++;
        }
        if (seuranta[kohta]->paino == 2 || seuranta[kohta]->paino == -2)
        {
            return kohta;
        } else if (seuranta[kohta]->paino == 0) {
            break;
        }
        vertailtava = seuranta[kohta];
    }
    return -1;
}

int selvita_tasapaino(Solmu **seuranta, int kohta)
{
    /* Selvitä, mikä tasapainon poikkeama on kyseessä. */
    /* Testaa LL */
    if (seuranta[kohta]->vasen == seuranta[kohta + 1] && seuranta[kohta + 1]->vasen == seuranta[kohta + 2]) return LL;
    else if (seuranta[kohta]->vasen == seuranta[kohta + 1] && seuranta[kohta + 1]->oikea == seuranta[kohta + 2]) return LR;
    else if (seuranta[kohta]->oikea == seuranta[kohta + 1] && seuranta[kohta + 1]->oikea == seuranta[kohta + 2]) return RR;
    else if (seuranta[kohta]->oikea == seuranta[kohta + 1] && seuranta[kohta + 1]->vasen == seuranta[kohta + 2]) return RL;
    else return NN;
}

Solmu **selvita_isanta(Solmu **seuranta, int kohta, Puu *puu)
{
    /* Selvitä muutettavan solmun isännän osoite. */
    if (kohta == 0)
    {
        /* Juuren muuttaminen on poikkeus. */
        return &(puu->juuri);
    }
    else if (seuranta[kohta - 1]->vasen == seuranta[kohta])
    {
        return &(seuranta[kohta - 1]->vasen);
    }
    else
    {
        return &(seuranta[kohta - 1]->oikea);
    }
}

void suorita_kaannokset(int kaannos, Solmu **isanta, Solmu *korjattava)
{
    /* Tarkista mikä käännös tulee tehdä ja suorita käännös vaaditulla tavalla. */
    switch (kaannos)
    {
    case LL:
        vasen_vasen_kaannos(isanta, korjattava);
        break;
    case LR:
        vasen_oikea_kaannos(isanta, korjattava);
        break;
    case RL:
        oikea_vasen_kaannos(isanta, korjattava);
        break;
    case RR:
        oikea_oikea_kaannos(isanta, korjattava);
        break;
    }
}

int nouda_avaimella(Puu *puu, int avain) {
    /* Etsi haluttu arvo iteratiivisesti. */
    Solmu *liukuri = puu->juuri;
    while (liukuri != NULL)
    {
        if (avain == liukuri->avain) {
            return liukuri->arvo;
        } else if (avain < liukuri->avain) {
            liukuri = liukuri->vasen;
        } else {
            liukuri = liukuri->oikea;
        }
    }
    /* Palauta virhe. */
    return -1;
}

void tyhjenna_puu(Solmu *solmu) {
    /* Vapauta puun muisti rekursiivisesti. */
    if (solmu == NULL) return;
    tyhjenna_puu(solmu->vasen);
    tyhjenna_puu(solmu->oikea);
    free(solmu);
}