#include <GLFW/glfw3.h>
#include <stdio.h>
#include "list.h"
#include "link.h"
#include "ext_parser.h"
#include "path.h"
#include "ext_debug.h"
#include "window.h"

list Ts = NULL;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
		glVertex2f(-50, -50);
		glVertex2f( 50, -50);
		glVertex2f( 50,  50);
		glVertex2f(-50,  50);
	glEnd();
}

void idle() {
	window_redisplay();
}

int main(int argc, char *argv[]) {
	if (argc < 2) return 0;

	void *src = NULL;
	list Ps = NULL;
	list Ls = NULL;
	list Hs = NULL;

	putchar('\n');
	parse_file(argv[1], &Ps, &Ts, &Ls, &src);
	putchar('\n');
	Hs = path_find(Ls, src);
	Ts = list_reverse(Ts);
	Ps = list_reverse(Ps);
	Ls = list_reverse(Ls);
	report(Ts, Ls, Hs);
	putchar('\n'); 

	window_create();
	window_set_display(display);
	window_set_idle(idle);
	window_loop();

	free_all(Ps, Ts, Ls);
	path_free(Hs);

	printf("Hello, world!\n");
	return 0;
}
