#include "utils.h"

/*
primeste de la utilizator scorul minim pentru participantii ce trebuie filtrati,
si lanseaza functia de eliminare a lor, precum si functia de afisare a repo-ului
input: char* in - sirul de caractere ce trebuie verificat
postconditii: - returneaza 0 daca sirul nu este un numar
			  - returneaza 1 daca sirul este un numar int
			  - returneaza 2 daca sirul este un numar float
*/
int check_nr(char* in)
{
	float f;
	int i;
	if ((sscanf(in, "%f", &f)) == 0)
		return 0;
	sscanf(in, "%d", &i);
	if (f == i)
		return 1;
	return 2;
}