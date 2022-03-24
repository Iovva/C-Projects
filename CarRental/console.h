#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdio.h>
#include "service.h"

#define MAX_CHARS 1024

void ui_add(MyList* r, MyList* undo_r, int* undo_count);

void ui_modify(MyList* r, MyList* undo_r, int* undo_count);

void ui_rent(MyList* r, MyList* undo_r, int* undo_count);

void ui_return(MyList* r, MyList* undo_r, int* undo_count);

void ui_search(MyList* r);

void ui_sort(MyList* r, MyList* undo_r, int* undo_count);

void ui_filtrare(MyList* r, MyList* undo_r, int* undo_count);

void ui_undo(MyList** r, MyList* undo_r, int* undo_count);

void ui_afisare_judet(MyList* r);

void ui_run();

#endif
