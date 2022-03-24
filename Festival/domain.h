#ifndef DOMAIN_H_
#define DOMAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// o structura care contine doua pointere, catre un nume si prenume, si un float, reprezentand scorul participantului
typedef struct {
    char* nume;
    char* prenume;
    float scor;
} Participant;

/*
creaza un participant (struct)
input: char* nume - adresa sirului de caractere, reprezentand numele participantului
	   char* prenume - adresa sirului de caractere, reprezentand prenumele participantului
	   char* scor - adresa sirului de caractere, reprezentand scorului participantului
postconditii: returneaza adresa participantului
*/
Participant creeaza_participant(char* nume, char* prenume, char* scor);

/*
distruge (elibereaza) un participant
input: adresa struct Participant
postconditii: se elibereaza stringurile si se fac pointerii null-i
*/
void distruge_participant(Participant* participant);
#endif 