#include <stdio.h>
#include <raylib.h>

#define GRAPH_EDITOR_IMPLEMENTATION
#include "graph_editor.h"

#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"

typedef struct ControlPanel {
    int x, y;
    int width, height;
    Color background_color;
} ControlPanel;

/*** Global Variables ***/
static const int window_width = 600;
static const int window_height = 700;

static Graph graph;

static GraphEditor editor;
static ControlPanel controls;
/************************/

void graph_add_random_point(Graph *graph, int x, int y, int width, int height)
{
    Point p = point(randfromi(x, width), randfrom(y, height));

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

void control_panel_init(ControlPanel *panel, int x, int y, int width, int height)
{
    panel->x = x;
    panel->y = y;
    panel->width = width;
    panel->height = height;
    panel->background_color = DARKGRAY;
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

    graph_editor_init(&editor, &graph, 0, 0, window_width, 600);
    control_panel_init(&controls, 0, 600, window_width, 100);
}


void draw_control_panel(ControlPanel *panel)
{
    DrawRectangle(panel->x, panel->y, panel->width, panel->height, panel->background_color);

    const float top_padding = 20;
    const float left_padding = 10;
    const float button_width = 105;
    const float button_height = 40;
    const float button_padding = 5;

    /******** GUI ********/
    float x = panel->x + left_padding + button_padding;
    float y = panel->y + top_padding;
    if (GuiButton((Rectangle){ x, y, button_width, button_height }, "+ Add Point")) {
        graph_add_random_point(&graph, editor.x, editor.y, editor.width, editor.height);
    }

    x += button_padding + button_width + button_padding;
    if (GuiButton((Rectangle){ x, y, button_width, button_height }, "+ Add Segment")) {
        graph_add_random_segment(&graph);
    }

    x += button_padding + button_width + button_padding;
    if (GuiButton((Rectangle){ x, y, button_width, button_height }, "- Remove Segment")) {
        graph_remove_random_segment(&graph);
    }

    x += button_padding + button_width + button_padding;
    if (GuiButton((Rectangle){ x, y, button_width, button_height }, "- Remove Point")) {
        graph_remove_random_point(&graph);
    }

    x += button_padding + button_width + button_padding;
    if (GuiButton((Rectangle){ x, y, button_width, button_height }, "Clear")) {
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
    draw_control_panel(&controls);
}

