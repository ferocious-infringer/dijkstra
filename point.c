#include <stdlib.h>
#include <math.h>
#include "point.h"

point point_new(double x, double y) {
	point a = (point) malloc(sizeof(struct point));
	a->x = x;
	a->y = y;
	return a;
}

point point_free(point a) {
	free(a);
}

double point_distance(point a, point b) {
	double dist_x = a->x - b->x;
	double dist_y = a->y - b->y;
	return sqrt(dist_x*dist_x + dist_y*dist_y);
}
