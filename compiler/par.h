#pragma once

#include "lex.h"

#include <stdio.h>
#include <stdlib.h>

#define S_UNKNOWN -1
#define S_NULL 0
#define S_STATEMENT_output 1
#define S_STATEMENT_assignment 2
#define S_ASSIGNMENT_in 10
#define S_ASSIGNMENT_expression 11
#define S_EXPRESSION 20
#define S_PRODUCT 30
#define S_ENTITY_number 40
#define S_ENTITY_identifier 41
#define S_ENTITY_expression 42
#define S_PRODUCT_REST_multiply 50
#define S_PRODUCT_REST_divide 51
#define S_PRODUCT_REST_null
#define S_REST_add 60
#define S_REST_substract 61
#define S_REST_null 62

struct syntax_node {
	int type, value;
	struct syntax_node *child1, *child2;
	syntax_node() : type(S_NULL), value(0), child1(NULL), child2(NULL) { }
};

extern struct syntax_node *syntax_tree_root;

void s_assignment(struct syntax_node *&n);
void s_expression(struct syntax_node *&n);
void s_product(struct syntax_node *&n);
void s_entity(struct syntax_node *&n);
void s_product_rest(struct syntax_node *&n);
void s_rest(struct syntax_node *&n);

void parse();
void print_syntax_tree(struct syntax_node *n);
