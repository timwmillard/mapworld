/******************************************************************************
 * Header
 * map_draw.h
 ******************************************************************************/

#ifndef GRAPH_EDITOR_H
#define GRAPH_EDITOR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>

#include "../lib/map.h"

void draw_point(Point point, double size, Color color);

void draw_segment(Segment line, double width, Color color);

void draw_graph(Graph *graph);

typedef struct GraphEditor {
    Graph *graph;

    int x, y;
    int width, height;
    Color background_color;
} GraphEditor;

void graph_editor_init(GraphEditor *editor, Graph *graph, int x, int y, int width, int height);
void graph_editor_process_events(GraphEditor *editor);
void graph_editor_update(GraphEditor *editor, double dt);
void graph_editor_draw(GraphEditor *editor);

#endif

/******************************************************************************
 * Implementation
 * graph_editor.c
 ******************************************************************************/

#ifdef GRAPH_EDITOR_IMPLEMENTATION

#define MAP_IMPLEMENTATION
#include "../lib/map.h"

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
    if (graph == NULL) return;

    for (int i=0; i<arrlen(graph->segments); i++) {
        draw_segment(graph->segments[i], 2, DARKGRAY);
    }

    for (int i=0; i<arrlen(graph->points); i++) {
        draw_point(graph->points[i], 18, DARKGRAY);
    }
}

void graph_editor_init(GraphEditor *editor,
                       Graph *graph,
                       int x,
                       int y,
                       int width,
                       int height)
{
    editor->graph = graph;
    editor->x = x;
    editor->y = y;
    editor->width = width;
    editor->height = height;
    editor->background_color = (Color){ 34, 170, 84, 255 }; // #22aa55

}

void graph_editor_process_events(GraphEditor *editor)
{
}


void graph_editor_update(GraphEditor *editor, double dt)
{
}


void graph_editor_draw(GraphEditor *editor)
{
    // Draw Canvas
    DrawRectangle(editor->x, editor->y, editor->width, editor->height, editor->background_color);

    draw_graph(editor->graph);
}

#endif
