#include "asm.h"

const char *register_name[] = {
	"%eax",
	"%ebx",
	"%ecx",
	"%edx",
	"%esi"
};

FILE* file;

void asm_header() {
	fprintf(file, ".text\n");
	fprintf(file, ".section .rodata\n");
	fprintf(file, ".FORMAT:\n");
	fprintf(file, ".string \"%%d\\n\"\n");
	fprintf(file, ".text\n");
	fprintf(file, ".globl main\n");
	fprintf(file, ".type main, @function\n");
	fprintf(file, "main:\n");
	fprintf(file, "movq %%rsp, %%rbp\n");
}

void asm_print(int m) {
	asm_move_mr(m, EAX);
	fprintf(file, "movl %%eax, %%esi\n");
	fprintf(file, "leaq .FORMAT(%%rip), %%rdi\n");
	fprintf(file, "movl $0, %%eax\n");
	fprintf(file, "call printf@PLT\n");
}

void asm_move_im(int i, int m) {
	fprintf(file, "movl $%d, -%d(%%rbp)\n", i, m * 4);
}

void asm_move_mr(int m, int r) {
	fprintf(file, "movl -%d(%%rbp), %s\n", m * 4, register_name[r]);
}

void asm_move_rm(int r, int m) {
	fprintf(file, "movl %s, -%d(%%rbp)\n", register_name[r], m * 4);
}

void asm_imul_mr(int m, int r) {
	fprintf(file, "imull -%d(%%rbp), %s\n", m * 4, register_name[r]);
}

void asm_cltd() {
	fprintf(file, "cltd\n");
}

void asm_idiv_m(int m) {
	fprintf(file, "idivl -%d(%%rbp)\n", m * 4);
}

void asm_add_rm(int r, int m) {
	fprintf(file, "addl %s, -%d(%%rbp)\n", register_name[r], m * 4);
}

void asm_sub_rm(int r, int m) {
	fprintf(file, "subl %s, -%d(%%rbp)\n", register_name[r], m * 4);
}

void asm_footer() {
	fprintf(file, "movl $0, %%eax\n");
	fprintf(file, "ret\n");
}
