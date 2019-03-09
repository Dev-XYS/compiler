#include "tra.h"

#include <stdio.h>

int main() {
//	FILE *f = fopen("input.txt", "r");
//	char buffer[65536];
//	fscanf(f, "%[^\xff]", buffer);

	memset(variables, 0, sizeof(variables));

	while (1) {
		char buffer[65536];
		printf(">>> ");
		fgets(buffer, sizeof(buffer), stdin);

		try {
			set_text(buffer);
			parse();
			printf("\n");
			print_syntax_tree(syntax_tree_root);
			int result = calculate();

			printf("\nresult = %d\n\n", result);

			variables[syntax_tree_root->value] = result;
		}
		catch(int) { }
	}

	return 0;
}
