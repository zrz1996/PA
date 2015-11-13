#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}
static int cmd_si(char *args) {
	int n = 0;
	if (args != NULL)
	{
		if (sscanf(args, "%d", &n) != 1)
		{
			printf("The number of Steps should be a positive integer.\n");
			return 0;
		}
	}
	else
		n = 1;
	cpu_exec(n);
	return 0;
}
static int cmd_p(char *args) {
	bool parseState;
	int v = expr(args, &parseState);
	if (parseState)
		printf("%d\n", v);
	return 0;
}
static int cmd_info(char *args) {
	if (args == NULL || (strcmp(args, "w") != 0 && strcmp(args, "r") != 0))
	{
		printf("Argument should be either 'r' or 'w'.\n");
		return 0;
	}
	if (strcmp(args, "r") == 0)
	{
		int i;
		for (i = 0; i < 8; i++)
			printf("%3s:   0x%-12x     %d\n", regsl[i], reg_l(i), reg_l(i));
		for (i = 0; i < 8; i++)
			printf("%3s:   0x%-12x     %d\n", regsw[i], reg_w(i), reg_w(i));
		for (i = 0; i < 8; i++)
			printf("%3s:   0x%-12x     %d\n", regsb[i], reg_b(i), reg_b(i));
		printf("eflags\t%#10x [%s%s%s%s%s%s%s ]\n", cpu.eflags,
				cpu.cf ? "CF" : "",
				cpu.pf ? "PF" : "",
				cpu.zf ? "ZF" : "",
				cpu.sf ? "SF" : "",
				cpu._if_? "IF" : "",
				cpu.df ? "DF" : "",
				cpu.of ? "OF" : ""
			  );
	}
	else
	{
		print_wp();
	}
	return 0;
}
static int cmd_x(char *args) {
	char *num = strtok(args, " ");
	int len;
	if (num == NULL || sscanf(num, "%d", &len) != 1)
	{
		printf("Length required.\n");
		return 0;
	}
	char *ret = num + strlen(num) + 1;
	bool state;
	int val = expr(ret, &state);
	if (state == 0)
		return 0;
	int i;
	uint32_t v;
	for (i = 0; i < len; i++)
	{
		v = swaddr_read(val, 4);
		printf("0x%-12x:  0x%x ", val, v);
		val += 4;
		puts("");
	}	
	return 0;
}
static int cmd_w(char *args) 
{
	add_wp(args);
	return 0;
}
static int cmd_d(char *args) 
{
	int id;
	if (args == NULL || sscanf(args, "%d", &id) != 1)
	{
		printf("Watchpoint Num required.\n");
		return 0;
	}
	delete_wp(id);
	return 0;
}
static int cmd_help(char *args);

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	{ "si", "Single instruction", cmd_si},
	{ "p", "Print", cmd_p},
	{ "info", "Print register state or watch point information", cmd_info},
	{ "w", "Add watch point", cmd_w},
	{ "d", "Delete watch point", cmd_d},
	{ "x", "Scan memory", cmd_x},
	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
