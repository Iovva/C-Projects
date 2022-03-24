#ifndef SERVICE_H_
#define SERVICE_H_

#include "infrastructure.h"
#include "validator.h"
#include "utils.h"

/*
 * Adds a vehicle to the repository
 */
int serv_add(MyList* r, char* registration_number, char* brand, char* category);

/*
 * Modifies a vehicle in the repository
 */
int serv_modify(MyList* r, char* registration_number, char* brand, char* category);

/*
 * Rents a vehicle from the repository
 */
int serv_rent(MyList* r, char* cnp, char* name, char* registration_number);

/*
 * Returns a vehicle from the repository
 */
int serv_return(MyList* r, char* registration_number);

/*
 * Searches a vehicle in the repository
 */
MyList* serv_search(MyList* r, char* brand, char* category);

/*
 * Sorts vehicles in the repository by brand
 */
void serv_sort_brand(MyList* r, int reverse);

/*
 * Sorts vehicles in the repository by category
 */
void serv_sort_category(MyList* r, int reverse);

/*
* filters out vehicles with a matching brand
*/
void serv_filtrare(MyList* r_nou, char* brand_filtrare);

/*
* adds curent r MyList* to the end of the meta undo_r MyList*, that allows us to undo
*/
void serv_adauga_undo(MyList* r, MyList* undo_r, int* undo_count);

/*
* restores the r MyList** to its last form, while deleting the previous form and also the last form in the undo_repository
*/
void serv_undo(MyList** r, MyList* undo_r, int* undo_count);

MyList* serv_afisare_judet(MyList* r, char* judet);

void test_serv_add();

void test_serv_modify();

void test_serv_rent();

void test_serv_search();

void test_serv_sort_brand();

void test_serv_sort_category();

void test_serv_filtrare();

void test_serv_undo();

void test_all_service();

void test_serv_judete();

#endif
