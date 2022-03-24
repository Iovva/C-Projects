#ifndef VALIDATORS_H_
#define _CRT_SECURE_NO_WARNINGS
#define VALIDATORS_H_

#include <stdio.h>
#include <string.h>
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
int verificare_participant(char* nume, char* prenume, char* scor);

#endif