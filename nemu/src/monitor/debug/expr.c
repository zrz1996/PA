#include "nemu.h"
#include "parser.tab.h"
typedef struct yy_buffer_state * YY_BUFFER_STATE;
int yyparse();
void lex_debug();
extern YY_BUFFER_STATE yy_scan_string(char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
static char str[1000];
extern int parseValue;
uint32_t expr(char *e, bool *success) {
	if (e == NULL)
	{
		*success = false;
		return 0;
	}
	int len = strlen(e);
	for (int i = 0; i < len; i++)
		str[i] = e[i];
	str[len] = '\n';
	str[len + 1] = 0;
	YY_BUFFER_STATE buffer = yy_scan_string(str);
	if (yyparse() == 1)
		*success = 0;
	else
		*success = 1;
	yy_delete_buffer(buffer);
	return parseValue;
}
