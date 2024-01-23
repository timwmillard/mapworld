#include <stdio.h>
#include <raylib.h>

#include "../lib/map_draw.h"

#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui.h"


const int canvas_width = 600;
const int canvas_height = 600;
// #22aa55
#define CANVAS_BACKGROUND_COLOR   (Color){ 34, 170, 84, 255 }   

Graph graph;

void graph_add_random_point(Graph *graph, double width, double height) {

    Point p = point(randfrom(0, width), randfrom(0, height));

    graph_add_point(graph, p);
}

void Init(int width, int height)
{
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
    if (GuiButton((Rectangle){ 10, canvas_height + 10, 100, 40 }, "+ Add Point")) {
        graph_add_random_point(&graph, canvas_width, canvas_height);
    }


    /******** Canvas ********/

    // Draw Canvas
    DrawRectangle(0, 0, canvas_width, canvas_height, CANVAS_BACKGROUND_COLOR);

    DrawText("World Editor", 240, 20, 20, LIGHTGRAY);

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


    draw_graph(&graph);
}

