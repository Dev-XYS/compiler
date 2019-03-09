#pragma once

#include <stdio.h>

#define EAX 0
#define EDX 3
#define ESI 4

extern const char *register_name[];

extern FILE *file;

void asm_print(int m);
void asm_header();
void asm_move_im(int i, int m);
void asm_move_mr(int m, int r);
void asm_move_rm(int r, int m);
void asm_imul_mr(int m, int r);
void asm_cltd();
void asm_idiv_m(int m);
void asm_add_rm(int r, int m);
void asm_sub_rm(int r, int m);
void asm_footer();
