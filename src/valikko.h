#include "vakiot_rakenteet.h"

void tulosta_valikko(void);
int kysy_valintaa(void);
void kysy_tiedoston_nimea(char *tiedoston_nimi);
void lue_avaimia_tiedostosta(Puu *puu, char *tiedoston_nimi, int tulostus_tila);
void kysy_ja_lisaa_avain(Puu *puu, int tulostus_tila);
void nouda_arvo_avaimella(Puu *puu);
int vaihda_tulostus_tilaa(int nykyinen);
int kysy_numero(void);
int muuta_numeroksi(char *merkkijono);
void tyhjenna_puskuri(char *viimeinen);