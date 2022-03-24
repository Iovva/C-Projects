#define _CRT_SECURE_NO_WARNINGS

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <malloc.h>

#include "ui.h"
#include "teste.h"

int main() {
	teste_all();
	run();
	_CrtDumpMemoryLeaks();
}