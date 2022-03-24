#include "validators.h"


/*
valideaza datele unui posibil participant
input: Repo* repo - adresa structurii de tip Repo
	   char* nume - adresa sirului de caractere, reprezentand numele participantului
	   char* prenume - adresa sirului de caractere, reprezentand prenumele participantului
	   char* scor - adresa sirului de caractere, reprezentand scorului participantului
postconditii: - returneaza 0 daca participantul este valid
			  - returneza 1 daca numele e invalid
			  - returneza 2 daca prenumele e invalid
			  - returneza 3 daca numele si prenumele sunt invalide
			  - returneza 4 daca scorul este invalid
			  - returneza 5 daca numele si scorul sunt invalide
			  - returneza 6 daca prenumele si scorul sunt invalide
			  - returneza 7 daca numele si prenumele sunt invalide
*/
int verificare_participant(char* nume, char* prenume, char* scor) {
	int eroare = 0;
	if (strlen(nume) == 0)
		eroare += 1;
	if (strlen(prenume) == 0) 
		eroare += 2;
	float nr;
	sscanf(scor, "%f", &nr);
	if (nr < 0 || nr > 10)
		eroare += 4;
	return eroare;
}