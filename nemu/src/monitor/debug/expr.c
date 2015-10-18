#include "nemu.h"
#include "parser.tab.h"
typedef struct yy_buffer_state * YY_BUFFER_STATE;
int yyparse();
int yyerror();
void lex_debug();
extern YY_BUFFER_STATE yy_scan_string(char * str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
static char str[1000];
extern int parseValue;
//const char *regsl[] = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"};
//const char *regsw[] = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};
//const char *regsb[] = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};
extern int accessReg(char *str)
{
	for (int i = 0; i < 8; i++)
		if (strstr(str, regsl[i]) != NULL)
			return reg_l(i);
	for (int i = 0; i < 8; i++)
		if (strstr(str, regsw[i]) != NULL)
			return reg_w(i);
	for (int i = 0; i < 8; i++)
		if (strstr(str, regsb[i]) != NULL)
			return reg_b(i);
	yyerror("");
	return 0;
}
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
