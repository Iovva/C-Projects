#include "service.h"

int serv_add(MyList* r, char* registration_number, char* brand, char* category) {
	Vehicle* v = vehicle_create(registration_number, brand, category);
	int valid = validate_vehicle(v);
	if (valid != 0) {
		vehicle_destroy(v);
		return valid;
	}
	int exit_code = repo_add(r, v);
	if (exit_code != 0)
		return 2;
	return 0;
}

int serv_modify(MyList* r, char* registration_number, char* brand, char* category) {
	Vehicle* v = vehicle_create(registration_number, brand, category);
	int valid = validate_vehicle(v);
	if (valid != 0) {
		vehicle_destroy(v);
		return valid;
	}
	if (repo_modify(r, v) != 0) return 2;
	return 0;
}

int serv_rent(MyList* r, char* cnp, char* name, char* registration_number) {
	if (validate_cnp(cnp) != 0) return 3;
	if (validate_name(name) != 0) return 3;
	if (validate_registration_number(registration_number) != 0) return 3;
	Vehicle* v = repo_search(r, registration_number);
	if (v == NULL) return 2;
	if (v->rented != 0) return 1;
	vehicle_rent(v, cnp, name);
	return 0;
}

int serv_return(MyList* r, char* registration_number) {
	if (validate_registration_number(registration_number) != 0) return 3;
	Vehicle* v = repo_search(r, registration_number);
	if (v == NULL) return 2;
	if (v->rented == 0) return 1;
	vehicle_return(v);
	return 0;
}

MyList* serv_search(MyList* r, char* brand, char* category) {
	MyList* found_vehicles = repo_create();

	Iterator* i = it_create(r);
	it_first(i);
	while (it_valid(i)) {
		if ((strlen(brand) == 0 || strstr(it_element(i)->brand, brand) != NULL) && (strlen(category) == 0 || strstr(it_element(i)->category, category) != NULL)) {
			Vehicle* copy = vehicle_copy(it_element(i));
			repo_add(found_vehicles, copy);
		}
		it_next(i);
	}
	it_destroy(i);

	return found_vehicles;
}

void serv_sort_brand(MyList* r, int reverse) {
	sort(r, cmp_brand, reverse);
}

void serv_sort_category(MyList* r, int reverse) {
	sort(r, cmp_category, reverse);
}

void serv_filtrare(MyList* r_nou, char* brand_filtrare) {
	repository_filtrare(r_nou, brand_filtrare);
}

void serv_adauga_undo(MyList* r, MyList* undo_r, int* undo_count) {
	MyList* repo_copy = copyRepo(r);
	add(undo_r, repo_copy);
	(*undo_count)++;
}

void serv_undo(MyList** r, MyList* undo_r, int* undo_count) {
	if (*undo_count == 1) {
		destroy(*r, vehicle_destroy);
		destroy(undo_r->e[undo_r->n - 1], vehicle_destroy);
		undo_r->n--;
		*r = repo_create();
		(*undo_count)--;
		return;
	}
	destroy(*r, vehicle_destroy);
	destroy(undo_r->e[undo_r->n - 1], vehicle_destroy);
	undo_r->n--;
	MyList* repo = (MyList*)undo_r->e[undo_r->n - 1];
	*r = copyRepo(repo);
	(*undo_count)--;
}

MyList* serv_afisare_judet(MyList* r, char* judet)
{
	MyList* found_vehicles = repo_create();

	Iterator* i = it_create(r);
	it_first(i);
	while (it_valid(i)) {
		char aux[3];
		char* reg = it_element(i)->registration_number;
		aux[0] = reg[0];
		aux[1] = reg[1];
		aux[2] = '\0';
		if (strcmp(judet, aux) == 0 && it_element(i)->rented == 1) {
			Vehicle* copy = vehicle_copy(it_element(i));
			repo_add(found_vehicles, copy);
		}
		it_next(i);
	}
	it_destroy(i);

	return found_vehicles;
}

void test_serv_add() {
	char registration_number[] = "CJ12ABC";
	char brand[] = "Opel Corsa C";
	char category[] = "Family car";
	MyList* r = repo_create();
	serv_add(r, "", "", "");
	assert(repo_len(r) == 0);
	serv_add(r, registration_number, brand, category);
	assert(repo_len(r) == 1);
	assert(strcmp(repo_element(r, 1)->registration_number, "CJ12ABC") == 0 && strcmp(repo_element(r, 1)->brand, "Opel Corsa C") == 0 && strcmp(repo_element(r, 1)->category, "Family car") == 0);
	repo_destroy(r);
}

