#ifndef LINK_H
#define LINK_H

typedef enum link_head { link_a, link_b, link_both } link_head;

typedef struct link {
	double weight;
	void *ref_a;
	void *ref_b;
	link_head head;
} *link;

link link_new(double, void *, void *, link_head);
void link_free(link);

void link_reverse(link);
void *link_get(link, void *);

#endif /* LINK_H */
