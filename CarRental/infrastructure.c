#include "infrastructure.h"

void add(MyList* r, ElemType el) {
	if (r->n == r->cp)
		repo_resize(r);
	r->e[r->n] = el;
	r->n = r->n + 1;
}

void destroy(MyList* l, DestroyFunction destrFct) {
	int i;
	for (i = 0; i < l->n; i++) {
		ElemType p = l->e[i];
		destrFct(p);
	}
	free(l->e);
	free(l);
}

MyList* repo_create() {
	MyList* v = (MyList*)malloc(sizeof(MyList));
	v->cp = 1;
	v->e = (Vehicle**)malloc(sizeof(Vehicle*));
	v->n = 0;
	return v;
}

MyList* copyRepo(MyList* l) {
	MyList* l_nou = repo_create();
	for (int i = 0; i < l->n; i++) {
		Vehicle* veh = l->e[i];
		char* a = veh->registration_number;
		char* b = veh->brand;
		char* c = veh->category;
		Vehicle* v = vehicle_create(a, b, c);
		if (veh->rented == 1)
		{
			char* d = veh->cnp;
			char* e = veh->name;
			vehicle_rent(v, d, e);
		}
		repo_add(l_nou, v);
	}
	return l_nou;
}

void destroy_lista_vehicule(MyList* l) {
	destroy(l, vehicle_destroy);
}

void repo_destroy(MyList* r) {
	int i;
	for (i = 0; i < r->n; i++) {
		vehicle_destroy(r->e[i]);
	}
	free(r->e);
	free(r);
}

void repo_resize(MyList* r) {
	Vehicle** eNou = (Vehicle**)malloc(2 * r->cp * sizeof(Vehicle*));
	int i;

	for (i = 0; i < r->n; i++)
		eNou[i] = r->e[i];

	r->cp = 2 * r->cp;
	free(r->e);
	r->e = eNou;
}

int repo_len(MyList* r) {
	return r->n;
}

Vehicle* repo_element(MyList* r, int i) {
	return r->e[i - 1];
}

int repo_add(MyList* r, Vehicle* v) {
	int i;
	for (i = 0; i < r->n; i++) {
		// vechi:	   r->e[i]->registration_number
		// vers lunga: Vehicle* veh = r->e[i];
		//			   char* c = veh->registration_number;
		// cu apel c la strcmp
		if (strcmp(((Vehicle*)r->e[i])->registration_number, v->registration_number) == 0) {
			if (r->e[i] != v)
				vehicle_destroy(v);
			return 1;
		}
	}
	if (r->n == r->cp)
		repo_resize(r);
	r->e[r->n] = v;
	r->n = r->n + 1;
	return 0;
}

int repo_modify(MyList* r, Vehicle* v) {
	int i;
	for (i = 0; i < r->n; i++) {
		if (strcmp(((Vehicle*)r->e[i])->registration_number, v->registration_number) == 0) {
			if (r->e[i] != v)
				vehicle_destroy(r->e[i]);
			r->e[i] = v;
			return 0;
		}
	}
	vehicle_destroy(v);
	return 1;
}


Vehicle* repo_search(MyList* r, char* registration_number) {
	int i;
	for (i = 0; i < r->n; i++) {
		if (strcmp(((Vehicle*)r->e[i])->registration_number, registration_number) == 0) {
			return r->e[i];
		}
	}
	return NULL;
}

void repository_filtrare(MyList* r_nou, char* brand_filtrare) {
	for (int i = 0; i < r_nou->n; i++)
	{
		if (strcmp(((Vehicle*)r_nou->e[i])->brand, brand_filtrare) == 0)
		{
				vehicle_destroy((Vehicle*)r_nou->e[i]);
				for (int j = i; j < r_nou->n; j++)
				{
					r_nou->e[j] = r_nou->e[j + 1];
				}
				r_nou->n--;
				i--;
		}

	}
}


Iterator* it_create(MyList* r) {
	Iterator* i = (Iterator*)malloc(sizeof(Iterator));

	i->r = r;
	i->curent = 0;

	return i;
}

void it_destroy(Iterator* i) {
	free(i);
}

void it_first(Iterator* i) {
	i->curent = 0;
}

void it_next(Iterator* i) {
	i->curent++;
}

Vehicle* it_element(Iterator* i) {
	return i->r->e[i->curent];
}

int it_valid(Iterator* i) {
	int n = repo_len(i->r);
	return i->curent < n;
}

void test_repo_create_and_destroy() {
	MyList* r = repo_create();
	assert(r->cp > 0);
	assert(r->n == 0);
	repo_destroy(r);
}

void test_repo_resize() {
	MyList* r = repo_create();
	int cp1 = r->cp;
	repo_resize(r);
	assert(r->cp > cp1);
	repo_destroy(r);
}

void test_repo_len() {
	MyList* r = repo_create();
	assert(repo_len(r) == 0);
	Vehicle* v = vehicle_create("CJ12ASD", "asd", "zxc");
	repo_add(r, v);
	assert(repo_len(r) == 1);
	repo_destroy(r);
}

