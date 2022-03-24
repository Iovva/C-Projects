#include "ui.h"

/*
preia de la utilizator datele unui participant nou, si il adauga, sau lanseaza afisarea unei erori daca nu e bun
input: Repo* repo - adresa structurii de tip Repo
postconditii: lista este completata de un nou participant, daca nu au fost probleme, 
		      sau se lanseaza afisarea erorilor in caz contrar
*/
void ui_adauga_participant(Repo* repo) {
	char nume[20], prenume[20], scor[20];
	printf("\nIntroduceti numele:");
	fgets(nume, 20, stdin);
	printf("\nIntroduceti prenumele:");
	fgets(prenume, 20, stdin);
	printf("\nIntroduceti scorul:");
	fgets(scor, 20, stdin);
	int eroare = service_adauga_participant(repo, nume, prenume, scor);
	if (eroare != 0)
		ui_afisare_erori_validare(repo, eroare);
}

/*
preia de la utilizator id-ul si noile date ale unui participant, pentru a-l modifica, sau lanseaza 
afisarea unei erori daca nu e bun
input: Repo* repo - adresa structurii de tip Repo
postconditii: participantul listei este modificat, daca nu au fost probleme,
			  sau se lanseaza afisarea erorilor in caz contrar
*/
void ui_modifica_participant(Repo* repo) {
	char nume[20], prenume[20], scor[20], id[20];
	printf("Introduceti indicele participantului ce trebuie modificat:");
	fgets(id, 20, stdin);
	// getchar() in caz de urgenta
	printf("\nIntroduceti numele:");
	fgets(nume, 20, stdin);
	printf("\nIntroduceti prenumele:");
	fgets(prenume, 20, stdin);
	printf("\nIntroduceti scorul:");
	fgets(scor, 20, stdin);

	int eroare = service_modifica_participant(repo, id, nume, prenume, scor);
	if (eroare != 0)
		ui_afisare_erori_validare(repo, eroare);
}

/*
preia de la utilizator id-ul unui participant ce trebuie sters si il sterge, sau sau lanseaza 
afisarea unei erori daca nu e bun
input: Repo* repo - adresa structurii de tip Repo
postconditii: se sterge participantul dat, daca nu au fost probleme,
			  sau se lanseaza afisarea erorilor in caz contrar
*/
void ui_sterge_participant(Repo* repo) {
	printf("Introduceti indicele participantului ce trebuie eliminat din lista:");
	char id[20];
	fgets(id, 20, stdin);
	int eroare = service_sterge_participant(repo, id);
	if (eroare != 0)
		ui_afisare_erori_validare(repo, eroare);
}

/*
preia de la utilizator un scor maxim pe care il pot avea participantii, si ii afiseaza
input: Repo* repo - adresa structurii de tip Repo
*/
void ui_filtrare_sub_scor(Repo* repo) {
	printf("Introduceti scorul maxim al participantilor ce trebuie afisati:");
	char scor_sortare[20];
	fgets(scor_sortare, 20, stdin);
	Repo repo_nou = copyRepo(repo);
	int eroare = service_filtrare_sub_scor(&repo_nou, scor_sortare);
	if (eroare != 0)
		ui_afisare_erori_validare(repo, eroare);
	else
		ui_afisare(&repo_nou);
	distruge_repo(&repo_nou);
}
/*
preia de la utilizator modul de sortare si lanseaza afisarea listei sortate
input: Repo* repo - adresa structurii de tip Repo
*/
void ui_sortare(Repo* repo) {
	printf("Introduceti 0 daca doriti ca sortarea sa fie lexicografica, sau alt numar:");
	char reverse[20];
	fgets(reverse, 20, stdin);
	Repo repo_nou = copyRepo(repo);
	int eroare = service_bubble_sort(&repo_nou, reverse);
	if (eroare != 0)
		ui_afisare_erori_validare(repo, eroare);
	else
		ui_afisare(&repo_nou);
	distruge_repo(&repo_nou);
}

/*
afiseaza toti participantii din lista
input: Repo* repo - adresa structurii de tip Repo
*/
void ui_afisare(Repo* repo) {
	for (int i = 0; i < repo->len; i++)
		printf("\n%d - Nume: %s\n    Prenume: %s\n    Scor: %f\n", i + 1, repo->lista_participanti[i].nume,
			repo->lista_participanti[i].prenume, repo->lista_participanti[i].scor);
}

/*
afiseaza un mesaj de eroare
input: Repo* repo - adresa structurii de tip Repo
	   int nr - numarul erorii ce trebuie afisate
precondintii: n apartine {-2, -1, 1, 2, ... , 7}
*/
void ui_afisare_erori_validare(Repo* repo, int nr) {
	switch (nr) {
	case -3:
		printf("\nIndice invalid!\n");
		break;
	case -2:
		printf("\nNu exista nici un participant in lista!\n");
		break;
	case -1:
		printf("\nNu exista participantul dat!\nUltimul participant are id-ul: %d\n", repo->len);
		break;
	case 1:
		printf("\nNume invalid!\n");
		break;
	case 2:
		printf("\nPrenume invalid!\n");
		break;
	case 3:
		printf("\nNume invalid!");
		printf("\nPrenume invalid!\n");
		break;
	case 4:
		printf("\nScor invalid!\n");
		break;
	case 5:
		printf("\nNume invalid!");
		printf("\nScor invalid!\n");
		break;
	case 6:
		printf("\nPrenume invalid!");
		printf("\nScor invalid!");
		break;
	case 7:
		printf("\nNume invalid!");
		printf("\nPrenume invalid!");
		printf("\nScor invalid!\n");
		break;
	}
}

// afiseaza lista comenzilor
void ui_help() {
	printf("\nIntroduceti comanda:\n"
		"1 - adauga participant\n"
		"2 - modifica participant\n"
		"3 - sterge participant\n"
		"4 - filtrare dupa scor (afiseaza toti participantii cu scorul mai mic decat un numar dat)\n"
		"5 - afisare participanti\n"
		"6 - sortare participanti (dupa nume)\n"
		"7 - iesire\n\n");
}

// aplicatia principala
void run() {
	Repo repo = creeaza_repo();
	repo.len = 0;
	ui_help();
	int run = 1, cmd = 0;
	char cmd_string[20];
	while (run == 1)
	{
		printf(">>>");
		fgets(cmd_string, 20, stdin);
		if (check_nr(cmd_string) != 1)
			cmd = -1;
		else
			cmd = atoi(cmd_string);
		switch (cmd) {
		case 0:
			ui_help();
			break;
		case 1:
			ui_adauga_participant(&repo);
			break;
		case 2:
			ui_modifica_participant(&repo);
			break;
		case 3:
			ui_sterge_participant(&repo);
			break;
		case 4:
			ui_filtrare_sub_scor(&repo);
			break;
		case 5:
			ui_afisare(&repo);
			break;
		case 6:
			ui_sortare(&repo);
			break;
		case 7:
			run = 0;
			break;
		default:
			printf("Comanda invalida!\n"
				"Introduceti comanda ' 0 ' pentru ajutor!\n");
			break;
		}
	}
	distruge_repo(&repo);
	printf("\nAdios!\n");
}