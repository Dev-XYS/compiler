#pragma once

#include "asm.h"
#include "par.h"

extern int address;

void dfs(struct syntax_node *n, int r);
void translate();
