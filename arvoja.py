#!/bin/python3

import sys
import random

if (len(sys.argv) != 2):
    print("Tämä skripti tarvitsee argumentikseen arvottavien lukujen määrän.")

try:
    maara = int(sys.argv[1])
except ValueError:
    print("Argumentti on annettava kokonaislukuna.")
    exit(1)

# https://stackoverflow.com/questions/22842289/generate-n-unique-random-numbers-within-a-range
lista = random.sample(range(1, maara * 10), maara)

with open("random.txt", "w") as tiedosto:
    for alkio in lista:
        tiedosto.write(str(alkio) + "\n")