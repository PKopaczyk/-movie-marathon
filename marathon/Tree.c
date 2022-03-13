#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Tree.h"

//free entire memory
void freememory(){
	for(unsigned int i = 1; i <65536; i++){
		if(position[i] !=NULL){
			del(position[i]->neighbours, position[i]);
		}
	}
	free(position[0]->neighbours->beg);
	free(position[0]->neighbours->end);
	free(position[0]->neighbours);
	freelist(position[0]->film);
	free(position[0]);
	position[0] = NULL;
}

//set nodeelem a and b to point at each other
void connectne(Nodeelem* a, Nodeelem* b){
	a->next = b;
	b->prev = a;
}

//create new nodeelem
Nodeelem* newne(Node* x){
	Nodeelem* r = malloc(sizeof(Nodeelem));
	if(r == NULL){
		freememory();
		exit(1);
	}
	else{
		r->prev = NULL;
		r->next = NULL;
		r->val = x;
		return r;
	}
}

//create new nodeelem list
Nodelist* createnl(){
	Nodelist* r = malloc(sizeof(Nodelist));
	if(r == NULL){
		freememory();
		exit(1);
	}
	else{
		r->beg = newne(NULL);
		r->end = newne(NULL);
		connectne(r->beg,r->end);
		return r;
	}
}

//create new node
Node* newnode(unsigned int x){
	Node* r = malloc(sizeof(Node));
	if(r == NULL){
		freememory();
		exit(1);
	}
	else{
		r->id = x;
		r->film = create();
		if(r->film == NULL){
			freememory();
			exit(1);
		}
		r->neighbours = createnl();
		return r;
	}
}

//connect nodeelem with value n to nodeelem x
Nodeelem* insertne(Nodeelem* x, Node* n){
	Nodeelem* y = newne(n);
	connectne(y, x->next);
	connectne(x,y);
	return y;
}

//connect nodeelem with value n at the beggining of the list
Nodeelem* pushfrontne(Nodelist* x, Node* n){
	return insertne(x->beg, n);
}

//delete nodeelem with value a from list x
void del(Nodelist* x, Node* a){
		connectne(a->nepointer->prev, x->beg->next);
		connectne(x->end->prev, a->nepointer->next);
		position[a->id] = NULL;
		free(a->neighbours->beg);
		free(a->neighbours->end);
		free(a->neighbours);
		freelist(a->film);
		free(a->nepointer);
		free(a);
}

void addUser(unsigned int parent, unsigned int user){
	if(position[user] != NULL || position[parent] == NULL)
		fprintf(stderr, "ERROR\n");
	else{
		Node* x = newnode(user);
		x->nepointer = pushfrontne(position[parent]->neighbours, x);
		position[user] = x;
		printf("OK\n");
	}
}

void delUser(unsigned int user){
	if(position[user] == NULL || user == 0)
		fprintf(stderr, "ERROR\n");
	else{
		del(position[user]->neighbours, position[user]);
		printf("OK\n");
	}
}

void addMovie(unsigned int user, long int movie){
	if(position[user] == NULL)
		fprintf(stderr, "ERROR\n");
	else{
		Elem* a = sortinsert(position[user]->film, movie);
		if(a == position[user]->film->beg)
			fprintf(stderr, "ERROR\n");
		else if(a == NULL){
			freememory();
			exit(1);
		}
		else 
			printf("OK\n");
	}
}

void delMovie(unsigned int user, long int movie){
	if(position[user] == NULL || checkmovie(position[user]->film, movie))
		fprintf(stderr, "ERROR\n");
	else{
		delelem(position[user]->film, movie);
		printf("OK\n"); 
	}
}

List* marathon(unsigned int user, long int k){
	if(position[user] == NULL){
		fprintf(stderr, "ERROR\n");
		return NULL;
	}
	else if(position[user]->neighbours->beg->next ==
			position[user]->neighbours->end){
		List *a = merge2(position[user]->film, create(), k);
		if(a == NULL){
			freememory();
			exit(1);
		}
		else
		return a;
	}
	else {
		List* l = create();
		if(l == NULL){
			freememory();
			exit(1);
		}
		else{
			for(Nodeelem* i = position[user]->neighbours->beg->next; 
				i != position[user]->neighbours->end; i = i->next){
				l = merge(l, marathon(i->val->id, k), k);
				if(l == NULL){
					freememory();
					exit(1);
				}
			}
			l = merge2(position[user]->film, l, k);
			if(l==NULL){
				freememory();
				exit(1);
			}
			return l;
		}
	}
}

