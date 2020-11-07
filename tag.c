#include <stdlib.h>
#include <string.h>
#include "tag.h"

tag tag_new(void *addr, tag_type type) {
	tag a = (tag) malloc(sizeof(struct tag));
	a->addr = addr;
	a->type = type;
	return a;
}

tag tag_new_s(char *s, void *addr) {
	tag a = tag_new(addr, tag_s);
	a->id.s = (char *) calloc(strlen(s)+1, sizeof(char));
	strcpy(a->id.s, s);
	return a;
}

tag tag_new_i(int i, void *addr) {
	tag a = tag_new(addr, tag_i);
	a->id.i = i;
	return a;
}

tag tag_new_f(double f, void *addr) {
	tag a = tag_new(addr, tag_f);
	a->id.f = f;
	return a;
}

void tag_free(tag a) {
	if (a->type == tag_s)
		free(a->id.s);
	free(a);
}

int tag_id_s(tag a, char *s) {
	return !strcmp(a->id.s, s);
}
