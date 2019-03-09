#include "tra.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *in = fopen(argv[1], "r");
	file = fopen("output.s", "w");

	asm_header();
	while (1) {
		char buffer[65536];
		if (fscanf(in, "%[^\n]\n", buffer) == -1) {
			break;
		}
		printf("[%s]\n", buffer);
		if (buffer[0] == '\0') {
			continue;
		}

		try {
			set_text(buffer);
			parse();
			print_syntax_tree(syntax_tree_root);
			printf("\n");
			translate();
		}
		catch(int) { }
	}
	asm_footer();

	return 0;
}
