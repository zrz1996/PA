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

