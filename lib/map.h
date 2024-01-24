/******************************************************************************
 * Header
 * map.h
 ******************************************************************************/

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

static inline double normalize(double value, double start, double end)
{
    return (value - start) / (end - start);
}

static inline double lerp(double start, double end, double amount)
{
    return start + amount * (end - start);
}

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

/* generate a random int number from min to max 
 * #include <time.h>
 * srand(time(NULL));
 * */
static int randfromi(int min, int max) 
{
    int range = (max - min); 
    int div = RAND_MAX / range;
    return (int)(min + (rand() / div));
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
    int x;
    int y;

} Point;

static inline Point point(int x, int y)
{
    return (Point){ .x = x, .y = y, };
}

static inline bool point_equals(Point p1, Point p2)
{
    return p1.x == p2.x && p1.y == p2.y;
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

static inline bool segment_includes_point(Segment s, Point p)
{
    return point_equals(s.p1, p) || point_equals(s.p2, p);
}

static inline bool segment_equals(Segment s1, Segment s2)
{
    return segment_includes_point(s1, s2.p1) && segment_includes_point(s1, s2.p2);
}

// Spatial Graph
typedef struct Graph {
    Point *points;
    Segment *segments;
} Graph;

#endif

/******************************************************************************
 * Implementation
 * map.c
 ******************************************************************************/

#ifdef MAP_IMPLEMENTATION

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

bool graph_contains_point(Graph *graph, Point p)
{
    for (int i=0; i<arrlen(graph->points); i++) {
        if (point_equals(graph->points[i], p))
            return true;
    }
    return false;
}

bool graph_add_point(Graph *graph, Point p)
{
    if (graph_contains_point(graph, p)) return false;

    arrput(graph->points, p);
    return true;
}

void graph_add_pointxy(Graph *graph, double x, double y)
{
    graph_add_point(graph, point(x, y));
}

int graph_points_len(Graph *graph)
{
    return arrlen(graph->points);
}

Point graph_point_at(Graph *graph, int index)
{
    if (index >= arrlen(graph->points) || index < 0)
        return (Point){0};

    return graph->points[index];
}

int graph_segments_len(Graph *graph)
{
    return arrlen(graph->segments);
}

Segment graph_segment_at(Graph *graph, int index)
{
    if (index >= arrlen(graph->segments) || index < 0)
        return (Segment){0};

    return graph->segments[index];
}

bool graph_add_segment(Graph *graph, Segment s)
{
    if (point_equals(s.p1, s.p2)) return false; 

    for (int i=0; i<arrlen(graph->segments); i++) {
        if (segment_equals(graph->segments[i], s))
            return false;
    }

    arrput(graph->segments, s);
    return true;
}

void graph_add_segmentp(Graph *graph, Point p1, Point p2)
{
   graph_add_segment(graph, segmentp(p1, p2));
}

bool graph_remove_segment(Graph *graph, Segment s)
{
    for (int i=0; i<arrlen(graph->segments); i++) {
        if (segment_equals(graph->segments[i], s)) {
            arrdel(graph->segments, i);
            return true;
        }
    }
    return false;
}

bool graph_remove_segment_at(Graph *graph, int index)
{
    if (index < 0 || index >= graph_segments_len(graph))
        return false;

    arrdel(graph->segments, index);
    return true;
}

#endif

