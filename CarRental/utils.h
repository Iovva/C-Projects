#ifndef UTILS_H_
#define UTILS_H_

#include <ctype.h>
#include "domain.h"
#include "infrastructure.h"
#include "service.h"


typedef int(*FunctieComparare)(Vehicle* v1, Vehicle* v2);
/*
 * Sorts a MyList by a comparation function cmp_f
 * pre: r - MyList*
 *		cmp_f - FunctieComparare
 *		reverse - int
 * post: r sorted
 */
void sort(MyList* r, FunctieComparare cmp_f, int reverse);

/*
 * Comparation function for 2 vehicles by brand
 * pre: v1, v2 - Vehicle*
 * post: if v1 < v2 return -1, if v1 = v2 return 0, if v1 > v2 return 1
 */
int cmp_brand(Vehicle* v1, Vehicle* v2);

/*
 * Comparation function for 2 vehicles by category
 * pre: v1, v2 - Vehicle*
 * post: if v1 < v2 return -1, if v1 = v2 return 0, if v1 > v2 return 1
 */
int cmp_category(Vehicle* v1, Vehicle* v2);

/*
 * strcmp but ignore case
 * see strcmp manual for more information
 */
int stricmp_homemade(char const* a, char const* b);

void test_sort();

void test_cmp_brand();

void test_cmp_category();

void test_stricmp_homemade();

void test_all_utils();

#endif
