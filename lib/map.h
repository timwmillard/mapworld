
#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


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

