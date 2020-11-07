#include <stdlib.h>
#include "link.h"

link link_new(double weight, void *ref_a, void *ref_b, link_head head) {
	link a = (link) malloc(sizeof(struct link));
	a->weight = weight;
	a->ref_a = ref_a;
	a->ref_b = ref_b;
	a->head = head;
	return a;
}

void link_free(link a) {
	free(a);
}

void link_reverse(link l) {
	switch (l->head) {
		case link_a: l->head = link_b; break;
		case link_b: l->head = link_a; break;
	}
}

void *link_get(link l, void *tail) {
	void *head = NULL;
	if (l->ref_a == tail && (l->head == link_b || l->head == link_both)) head = l->ref_b;
	if (l->ref_b == tail && (l->head == link_a || l->head == link_both)) head = l->ref_a;
	return head;
}
