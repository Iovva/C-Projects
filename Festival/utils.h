#ifndef utils_H_
#define utils_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*
primeste de la utilizator scorul minim pentru participantii ce trebuie filtrati,
si lanseaza functia de eliminare a lor, precum si functia de afisare a repo-ului
input: char* in - sirul de caractere ce trebuie verificat
postconditii: - returneaza 0 daca sirul nu este un numar
			  - returneaza 1 daca sirul este un numar int
			  - returneaza 2 daca sirul este un numar float
*/
int check_nr(char* in);

#endif