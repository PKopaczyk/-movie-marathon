#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

//ustawianie wskaźników elementów a i b na siebie nawzajem
void connect(Elem* a, Elem* b){
	a->next = b;
	b->prev = a;
}

//tworzenie nowgo elementu
Elem* new(long int x){
	Elem* r = malloc(sizeof(Elem));
	if(r==NULL){
		return r;
	}
	else{
		r->prev = NULL;
		r->next = NULL;
		r->val = x;
		return r;
	}
}

//tworzenie nowej listy
List* create(){
	List* r = malloc(sizeof(List));
	if(r==NULL){
	}
	else{
		r->beg = new(-1);
		r->end = new(-1);
		connect(r->beg,r->end);
	}
	return r;
}

//dołączanie elementu o wartości n za element x
Elem* insert(Elem* x, long int n){
	Elem* y = new(n);
	if(y == NULL){
	}
	else{
		connect(y, x->next);
		connect(x,y);
	}
	return y;
}

//wkładanie elementu z tyłu listy
Elem* pushback(List* x, long int n){
	return insert(x->end->prev, n);
}

//wkładanie elementu z przodu listy
Elem* pushfront(List* x, long int n){
	return insert(x->beg, n); //bez ->next
}

//sprawdzanie czy lista jest pusta
bool isempty(List* x){
	return x->end == x->beg->next;
}

//wkładanie elementu o wartości n do posortowanej listy
Elem* sortinsert(List* x, long int n){
	if (isempty(x) || x->end->prev->val < n)
		return pushback(x, n);
	else if (x->beg->next->val > n)
		return pushfront(x, n);
	else {
		for(Elem* i = x->beg->next; i!=x->end; i=i->next){
			if (i->prev->val < n && i->val > n){
				return insert(i->prev, n);
			}
		}
		return x->beg;
	}
}

//usuwanie elementu o wartości n z listy
void delelem(List* x, long int n){
	Elem* a = x->beg->next;
	while(a != x->end){
		if(a->val == n){
			connect(a->prev, a->next);
			free(a);
			break;
		}
		a = a->next;
	}
}

//sprawdzanie czy element o wartości n jest w liście
bool checkmovie(List* x, long int n){
	Elem* a = x->beg->next;
	while(a != x->end){
		if(a->val == n){
			return false;
			free(a);
			break;
		}
		a = a->next;
	}
	return true;
}

//łączenie dwóch posortowanych list
List* merge(List* x, List* y, long int k){
	List* l = create();
	if(l == NULL){
		freelist(x);
		freelist(y);
		return l;
	}
	else{
		long int a = 0;
		for(Elem *i = x->end->prev, *j = y->end->prev; a < k ; a++){
			if(i == x->beg && j == y->beg){
				a = k;
			}
			else if(i == x->beg || i->val < j->val){
				if(pushfront(l, j->val) == NULL){
					freelist(x);
					freelist(y);
					freelist(l);
					return NULL;
				};
				j=j->prev;
			}
			else if(j == y->beg || i->val > j->val){
				if(pushfront(l, i->val) == NULL){
					freelist(x);
					freelist(y);
					freelist(l);
					return NULL;
				};
				i=i->prev;
			}
			else if(i->val == j->val){
				if(pushfront(l, i->val) == NULL){
					freelist(x);
					freelist(y);
					freelist(l);
					return NULL;
				};
				i=i->prev;
				j=j->prev;
			}
		}
		freelist(x);
		freelist(y);
		return l;
	}
}

//łączenie dwuch posortowanych list, pierwsza lista jest uprzywilejowana
List* merge2(List* x, List* y, long int k){
	List* l = create();
	if(l == NULL){
		freelist(y);
		return l;
	}
	else{
		if(x->beg == x->end->prev)
			l = merge(create(), y, k);
		else{
			long int a = 0;
			if(y->beg->next==y->end){
				for(Elem* i = x->end->prev; a < k; a++){
					if(i == x->beg)
						a = k;
					else{
						if(pushfront(l, i->val) == NULL){
							freelist(l);
							freelist(y);
							return NULL;
						};
						i=i->prev;
					}
				}
			}
			else{
				long int b = x->end->prev->val;
				for(Elem *i = x->end->prev, *j = y->end->prev; a < k ; a++){
					if(i == x->beg || (i == x->beg && b >= j->val)){
						a = k;
					}
					else if(j == y->beg){
						if(pushfront(l, i->val) == NULL){
							freelist(l);
							freelist(y);
							return NULL;
						};
						i=i->prev;
					}
					else if(b < j->val){
						if(pushfront(l, j->val) == NULL){
							freelist(l);
							freelist(y);
							return NULL;
						};
						j=j->prev;
					}
					else if(b >= j->val &&  i->val >= 0){
						if(pushfront(l, i->val) == NULL){
							freelist(l);
							freelist(y);
							return NULL;
						};
						i=i->prev;
					}
				}
			}
		freelist(y);
		}
	return l;
	}
}

//wypisywanie wartości elementów listy
void print(List* x){
	if(x->beg->next == x->end)
		printf("NONE");
	else{
	for(Elem* i = x->end->prev; i!=x->beg; i=i->prev)
		if(i == x->beg->next){
			printf("%li", i->val);
		}
		else{
			printf("%li ", i->val);
		}
	}
	printf("\n");
}

//zwalnianie pamięci z całej listy
void freelist(List* x){
	for(Elem* i = x->beg->next; i!=x->end; i=i->next)
		free(i->prev);
	free(x->end->prev);
	free(x->end);
	free(x);
}