#pragma once

#include "par.h"

extern int variables[256];

int dfs(struct syntax_node *n, int r);
int calculate();
