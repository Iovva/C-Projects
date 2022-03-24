#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include "domain.h"
#include <string.h>

// o structura care contine un vector de 100 de participanti, de tipul struct Participant, si numarul participantilor din lista
typedef struct {
	Participant* lista_participanti;
	int len;
	int cap;
} Repo;

// creeaza un repo gol
Repo creeaza_repo();

/*
verifica daca mai este loc in repo, si mareste spatiul disponibil in caz contrar
input: Repo* repo - pointer la struct repo
*/
void verifica_capacitate(Repo* repo);

/*
distruge (elibereaza) spatiul ocupat de repository
input: Repo* repo - pointer la struct repo
*/
void distruge_repo(Repo* repo);

/*
adauga in lista de repo un nou participant
input: Repo* repo - adresa structurii de tip Repo
	   char* nume - adresa sirului de caractere, reprezentand numele participantului
	   char* prenume - adresa sirului de caractere, reprezentand prenumele participantului
	   char* scor - adresa sirului de caractere, reprezentand scorului participantului
postconditii: lista este completata de un nou participant
*/
void repository_adauga_participant(Repo* repo, char* nume, char* prenume, char* scor);

/*
modifica un participant in lista de repo
input: Repo* repo - adresa structurii de tip Repo
	   int id - id-ul persoanei ce trebuie modificate
	   char* nume - adresa sirului de caractere, reprezentand noul nume
	   char* prenume - adresa sirului de caractere, reprezentand noul prenume
	   char* scor - adresa sirului de caractere, reprezentand noul scor
postconditii: participantul din lissta este modificat, daca exista
*/
void repository_modifica_participant(Repo* repo, int id, char* nume, char* prenume, char* scor);

/*
sterge un participant din lista de repo
input: Repo* repo - adresa structurii de tip Repo
       int id - id-ul persoanei ce trebuie sterse
postconditii: participantul din lissta este sters, daca exista
*/
void repository_sterge_participant(Repo* repo, int id);

/*
sterge toti din participantii care au scorul mai mic de scor_sortare
input: Repo* repo - adresa structurii de tip Repo
	   float scor_sortare - scorul minim al persoanelor care vor fi sterse
postconditii: repo nou, cu persoanele specificate, sterse
*/
void repository_filtrare_sub_scor(Repo* repo_nou, float scor_sortare);

/*
sorteaza participantii dupa nume, folosind bubble sort
input: Repo* repo_nou - adresa structurii de tip Repo care contine participantii
	   int reverse - 0 daca se sorteaza lexicografie, diferit de 0 in caz contrar
postconditii: repo-ul sortat
*/

Repo copyRepo(Repo* repo);

typedef int(*cmp)(Participant A, Participant B);

void repository_bubble_sort(Repo* repo_nou, int reverse, cmp f);
#endif