void test_serv_modify() {
	char registration_number[] = "CJ12ABC";
	char brand[] = "Opel";
	char category[] = "car";
	char brand2[] = "Opel Corsa C";
	char category2[] = "Family car";

	MyList* r = repo_create();
	serv_add(r, registration_number, brand, category);
	serv_modify(r, "", "", "");
	assert(strcmp(repo_element(r, 1)->registration_number, "CJ12ABC") == 0 && strcmp(repo_element(r, 1)->brand, brand) == 0 && strcmp(repo_element(r, 1)->category, category) == 0);
	serv_modify(r, registration_number, brand2, category2);
	assert(repo_len(r) == 1);
	assert(strcmp(repo_element(r, 1)->registration_number, "CJ12ABC") == 0 && strcmp(repo_element(r, 1)->brand, brand2) == 0 && strcmp(repo_element(r, 1)->category, category2) == 0);
	repo_destroy(r);
}

void test_serv_rent() {
	char registration_number[] = "CJ12ABC";
	char brand[] = "Opel Corsa C";
	char category[] = "Family car";
	char cnp[] = "1234567890123";
	char name[] = "Popescu Ion";
	MyList* r = repo_create();
	serv_add(r, registration_number, brand, category);
	assert(repo_search(r, registration_number)->rented == 0);
	assert(serv_rent(r, cnp, name, registration_number) == 0);
	assert(repo_search(r, registration_number)->rented != 0);
	assert(serv_rent(r, cnp, name, registration_number) == 1);
	assert(serv_rent(r, cnp, name, "BV99ZZZ") == 2);
	assert(serv_rent(r, "0B2345G78H12A", name, registration_number) == 3);
	assert(serv_rent(r, cnp, "", registration_number) == 3);
	assert(serv_rent(r, cnp, name, "ABCDEFG") == 3);
	repo_destroy(r);
}

void test_serv_return() {
	char registration_number[] = "CJ12ABC";
	char brand[] = "Opel Corsa C";
	char category[] = "Family car";
	char cnp[] = "1234567890123";
	char name[] = "Popescu Ion";
	MyList* r = repo_create();
	serv_add(r, registration_number, brand, category);
	serv_rent(r, cnp, name, registration_number);
	assert(repo_search(r, registration_number)->rented != 0);
	assert(serv_return(r, registration_number) == 0);
	assert(serv_return(r, registration_number) == 1);
	assert(serv_return(r, "BV99ZZZ") == 2);
	assert(serv_return(r, "ABCDEFG") == 3);
	assert(repo_search(r, registration_number)->rented == 0);
	repo_destroy(r);
}

void test_serv_search() {
	char registration_number[] = "CJ12ABC";
	char brand[] = "Opel";
	char category[] = "car";

	char registration_number2[] = "BV01ASD";
	char brand2[] = "Opel Corsa C";
	char category2[] = "Family car";

	char registration_number3[] = "BV01ASD";
	char brand3[] = "Ford";
	char category3[] = "Sedan";

	MyList* r = repo_create();
	serv_add(r, registration_number, brand, category);
	serv_add(r, registration_number2, brand2, category2);
	serv_add(r, registration_number3, brand3, category3);
	MyList* found = serv_search(r, "Opel", "");
	assert(repo_len(found) == 2);
	repo_destroy(r);
	repo_destroy(found);
}

void test_serv_sort_brand() {
	char registration_number1[] = "CJ12ABC";
	char brand[] = "ZXC";
	char category[] = "FGH";

	char registration_number2[] = "BV01ASD";
	char brand2[] = "ASD";
	char category2[] = "BNM";

	char registration_number3[] = "CT23RKD";
	char brand3[] = "BNM";
	char category3[] = "ZXC";

	MyList* r = repo_create();
	serv_add(r, registration_number1, brand, category);
	serv_add(r, registration_number2, brand2, category2);
	serv_add(r, registration_number3, brand3, category3);

	serv_sort_brand(r, 0);
	assert(strcmp(repo_element(r, 1)->registration_number, registration_number2) == 0);
	assert(strcmp(repo_element(r, 2)->registration_number, registration_number3) == 0);
	assert(strcmp(repo_element(r, 3)->registration_number, registration_number1) == 0);
	serv_sort_brand(r, 1);
	assert(strcmp(repo_element(r, 1)->registration_number, registration_number1) == 0);
	assert(strcmp(repo_element(r, 2)->registration_number, registration_number3) == 0);
	assert(strcmp(repo_element(r, 3)->registration_number, registration_number2) == 0);

	repo_destroy(r);
}

