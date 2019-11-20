# AVL-Puu
Tietorakenteet ja algoritmit kurssin harjoitustyö

## Tarkoitus
Tämän harjoituksen tarkoituksena oli tehdä itsestään painottuva binäärinen AVL-puu. AVL-puu on tyypiltään erittäin tehokas tietorakenne ja siihen arvojen lisääminen sekä hakuoperaatiot kestävät huonoimmillaan logaritmisen ajan.

Monet verkosta löytyvät AVL-algoritmit ovat luonteeltaan pääsäntöisesti rekursiivisia. Päätin kuitenkin pyrkiä omassa työssäni pitämään rekursiivisuuden minimissään, koska mielestäni lähes kaikki ratkaisut olivat erittäin vaikeasti ymmärrettävissä. Tässä työssä keskityin erityisesti ratkaisun helppolukuisuuteen, mutta algoritmista tuli myös kohtalaisen tehokas.

## Kääntäminen
Varsinainen AVL-puu ohjelma löytyy **src**-kansiosta. Ohjelman pitäisi kääntyä suoraan make komennon avulla **harjoitustyo**-nimiseen tiedostoon, joka on suoraan ajettavissa.

## Käyttö
Ohjelmaa voi käyttää sellaisenaan komennolla `./harjoitustyo` tai sitten sille voi antaa ensimmäisenä argumenttina tiedoston nimen. Tiedostosta luetaan avaimet suoraan ohjelman ylläpitämään puuhun ennen päävalikon näyttämistä. Tässä repositoriossa on *avaimet.txt* tiedosto, jota voi käyttää testaamiseen. Tiedoston kanssa ohjelma voidaan ajaa esim. näin: `./harjoitustyo avaimet.txt`. Toisena argumenttina ohjelmalle voi syöttää argumentin `t`, jolloin ohjelma luo puurakenteen ja poistuu sen jälkeen välittömästi. Ohjelma on valikkopohjainen ja jokaisen valinnan pitäisi olla itsestään selviä.

## Tiedoston rakenne
Ohjelmalle voi syöttää tiedostoja, jotka sisältävät solmujen avaimia. Tiedoston tulisi sisältää kokonaislukuina esitettyjä avaimia erotettuna rivinvaihdolla.

## Apuohjelmat
Varsinaisen ohjelman lisäksi tästä repositoriosta löytyy kaksi apuohjelmaa. Ensimmäinen apuohjelma on nimeltään *arvoja.py*, jonka avulla voi generoida testaus dataa. Toinen apuohjelma on nimeltään *testaa_nopeuksia.sh*, jonka avulla voi testata ohjelman performanssia automaattisesti.

### arvoja.py:n käyttö
*arvoja.py* luo *random.txt* nimisen tiedoston ajamisen jälkeen. Ohjelman voi ajaa esimerkiksi komennolla `python3 ./arvoja.py 100`, jolloin ohjelma luo 100 kappaletta 1-1000 välillä olevia lukuja *random.txt* tiedostoon. Kyseisen tiedoston voi avata suoraan varsinaisella AVL-puu ohjelmalla.

### testaa_nopeuksia.sh:n käyttö
*testaa_nopeuksia.sh* skripti ajaa performanssi testauksen ohjelmalle oletuksena noin alkioilla (1-100 000) 1 000 alkion välein. Skripti ei odota parametreja vaan sen voi ajaa suoraan komennolla `./testaa_nopeuksia.sh`. Valmistuttuaan skripti tallettaa tulokset *Tulokset* kansioon csv tiedostoon, jossa ensimmäisellä sarakkeella on lisättyjen solmujen määrä ja toisella sarakkeella on lisäilyyn kulunut aika.

## Analyysi.m
Analyysi.m on pieni Matlab skripti, jolla voi piirtää kuvaajan *testaa_nopeuksia.sh*:n tuotoksista. Skriptin voi avata Matlabissa ja yrittää ajaa sen samassa kansiossa kuin csv-tiedostonkin, jolloin skriptin pitäisi piirtää kuvaaja.

### Lisättäviä ominaisuuksia
- [ ] Alkioiden poisto
- [ ] Tehokkaampi muistin varaus (ei aina uutta mallocia)
- [ ] Parempi tulostus
- [ ] Lisää selkeyttä painojen päivittämiseen kiertojen yhteydessä
- [ ] Parempi Makefile
