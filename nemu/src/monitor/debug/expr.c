#include "nemu.h"
#include "parser.tab.h"
int yyparse();
void lex_debug();
extern char *yyin;
uint32_t expr(char *e, bool *success) {
	/*
	globalReadOffset = 0;
	int len = strlen(e);
	for (int i = 0; i < len; i++)
		globalInputText[i] = e[i];
	globalInputText[len] = '\n';
	globalInputText[len + 1] = 0;
	*/
	yyin = e;
	uint32_t v = yyparse();
	return v;
}
