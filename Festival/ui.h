#ifndef UI_H_
#define UI_H_

#include <stdio.h>
#include <string.h>
#include "service.h"

/*
preia de la utilizator datele unui participant nou, si il adauga, sau lanseaza afisarea unei erori daca nu e bun
input: Repo* repo - adresa structurii de tip Repo
postconditii: lista este completata de un nou participant, daca nu au fost probleme,
			  sau se lanseaza afisarea erorilor in caz contrar
*/
void ui_adauga_participant(Repo* repo);

/*
preia de la utilizator id-ul si noile date ale unui participant, pentru a-l modifica, sau lanseaza
afisarea unei erori daca nu e bun
input: Repo* repo - adresa structurii de tip Repo
postconditii: participantul listei este modificat, daca nu au fost probleme,
			  sau se lanseaza afisarea erorilor in caz contrar
*/
void ui_modifica_participant(Repo* repo);

/*
preia de la utilizator id-ul unui participant ce trebuie sters si il sterge, sau sau lanseaza
afisarea unei erori daca nu e bun
input: Repo* repo - adresa structurii de tip Repo
postconditii: se sterge participantul dat, daca nu au fost probleme,
			  sau se lanseaza afisarea erorilor in caz contrar
*/
void ui_sterge_participant(Repo* repo);

/*
primeste de la utilizator scorul minim pentru participantii ce trebuie filtrati,
si lanseaza functia de eliminare a lor, precum si functia de afisare a repo-ului
input: Repo* repo - adresa structurii de tip Repo
*/
void ui_filtrare_sub_scor(Repo* repo);

/*
afiseaza toti participantii din lista
input: Repo* repo - adresa structurii de tip Repo
*/
void ui_afisare(Repo* repo);

/*
afiseaza un mesaj de eroare
input: Repo* repo - adresa structurii de tip Repo
	   int nr - numarul erorii ce trebuie afisate
precondintii: n apartine {-3, -2, -1, 1, 2, ... , 7}
*/
void ui_afisare_erori_validare(Repo*, int nr);

// afiseaza lista comenzilor
void ui_help();

// aplicatia principala
void run();

#endif