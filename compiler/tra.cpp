#include "tra.h"

int address = 256;

void dfs(struct syntax_node *n, int w) {
	int a = address;
	switch (n->type) {
	case S_STATEMENT_output:
		asm_print(n->value);
		return;
	case S_STATEMENT_assignment:
		dfs(n->child1, 0);
		return;
	case S_ASSIGNMENT_expression:
		dfs(n->child1, n->value);
		return;
	case S_EXPRESSION:
		dfs(n->child1, w);
		dfs(n->child2, w);
		return;
	case S_PRODUCT:
		dfs(n->child1, w);
		dfs(n->child2, w);
		return;
	case S_ENTITY_number:
		asm_move_im(n->value, w);
		return;
	case S_ENTITY_identifier:
		asm_move_mr(n->value, EDX);
		asm_move_rm(EDX, w);
		return;
	case S_ENTITY_expression:
		dfs(n->child1, w);
		return;
	case S_PRODUCT_REST_multiply:
		dfs(n->child1, address++);
		asm_move_mr(w, EAX);
		asm_imul_mr(a, EAX);
		asm_move_rm(EAX, w);
		dfs(n->child2, w);
		return;
	case S_PRODUCT_REST_divide:
		dfs(n->child1, address++);
		asm_move_mr(w, EAX);
		asm_cltd();
		asm_idiv_m(a);
		asm_move_rm(EAX, w);
		dfs(n->child2, w);
		return;
	case S_REST_add:
		dfs(n->child1, address++);
		asm_move_mr(a, EDX);
		asm_add_rm(EDX, w);
		dfs(n->child2, w);
		return;
	case S_REST_substract:
		dfs(n->child1, address++);
		asm_move_mr(a, EDX);
		asm_sub_rm(EDX, w);
		dfs(n->child2, w);
		return;
	}
}

void translate() {
	dfs(syntax_tree_root, 0);
}
