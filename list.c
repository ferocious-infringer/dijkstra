#include <stdlib.h>
#include "list.h"

list list_add(list a, void *data) {
	list b = (list) malloc(sizeof(struct list));
	b->next = a;
	b->data = data;
	return b;
}

void list_free(list a) {
	list next;
	while (a) {
		next = a->next;
		free(a);
		a = next;
	}
}

list list_reverse(list a) {
	list b = NULL;
	list c;
	while (a) {
		c = a->next;
		a->next = b;
		b = a;
		a = c;
	}
	return b;
}

int list_length(list a) {
	int n = 0;
	for (; a; a =a->next)
		n += 1;
	return n;
}
