#pragma once

#include "err.h"

#include <ctype.h>
#include <string.h>

#define T_UNKNOWN -1
#define T_NULL 0
#define T_IDENTIFIER 1
#define T_EQUAL 2
#define T_LEFT_PARENTHESIS 3
#define T_RIGHT_PARENTHESIS 4
#define T_KEYWORD_IN 5
#define T_ADD 6
#define T_SUBSTRACT 7
#define T_MULTIPLY 8
#define T_DIVIDE 9
#define T_NUMBER 10

extern char token[256];
extern int type;

void set_text(const char *s);
void next();
int match(int t);
void rewind_one();
