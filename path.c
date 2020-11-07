#include <stdlib.h>
#include "list.h"
#include "link.h"
#include "path.h"

/*--------------------------------------------------*
   PRIVATE
 *--------------------------------------------------*/

static path path_new(double distance, path parent, void *node, link link) {
	path h = (path) malloc(sizeof(struct path));
	h->distance = distance;
	h->parent = parent;
	h->ref_node = node;
	h->ref_link = link;
	return h;
}

/*--------------------------------------------------*
   PUBLIC
 *--------------------------------------------------*/

void path_free(list Hs) {
	for (list i = Hs; i; i = i->next)
		free(i->data);
	list_free(Hs);
}

path path_get(list Hs, void *node) {
	for (; Hs; Hs = Hs->next) {
		path h = (path) Hs->data;
		if (h->ref_node == node) return h;
	}
	return NULL;
}

list path_find(list Ls, void *source) {
	if (!source) return NULL;

	list Qs = NULL;
	list Hs = NULL;

	for (list i = Ls; i; i = i->next) {
		link l = (link) i->data;
		if (!path_get(Qs, l->ref_a)) Qs = list_add(Qs, path_new(-1, NULL, l->ref_a, NULL));
		if (!path_get(Qs, l->ref_b)) Qs = list_add(Qs, path_new(-1, NULL, l->ref_b, NULL));
	}

	path h = path_get(Qs, source);
	if (h) h->distance = 0;
	else Hs = list_add(Hs, path_new(0, NULL, source, NULL));

	while (h) {
		Hs = list_add(Hs, h);

		for (list i = Ls; i; i = i->next) {
			link l = (link) i->data;
			void *head = link_get(l, h->ref_node);
			if (!head) continue;
			path q = path_get(Qs, head);
			if (!q) continue;
			double distance = h->distance + l->weight;
			if (q->distance >= 0 && distance >= q->distance) continue;
			q->distance = distance;
			q->parent = h;
			q->ref_link = l;
		}

		h = NULL;
		for (list i = Qs; i; i = i->next) {
			path q = (path) i->data;
			if (q->distance >= 0 && !path_get(Hs, q->ref_node) && (!h || q->distance < h->distance ))
				h = q;
		}
	}

	for (list i = Qs; i; i = i->next) {
		path q = (path) i->data;
		if (!path_get(Hs, q->ref_node)) free(q);
	}
	list_free(Qs);

	return Hs;
}
