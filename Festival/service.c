#include "service.h"

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
int service_adauga_participant(Repo* repo, char* nume, char* prenume, char* scor) {
	int eroare = verificare_participant(nume, prenume, scor);
	if (eroare != 0)
		return eroare;
	repository_adauga_participant(repo, nume, prenume, scor);
	return 0;
}

/*
lanseaza verificarea datelor participantului si modificarea lui in repo
input: Repo* repo - adresa structurii de tip Repo
		int id - id-ul persoanei ce trebuie modificate
		char* nume - adresa sirului de caractere, reprezentand noul nume
		char* prenume - adresa sirului de caractere, reprezentand noul prenume
		char* scor - adresa sirului de caractere, reprezentand noul scor
postconditii: - participantul din lista este modificat, daca exista si daca este validat cu succes si returneaza 0
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
int service_modifica_participant(Repo* repo, char* id, char* nume, char* prenume, char* scor) {
	if (check_nr(id) != 1)
		return -3;
	int id_int = atoi(id);
	if (repo->len == 0) return -2;
	if (repo->len < id_int || id_int < 0) return -1;
	int eroare = verificare_participant(nume, prenume, scor);
	if (eroare != 0)
		return eroare;
	repository_modifica_participant(repo, id_int, nume, prenume, scor);
	return 0;
}

/*
sterge un participant din lista de repo
input: Repo* repo - adresa structurii de tip Repo
		int id - id-ul persoanei ce trebuie sterse
postconditii: - participantul din lista este sters, daca exista si returneaza 0
			  - returneaza -2 daca lista este goala
			  - returneaza -1 daca nu exista persoana data
*/
int service_sterge_participant(Repo* repo, char* id) {
	if (check_nr(id) != 1)
		return -3;
	int id_int = atoi(id);
	if (repo->len == 0) return -2;
	if (repo->len < id_int || id_int < 0) return -1;
	repository_sterge_participant(repo, id_int);
	return 0;
}

/*
lanseaza aplicatia de stergere cu filtrare din repository
input: Repo* repo_nou - adresa structurii de tip Repo
	   float scor_sortare - scorul maxim
*/
int service_filtrare_sub_scor(Repo* repo_nou, char* scor_sortare) {
	if (check_nr(scor_sortare) == 2 || check_nr(scor_sortare) == 1)
	{
		float scor_sortare_float;
		sscanf(scor_sortare, "%f", &scor_sortare_float);
		repository_filtrare_sub_scor(repo_nou, scor_sortare_float);
		return 0;
	}
	return -3;
}

/*
lanseaza operatia de sortare din repo, si verifica daca reverse este valid
input: Repo* repo - adresa structurii de tip Repo
	   char* reverse - 0 daca se sorteaza lexicografie, diferit de 0 in caz contrar
postconditii: lista este sortata, si returneaza 0
			  returneaza -3 daca scorul a fost invalid
*/
int service_bubble_sort(Repo * repo_nou, char* reverse) {
	if (check_nr(reverse) == 1)
	{
		int reverse_int;
		sscanf(reverse, "%d", &reverse_int);
		repository_bubble_sort(repo_nou, reverse_int, cmp_nume);
		return 0;
	}
	return -3;
}

int cmp_nume(Participant p1, Participant p2) {
	return strcmp(p1.nume, p2.nume);
}
