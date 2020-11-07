#ifndef PATH_H
#define PATH_H

#ifndef LIST_H
	#error Require list.h, please load before this header.
#endif /* Require LIST_H */
#ifndef LINK_H
	#error Require link.h, please load before this header.
#endif /* Require LINK_H */

typedef struct path {
	double distance;
	struct path *parent;
	void *ref_node;
	link ref_link;
} *path;

list path_find(list, void *);
/* list of path: list of link */
void path_free(list);

path path_get(list, void *);
/* list of path */

#endif /* PATH_H */
