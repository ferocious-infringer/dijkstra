#include <stdio.h>
#include <string.h>
#include "list.h"
#include "point.h"
#include "tag.h"
#include "link.h"
#include "ext_parser.h"

/*--------------------------------------------------*
   PRIVATE
 *--------------------------------------------------*/

static tag tag_find(char *s, list Ts) {
	for (; Ts; Ts = Ts->next) {
		tag t = (tag) Ts->data;
		if (tag_id_s(t, s)) return t;
	}
	return NULL;
}

#define max 128
#define max_s "127"

/*--------------------------------------------------*
   PUBLIC
 *--------------------------------------------------*/

void parse_file(char *filename, list *Pptr, list *Tptr, list *Lptr, void **src) {
	list Ts = *Tptr, Ps = *Pptr, Ls = *Lptr;

	FILE *file = fopen(filename, "r");
	if (!file) fprintf(stderr, "Fail to open file %s.\n", filename);

	char line[max];

	int error = 0;
	int error_total = 0;
	int position = 0;
	char *message;

	for (;;) {
		/* Display parsing error */
		if (error) {
			fprintf(stderr, "[%s] Error at line %d: %s\n", filename, position, line);
			fprintf(stderr, "%*c%d: %s\n", strlen(filename)+17, ' ', position, message);
			error_total += 1;
		}

		position += 1;

		/* Process per line basis */
		{ 
			int i = 0;
			int c;
			for (;; i++) {
				c = fgetc(file);
				if (c == EOF)
					break;
				if (c == '\n')
					break;
				if (i < max-1)
					line[i] = c;
			}
			if (i < 1 && c == EOF)
				break;
			if (i > max-1) {
				error = 1;
				message = max_s " characters per-line maximum exceeded.";
				continue;
			}
			line[i] = '\0';
		}

		error = 0;

		/* Process first word */
		char word[max];
		int last = 0;

		int n = sscanf(line, "%" max_s "s%n", word, &last);
		/* Ignore empty line */
		if (n < 1) continue;

		/* Comment, signified by ~ (tilde) */
		if (word[0] == '~') continue;

		/* Source */
		if (!strcmp(word, "source")) {
			char id[max];
			int n = sscanf(line + last, "%" max_s "s", id);
			if (n < 1) {
				error = 1;
				message = "Usage: source <point>";
				continue;
			}

			tag t = tag_find(id, Ts);
			if (!t) {
				error = 1;
				message = "Point not found.";
				continue;
			}

			*src = t->addr;
			continue;
		}

		/* Point */
		if (!strcmp(word, "point")) {
			double x, y;
			char id[max];

			int n = sscanf(line + last, "%" max_s "s = (%lf, %lf)", id, &x, &y);
			if (n < 3){
				error = 1;
				message = "Usage: point <name> = (<x>, <y>)";
				continue;
			}

			tag t = tag_find(id, Ts);
			if (t) {
				error = 1;
				message = "Point already exist.";
				continue;
			}

			point p = point_new(x, y);
			Ps = list_add(Ps, p);

			t = tag_new_s(id, p);
			Ts = list_add(Ts, t);

			continue;
		}

		/* Link */
		if (!strcmp(word, "link")) {
			char id_a[max];
			char id_b[max];
			char head_s[max];

			int n = sscanf(line + last, "%" max_s "s %" max_s "s %" max_s "s", id_a, head_s, id_b);
			if (n < 3) {
				error = 1;
				message = "Usage: link <point> <relation> <point>";
				continue;
			}

			tag t_a = tag_find(id_a, Ts);
			tag t_b = tag_find(id_b, Ts);
			if (!t_a || !t_b) {
				error = 1;
				message = "Point not found.";
				continue;
			}
			if (t_a == t_b) {
				error = 1;
				message = "Link cannot be self referencing.";
				continue;
			}

			link_head head;
			     if (!strcmp(head_s, "<-->")) head = link_both;
			else if (!strcmp(head_s, "<---")) head = link_a;
			else if (!strcmp(head_s, "--->")) head = link_b;
			else {
				error = 1;
				message = "Invalid relation. ( <--> | ---> | <--- )";
				continue;
			}

			point ref_a = t_a->addr;
			point ref_b = t_b->addr;
			double weight = point_distance(ref_a, ref_b);

			for (list i = Ls; i; i = i->next) {
				link l = (link) i->data;
				if (l->ref_a == ref_a && l->ref_b == ref_b) {
					if (l->head == link_both || head == link_both)
						error = 1;
					if (l->head == link_a && head == link_a)
						error = 1;
					if (l->head == link_b && head == link_b)
						error = 1;
				}
				if (l->ref_a == ref_b && l->ref_b == ref_a) {
					if (l->head == link_both || head == link_both)
						error = 1;
					if (l->head == link_a && head == link_b)
						error = 1;
					if (l->head == link_b && head == link_a)
						error = 1;
				}
				if (error) break;
			}
			if (error) {
				message = "Link already exist.";
				continue;
			}

			link l = link_new(weight, ref_a, ref_b, head);
			Ls = list_add(Ls, l);

			continue;
		}

		/* Unknown option */
		error = 1;
		message = "Unknown option.";
	}

	printf("[%s] %d errors found.\n", filename, error_total);
	fclose(file);
	*Tptr = Ts, *Pptr = Ps, *Lptr = Ls;
}

void free_all(list Ps, list Ts, list Ls) {
	for (list i = Ps; i; i = i->next)
		point_free(i->data);
	list_free(Ps);
	for (list i = Ts; i; i = i->next)
		tag_free(i->data);
	list_free(Ts);
	for (list i = Ls; i; i = i->next)
		link_free(i->data);
	list_free(Ls);
}
