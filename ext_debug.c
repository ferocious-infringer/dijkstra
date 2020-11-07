#include <stdio.h>
#include "list.h"
#include "point.h"
#include "tag.h"
#include "link.h"
#include "path.h"
#include "ext_debug.h"

/*--------------------------------------------------*
   PRIVATE
 *--------------------------------------------------*/

static tag tag_find_addr(void *addr, list Ts) {
	for (; Ts; Ts = Ts->next) {
		tag t = (tag) Ts->data;
		if (tag_addr(t, addr)) return t;
	}
	return NULL;
}

static void head_symbol(link_head h, char **a, char **b) {
	if (h == link_both) { *a = "<<--"; *b = "-->>"; }
	if (h == link_a)    { *a = "<<--"; *b = "----"; }
	if (h == link_b)    { *a = "----"; *b = "-->>"; }
}

/*--------------------------------------------------*
   PUBLIC
 *--------------------------------------------------*/

void report(list Ts, list Ls, list Hs) {
	printf("TAGS: %d\n", list_length(Ts));
	for (list i = Ts; i; i = i->next) {
		tag   t =   (tag) i->data;
		point p = (point) t->addr;
		printf("[- %s -] %f, %f\n", t->id.s, p->x, p->y);
	}
	putchar('\n');

	printf("LINKS: %d\n", list_length(Ls));
	for (list i = Ls; i; i = i->next) {
		link l = (link) i->data;
		char *head_a, *head_b;
		head_symbol(l->head, &head_a, &head_b);
		printf("[- %s -] %s %lf %s [- %s -]\n",
			tag_find_addr(l->ref_a, Ts)->id.s,
			head_a,
			l->weight,
			head_b,
			tag_find_addr(l->ref_b, Ts)->id.s
		);
	}
	putchar('\n');

	printf("PATHS: %d\n", list_length(Hs));
	for (list i = Hs; i; i = i->next) {
		path h = (path) i->data;
		printf("[- %s -] <<-- %lf ---- [- %s -]",
			(h->parent)
				? tag_find_addr(h->parent->ref_node, Ts)->id.s
				: " ",
			h->distance,
			tag_find_addr(h->ref_node, Ts)->id.s
		);

		if (!h->ref_link) {
			printf(" --SOURCE\n");
			continue;
		}
		printf("   |   ");

		link l = h->ref_link;
		char *head_a, *head_b;
		head_symbol(l->head, &head_a, &head_b);
		printf("[- %s -] %s %lf %s [- %s -]\n",
			tag_find_addr(l->ref_a, Ts)->id.s,
			head_a,
			l->weight,
			head_b,
			tag_find_addr(l->ref_b, Ts)->id.s
		);
	}
}
