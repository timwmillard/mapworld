#include <stdio.h>
#include <raylib.h>

#define GRAPH_EDITOR_IMPLEMENTATION
#include "graph_editor.h"

#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"

typedef struct ControlPanel {
    int x, y;
    int width, height;
} ControlPanel;

/*** Global Variables ***/
static const int window_width = 600;
static const int window_height = 700;

static const int canvas_width = 600;
static const int canvas_height = 600;

Graph graph;

GraphEditor editor;
ControlPanel controls;
/************************/

void graph_add_random_point(Graph *graph, int width, int height)
{
    Point p = point(randfromi(0, width), randfrom(0, height));

    graph_add_point(graph, p);
}

void graph_add_random_segment(Graph *graph)
{

    int index1 = randfromi(0, graph_points_len(graph));
    int index2 = randfromi(0, graph_points_len(graph));

    Point p1 = graph_point_at(graph, index1);
    Point p2 = graph_point_at(graph, index2);

    bool success = graph_add_segment(graph, segmentp(p1, p2));
}

void graph_remove_random_segment(Graph *graph)
{
    int index = randfromi(0, graph_segments_len(graph)-1);
    Segment s = graph_segment_at(graph, index);
    bool success = graph_remove_segment(graph, s);
}

void graph_remove_random_point(Graph *graph)
{
    int index = randfromi(0, graph_points_len(graph)-1);
    Point p = graph_point_at(graph, index);
    bool success = graph_remove_point(graph, p);
}


void Init()
{
    InitWindow(window_width, window_height, "Map Editor");
    SetWindowPosition(100, 100);

    Point p1 = point(200, 200);
    Point p2 = point(500, 200);
    Point p3 = point(400, 400);
    Point p4 = point(100, 300);

    Segment s1 = segmentp(p1, p2);
    Segment s2 = segmentp(p1, p3);
    Segment s3 = segmentp(p1, p4);
    Segment s4 = segmentp(p2, p3);

    graph_add_point(&graph, p1);
    graph_add_point(&graph, p2);
    graph_add_point(&graph, p3);
    graph_add_point(&graph, p4);

    graph_add_segment(&graph, s1);
    graph_add_segment(&graph, s2);
    graph_add_segment(&graph, s3);
    graph_add_segment(&graph, s4);

    graph_editor_init(&editor, &graph, 0, 0, canvas_width, canvas_height);
    controls.x = canvas_width;
    controls.y = canvas_height;
    controls.width = window_width;
    controls.height = window_height - canvas_height;
}


void draw_control_panel(ControlPanel *panel)
{
    /******** GUI ********/
    if (GuiButton((Rectangle){ 10, panel->x + 20, 100, 35 }, "+ Add Point")) {
        graph_add_random_point(&graph, canvas_width, canvas_height);
    }

    if (GuiButton((Rectangle){ 120, panel->x + 20, 100, 35 }, "+ Add Segment")) {
        graph_add_random_segment(&graph);
    }

    if (GuiButton((Rectangle){ 230, panel->x + 20, 100, 35 }, "- Remove Segment")) {
        graph_remove_random_segment(&graph);
    }

    if (GuiButton((Rectangle){ 340, panel->x + 20, 100, 35 }, "- Remove Point")) {
        graph_remove_random_point(&graph);
    }

    if (GuiButton((Rectangle){ 450, panel->x + 20, 100, 35 }, "Clear")) {
        graph_free(&graph);
    }
}

void ProcessEvents()
{
}


void Update(float dt)
{
}


void Draw()
{
    ClearBackground(LIGHTGRAY);


    graph_editor_draw(&editor);
}

