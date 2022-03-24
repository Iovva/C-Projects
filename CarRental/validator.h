#ifndef VALIDATOR_H_
#define VALIDATOR_H_

#include <string.h>
#include <assert.h>
#include "domain.h"

/*
 * Validates registration number
 * pre: reg_num - c string
 * post: return 0 if reg_num is valid, else returns 1
 */
int validate_registration_number(char* reg_num);

/*
 * Validates brand
 * pre: brand - c string
 * post: return 0 if brand is valid, else returns 1
 */
int validate_brand(char* brand);

/*
 * Validates category
 * pre: category - c string
 * post: return 0 if category is valid, else returns 1
 */
int validate_category(char* category);

/*
 * Validates vehicle
 * pre: v - Vehicle      ___
 * post: return a number abc where:
 *		 a is 0 if the category is valid, else 1
 *		 b is 0 if the brand is valid, else 1
 *		 c is 0 if the registration number is valid, else 1
 */
int validate_vehicle(Vehicle* v);

/*
 * Validates CNP
 * pre: cnp - c string
 * post: return 0 if cnp is valid, else returns 1
 */
int validate_cnp(char* cnp);

/*
 * Validates name
 * pre: name - c string
 * post: return 0 if name is valid, else returns 1
 */
int validate_name(char* name);

void test_validate_registration_number();

void test_validate_brand();

void test_validate_category();

void test_validate_vehicle();

void test_validate_cnp();

void test_validate_name();

void test_all_validator();

#endif
