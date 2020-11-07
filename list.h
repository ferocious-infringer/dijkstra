#ifndef LIST_H
#define LIST_H

#define list_data(a, b) ((a) (b)->data)
/* type, list */

typedef struct list {
	void *data;
	struct list *next;
} *list;

list list_add(list, void *);
void list_free(list);

list list_reverse(list);
int list_length(list);

#endif /* LIST_H */
