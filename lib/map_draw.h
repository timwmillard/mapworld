/******************************************************************************
 * Header
 * map_draw.h
 ******************************************************************************/

#ifndef MAP_DRAW_H
#define MAP_DRAW_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>

#include "map.h"


void draw_point(Point point, double size, Color color);

void draw_segment(Segment line, double width, Color color);

void draw_graph(Graph *graph);

#endif

/******************************************************************************
 * Implementation
 * map_draw.c
 ******************************************************************************/

#ifdef MAP_DRAW_IMPLEMENTATION
#define MAP_DRAW_IMPLEMENTATION

#define MAP_IMPLEMENTATION
#include "map.h"

Vector2 point_to_vector2(Point p)
{
    return (Vector2) { .x = (float) p.x, .y = (float) p.y };
}

void draw_point(Point point, double size, Color color)
{
    DrawCircle(point.x, point.y, size/2, color);
}

void draw_segment(Segment seg, double width, Color color)
{
    Vector2 start = point_to_vector2(seg.p1);
    Vector2 end = point_to_vector2(seg.p2);
    DrawLineEx(start, end, width, color);
}

void draw_graph(Graph *graph)
{
    for (int i=0; i<arrlen(graph->segments); i++) {
        draw_segment(graph->segments[i], 2, DARKGRAY);
    }

    for (int i=0; i<arrlen(graph->points); i++) {
        draw_point(graph->points[i], 18, DARKGRAY);
    }
}


#endif
