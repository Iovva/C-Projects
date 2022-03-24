#include "teste.h"

void teste_utils()
{
	char a[10] = "ad-d2";
	assert(check_nr(a) == 0);
	strcpy(a, "13");
	assert(check_nr(a) == 1);
	strcpy(a, "13.4");
	assert(check_nr(a) == 2);
}

void teste_validators() {
	char nume[20]; char prenume[20]; char scor[20];
	strcpy(nume, "Maria");
	strcpy(prenume, "Andreea");
	strcpy(scor, "5");
	assert(verificare_participant(nume, prenume, scor) == 0);
	strcpy(nume, "");
	assert(verificare_participant(nume, prenume, scor) == 1);
	strcpy(nume, "Maria");
	strcpy(prenume, "");
	assert(verificare_participant(nume, prenume, scor) == 2);
	strcpy(nume, "");
	assert(verificare_participant(nume, prenume, scor) == 3);
	strcpy(nume, "Maria");
	strcpy(prenume, "Andreea");
	strcpy(scor, "a");
	assert(verificare_participant(nume, prenume, scor) == 4);
	strcpy(nume, "");
	assert(verificare_participant(nume, prenume, scor) == 5);
	strcpy(nume, "Maria");
	strcpy(prenume, "");
	assert(verificare_participant(nume, prenume, scor) == 6);
	strcpy(nume, "");
	assert(verificare_participant(nume, prenume, scor) == 7);

}

void teste_repository() {
	Repo repo = creeaza_repo();
	repo.len = 0;
	char nume[20]; char prenume[20]; char scor[20];
	strcpy(nume, "Maria");
	strcpy(prenume, "Andreea");
	strcpy(scor, "5");
	repository_adauga_participant(&repo, nume, prenume, scor);
	assert(strcmp(repo.lista_participanti[0].nume, "Maria") == 0);
	assert(strcmp(repo.lista_participanti[0].prenume, "Andreea") == 0);
	assert(repo.lista_participanti[0].scor == 5);
	assert(repo.len == 1);
	strcpy(nume, "Alin");
	strcpy(prenume, "Bercecov");
	strcpy(scor, "7.3");
	repository_modifica_participant(&repo, 1, nume, prenume, scor);
	assert(strcmp(repo.lista_participanti[0].nume, "Alin") == 0);
	assert(strcmp(repo.lista_participanti[0].prenume, "Bercecov") == 0);
	assert(fabs(repo.lista_participanti[0].scor - 7.3) < 0.01);
	repository_sterge_participant(&repo, 1);
	assert(repo.len == 0);
	strcpy(nume, "Maria");
	strcpy(prenume, "Andreea");
	strcpy(scor, "5");
	repository_adauga_participant(&repo, nume, prenume, scor);
	strcpy(nume, "Alin");
	strcpy(prenume, "Bercecov");
	strcpy(scor, "6.3");
	repository_adauga_participant(&repo, nume, prenume, scor);
	strcpy(nume, "Alex");
	strcpy(prenume, "Berlioz");
	strcpy(scor, "8");
	repository_adauga_participant(&repo, nume, prenume, scor);

	Repo repo_nou = copyRepo(&repo);
	repository_filtrare_sub_scor(&repo_nou, 7);
	assert(repo_nou.len == 2);
	distruge_repo(&repo_nou);

	repository_bubble_sort(&repo, 0, cmp_nume);
	assert(strcmp(repo.lista_participanti[0].nume, "Alex") == 0);
	assert(strcmp(repo.lista_participanti[0].prenume, "Berlioz") == 0);
	assert(repo.lista_participanti[0].scor == 8);
	assert(strcmp(repo.lista_participanti[1].nume, "Alin") == 0);
	assert(strcmp(repo.lista_participanti[1].prenume, "Bercecov") == 0);
	assert(fabs(repo.lista_participanti[1].scor - 6.3) < 0.01);
	assert(strcmp(repo.lista_participanti[2].nume, "Maria") == 0);
	assert(strcmp(repo.lista_participanti[2].prenume, "Andreea") == 0);
	assert(repo.lista_participanti[2].scor == 5);

	repository_bubble_sort(&repo, 1, cmp_nume);
	assert(strcmp(repo.lista_participanti[0].nume, "Maria") == 0);
	assert(strcmp(repo.lista_participanti[0].prenume, "Andreea") == 0);
	assert(repo.lista_participanti[0].scor == 5);
	assert(strcmp(repo.lista_participanti[1].nume, "Alin") == 0);
	assert(strcmp(repo.lista_participanti[1].prenume, "Bercecov") == 0);
	assert(fabs(repo.lista_participanti[1].scor - 6.3) < 0.01);
	assert(strcmp(repo.lista_participanti[2].nume, "Alex") == 0);
	assert(strcmp(repo.lista_participanti[2].prenume, "Berlioz") == 0);
	assert(repo.lista_participanti[2].scor == 8);
	
	distruge_repo(&repo);

}

