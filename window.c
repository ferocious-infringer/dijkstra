#include <GLFW/glfw3.h>
#include "window.h"

/*--------------------------------------------------*
   PRIVATE
 *--------------------------------------------------*/

static void (*window_display)(void) = NULL;
static void (*window_idle)(void) = NULL;

static void window_refresh_callback(GLFWwindow *window) {
 	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(width / -2, width / 2, height / -2, height / 2, -1, 1);
	window_redisplay();
 }

static GLFWwindow* window;

/*--------------------------------------------------*
   PUBLIC
 *--------------------------------------------------*/

int window_create() {
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowRefreshCallback(window, window_refresh_callback);

	return 0;
}

void window_loop() {
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	window_redisplay();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		if (window_idle) window_idle();

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}

void window_set_display(void (*ptr)(void)) { window_display = ptr; }
void window_set_idle(void (*ptr)(void)) { window_idle = ptr; }

void window_redisplay() {
	/* Render here */
	if (window_display) window_display();

	/* Swap front and back buffers */
	glfwSwapBuffers(window);
}
