#include "domain.h"
/*
creaza un participant(struct)
input: char* nume - adresa sirului de caractere, reprezentand numele participantului
	   char* prenume - adresa sirului de caractere, reprezentand prenumele participantului
	   char* scor - adresa sirului de caractere, reprezentand scorului participantului
*/
Participant creeaza_participant(char* nume, char* prenume, char* scor)
{
	Participant participant;
	int len_string = strlen(nume) + 1;
	participant.nume = malloc(sizeof(char) * len_string);
	strcpy(participant.nume, nume);
	len_string = strlen(prenume) + 1;
	participant.prenume = malloc(sizeof(char) * len_string);
	strcpy(participant.prenume, prenume);
	sscanf(scor, "%f", &participant.scor);
	return participant;
}

void distruge_participant(Participant* participant)
{
	free(participant->nume);
	free(participant->prenume);
	participant->nume = NULL;
	participant->prenume = NULL;
	participant->scor = -1;
}