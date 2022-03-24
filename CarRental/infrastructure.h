#ifndef INFRASTRUCTURE_H_
#define INFRASTRUCTURE_H_

#include <stdlib.h>
#include <stdio.h>
#include "domain.h"

typedef void* ElemType;

typedef struct {
	int cp;
	int n;
	ElemType* e;
} MyList;

typedef struct {
	MyList* r;
	int curent;
} Iterator;

typedef void(*DestroyFunction)(ElemType);

/*
 * Add a vehicle to the generic repository
 * pre: r - MyList*
		v - Vehicle
 * post: r' - MyList*, *r' = *r reunited with {v}
 */
void add(MyList* r, ElemType el);

/*
 * generic destruction function
 * post: passes each element to the destruction function
 */
void destroy(MyList* l, DestroyFunction);

/*
 * copy a MyList object, filled with vehicles
 * pre: ElemType - Vehicles*
 * post: returns l_nou, adress of new list
 */
MyList* copyRepo(MyList* l);

/*
 * Creates a MyList object of size 0
 * pre:
 * post: returns r - MyList*, r.n = 0, r.cp = 1
 */
MyList* repo_create();

/*
 * launches destruction of vehicle list for MyList
 * post: list is destroyed
 */
void destroy_lista_vehicule(MyList* l);



/*
 * Destroys a MyList object
 * pre: r - MyList
 * post: r has been destroyed
 */
void repo_destroy(MyList* r);

/*
 * Resize a MyList object
 * pre: r - MyList*
 * post: returns r' - MyList*, r'->cp = 2 * r->cp
 */
void repo_resize(MyList* r);

/*
 * Gives the length of an MyList object
 * pre: r - MyList*
 * post: returns dim - int, dim = number of elements in r
 */
int repo_len(MyList* r);

/*
 * Gives the adress of a Vehicle object from a certain position in a MyList object
 * pre: r - MyList*
		i - int
 * post: returns v - Vehicle*, *v = the i-th element in r
 */
Vehicle* repo_element(MyList* r, int i);

/*
 * Add a vehicle to the repository
 * pre: r - MyList*
		v - Vehicle
 * post: r' - MyList*, *r' = *r reunited with {v}
 *		 returns 0 if the vehicle was succesfully added, else returns 1
 */
int repo_add(MyList* r, Vehicle* v);

/*
 * Modify a vehicle from the repository
 * pre: r - MyList*
		v - Vehicle
 * post: r' - MyList*, *r' = *r, where the Vehicle with a registration_number equal to the registration_number of v is replaced with v
 *		 returns 0 if the vehicle was succesfully modified, else returns 1
 */
int repo_modify(MyList* r, Vehicle* v);

/*
 * Searches a Vehicle in a repository
 * pre: r - MyList*
 *		registration_number - char*
 * post: if the vehicle with the registration number is found, it is returning it's adress in the repository, else returns NULL
 */
Vehicle* repo_search(MyList* r, char* registration_number);

/*
 * Creates an Iterator for MyList
 * pre: r - MyList*
 * post: returns i - Iterator*, i->r = r, i->curent = 0
 */
Iterator* it_create(MyList* r);

/*
 * Destroys an Iterator for MyList
 * pre: i - Iterator*
 * post: i has been destroyed
 */
void it_destroy(Iterator* i);

/*
 * Sets the curent of an Iterator object to 0
 * pre: i - Iterator*
 * post: i' - Iterator*, *i' = *i, i'->curent = 0
 */
void it_first(Iterator* i);

/*
 * Increments the curent of an Iterator object
 * pre: i - Iterator*
 * post: i' - Iterator*, *i' = *i, i'->curent = i->curent + 1
 */
void it_next(Iterator* i);

/*
 * Gives the Vehicle object refered by the curent of an Iterator object
 * pre: i - Iterator*
 * post: returns v - Vehicle, where i->current is the adress of v
 */
Vehicle* it_element(Iterator* i);

/*
 * Verifies if an Iterator object is valid
 * pre: i - Iterator*
 * post: returns 1 if i->curent points to a valid Vehicle object, else 0
 */
int it_valid(Iterator* i);

/*
 * deletes all Vehicles in MyList, of a given brand
 * brand_filtrare - brand to be filtered out
 */
void repository_filtrare(MyList* r_nou, char* brand_filtrare);

void test_repo_create_and_destroy();

void test_repo_resize();

void test_repo_len();

void test_repo_element();

void test_repo_add();

void test_repo_modify();

void test_it_create();

void test_it_destroy();

void test_it_first();

void test_it_next();

void test_it_element();

void test_it_valid();

void test_lista_de_liste1();

void test_lista_de_liste2();

void test_all_infrastructure();

#endif
