#include <stdio.h>
#include <raylib.h>

#define MAP_DRAW_IMPLEMENTATION
#include "map_draw.h"

#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"


const int canvas_width = 600;
const int canvas_height = 600;
// #22aa55
#define CANVAS_BACKGROUND_COLOR   (Color){ 34, 170, 84, 255 }   

Graph graph;

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


void Init(int width, int height)
{
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

    /******** GUI ********/
    if (GuiButton((Rectangle){ 10, canvas_height + 20, 100, 35 }, "+ Add Point")) {
        graph_add_random_point(&graph, canvas_width, canvas_height);
    }

    if (GuiButton((Rectangle){ 120, canvas_height + 20, 100, 35 }, "+ Add Segment")) {
        graph_add_random_segment(&graph);
    }

    if (GuiButton((Rectangle){ 230, canvas_height + 20, 100, 35 }, "- Remove Segment")) {
        graph_remove_random_segment(&graph);
    }

    if (GuiButton((Rectangle){ 340, canvas_height + 20, 100, 35 }, "- Remove Point")) {
        graph_remove_random_point(&graph);
    }

    if (GuiButton((Rectangle){ 450, canvas_height + 20, 100, 35 }, "Clear")) {
        graph_free(&graph);
    }


    /******** Canvas ********/

    // Draw Canvas
    DrawRectangle(0, 0, canvas_width, canvas_height + 10, CANVAS_BACKGROUND_COLOR);

    DrawText("World Editor", 240, 20, 20, LIGHTGRAY);


    draw_graph(&graph);
}

