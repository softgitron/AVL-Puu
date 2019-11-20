#include <stdio.h>

#include "puu.h"
#include "tulostus.h"

void tulosta_puu(Puu *puu, int lisatty, int viimeisin_kaannos, int tila)
{
    /* Tulosta tietoja viimeisimmistä lisäyksistä ja aloita sitten puun tulostus. */
    if (tila == EI_MITAAN)
    {
        return;
    }
    if (lisatty != -1)
    {
        printf("Viimeisimpänä lisätty %i.\n", lisatty);
        switch (viimeisin_kaannos)
        {
        case LL:
            printf("Viimeisin käännös oli tyyppiä vasen vasen.\n");
            break;
        case LR:
            printf("Viimeisin käännös oli tyyppiä vasen oikea.\n");
            break;
        case RL:
            printf("Viimeisin käännös oli tyyppiä oikea vasen.\n");
            break;
        case RR:
            printf("Viimeisin käännös oli tyyppiä oikea oikea.\n");
            break;
        default:
            printf("Viimeisimmän lisäyksen jälkeen ei suoritettu käännöksiä.\n");
            break;
        }
    }
    printf("Puu:\n");
    tulosta_rekursiivisesti(puu->juuri, 0, tila, ' ');
    printf("\n");
    fflush(stdout);
}

void tulosta_rekursiivisesti(Solmu *solmu, int syvyys, int tila, char viimeisin)
{
    /* Tulosta ensin oikea, sitten keskimmäinen ja lopuksi vasen. */
    if (solmu == NULL)
    {
        /* Jos solmua ei ole, palaa välittömästi. */
        return;
    }
    tulosta_rekursiivisesti(solmu->oikea, syvyys + 1, tila, '/');
    /* Tulosta riittävä määrä tyhjää. */
    int kierros;
    for (kierros = 0; kierros < syvyys; kierros++)
    {
        if (tila == VAIN_AVAIMET)
        {
            printf("      ");
        }
        else
        {
            printf("         ");
        }
    }
    switch (tila)
    {
    case VAIN_AVAIMET:
        printf("%c %.3i\n", viimeisin, solmu->avain);
        break;
    case AVAIMET_JA_PAINOT:
        printf("%c %.3i(%.1i)\n", viimeisin, solmu->avain, solmu->paino);
        break;
    case AVAIMET_JA_ARVOT:
        printf("%c %.3i(%.1i)\n", viimeisin, solmu->avain, solmu->arvo);
        break;
    default:
        break;
    }
    tulosta_rekursiivisesti(solmu->vasen, syvyys + 1, tila, '\\');
}