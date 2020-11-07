#ifndef EXT_DEBUG_H
#define EXT_DEBUG_H

#ifndef LIST_H
	#error Require list.h, please load before this header.
#endif /* Require LIST_H */

void report(list, list, list);
/* list of tag,  list of link, list of path */

#endif /* EXT_DEBUG_H */
