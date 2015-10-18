#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_list[NR_WP];
static WP *head, *free_;

extern void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_list[i].NO = i;
		wp_list[i].next = &wp_list[i + 1];
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}

extern WP* new_wp()
{
	if (free_ == NULL)
		return NULL;
	WP *node = free_;
	free_ = free_->next;
	return node;
}
extern void free_wp(WP *wp)
{
	wp->next = free_; free_ = wp;
	free_->next = NULL;
	free_->NO = 0;
}
extern void print_wp()
{
	WP *p;
	printf(" Num     Value1     Value2   What\n");
	for (p = head; p != NULL; p = p->next)
	{
		printf("%4d %10d %10d   %s\n", p->NO, p->val1, p->val2, p->Expr);
	}
}
extern void add_wp(char *args)
{
	bool parseState;
	int v = expr(args, &parseState);
	if (parseState)
	{
		WP *p = new_wp();
		p->NO = ++numWP;
		p->val1 = v;
		p->val2 = 0;
		strcpy(p->Expr, args);
		p->next = head;
		head = p;
	}
}
extern void delete_wp(int id)
{
	WP *p = head;
	bool flag = 0;
	if (p->NO == id)
	{
		head = p->next;
		free_wp(p);
		flag = 1;
	}
	else
	{
		for (; p != NULL; p = p->next)
			if (p->next != NULL && p->next->NO == id)
			{
				WP *q = p->next;
				p->next = q->next;
				free_wp(q);
				flag = 1;
				break;
			}
	}
	if (!flag)
		printf("No such watchpoint!\n");
}
