#include "repository.h"

// creeaza un repo gol
Repo creeaza_repo()
{
	Repo repo;
	repo.len = 0;
	repo.cap = 2;
	repo.lista_participanti = malloc(sizeof(Participant) * repo.cap);
	return repo;
}

/*
verifica daca mai este loc in repo, si mareste spatiul disponibil in caz contrar
input: Repo* repo - pointer la struct repo
*/
void verifica_capacitate(Repo* repo)
{
	if (repo->len < repo->cap)
		return;
	int new_cap = repo->len + 2;
	Participant* new_lista_participanti = malloc(sizeof(Participant) * new_cap);
	for (int i = 0; i < repo->len; i++) {
		new_lista_participanti[i] = repo->lista_participanti[i];
	}
	free(repo->lista_participanti);
	repo->lista_participanti = new_lista_participanti;
	repo->cap = new_cap;
}

/*
distruge (elibereaza) spatiul ocupat de repository
input: Repo* repo - pointer la struct repo
*/
void distruge_repo(Repo* repo)
{
	for (int i = 0; i < repo->len; i++)
		distruge_participant(&repo->lista_participanti[i]);
	free(repo->lista_participanti);
	repo->lista_participanti = NULL;
	repo->len = 0;
}

/*
adauga in lista de repo un nou participant
input: Repo* repo - adresa structurii de tip Repo
	   char* nume - adresa sirului de caractere, reprezentand numele participantului
	   char* prenume - adresa sirului de caractere, reprezentand prenumele participantului
	   char* scor - adresa sirului de caractere, reprezentand scorului participantului
postconditii: lista este completata de un nou participant
*/
void repository_adauga_participant(Repo* repo, char* nume, char* prenume, char* scor) {
	verifica_capacitate(repo);
	Participant participant = creeaza_participant(nume, prenume, scor);
	repo->lista_participanti[repo->len] = participant;
	repo->len++;
}

/*
modifica un participant in lista de repo
input: Repo* repo - adresa structurii de tip Repo
	   int id - id-ul persoanei ce trebuie modificate
	   char* nume - adresa sirului de caractere, reprezentand noul nume
	   char* prenume - adresa sirului de caractere, reprezentand noul prenume
	   char* scor - adresa sirului de caractere, reprezentand noul scor
postconditii: participantul din lissta este modificat, daca exista
*/
void repository_modifica_participant(Repo* repo, int id, char* nume, char* prenume, char* scor) {
	Participant participant = creeaza_participant(nume, prenume, scor);
	distruge_participant(&repo->lista_participanti[id - 1]);
	repo->lista_participanti[id - 1] = participant;
}

/*
sterge un participant din lista de repo
input: Repo* repo - adresa structurii de tip Repo
	   int id - id-ul persoanei ce trebuie sterse
postconditii: participantul din lissta este sters, daca exista
*/
void repository_sterge_participant(Repo* repo, int id)
{
	distruge_participant(&repo->lista_participanti[id - 1]);
	for (int i = id - 1; i < repo->len - 1; i++)
	{ 
		repo->lista_participanti[i] = repo->lista_participanti[i + 1];
	}
	repo->len--;

}

/*
sterge toti participantii care au scorul mai mic ca unul dat
input: Repo* repo_nou - adresa structurii de tip Repo
	   float scor_sortare - scorul maxim
postconditii: repo-ul modificat
*/
void repository_filtrare_sub_scor(Repo* repo_nou, float scor_sortare) {
	for (int i = 0; i < repo_nou->len; i++)
	{
		if (repo_nou->lista_participanti[i].scor >= scor_sortare)
		{
			repository_sterge_participant(repo_nou, i + 1);
			i--;
		}
	}

}

/*
sorteaza participantii dupa nume, folosind bubble sort
input: Repo* repo_nou - adresa structurii de tip Repo care contine participantii
	   int reverse - 0 daca se sorteaza lexicografie, diferit de 0 in caz contrar
postconditii: repo-ul sortat
*/
void repository_bubble_sort(Repo* repo_nou, int reverse, cmp f)
{
	int sort = 0;
	while (sort == 0)
	{	
		sort = 1;
		for (int i = 0; i < repo_nou->len - 1; i++)
		{	
			Participant p1 = (repo_nou->lista_participanti)[i];
			Participant p2 = (repo_nou->lista_participanti)[i + 1];
			if ((f(p1, p2) > 0 && reverse == 0) || 
				(f(p1, p2) < 0 && reverse != 0))
			{
				char* temp = repo_nou->lista_participanti[i].nume;
				repo_nou->lista_participanti[i].nume = repo_nou->lista_participanti[i + 1].nume;
				repo_nou->lista_participanti[i + 1].nume = temp;
				temp = repo_nou->lista_participanti[i].prenume;
				repo_nou->lista_participanti[i].prenume = repo_nou->lista_participanti[i + 1].prenume;
				repo_nou->lista_participanti[i + 1].prenume = temp;
				float temp_f = repo_nou->lista_participanti[i].scor;
				repo_nou->lista_participanti[i].scor = repo_nou->lista_participanti[i + 1].scor;
				repo_nou->lista_participanti[i + 1].scor = temp_f;
				sort = 0;
			}
		}
	}
}

Repo copyRepo(Repo* repo) {
	Repo repo_nou = creeaza_repo();
	for (int i = 0; i < repo->len; i++) {
		Participant p = (repo->lista_participanti)[i];
		repository_adauga_participant(&repo_nou, p.nume, p.prenume, "1");
		repo_nou.lista_participanti[i].scor = p.scor;
	}
	return repo_nou;
}