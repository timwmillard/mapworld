/******************************************************************************
 * Header
 * editor.h
 ******************************************************************************/

#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>

#include "graph.h"

void draw_point(Point point, double size, Color color);

void draw_segment(Segment line, double width, Color color);

void draw_graph(Graph *graph);

typedef struct GraphEditor {
    Graph *graph;

    int x, y;
    int width, height;
    Color background_color;

    Point selected_point;
    Point hovered_point;

} GraphEditor;

void graph_editor_init(GraphEditor *editor, Graph *graph, int x, int y, int width, int height);
void graph_editor_process_events(GraphEditor *editor);
void graph_editor_update(GraphEditor *editor, float ft);
void graph_editor_draw(GraphEditor *editor);

#endif

/******************************************************************************
 * Implementation
 * editor.c
 ******************************************************************************/

#ifdef EDITOR_IMPLEMENTATION

#define GRAPH_IMPLEMENTATION
#include "graph.h"

Vector2 point_to_vector2(Point p)
{
    return (Vector2) { .x = (float) p.x, .y = (float) p.y };
}

void draw_point(Point point, double size, Color color)
{
    if (!point_is_valid(point)) return;
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
    editor->selected_point = invalid_point;
}

void graph_editor_process_events(GraphEditor *editor)
{
    Point mouse = point(GetMouseX(), GetMouseY());
    Point hovered = graph_nearest_point(editor->graph, mouse, 10);
    editor->hovered_point = hovered;
    if (IsMouseButtonReleased(0)) {
        if (!point_is_valid(hovered)) {
            graph_add_point(editor->graph, mouse);
            editor->selected_point = mouse;
        } else {
            editor->selected_point = hovered;
        }
    }
}


void graph_editor_update(GraphEditor *editor, float dt)
{
}


void graph_editor_draw(GraphEditor *editor)
{
    // Draw Canvas Background
    DrawRectangle(editor->x, editor->y, editor->width, editor->height, editor->background_color);

    draw_graph(editor->graph);
    draw_point(editor->selected_point, 6, RED);
    draw_point(editor->hovered_point, 8, YELLOW);
}

#endif
