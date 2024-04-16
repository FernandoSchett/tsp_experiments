#include "dists.hpp"

int dist_euc_2D(Point p1, Point p2) {
    long double xd = p1.x - p2.x;
    long double yd = p1.y - p2.y;
    return int(sqrt(xd * xd + yd * yd) + 0.5);
}

int dist_ceil_2D(Point p1, Point p2) {
	long double xd = p1.x - p2.x;
	long double yd = p1.y - p2.y;
	return ceil(sqrt(xd * xd + yd * yd));
}