
#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

static inline double map(const double value,
        const double start1, const double stop1,
        const double start2, const double stop2)
{
    return (value - start1) / (stop1 - start1) * (stop2 - start2) + start2;
}

static inline double max(const double a, const double b)
{
    return (a > b)? a : b;
}

static inline double min(const double a, const double b)
{
    return (a < b)? a : b;
}

// equalp compares two doubles for equality with given percision.
static inline bool equalp(double a, double b, int percision)
{
    int multi = pow(10, percision);
    int value_a = (int)(a * multi + 0.5); 
    int value_b = (int)(b * multi + 0.5); 
    return value_a == value_b;
}

/* generate a random floating point number from min to max 
 * #include <time.h>
 * srand(time(NULL));
 * */
static double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

typedef struct Point {
    double x;
    double y;

} Point;

static inline Point point(double x, double y)
{
    return (Point){ .x = x, .y = y, };
}

typedef struct Segment {
    Point p1;
    Point p2;
} Segment;

static inline Segment segmentp(Point p1, Point p2)
{
    return (Segment){ 
        .p1 = p1,
        .p2 = p2,
    };
}
static inline Segment segment(double x1, double y1, double x2, double y2)
{
    return segmentp(point(x1, y1), point(x2, y2));
}

// Spatial Graph
typedef struct Graph {
    Point *points;
    Segment *segments;
} Graph;

#endif

/******************************************************************************/


#ifndef MAP_IMPLEMENTATION
#define MAP_IMPLEMENTATION

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"


void graph_add_point(Graph *graph, Point p)
{
    arrput(graph->points, p);
}

void graph_add_pointxy(Graph *graph, double x, double y)
{
    graph_add_point(graph, point(x, y));
}

void graph_add_segment(Graph *graph, Segment s)
{
    arrput(graph->segments, s);
}

void graph_add_segmentp(Graph *graph, Point p1, Point p2)
{
   graph_add_segment(graph, segmentp(p1, p2));
}


#endif

