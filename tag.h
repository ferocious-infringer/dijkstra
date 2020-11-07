#ifndef TAG_H
#define TAG_H

#define tag_addr(a, b) ((a)->addr == (b))
#define tag_id_i(a, b) ((a)->id.s == (b))
#define tag_id_f(a, b) ((a)->id.f == (b))

typedef enum tag_type { tag_s, tag_i, tag_f } tag_type;

typedef union tag_id {
	char *s;
	int i;
	double f;
} tag_id;

typedef struct tag {
	void *addr;
	tag_id id;
	tag_type type;
} *tag;

tag tag_new(void *, tag_type);

tag tag_new_s(char *, void *);
tag tag_new_i(int, void *);
tag tag_new_d(double, void *);

void tag_free(tag);
int tag_id_s(tag, char *);

#endif /* TAG_H */
