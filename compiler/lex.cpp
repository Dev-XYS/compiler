#include "lex.h"

char token[256];
int type;

static char text[65536];
static char *end, *last, *p;

/* Utility functions */

static int is_space(char c) {
	return isspace(c);
}

static int is_alpha(char c) {
	return isalpha(c);
}

static int is_digit(char c) {
	return isdigit(c);
}

/* Interface functions */

void set_text(const char *s) {
	strcpy(text, s);
	p = text;
	end = text + strlen(text);

	next();
}

void next() {
	last = p;
	while (p < end && is_space(*p)) {
		p++;
	}
	if (p >= end) {
		type = T_NULL;
		return;
	}
	if (is_alpha(*p)) {
		if (*p == 'i' && p + 1 < end && *(p + 1) == 'n') {
			strcpy(token, "in");
			type = T_KEYWORD_IN;
			p += 2;
			return;
		}
		else {
			type = T_IDENTIFIER;
		}
	}
	else if (is_digit(*p)) {
		type = T_NUMBER;
	}
	else if (*p == '=') {
		type = T_EQUAL;
	}
	else if (*p == '(') {
		type = T_LEFT_PARENTHESIS;
	}
	else if (*p == ')') {
		type = T_RIGHT_PARENTHESIS;
	}
	else if (*p == '+') {
		type = T_ADD;
	}
	else if (*p == '-') {
		type = T_SUBSTRACT;
	}
	else if (*p == '*') {
		type = T_MULTIPLY;
	}
	else if (*p == '/') {
		type = T_DIVIDE;
	}
	else if (*p == '>') {
		type = T_OUTPUT_OPERATOR;
	}
	token[0] = *p;
	token[1] = '\0';
	p++;
}

int match(int t) {
	if (type != t) {
		panic();
		return E_SYNTAX_ERROR;
	}
	next();
	return E_NULL;
}
