#ifndef SERVICE_H_
#define SERVICE_H_

#define _CRT_SECURE_NO_WARNINGS
#include "repository.h"
#include "utils.h"
#include "validators.h"


/*
lanseaza verificarea datelor participantului si adaugarea lui in repo
input: Repo* repo - adresa structurii de tip Repo
		char* nume - adresa sirului de caractere, reprezentand numele participantului
		char* prenume - adresa sirului de caractere, reprezentand prenumele participantului
		char* scor - adresa sirului de caractere, reprezentand scorului participantului
postconditii: - lista este completata de un nou participant, daca este validat cu succes, si returneaza 0
			  - returneza 1 daca numele e invalid
			  - returneza 2 daca prenumele e invalid
			  - returneza 3 daca numele si prenumele sunt invalide
			  - returneza 4 daca scorul este invalid
			  - returneza 5 daca numele si scorul sunt invalide
			  - returneza 6 daca prenumele si scorul sunt invalide
			  - returneza 7 daca numele si prenumele sunt invalide
*/
int service_adauga_participant(Repo* repo, char* nume, char* prenume, char* scor);

/*
lanseaza verificarea datelor participantului si modificarea lui in repo
input: Repo* repo - adresa structurii de tip Repo
		int id - id-ul persoanei ce trebuie modificate
		char* nume - adresa sirului de caractere, reprezentand noul nume
		char* prenume - adresa sirului de caractere, reprezentand noul prenume
		char* scor - adresa sirului de caractere, reprezentand noul scor
postconditii: - participantul din lista este modificat, daca exista si daca este validat cu succes si returneaza 0
			  - returneaza -3 daca scorul a fost invalid
			  - returneaza -2 daca lista este goala
			  - returneaza -1 daca nu exista persoana data
			  - returneza 1 daca numele e invalid
			  - returneza 2 daca prenumele e invalid
			  - returneza 3 daca numele si prenumele sunt invalide
			  - returneza 4 daca scorul este invalid
			  - returneza 5 daca numele si scorul sunt invalide
			  - returneza 6 daca prenumele si scorul sunt invalide
			  - returneza 7 daca numele si prenumele sunt invalide
*/
int service_modifica_participant(Repo* repo, char* id, char* nume, char* prenume, char* scor);

/*
sterge un participant din lista de repo
input: Repo* repo - adresa structurii de tip Repo
		int id - id-ul persoanei ce trebuie sterse
postconditii: - participantul din lista este sters, daca exista si returneaza 0
			  - returneaza -3 daca scorul a fost invalid
			  - returneaza -2 daca lista este goala
			  - returneaza -1 daca nu exista persoana data
*/
int service_sterge_participant(Repo* repo, char* id);

/*
lanseaza operatia de filtrare din repo, si verifica daca scorul este valid
input: Repo* repo - adresa structurii de tip Repo
	   char* scor_sortare - scorul minim al persoanelor care vor fi sterse
postconditii: - repo nou, cu persoanele specificate, sterse, si returneaza 0 daca scorul a fost valid
			  - returneaza -3 daca scorul a fost invalid
*/
int service_filtrare_sub_scor(Repo* repo_nou, char* scor_sortare);

/*
lanseaza operatia de sortare din repo, si verifica daca reverse este valid
input: Repo* repo - adresa structurii de tip Repo
	   char* reverse - 0 daca se sorteaza lexicografie, diferit de 0 in caz contrar
postconditii: lista este sortata, si returneaza 0
			  returneaza -3 daca scorul a fost invalid
*/
int service_bubble_sort(Repo* repo_nou, char* reverse);



int cmp_nume(Participant p1, Participant p2);

#endif