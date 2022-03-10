#ifndef TREE_H
#define TREE_H

typedef struct Node Node;
typedef struct Nodeelem Nodeelem;
typedef struct Nodelist Nodelist;

//Node reprezentuje Usera w drzewie
struct Node {
	unsigned int id;
	List *film;
	//neighbours reprezentuje liste użytkowników dodatych przez niego
	Nodelist *neighbours;
	Nodeelem *nepointer;
};

struct Nodelist {
	Nodeelem *beg, *end;
};

struct Nodeelem {
	Nodeelem *prev, *next;
	Node *val;
};

//tablica wskaźników na pozycje użytkownika w drzewie
Node* position[65536];

void freememory();

void connectne(Nodeelem *a, Nodeelem *b);

Nodeelem* newne(Node* x);

Nodelist* createnl();

Node* newnode(unsigned int x);

Nodeelem* insertne(Nodeelem* x, Node* n);

Nodeelem* pushfrontne(Nodelist* x, Node* n);

void del(Nodelist* x, Node* a);

void addUser(unsigned int parent, unsigned int user);

void delUser(unsigned int user);

void addMovie(unsigned int user, long int movie);

void delMovie(unsigned int user, long int movie);

List* marathon(unsigned int user, long int k);

#endif