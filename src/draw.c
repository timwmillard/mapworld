// #include <stdio.h>
#include <raylib.h>

#include "../lib/map_draw.h"

Graph graph;

void Init(int width, int height)
{
}

void ProcessEvents()
{
}


void Update(float dt)
{
}

// #22aa55
#define BACKGROUND_COLOR   (Color){ 34, 170, 84, 255 }   

void Draw()
{
    ClearBackground(BACKGROUND_COLOR);

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

