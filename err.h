#pragma once

#include <stdio.h>
#include <stdlib.h>

#define E_UNKNOWN -1
#define E_NULL 0
#define E_LEXICAL_ERROR 1
#define E_SYNTAX_ERROR 2

void report(int e);
void panic();
void panic(const char *s);
