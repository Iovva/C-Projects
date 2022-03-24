#include "utils.h"

void sort(MyList* r, FunctieComparare cmp_f, int reverse) {
	int i, j;
	for (i = 1; i < repo_len(r); i++) {
		for (j = i + 1; j <= repo_len(r); j++) {
			int condition;
			if (reverse == 0)
				condition = cmp_f(repo_element(r, i), repo_element(r, j)) > 0;
			else
				condition = cmp_f(repo_element(r, i), repo_element(r, j)) < 0;
			if (condition) {
				Vehicle* aux = r->e[i - 1];
				r->e[i - 1] = r->e[j - 1];
				r->e[j - 1] = aux;
			}
		}
	}
}


int cmp_brand(Vehicle* v1, Vehicle* v2) {
	return stricmp_homemade(v1->brand, v2->brand);
}

int cmp_category(Vehicle* v1, Vehicle* v2) {
	return stricmp_homemade(v1->category, v2->category);
}

int stricmp_homemade(char const* a, char const* b)
{
	for (;; a++, b++) {
		int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
		if (d != 0 || !*a)
			return d;
	}
}

void test_sort() {
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

	sort(r, cmp_brand, 0);
	assert(strcmp(repo_element(r, 1)->registration_number, registration_number2) == 0);
	assert(strcmp(repo_element(r, 2)->registration_number, registration_number3) == 0);
	assert(strcmp(repo_element(r, 3)->registration_number, registration_number1) == 0);
	sort(r, cmp_brand, 1);
	assert(strcmp(repo_element(r, 1)->registration_number, registration_number1) == 0);
	assert(strcmp(repo_element(r, 2)->registration_number, registration_number3) == 0);
	assert(strcmp(repo_element(r, 3)->registration_number, registration_number2) == 0);
	sort(r, cmp_category, 0);
	assert(strcmp(repo_element(r, 1)->registration_number, registration_number2) == 0);
	assert(strcmp(repo_element(r, 2)->registration_number, registration_number1) == 0);
	assert(strcmp(repo_element(r, 3)->registration_number, registration_number3) == 0);
	sort(r, cmp_category, 1);
	assert(strcmp(repo_element(r, 1)->registration_number, registration_number3) == 0);
	assert(strcmp(repo_element(r, 2)->registration_number, registration_number1) == 0);
	assert(strcmp(repo_element(r, 3)->registration_number, registration_number2) == 0);

	repo_destroy(r);
}

void test_cmp_brand() {
	Vehicle* v1 = vehicle_create("CJ12ASD", "qwe", "vbn");
	Vehicle* v2 = vehicle_create("CJ12ASD", "zxc", "asd");
	assert(cmp_brand(v1, v2) < 0);
	assert(cmp_brand(v2, v1) > 0);
	assert(cmp_brand(v1, v1) == 0);
	vehicle_destroy(v1);
	vehicle_destroy(v2);
}

void test_cmp_category() {
	Vehicle* v1 = vehicle_create("CJ12ASD", "qwe", "vbn");
	Vehicle* v2 = vehicle_create("CJ12ASD", "zxc", "asd");
	assert(cmp_category(v1, v2) > 0);
	assert(cmp_category(v2, v1) < 0);
	assert(cmp_category(v1, v1) == 0);
	vehicle_destroy(v1);
	vehicle_destroy(v2);
}

void test_stricmp_homemade() {
	assert(stricmp_homemade("ASD", "asd") == 0);
	assert(stricmp_homemade("asd", "asd") == 0);
	assert(stricmp_homemade("ASD", "ASD") == 0);
	assert(stricmp_homemade("asd", "asdf") != 0);
}

void test_all_utils() {
	test_sort();
	test_cmp_brand();
	test_cmp_category();
	test_stricmp_homemade();
}
