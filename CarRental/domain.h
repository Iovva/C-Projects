#ifndef DOMAIN_H_
#define DOMAIN_H_

#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char* registration_number;
	char* brand;
	char* category;
	char* cnp;
	char* name;
	int rented;
} Vehicle;

/*
 * Creates a Vehicle object
 * pre: registration_number, brand, category - char*
 * post: returns v - Vehicle*
 */
Vehicle* vehicle_create(char* registration_number, char* brand, char* category);

/*
 * Creates an independent copy of a Vehicle object
 * pre: v - Vehicle*
 * post: returns copy - Vehicle*
 */
Vehicle* vehicle_copy(Vehicle* v);

/*
 * destroys a Vehicle object
 * pre: v - Vehicle*
 * post: v is destroyed
 */
void vehicle_destroy(Vehicle* v);

/*
 * rents a Vehicle object
 * pre: v - Vehicle*
 *		cnp, name - char*
 * post: v is now rented
 */
void vehicle_rent(Vehicle* v, char* cnp, char* name);

/*
 * returns a Vehicle object
 * pre: v - Vehicle*
 * post: v is now returned
 */
void vehicle_return(Vehicle* v);

void test_vehicle_create_and_destroy();

void test_vehicle_copy();

void test_vehicle_rent();

void test_vehicle_return();

void test_all_domain();

#endif
