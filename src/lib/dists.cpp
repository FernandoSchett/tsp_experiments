/*
 * -----------------------------------------------------------------------------
 * File Name:          dists.cpp
 * Authors:            Fernando Schettini (Fernandoschettini@outlook.com) and Vitor Barbosa
 * Last Modified Date: 22/07/2024
 * Purpose: 		  Functions responsible for calculating the distance between two points for each instance type.           
 * -----------------------------------------------------------------------------
 */

#include "dists.hpp"

// For EUC TSP instances
int dist_euc_2D(Point p_i, Point p_j) {
    long double xd = p_i.x - p_j.x;
    long double yd = p_i.y - p_j.y;
    return int(sqrt(xd * xd + yd * yd) + 0.5);
}

// For CEIL TSP instances
int dist_ceil_2D(Point p_i, Point p_j) {
    long double xd = p_i.x - p_j.x;
    long double yd = p_i.y - p_j.y;
    return ceil(sqrt(xd * xd + yd * yd));
}

// For GEO TSP instances
int dist_geo(Point p_i, Point p_j) {
    long double PI = 3.141592;
    
    int deg = int(p_i.x + 0.5);
    long double min = p_i.x - deg;
    long double lat_i = PI * (deg + 5.0 * min / 3.0) / 180.0;
    deg = int(p_i.y + 0.5);
    min = p_i.y - deg;
    long double lon_i = PI * (deg + 5.0 * min / 3.0) / 180.0;

    deg = int(p_j.x + 0.5);
    min = p_j.x - deg;
    long double lat_j = PI * (deg + 5.0 * min / 3.0) / 180.0;
    deg = int(p_j.y + 0.5);
    min = p_j.y - deg;
    long double lon_j = PI * (deg + 5.0 * min / 3.0) / 180.0;
    
    long double RRR = 6378.388;
    long double q1 = cos(lon_i - lon_j);
    long double q2 = cos(lat_i - lat_j);
    long double q3 = cos(lat_i + lat_j);

    int dij = int(RRR * acos(0.5*((1.0+q1)*q2 - (1.0-q1)*q3)) + 1.0);
    return dij;
}
