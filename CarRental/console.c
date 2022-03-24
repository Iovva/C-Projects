#include "console.h"

void ui_add(MyList* r, MyList* undo_r, int* undo_count) {
	char registration_number[MAX_CHARS];
	char brand[MAX_CHARS];
	char category[MAX_CHARS];

	fgetc(stdin);
	printf("Please fill in the following information about the vehicle:\n");
	printf("Registration number: ");
	fgets(registration_number, sizeof(registration_number), stdin);
	registration_number[strcspn(registration_number, "\n")] = 0;
	printf("Brand: ");
	fgets(brand, sizeof(brand), stdin);
	brand[strcspn(brand, "\n")] = 0;
	printf("Category: ");
	fgets(category, sizeof(category), stdin);
	category[strcspn(category, "\n")] = 0;

	int exit_code = serv_add(r, registration_number, brand, category);

	if (exit_code == 0) {
		printf("\nThe vehicle has been succesfully added!");
		serv_adauga_undo(r, undo_r, undo_count);
	}
	else if (exit_code == 2) {
		printf("\nThe vehicle already exists!");
	}
	else {
		if (exit_code % 10 != 0) printf("\nInvalid registration number!");
		exit_code = exit_code / 10;
		if (exit_code % 10 != 0) printf("\nInvalid brand!");
		exit_code = exit_code / 10;
		if (exit_code % 10 != 0) printf("\nInvalid category!");
	}
	printf("\n\n");

}

void ui_modify(MyList* r, MyList* undo_r, int* undo_count) {
	char registration_number[MAX_CHARS];
	char brand[MAX_CHARS];
	char category[MAX_CHARS];

	fgetc(stdin);
	printf("Please fill in the following information about the vehicle:\n");
	printf("Registration number: ");
	fgets(registration_number, sizeof(registration_number), stdin);
	registration_number[strcspn(registration_number, "\n")] = 0;
	printf("Brand: ");
	fgets(brand, sizeof(brand), stdin);
	brand[strcspn(brand, "\n")] = 0;
	printf("Category: ");
	fgets(category, sizeof(category), stdin);
	category[strcspn(category, "\n")] = 0;

	int exit_code = serv_modify(r, registration_number, brand, category);

	if (exit_code == 0) {
		printf("\nThe vehicle has been succesfully modified!");
		serv_adauga_undo(r, undo_r, undo_count);
	}
	else if (exit_code == 2) {
		printf("\nThe vehicle already exists!");
	}
	else {
		if (exit_code % 10 != 0) printf("\nInvalid registration number!");
		exit_code = exit_code / 10;
		if (exit_code % 10 != 0) printf("\nInvalid brand!");
		exit_code = exit_code / 10;
		if (exit_code % 10 != 0) printf("\nInvalid category!");
	}
	printf("\n\n");
}

void ui_rent(MyList* r, MyList* undo_r, int* undo_count) {
	char cnp[MAX_CHARS];
	char name[MAX_CHARS];
	char reg_num[MAX_CHARS];

	fgetc(stdin);
	printf("CNP: ");
	fgets(cnp, sizeof(cnp), stdin);
	cnp[strcspn(cnp, "\n")] = 0;
	printf("Name: ");
	fgets(name, sizeof(name), stdin);
	name[strcspn(name, "\n")] = 0;
	printf("Registration number: ");
	fgets(reg_num, sizeof(name), stdin);
	reg_num[strcspn(reg_num, "\n")] = 0;
	int exit_code = serv_rent(r, cnp, name, reg_num);
	if (exit_code == 0)
	{
		printf("Vehicle rented succesfully!");
		serv_adauga_undo(r, undo_r, undo_count);
	}
	else if (exit_code == 1)
		printf("Vehicle already rented!");
	else if (exit_code == 2)
		printf("Vehicle not found!");
	else
		printf("Invalid data!");
	printf("\n\n");
}

void ui_return(MyList* r, MyList* undo_r, int* undo_count) {
	char reg_num[MAX_CHARS];

	fgetc(stdin);
	printf("Registration number: ");
	fgets(reg_num, sizeof(reg_num), stdin);
	reg_num[strcspn(reg_num, "\n")] = 0;
	int exit_code = serv_return(r, reg_num);
	if (exit_code == 0)
	{
		printf("Vehicle returned succesfully!");
		serv_adauga_undo(r, undo_r, undo_count);
	}
	else if (exit_code == 1)
		printf("Vehicle was not rented!");
	else if (exit_code == 2)
		printf("Vehicle not found!");
	else
		printf("Invalid data!");
	printf("\n\n");
}

