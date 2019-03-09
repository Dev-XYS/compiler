#include "tra.h"

int variables[256];

int dfs(struct syntax_node *n, int r) {
	switch (n->type) {
	case S_NULL:
		return r;
	case S_EXPRESSION:
	case S_PRODUCT:
		return dfs(n->child2, dfs(n->child1, 0));
	case S_ENTITY_number:
		return n->value;
	case S_ENTITY_identifier:
		return variables[n->value];
	case S_ENTITY_expression:
		return dfs(n->child1, 0);
	case S_PRODUCT_REST_multiply:
		return dfs(n->child2, r * dfs(n->child1, 0));
	case S_PRODUCT_REST_divide: {
		int t = dfs(n->child1, 0);
		if (t == 0) {
			panic("divided by zero");
		}
		return dfs(n->child2, r / t);
	}
	case S_REST_add:
		return dfs(n->child2, r + dfs(n->child1, 0));
	case S_REST_substract:
		return dfs(n->child2, r - dfs(n->child1, 0));
	}
}

int calculate() {
	return dfs(syntax_tree_root->child1, 0);
}
