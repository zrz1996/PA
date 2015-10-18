#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	struct watchpoint *next;
	char Expr[200];
	int val1, val2;
} WP;
int numWP;
void free_wp(WP *p);
WP *new_wp();
void print_wp();
void add_wp(char *args);
void delete_wp(int id);
#endif
