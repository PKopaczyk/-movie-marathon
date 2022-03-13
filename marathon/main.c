#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Tree.h"

#define MAX_USER_ID 65535
#define MAX_MOVIE_RATING 2147483647
int add_user(unsigned long parent_user_id, unsigned long user_id);
int del_user(unsigned long user_id);
int add_movie(unsigned long user_id, unsigned long movie_rating);
int del_movie(unsigned long user_id, unsigned long movie_rating);
int marathonn(unsigned long user_id, unsigned long k);

int add_user(unsigned long parent_user_id, unsigned long user_id) {
	if(parent_user_id > MAX_USER_ID || user_id > MAX_USER_ID)
		return 1;
	addUser(parent_user_id, user_id);
	return 0;
}
int del_user(unsigned long user_id) {
	if(user_id > MAX_USER_ID)
		return 1;
	delUser(user_id);
	return 0;
}
int add_movie(unsigned long user_id, unsigned long movie_rating) {
	if(user_id > MAX_USER_ID || movie_rating > MAX_MOVIE_RATING)
		return 1;
	addMovie(user_id, movie_rating);
	return 0;
}
int del_movie(unsigned long user_id, unsigned long movie_rating) {
	if(user_id > MAX_USER_ID || movie_rating > MAX_MOVIE_RATING)
		return 1;
	delMovie(user_id, movie_rating);
	return 0;
}
int marathonn(unsigned long user_id, unsigned long k) {
	if(user_id > MAX_USER_ID || k > MAX_MOVIE_RATING)
		return 1;
	List* l = marathon(user_id, k);
	if(l == NULL){
	}
	else{
		print(l);
		freelist(l);
	}
	return 0;
}

#define BUFF_SIZE 1024
#define MAX_PARSABLE_INT 3000000000ull

// returns 0 if and only if loaded int has no leading zeros and 
// belongs to [0, MAX_PARSABLE_INT]
int parse_int(char* buff, int buff_len, int* pos, unsigned long* x) {
	if(*pos == buff_len)
		return 1;

	if(buff[*pos] == '0' && *pos + 1 != buff_len && isdigit(buff[*pos + 1]))
		return 1; // wiodące zera

	unsigned long long a = 0;
	while (*pos != buff_len && isdigit(buff[*pos])) {
		a = a * 10 + (buff[*pos] - '0');
		++*pos;
		if(a > MAX_PARSABLE_INT)
			return 1;
	}

	*x = a;
	return 0;
}

int main(){

	for (int i = 0; i<65536; i++){
		position[i] = NULL;
	}

	position[0] = newnode(0);

	char buff[BUFF_SIZE];
	int c = ' ';
	while (c != EOF) {
		int len = 0, pos = 0;

		c = getchar();
		while (c != '\n' && c != EOF) {
			if(len < BUFF_SIZE)
				buff[len++] = c;
			c = getchar();
		}

		if(len == 0 || buff[0] == '#') {
			// nothing to do
		} else if(strncmp(buff, "addUser ", 8) == 0) {
			pos = 8;
			unsigned long arg1;
			unsigned long arg2;
			if(parse_int(buff, len, &pos, &arg1) || pos == len ||
				buff[pos++] != ' ' || parse_int(buff, len, &pos, &arg2) ||
				pos != len) {
				fprintf(stderr, "ERROR\n");
			} else if(add_user(arg1, arg2)) {
				fprintf(stderr, "ERROR\n");
			}

		} else if(strncmp(buff, "delUser ", 8) == 0) {
			pos = 8;
			unsigned long arg1;
			if(parse_int(buff, len, &pos, &arg1) || pos != len) {
				fprintf(stderr, "ERROR\n");
			} else if(del_user(arg1)) {
				fprintf(stderr, "ERROR\n");
			}

		} else if(strncmp(buff, "addMovie ", 9) == 0) {
			pos = 9;
			unsigned long arg1;
			unsigned long arg2;
			if(parse_int(buff, len, &pos, &arg1) || pos == len ||
				buff[pos++] != ' ' || parse_int(buff, len, &pos, &arg2) ||
				pos != len) {
				fprintf(stderr, "ERROR\n");
			} else if(add_movie(arg1, arg2)) {
				fprintf(stderr, "ERROR\n");
			}

		} else if(strncmp(buff, "delMovie ", 9) == 0) {
			pos = 9;
			unsigned long arg1;
			unsigned long arg2;
			if(parse_int(buff, len, &pos, &arg1) || pos == len ||
				buff[pos++] != ' ' || parse_int(buff, len, &pos, &arg2) ||
				pos != len) {
				fprintf(stderr, "ERROR\n");
			} else if(del_movie(arg1, arg2)) {
				fprintf(stderr, "ERROR\n");
			}

		} else if(strncmp(buff, "marathon ", 9) == 0) {
			pos = 9;
			unsigned long arg1;
			unsigned long arg2;
			if(parse_int(buff, len, &pos, &arg1) || pos == len ||
				buff[pos++] != ' ' || parse_int(buff, len, &pos, &arg2) ||
				pos != len) {
				fprintf(stderr, "ERROR\n");
			} else {
				if(marathonn(arg1, arg2)) {
					fprintf(stderr, "ERROR\n");
				}
			}
		} else {
			fprintf(stderr, "ERROR\n");
		}
	}
	freememory();
	return 0;
}