void teste_service() {
	Repo repo = creeaza_repo();
	repo.len = 0;
	char nume[20]; char prenume[20]; char scor[20];
	strcpy(nume, "");
	strcpy(prenume, "Andreea");
	strcpy(scor, "5");
	assert(service_adauga_participant(&repo, nume, prenume, scor) == 1);
	strcpy(nume, "Maria");
	strcpy(prenume, "");
	assert(service_adauga_participant(&repo, nume, prenume, scor) == 2);
	strcpy(nume, "");
	assert(service_adauga_participant(&repo, nume, prenume, scor) == 3);
	strcpy(nume, "Maria");
	strcpy(prenume, "Andreea");
	strcpy(scor, "a");
	assert(service_adauga_participant(&repo, nume, prenume, scor) == 4);
	strcpy(nume, "");
	assert(service_adauga_participant(&repo, nume, prenume, scor) == 5);
	strcpy(nume, "Maria");
	strcpy(prenume, "");
	assert(service_adauga_participant(&repo, nume, prenume, scor) == 6);
	strcpy(nume, "");
	assert(service_adauga_participant(&repo, nume, prenume, scor) == 7);
	strcpy(nume, "Maria");
	strcpy(prenume, "Andreea");
	strcpy(scor, "5");
	assert(service_adauga_participant(&repo, nume, prenume, scor) == 0);
	
	strcpy(nume, "");
	strcpy(prenume, "Andreea");
	strcpy(scor, "5");
	assert(service_modifica_participant(&repo, "1", nume, prenume, scor) == 1);
	strcpy(nume, "Maria");
	strcpy(prenume, "");
	assert(service_modifica_participant(&repo, "1", nume, prenume, scor) == 2);
	strcpy(nume, "");
	assert(service_modifica_participant(&repo, "1", nume, prenume, scor) == 3);
	strcpy(nume, "Maria");
	strcpy(prenume, "Andreea");
	strcpy(scor, "a");
	assert(service_modifica_participant(&repo, "1", nume, prenume, scor) == 4);
	strcpy(nume, "");
	assert(service_modifica_participant(&repo, "1", nume, prenume, scor) == 5);
	strcpy(nume, "Maria");
	strcpy(prenume, "");
	assert(service_modifica_participant(&repo, "1", nume, prenume, scor) == 6);
	strcpy(nume, "");
	assert(service_modifica_participant(&repo, "1", nume, prenume, scor) == 7);
	
	strcpy(nume, "Alin");
	strcpy(prenume, "Bercecov");
	strcpy(scor, "7.3");
	assert(repo.len == 1);
	assert(service_modifica_participant(&repo, "a", nume, prenume, scor) == -3);
	assert(service_modifica_participant(&repo, "1.3", nume, prenume, scor) == -3);
	assert(service_modifica_participant(&repo, "1", nume, prenume, scor) == 0);
	assert(service_modifica_participant(&repo, "2", nume, prenume, scor) == -1);
	assert(service_modifica_participant(&repo, "1", nume, prenume, scor) == 0);
	assert(service_sterge_participant(&repo, "a") == -3);
	assert(service_sterge_participant(&repo, "1.3") == -3);
	assert(service_sterge_participant(&repo, "2") == -1);
	assert(service_sterge_participant(&repo, "1") == 0);
	assert(repo.len == 0);
	assert(service_sterge_participant(&repo, "1") == -2);
	assert(service_modifica_participant(&repo, "1", nume, prenume, scor) == -2);

	strcpy(nume, "Maria");
	strcpy(prenume, "Andreea");
	strcpy(scor, "5");
	service_adauga_participant(&repo, nume, prenume, scor);
	strcpy(nume, "Alin");
	strcpy(prenume, "Bercecov");
	strcpy(scor, "7.3");
	service_adauga_participant(&repo, nume, prenume, scor);
	assert(service_bubble_sort(&repo, "a") == -3);
	assert(service_bubble_sort(&repo, "1") == 0);
	assert(service_filtrare_sub_scor(&repo, "a") == -3);
	assert(service_filtrare_sub_scor(&repo, "5") == 0);
	assert(repo.len == 0);

	distruge_repo(&repo);
}

void teste_all() {
	teste_utils();
	teste_validators();
	teste_repository();
	teste_service();
}