void test_serv_sort_category() {
	char registration_number1[] = "CJ12ABC";
	char brand[] = "ZXC";
	char category[] = "FGH";

	char registration_number2[] = "BV01ASD";
	char brand2[] = "ASD";
	char category2[] = "BNM";

	char registration_number3[] = "CT23RKD";
	char brand3[] = "BNM";
	char category3[] = "ZXC";

	MyList* r = repo_create();
	serv_add(r, registration_number1, brand, category);
	serv_add(r, registration_number2, brand2, category2);
	serv_add(r, registration_number3, brand3, category3);

	serv_sort_category(r, 0);
	assert(strcmp(repo_element(r, 1)->registration_number, registration_number2) == 0);
	assert(strcmp(repo_element(r, 2)->registration_number, registration_number1) == 0);
	assert(strcmp(repo_element(r, 3)->registration_number, registration_number3) == 0);
	serv_sort_category(r, 1);
	assert(strcmp(repo_element(r, 1)->registration_number, registration_number3) == 0);
	assert(strcmp(repo_element(r, 2)->registration_number, registration_number1) == 0);
	assert(strcmp(repo_element(r, 3)->registration_number, registration_number2) == 0);

	repo_destroy(r);
}

void test_serv_filtrare() {
	MyList* r = repo_create();
	serv_add(r, "CJ12ABC", "Opel Corsa C", "Suv");
	serv_add(r, "VN13PJN", "Alfa Romeo 147", "Family car");
	serv_add(r, "VN15XYZ", "Alfa Romeo 147", "Family car");
	assert(r->n == 3);
	serv_filtrare(r, "Alfa Romeo 147");
	assert(r->n == 1);
	destroy(r, vehicle_destroy);
}

void test_serv_undo() {
	MyList* r = repo_create();

	MyList* undo_r = repo_create();
	int undo_count = 0;

	serv_add(r, "CJ12ABC", "Opel Corsa C", "Family car");
	serv_adauga_undo(r, undo_r, &undo_count);
	serv_add(r, "VN13PJN", "Alfa Romeo 147", "Family car");
	serv_adauga_undo(r, undo_r, &undo_count);

	assert(undo_r->n == 2);
	assert(r->n == 2);
	serv_undo(&r, undo_r, &undo_count);
	assert(undo_r->n == 1);
	assert(r->n == 1);
	serv_undo(&r, undo_r, &undo_count);
	assert(undo_r->n == 0);
	assert(r->n == 0);

	destroy(r, vehicle_destroy);
	destroy(undo_r, destroy_lista_vehicule);

}

void test_serv_judete() {
	char registration_number[] = "CJ12ABC";
	char brand[] = "Opel";
	char category[] = "car";

	char registration_number2[] = "BV01ASD";
	char brand2[] = "Opel Corsa C";
	char category2[] = "Family car";

	char registration_number3[] = "BV01ASD";
	char brand3[] = "Ford";
	char category3[] = "Sedan";

	char registration_number4[] = "BV01ASD";
	char brand4[] = "Ford";
	char category4[] = "Sedan";

	MyList* r = repo_create();
	serv_add(r, registration_number, brand, category);
	serv_add(r, registration_number2, brand2, category2);
	serv_add(r, registration_number3, brand3, category3);
	serv_add(r, registration_number4, brand4, category4);
	serv_rent(r, "1111111111111", "Anrei", "CJ12ABC");
	MyList* found = serv_afisare_judet(r, "CJ");
	assert(repo_len(found) == 1);
	repo_destroy(r);
	repo_destroy(found);
}

void test_all_service() {
	test_serv_add();
	test_serv_modify();
	test_serv_rent();
	test_serv_return();
	test_serv_search();
	test_serv_sort_brand();
	test_serv_sort_category();
	test_serv_filtrare();
	test_serv_judete();
	test_serv_undo();
}
