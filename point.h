#ifndef POINT_H
#define POINT_H

typedef struct point {
	double x;
	double y;
} *point;

point point_new(double, double);
point point_free(point);

double point_distance(point, point);

#endif /* POINT_H */