void ui_search(MyList* r) {
	char brand[MAX_CHARS];
	char category[MAX_CHARS];

	fgetc(stdin);
	printf("Leave blank if you dont want to search by that criteria\n");
	printf("Brand: ");
	fgets(brand, sizeof(brand), stdin);
	brand[strcspn(brand, "\n")] = 0;
	printf("Category: ");
	fgets(category, sizeof(category), stdin);
	category[strcspn(category, "\n")] = 0;

	MyList* found_vehicles = serv_search(r, brand, category);
	if (repo_len(found_vehicles) != 0) {
		int nr = 0;
		Iterator* i = it_create(found_vehicles);
		it_first(i);
		printf("\n");
		while(it_valid(i)) {
			printf("Vehicle %d:\n", nr++);
			printf("%s\n%s\n%s\n\n", it_element(i)->registration_number, it_element(i)->brand, it_element(i)->category);
			it_next(i);
		}
		it_destroy(i);
	}
	else {
		printf("\nNo vehicles found!\n\n");
	}
	repo_destroy(found_vehicles);
}

void ui_sort(MyList* r, MyList* undo_r, int* undo_count) {
	fgetc(stdin);
	printf("Sort by:\n");
	printf("1 - Brand\n");
	printf("2 - Category\n");
	printf("3 - Back\n");
	printf("Your opion: ");
	int option;
	scanf("%d", &option);
	printf("\n");
	if (option == 3) {
		printf("Cancelling...");
	}
	else if (option != 1 && option != 2) {
		printf("I'm sorry but I don't know that option!");
	}
	else {
		printf("1 - Ascending\n");
		printf("2 - Descending\n");
		printf("Your opion: ");
		int reverse;
		scanf("%d", &reverse);
		printf("\n");
		reverse = reverse - 1;
		if (reverse == 0 || reverse == 1) {
			if (option == 1) {
				serv_sort_brand(r, reverse);
			}
			if (option == 2) {
				serv_sort_category(r, reverse);
			}
			printf("Sorted succesfully!");
			serv_adauga_undo(r, undo_r, undo_count);
		}
		else {
			printf("I'm sorry but I don't know that option!");
		}
	}
	printf("\n\n");
}

void ui_filtrare(MyList* r, MyList* undo_r, int* undo_count) {
	fgetc(stdin);
	printf("Introduceti brandul pe care vreti sa il filtrati!:\n");
	char brand_filtrare[20];
	fgets(brand_filtrare, 20, stdin);
	brand_filtrare[strcspn(brand_filtrare, "\n")] = 0;
	serv_filtrare(r, brand_filtrare);
	serv_adauga_undo(r, undo_r, undo_count);
	printf("\nFiltrare executata cu succes!\n");
}

void ui_undo(MyList** r, MyList* undo_r, int* undo_count) {
	if (*undo_count == 0) {
		printf("Nu se mai poate realiza undo!\n");
		return;
	}
	serv_undo( r,  undo_r, undo_count);
}

void ui_afisare_judet(MyList* r) {
	char judet[MAX_CHARS];

	fgetc(stdin);
	printf("Introduceti judetul:");
	fgets(judet, sizeof(judet), stdin);
	judet[strcspn(judet, "\n")] = 0;

	MyList* found_vehicles = serv_afisare_judet(r, judet);
	if (repo_len(found_vehicles) != 0) {
		int nr = 0;
		Iterator* i = it_create(found_vehicles);
		it_first(i);
		printf("\n");
		while (it_valid(i)) {
			printf("Vehicle %d:\n", nr++);
			printf("%s\n%s\n%s\n\n", it_element(i)->registration_number, it_element(i)->brand, it_element(i)->category);
			it_next(i);
		}
		it_destroy(i);
	}
	else {
		printf("\nNo vehicles found!\n\n");
	}
	repo_destroy(found_vehicles);
}


void ui_run() {
	MyList* repo = repo_create();
	MyList* undo_repo = repo_create();
	int undo_count = 0;
	int cmd;
	int quit = 0;
	while (!quit) {
		printf("Menu:\n");
		printf("1 - Add vehicle\n");
		printf("2 - Modify vehicle\n");
		printf("3 - Rent vehicle\n");
		printf("4 - Return vehicle\n");
		printf("5 - Search vehicles\n");
		printf("6 - Sort vehicles\n");
		printf("7 - Filtrare\n");
		printf("8 - Undo\n");
		printf("9 - QUIT\n");
		printf("10 - Afisare judet\n");
		printf("Your option: ");

		scanf("%d", &cmd);
		printf("\n");

		switch (cmd) {
		case 1:
			ui_add(repo, undo_repo, &undo_count);
			break;
		case 2:
			ui_modify(repo, undo_repo, &undo_count);
			break;
		case 3:
			ui_rent(repo, undo_repo, &undo_count);
			break;
		case 4:
			ui_return(repo, undo_repo, &undo_count);
			break;
		case 5:
			ui_search(repo);
			break;
		case 6:
			ui_sort(repo, undo_repo, &undo_count);
			break;
		case 7:
			ui_filtrare(repo, undo_repo, &undo_count);
			break;
		case 8:
			ui_undo(&repo, undo_repo, &undo_count);
			break;
		case 9:
			printf("Have a great day!\n");
			quit = 1;
			break;
		case 10:
			ui_afisare_judet(repo);
			break;
		default:
			printf("I'm sorry but I don't know that option!\n\n");
		}
	}
	destroy(repo, vehicle_destroy);	
	destroy(undo_repo, destroy_lista_vehicule);
}
