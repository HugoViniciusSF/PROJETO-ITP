PARAMS = -Wall -Wextra -Werror
all: app app/ocma.js Poseidon Netuno
	cd app && node ocma Poseidon Netuno

Poseidon: src/mainBot.c entryFunctions distanceFunctions
	gcc $(PARAMS) -I include/ src/mainBot.c objects/entryFunctions.o objects/distanceFunctions.o -o app/Poseidon
Netuno: src/mainBot.c entryFunctions distanceFunctions
	gcc $(PARAMS) -I include/ src/mainBot.c objects/entryFunctions.o objects/distanceFunctions.o -o app/Netuno
entryFunctions:
	gcc $(PARAMS) -I include/ -o objects/entryFunctions.o -c src/entryFunctions.c
distanceFunctions:
	gcc $(PARAMS) -I include/ -o objects/distanceFunctions.o -c src/distanceFunctions.c