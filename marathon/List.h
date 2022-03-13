#ifndef LIST_H
#define LIST_H

typedef struct Elem Elem;
typedef struct List List;

//element containing film id and pointer to next film
struct Elem {
	Elem *prev, *next;
	long int val;

};

//list of all films
struct List {
	Elem *beg, *end;
};

void connect(Elem* a, Elem* b);

Elem* new(long int x);

List* create();

Elem* insert(Elem* x, long int n);

Elem* pushback(List* x, long int n);

Elem* pushfront(List* x, long int n);

bool isempty(List* x);

Elem* sortinsert(List* x, long int n);

void delelem(List* x, long int n);

bool checkmovie(List* x, long int n);

List* merge(List* x, List* y, long int k);

List* merge2(List* x, List* y, long int k);

void print(List* x);

void freelist(List* x);

#endif
