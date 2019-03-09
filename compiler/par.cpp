#include "par.h"

struct syntax_node *syntax_tree_root;

void s_statement(struct syntax_node *&n) {
	n = new syntax_node;
	if (type == T_OUTPUT_OPERATOR) {
		match(T_OUTPUT_OPERATOR);
		n->type = S_STATEMENT_output;
		n->value = token[0];
		match(T_IDENTIFIER);
	}
	else {
		n->type = S_STATEMENT_assignment;
		s_assignment(n->child1);
	}
}

void s_assignment(struct syntax_node *&n) {
	n = new syntax_node;
	n->value = token[0];
	match(T_IDENTIFIER);
	match(T_EQUAL);
	if (type == T_KEYWORD_IN) {
		match(T_KEYWORD_IN);
		n->type = S_ASSIGNMENT_in;
		panic("unimplemented");
	}
	else {
		n->type = S_ASSIGNMENT_expression;
		s_expression(n->child1);
	}
}

void s_expression(struct syntax_node *&n) {
	n = new syntax_node;
	n->type = S_EXPRESSION;
	s_product(n->child1);
	s_rest(n->child2);
}

void s_product(struct syntax_node *&n) {
	n = new syntax_node;
	n->type = S_PRODUCT;
	s_entity(n->child1);
	s_product_rest(n->child2);
}

void s_entity(struct syntax_node *&n) {
	n = new syntax_node;
	if (type == T_NUMBER) {
		n->type = S_ENTITY_number;
		n->value = token[0] - '0';
		match(T_NUMBER);
	}
	else if (type == T_IDENTIFIER) {
		n->type = S_ENTITY_identifier;
		n->value = token[0];
		match(T_IDENTIFIER);
	}
	else if (type == T_LEFT_PARENTHESIS) {
		match(T_LEFT_PARENTHESIS);
		n->type = S_ENTITY_expression;
		s_expression(n->child1);
		match(T_RIGHT_PARENTHESIS);
	}
	else {
		report(E_SYNTAX_ERROR);
		panic();
	}
}

void s_product_rest(struct syntax_node *&n) {
	n = new syntax_node;
	if (type == T_MULTIPLY) {
		match(T_MULTIPLY);
		n->type = S_PRODUCT_REST_multiply;
		s_entity(n->child1);
		s_product_rest(n->child2);
	}
	else if (type == T_DIVIDE) {
		match(T_DIVIDE);
		n->type = S_PRODUCT_REST_divide;
		s_entity(n->child1);
		s_product_rest(n->child2);
	}
}

void s_rest(struct syntax_node *&n) {
	n = new syntax_node;
	if (type == T_ADD) {
		match(T_ADD);
		n->type = S_REST_add;
		s_product(n->child1);
		s_rest(n->child2);
	}
	if (type == T_SUBSTRACT) {
		match(T_SUBSTRACT);
		n->type = S_REST_substract;
		s_product(n->child1);
		s_rest(n->child2);
	}
}

void parse() {
	s_statement(syntax_tree_root);
	if (type != T_NULL) {
		panic();
	}
}

void print_tab(int c) {
	while (c--) {
		printf("  ");
	}
}

void print_syntax_tree(struct syntax_node *n) {
	static int level = 0;
	if (n == NULL) {
		return;
	}
	else {
		print_tab(level);
		if (n->type == S_ASSIGNMENT_expression || n->type == S_ASSIGNMENT_in) {
			printf("%d value='%c'\n", n->type, n->value);
		}
		else if (n->type == S_ENTITY_identifier) {
			printf("%d value='%c'\n", n->type, n->value);
		}
		else {
			printf("%d value=%d\n", n->type, n->value);
		}
		level++;
		if (n->child1 != NULL) {
			print_syntax_tree(n->child1);
		}
		if (n->child2 != NULL) {
			print_syntax_tree(n->child2);
		}
		level--;
	}
}
