#!/bin/bash
TESTATTAVA="harjoitustyo"
VALMISTELEVA="arvoja.py"
TULOS_TIEDOSTO="./Tulokset/${TESTATTAVA}_tulokset.csv"
mkdir -p ./Tulokset
# for KIERROS in {1000..1000000..10000}
for KIERROS in {1..100000..1000}
do
    # https://www.unix.com/shell-programming-and-scripting/152554-storing-output-time-command-variable.html
    # Uudet arvot testattavaksi
    python3 ./${VALMISTELEVA} ${KIERROS}
    TULOKSET=$(TIMEFORMAT='%E';time (./$TESTATTAVA random.txt t) 2>&1 1>/dev/null)
    echo $TULOKSET
    echo "$KIERROS;$TULOKSET" >> $TULOS_TIEDOSTO
done
