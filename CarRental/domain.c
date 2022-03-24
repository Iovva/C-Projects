#include "domain.h"
#include <stdio.h>

Vehicle* vehicle_create(char* registration_number, char* brand, char* category) {
	 Vehicle* v = (Vehicle*)malloc(sizeof(Vehicle));
	 v->registration_number = (char*)malloc(sizeof(char) * (strlen(registration_number) + 1));
	 v->brand = (char*)malloc(sizeof(char) * (strlen(brand) + 1));
	 v->category = (char*)malloc(sizeof(char) * (strlen(category) + 1));
	 strcpy(v->registration_number, registration_number);
	 strcpy(v->brand, brand);
	 strcpy(v->category, category);
	 v->cnp = NULL;
	 v->name = NULL;
	 v->rented = 0;
	 return v;
}

Vehicle* vehicle_copy(Vehicle* v) {
	Vehicle* copy = (Vehicle*)malloc(sizeof(Vehicle));
	copy->registration_number = (char*)malloc(sizeof(char) * (strlen(v->registration_number) + 1));
	copy->brand = (char*)malloc(sizeof(char) * (strlen(v->brand) + 1));
	copy->category = (char*)malloc(sizeof(char) * (strlen(v->category) + 1));
	strcpy(copy->registration_number, v->registration_number);
	strcpy(copy->brand, v->brand);
	strcpy(copy->category, v->category);
	copy->rented = v->rented;
	if (v->rented != 0) {
		copy->cnp = (char*)malloc(sizeof(char) * (strlen(v->cnp) + 1));
		copy->name = (char*)malloc(sizeof(char) * (strlen(v->name) + 1));
		strcpy(copy->cnp, v->cnp);
		strcpy(copy->name, v->name);
	}
	else {
		copy->cnp = NULL;
		copy->name = NULL;
	}
	return copy;
}

void vehicle_destroy(Vehicle* v) {
	free(v->registration_number);
	free(v->brand);
	free(v->category);
	v->registration_number = NULL;
	v->brand = NULL;
	v->category = NULL;
	if (v->rented != 0) {
		free(v->cnp);
		free(v->name);

	}
	v->cnp = NULL;
	v->name = NULL;
	v->rented = 0;
	free(v);
}

void vehicle_rent(Vehicle* v, char* cnp, char* name) {
	v->cnp = (char*)malloc(sizeof(char) * (strlen(cnp) + 1));
	v->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(v->cnp, cnp);
	strcpy(v->name, name);
	v->rented = 1;
}

void vehicle_return(Vehicle* v) {
	free(v->cnp);
	free(v->name);
	v->cnp = NULL;
	v->name = NULL;
	v->rented = 0;
}

void test_vehicle_create_and_destroy() {
	Vehicle* v = vehicle_create("CJ12ASD", "asd", "zxc");
	assert(strcmp(v->registration_number, "CJ12ASD") == 0);
	assert(strcmp(v->brand, "asd") == 0);
	assert(strcmp(v->category, "zxc") == 0);
	assert(v->cnp == NULL);
	assert(v->name == NULL);
	assert(v->rented == 0);
	vehicle_destroy(v);
}

void test_vehicle_copy() {
	Vehicle* v = vehicle_create("CJ12ASD", "asd", "zxc");
	Vehicle* copy;
	copy = vehicle_copy(v);
	assert(strcmp(copy->registration_number, v->registration_number) == 0);
	assert(strcmp(copy->brand, v->brand) == 0);
	assert(strcmp(copy->category, v->category) == 0);
	vehicle_destroy(copy);
	vehicle_rent(v, "1234567890123", "asd");
	copy = vehicle_copy(v);
	assert(copy->rented == v->rented);
	assert(strcmp(copy->cnp, v->cnp) == 0);
	assert(strcmp(copy->name, v->name) == 0);
	strcpy(v->brand, "fgh");
	assert(strcmp(copy->brand, "asd") == 0);
	vehicle_destroy(v);
	vehicle_destroy(copy);
}

void test_vehicle_rent() {
	Vehicle* v = vehicle_create("CJ12ASD", "asd", "zxc");
	vehicle_rent(v, "1234567890123", "asd");
	assert(v->rented != 0);
	assert(strcmp(v->cnp, "1234567890123") == 0);
	assert(strcmp(v->name, "asd") == 0);
	vehicle_destroy(v);
}

void test_vehicle_return() {
	Vehicle* v = vehicle_create("CJ12ASD", "asd", "zxc");
	vehicle_rent(v, "1234567890123", "asd");
	vehicle_return(v);
	assert(v->rented == 0);
	vehicle_destroy(v);
}

void test_all_domain() {
	test_vehicle_create_and_destroy();
	test_vehicle_copy();
	test_vehicle_rent();
	test_vehicle_return();
}