void test_repo_element() {
	MyList* r = repo_create();
	Vehicle* v = vehicle_create("CJ12ABC", "Opel Corsa C", "Family car");
	repo_add(r, v);
	Vehicle* v1 = repo_element(r, 1);
	assert(strcmp(v->registration_number, v1->registration_number) == 0);
	assert(strcmp(v->brand, v1->brand) == 0);
	assert(strcmp(v->category, v1->category) == 0);
	repo_destroy(r);
}

void test_repo_add() {
	Vehicle* v = vehicle_create("CJ12ABC", "Opel Corsa C", "Family car");
	MyList* r = repo_create();
	assert(repo_add(r, v) == 0);
	assert(repo_len(r) == 1);
	assert(repo_add(r, v) == 1);
	assert(repo_len(r) == 1);
	assert(strcmp(repo_element(r, 1)->registration_number, "CJ12ABC") == 0 && strcmp(repo_element(r, 1)->brand, "Opel Corsa C") == 0 && strcmp(repo_element(r, 1)->category, "Family car") == 0);
	repo_destroy(r);
}

void test_repo_modify() {
	Vehicle* v1 = vehicle_create("CJ12ABC", "Opel", "car");
	Vehicle* v2 = vehicle_create("CJ12ABC", "Opel Corsa C", "Family car");
	MyList* r = repo_create();
	repo_add(r, v1);
	assert(repo_modify(r, v2) == 0);
	assert(repo_len(r) == 1);
	assert(strcmp(repo_element(r, 1)->registration_number, "CJ12ABC") == 0 && strcmp(repo_element(r, 1)->brand, "Opel Corsa C") == 0 && strcmp(repo_element(r, 1)->category, "Family car") == 0);
	Vehicle* v3 = vehicle_create("BV01ASD", "Audi A4", "Sedan");
	assert(repo_modify(r, v3) == 1);
	repo_destroy(r);
}

void test_repo_search() {
	Vehicle* v = vehicle_create("CJ12ABC", "Opel Corsa C", "Family car");
	MyList* r = repo_create();
	repo_add(r, v);
	assert(strcmp(repo_search(r, "CJ12ABC")->registration_number, "CJ12ABC") == 0);
	assert(repo_search(r, "CJ99ZZZ") == NULL);
	repo_destroy(r);
}

void test_it_create() {
	MyList* r = repo_create();
	Iterator* i = it_create(r);
	assert(i->r == r);
	assert(i->curent == 0);
	repo_destroy(r);
	it_destroy(i);
}

void test_it_destroy() {
	MyList* r = repo_create();
	Iterator* i = it_create(r);
	repo_destroy(r);
	it_destroy(i);
}

void test_it_first() {
	MyList* r = repo_create();
	Iterator* i = it_create(r);
	i->curent = 12;
	it_first(i);
	assert(i->curent == 0);
	repo_destroy(r);
	it_destroy(i);
}

void test_it_next() {
	MyList* r = repo_create();
	Iterator* i = it_create(r);
	it_first(i);
	it_next(i);
	assert(i->curent == 1);
	repo_destroy(r);
	it_destroy(i);
}

void test_it_element() {
	MyList* r = repo_create();
	Vehicle* v = vehicle_create("CJ12ABC", "Opel Corsa C", "Family car");
	repo_add(r, v);
	Iterator* i = it_create(r);
	it_first(i);
	Vehicle* e = it_element(i);
	assert(strcmp(v->registration_number, e->registration_number) == 0);
	assert(strcmp(v->brand, e->brand) == 0);
	assert(strcmp(v->category, e->category) == 0);
	repo_destroy(r);
	it_destroy(i);
}

void test_it_valid() {
	MyList* r = repo_create();
	Vehicle* v = vehicle_create("CJ12ABC", "Opel Corsa C", "Family car");
	repo_add(r, v);
	Iterator* i = it_create(r);
	it_first(i);
	assert(it_valid(i) != 0);
	it_next(i);
	assert(it_valid(i) == 0);
	repo_destroy(r);
	it_destroy(i);
}

void test_lista_de_liste1()
{
	Vehicle* v = vehicle_create("CJ12ABC", "Opel Corsa C", "Family car");

	MyList* repo = repo_create();
	add(repo, v);

	MyList* repo1 = repo_create();

	MyList* undo_repo = repo_create();
	add(undo_repo, repo);
	assert(undo_repo->cp == 1);
	add(undo_repo, repo1);
	assert(undo_repo->cp == 2);

	destroy(undo_repo, destroy_lista_vehicule);

}

void test_lista_de_liste2() {
	Vehicle* v = vehicle_create("CJ12ABC", "Opel Corsa C", "Family car");
	vehicle_rent(v, "1234567890123", "asd");

	MyList* repo = repo_create();
	add(repo, v);

	MyList* undo_repo = repo_create();

	MyList* repo_copy = copyRepo(repo);
	add(undo_repo, repo_copy);
	assert(undo_repo->cp == 1);

	destroy(repo, vehicle_destroy);
	destroy(undo_repo, destroy_lista_vehicule);
}

void test_all_infrastructure() {
	test_repo_create_and_destroy();
	test_repo_resize();
	test_repo_len();
	test_repo_element();
	test_repo_add();
	test_repo_modify();
	test_repo_search();
	test_it_create();
	test_it_destroy();
	test_it_first();
	test_it_next();
	test_it_element();
	test_it_valid();
	test_lista_de_liste1();
	test_lista_de_liste2();
}
