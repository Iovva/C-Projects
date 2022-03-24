#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include "console.h"

void test_all() {
	test_all_utils();
	test_all_validator();
	test_all_domain();
	test_all_infrastructure();
	test_all_service();
}

int main() {
	test_all();
	ui_run();
	_CrtDumpMemoryLeaks();
	return 0;
}
