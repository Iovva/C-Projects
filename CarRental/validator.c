#include "validator.h"

int validate_registration_number(char* reg_num) {
	char* judete[41] = { "AB", "AG", "AR", "BC", "BH", "BN", "BR", "BT", "BV", "BZ", "CJ", "CL", "CS", "CT", "CV", "DB", "DJ", "GJ", "GL", "GR", "HD", "HR", "IF", "IL", "IS", "MH", "MM", "MS", "NT", "OT", "PH", "SB", "SJ", "SM", "SV", "TL", "TM", "TR", "VL", "VN", "VS" };
	char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char digits[] = "0123456789";
	int i;
	int len = strlen(reg_num);
	if (len != 6 && len != 7) return 1;
	if (strchr(letters, reg_num[0]) == NULL) return 1;
	if (strchr(letters, reg_num[1]) == NULL) {
		if (reg_num[0] != 'B') return 1;
		if (strchr(digits, reg_num[1]) == NULL || strchr(digits, reg_num[2]) == NULL) return 1;
		if (strchr(digits, reg_num[3]) == NULL) {
			if (len != 6) return 1;
			if (strchr(letters, reg_num[3]) == NULL || strchr(letters, reg_num[4]) == NULL || strchr(letters, reg_num[5]) == NULL) return 1;
		}
		else {
			if (len != 7) return 1;
			if (strchr(letters, reg_num[4]) == NULL || strchr(letters, reg_num[5]) == NULL || strchr(letters, reg_num[6]) == NULL) return 1;
		}
	}
	else {
		if (len != 7) return 1;
		int ok = 0;
		for (i = 0; i < 41; i++) {
			if (judete[i][0] == reg_num[0] && judete[i][1] == reg_num[1]) ok = 1;
		}
		if (ok == 0) return 1;
		if (strchr(digits, reg_num[2]) == NULL || strchr(digits, reg_num[3]) == NULL) return 1;
		if (strchr(letters, reg_num[4]) == NULL || strchr(letters, reg_num[5]) == NULL || strchr(letters, reg_num[6]) == NULL) return 1;
	}
	return 0;
}

int validate_brand(char* brand) {
	if (strlen(brand) <= 0) return 1;
	return 0;
}

int validate_category(char* category) {
	if (strlen(category) <= 0) return 1;
	return 0;
}

int validate_vehicle(Vehicle* v) {
	int n = 0;
	if (validate_category(v->category) != 0) n = n + 1;
	n = n * 10;
	if (validate_brand(v->brand) != 0) n = n + 1;
	n = n * 10;
	if (validate_registration_number(v->registration_number) != 0) n = n + 1;
	return n;
}

int validate_cnp(char* cnp) {
	if (strlen(cnp) != 13) return 1;
	int i;
	for (i = 0; i < 13; i++) {
		if (strchr("0123456789", cnp[i]) == NULL) {
			return 1;
		}
	}
	return 0;
}

int validate_name(char* name) {
	if (strlen(name) <= 0) return 1;
	return 0;
}

void test_validate_registration_number() {
	assert(validate_registration_number("CJ12ASD") == 0);
	assert(validate_registration_number("CJ12ASDFG") == 1);
	assert(validate_registration_number("8J12ASD") == 1);
	assert(validate_registration_number("C12ASD") == 1);
	assert(validate_registration_number("BCDASD") == 1);
	assert(validate_registration_number("B12ASDF") == 1);
	assert(validate_registration_number("B12A2D") == 1);
	assert(validate_registration_number("B123AS") == 1);
	assert(validate_registration_number("B123A2D") == 1);
	assert(validate_registration_number("CJ12SD") == 1);
	assert(validate_registration_number("ZZ12ASD") == 1);
	assert(validate_registration_number("CJ1WASD") == 1);
	assert(validate_registration_number("CJ12A7D") == 1);
}

void test_validate_brand() {
	assert(validate_brand("opel") == 0);
	assert(validate_brand("") == 1);
}

void test_validate_category() {
	assert(validate_category("suv") == 0);
	assert(validate_category("") == 1);
}

void test_validate_vehicle() {
	Vehicle* v;
	v = vehicle_create("CJ12ABC", "Opel Corsa C", "Family car");
	assert(validate_vehicle(v) == 0);
	vehicle_destroy(v);
	v = vehicle_create("", "", "");
	assert(validate_vehicle(v) == 111);
	vehicle_destroy(v);
}

void test_validate_cnp() {
	assert(validate_cnp("1234567890123") == 0);
	assert(validate_cnp("") == 1);
	assert(validate_cnp("123A56F89G123") == 1);
}

void test_validate_name() {
	assert(validate_category("Mihai") == 0);
	assert(validate_category("") == 1);
}

void test_all_validator() {
	test_validate_registration_number();
	test_validate_brand();
	test_validate_category();
	test_validate_vehicle();
	test_validate_cnp();
	test_validate_name();
}
