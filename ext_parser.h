#ifndef EXT_PARSER_H
#define EXT_PARSER_H

#ifndef LIST_H
	#error Require list.h, please load before this header.
#endif /* Require LIST_H */

void parse_file(char *, list *, list *, list *, void **);
/* list of point, list of tag, list of link */
void free_all(list, list, list);
/* list of point, list of tag, list of link */

#endif /* EXT_PARSER_H */
