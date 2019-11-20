#include "vakiot_rakenteet.h"

Solmu *varaa_muistia(void);
int lisaa_uusi_solmu(Puu *puu, int avain, int arvo);
int binaarinen_lisays(Solmu *solmu, Solmu *lisattava, Solmu **seuranta);
int tutki_tasapaino(Solmu **seuranta, int maara);
int selvita_tasapaino(Solmu **seuranta, int kohta);
Solmu **selvita_isanta(Solmu **seuranta, int kohta, Puu *puu);
void suorita_kaannokset(int kaannos, Solmu **isanta, Solmu *korjattava);
int nouda_avaimella(Puu *puu, int avain);
void tyhjenna_puu(Solmu *solmu);