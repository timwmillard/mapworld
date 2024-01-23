/*
MIT License
Copyright (c) 2024 Tim Millard

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the “Software”), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


physics2d.h is a simple physics 2D library for programming games and
simulations.

This is a single-header-file library that provides easy-to-use.

Usage:
To use this library, copy physics2d.h into project.
This include this in one C files:

   #define PHYSICS2D_IMPLEMENTATION
   #include "physics2d.h"

*/

#ifndef PHYSICS2D_H
#define PHYSICS2D_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

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

extern void noise_seed(int seed);
extern double noise(double x);
extern double noise2(double x, double y);
extern double noise3(double x, double y, double z);
/* extern void destroy_noise(); */


/**
 * 2D Vector functions
 * 
 */
typedef struct Vec2 {
    double x;
    double y;
} Vec2;

static const Vec2 vec2zero = {0.0f, 0.0f};

static inline Vec2 vec2(const double x, const double y)
{
    return (Vec2){x, y};
}

static inline Vec2 vec2_add(const Vec2 a, const Vec2 b)
{
    return vec2(a.x + b.x, a.y + b.y);
}

static inline Vec2 vec2_sub(const Vec2 a, const Vec2 b)
{
    return vec2(a.x - b.x, a.y - b.y);
}

static inline double vec2_dot(const Vec2 a, const Vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

// Returns the magnitude (length) of the vector.
static inline double vec2_mag(const Vec2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

// Returns the magnitude (length) of the vector squared.
static inline double vec2_mag_sq(const Vec2 v)
{
    return v.x * v.x + v.y * v.y;
}

static inline Vec2 vec2_mult(const Vec2 v, const double m)
{
    return vec2(v.x * m, v.y * m);
}

static inline Vec2 vec2_div(const Vec2 v, const double m)
{
    return m == 0 ? vec2zero : vec2(v.x / m, v.y / m);
}

static inline Vec2 vec2_normalize(const Vec2 v)
{
    double mag = vec2_mag(v);
    return mag == 0 ? vec2zero : vec2(v.x/mag, v.y/mag);
}

// Set the magnitude (length) of the vector.
// Returns a new Vec2.
static inline Vec2 vec2_set_mag(const Vec2 v, double m)
{
    return vec2_mult(vec2_normalize(v), m);
}

static inline Vec2 vec2_neg(const Vec2 v)
{
    return vec2(-v.x, -v.y);
}

static inline bool vec2_equal(const Vec2 a, const Vec2 b)
{
    return a.x == b.x && a.y == b.y;
}

static inline bool vec2_equalp(const Vec2 a, const Vec2 b, int percision)
{
    return equalp(a.x, b.x, percision) 
        && equalp(a.y, b.y, percision);
}

/* First seed:
 * #include <time.h>
 * srand(time(NULL));
 */
static inline Vec2 vec2_random()
{
    double x = randfrom(-1, 1);
    double y = randfrom(-1, 1);
    return vec2(x, y);
}

// Limits a vector's magnitude to a maximum value. 
static inline Vec2 vec2_limit(const Vec2 v, double max)
{
    double mag = vec2_mag(v);
    if (mag <= max) return v;
    return vec2_set_mag(v, max);
}

/**
 * Vec2 TODO Funcs
 *

// Calculates the angle a 2D vector makes with the positive x-axis. Angles
// increase in the clockwise direction.p
static inline double vec2_heading(const Vec2 v);

// Rotates a 2D vector to a specific angle without changing its magnitude. By
// convention, the positive x-axis has an angle of 0. Angles increase in the
// clockwise direction.
static inline Vec2 vec2_set_heading(const Vec2 v, double angle);

// Rotates a 2D vector by an angle without changing its magnitude. By
// convention, the positive x-axis has an angle of 0. Angles increase in the
// clockwise direction.
static inline Vec2 vec2_rotate(const Vec2 v, double angle);

// Returns the angle between two vectors. The angle returned are signed.
static inline double vec2_angle_between(const Vec2 a, const Vec2 b);

// Calculates new x and y components that are proportionally the same
// distance between two vectors. The amt parameter is the amount to interpolate
// between the old vector and the new vector. 0.0 keeps all components equal to
// the old vector's, 0.5 is halfway between, and 1.0 sets all components equal
// to the new vector's.
static inline double vec2_lerp(const Vec2 a, const Vec2 b, const double amp);

*/

static inline void debug_vec2(char* name, Vec2 v)
{
    printf("%s: x=%lf, y=%lf\n", name, v.x, v.y);
}


/**
 * Body is a physics body that lives in an enviroment.
 * 
 *
 */
typedef struct Body {
    // Position
    Vec2 pos;

    // Velocity
    Vec2 vel;

    // Acceleration
    Vec2 acc;

    // Mass
    double mass;

    // Maximum speed
    double max_speed;

} Body;

extern Body *body_alloc();
extern void body_init(Body *body, Vec2 pos, double mass);
extern Body *body_new(Vec2 pos, float mass);
extern void body_apply_force(Body *body, const Vec2 force);
extern void body_apply_gravity(Body *body, const Vec2 gravity);
extern void body_update(Body *body, const double dt);
extern Vec2 body_momentum(Body *body);


/************
 * Shapes
 * 
 *
 */

// Point
typedef Vec2 Point;


// Line
typedef struct Line {
    Vec2 v1;
    Vec2 v2;
} Line;


// Circle
typedef struct Circle {
    Vec2 center;
    double radius;
} Circle;


// Triangle
typedef struct Triangle {
    Vec2 v1;
    Vec2 v2;
    Vec2 v3;
} Triangle;

// Quadrilateral
typedef struct Quad {
    Vec2 v1;
    Vec2 v2;
    Vec2 v3;
    Vec2 v4;
} Quad;

// Polygon
typedef struct Poly {
    int n;
    Vec2 *v;
} Poly;


// Rectangle
typedef struct Rect {
    Vec2 pos;
    double width;
    double height;
} Rect;


// Shape Type
typedef enum ShapeType {
    POINT,
    LINE,
    CIRCLE,
    RECT,
    TRIANGLE,
    QUAD,
    POLY,
} ShapeType;

// Shape is a general shape.
typedef struct Shape {
    ShapeType type;
    union {
        Point point;
        Line line;
        Circle circle;
        Rect rect;
        Triangle triangle;
        Quad quad;
        Poly poly;
    };
} Shape;


static inline Shape point(const double x, const double y)
{
    return (Shape){
        .type = POINT,
        .point = {x,y},
    };
}

static inline Shape linev(Vec2 v1, Vec2 v2)
{
    return (Shape){
        .type = LINE,
        .line = {v1, v2}
    };
}

static inline Shape line(double x1, double y1, double x2, double y2)
{
    return linev(vec2(x1, y1), vec2(x2, y2));
}

static inline Shape circlev(Vec2 center, double radius)
{
    return (Shape){
        .type = CIRCLE,
        .circle = {
            .center = center,
            .radius = radius,
        },
    };
}

static inline Shape circle(double x, double y, double radius)
{
    return circlev(vec2(x,y), radius);
}

static inline Shape rectv(const Vec2 pos, const double width, const double height)
{
    return (Shape){
        .type = RECT,
        .rect = {
            .pos = pos,
            .width = width,
            .height = height,
        },
    };
}

static inline Shape rect(const double x, const double y, const double width, const double height)
{
    return rectv(vec2(x,y), width, height);
}

static inline Shape trianglev(Vec2 v1, Vec2 v2, Vec2 v3)
{
    return (Shape){
        .type = TRIANGLE,
        .triangle = {v1, v2, v3},
    };
}

static inline Shape triangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return trianglev(vec2(x1,y1), vec2(x2,y2), vec2(x3,y3));
}

static inline Shape quadv(Vec2 v1, Vec2 v2, Vec2 v3, Vec2 v4)
{
    return (Shape){
        .type = QUAD,
        .quad = {v1, v2, v3, v4},
    };
}

static inline Shape quad(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
    return quadv(vec2(x1,y1), vec2(x2,y2), vec2(x3,y3), vec2(x4,y4));
}

static inline Quad rect_to_quad(Rect r)
{
    return (Quad){
        .v1 = r.pos,
        .v2 = vec2(r.pos.x + r.width, r.pos.y),
        .v3 = vec2(r.pos.x + r.width, r.pos.y + r.height),
        .v4 = vec2(r.pos.x , r.pos.y + r.height),
    };
}

static inline Shape poly(int n, Vec2 v1, ...)
{
    Vec2 *v = (Vec2*) malloc(sizeof(Vec2) * n);

    va_list args;
    va_start(args, v1);
    for (int i; i<n; i++) {
        Vec2 va = va_arg(args, Vec2);
        v[i] = va;
    }
    va_end(args);

    return (Shape){
        .type = POLY,
        .poly = {
            .n = n,
            .v = v,
        },
    };
}

static inline void poly_free(Poly p)
{
    free(p.v);
}

// Shape free can be called on any shape.
// Only a allocated poly will be freed.
// All other shapes will safely be ignored.
static inline void shape_free(Shape s)
{
    if (s.type == POLY) poly_free(s.poly);
}


// Collision
typedef struct Collision {
    bool hit;
    Shape shapes[2]; 
    Vec2 dir;
} Collision;

static const Collision collision_miss = {0};


#endif // End PHYSICS2D_H


/******************************************************************************/


#define PHYSICS2D_IMPLEMENTATION
#ifdef PHYSICS2D_IMPLEMENTATION


#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"


/**********************************************
 *
 * Body
 *
 **********************************************/

extern Body *body_alloc()
{
    return (Body *) malloc(sizeof(Body));
}

void body_init(Body *body, Vec2 pos, double mass)
{
    body->pos = pos;
    body->vel = vec2zero;
    body->acc = vec2zero;
    body->mass = mass;
    body->max_speed = -1;
}

Body *body_new(Vec2 pos, float mass)
{
    // Can't have zero mass body
    if (mass==0)
        return NULL;

    Body *body = body_alloc();
    if (!body)
        return NULL;

    body_init(body, pos, mass);

    return body;
}

void body_apply_force(Body *body, const Vec2 force)
{
    // Newtons law
    // ∑F = ma or a = F / m
    Vec2 acc = vec2_div(force, body->mass);
    body->acc = vec2_add(body->acc, acc);
}

void body_apply_gravity(Body *body, const Vec2 gravity)
{
    body->acc = vec2_add(body->acc, gravity);
}

void body_update(Body *body, const double dt)
{
    // Mutiply by delta time
    Vec2 acc = vec2_mult(body->acc, dt);
    body->vel = vec2_add(body->vel, acc);

    Vec2 vel = vec2_mult(body->vel, dt);
    body->pos = vec2_add(body->pos, vel);

    body->acc = vec2zero;
    if (body->max_speed >= 0) {
        body->vel = vec2_limit(body->vel, body->max_speed);
    }
}

Vec2 body_momentum(Body *body)
{
    return vec2_mult(body->vel, body->mass);
}

// friction returns a force. 
// f = -1 * u * N v
// 
// n normal force magnature
// coff coffiefient of friction
Vec2 friction(Vec2 vel, double coff, double n)
{
    vel = vec2_normalize(vel);
    return vec2_mult(vel, -coff*n);
}

Vec2 drag(Vec2 vel, double coff, double n)
{
    return vec2zero;
}

/**
 * Perlin Noise
 *
 */
/* #define STB_PERLIN_IMPLEMENTATION */
/* #include "stb_perlin.h" */

void noise_seed(int seed)
{
    /* stb_perlin_noise3_seed(x, y, z, 0, 0, 0, seed); */
}
double noise(double x);
double noise2(double x, double y);
double noise3(double x, double y, double z)
{
    /* return stb_perlin_noise3(x, y, z, 0, 0, 0); */
    return 0;
}

void destroy_noise();

/**********************************************
 *
 * Shapes
 *
 **********************************************/


// https://happycoding.io/tutorials/processing/collision-detection
// https://www.jeffreythompson.org/collision-detection/index.php

/**
 * Area functions
 * 
 */

double point_area(Point p)
{
    return 1;
}

double line_area(Line l)
{
    return 0;
}

double circle_area(Circle p)
{
    return M_PI * p.radius  * p.radius;
}

double triangle_area(Triangle t)
{
    return -1; // TODO
}

double rect_area(Rect r)
{
    return r.width * r.height;
}

double quad_area(Quad q)
{
    return -1; // TODO
}


double poly_area(Poly p)
{
    return -1; // TODO
}

double shape_area(Shape s) {
    switch (s.type) {
        case POINT: return point_area(s.point); break;
        case LINE: return line_area(s.line); break;
        case CIRCLE: return circle_area(s.circle); break;
        case TRIANGLE: return triangle_area(s.triangle); break;
        case QUAD: return quad_area(s.quad); break;
        case RECT: return rect_area(s.rect); break;
        case POLY: return poly_area(s.poly); break;
    }
    return false;
}

/**
 * Collision functions
 * 
 */

Collision point_collide(Point p1, Point p2)
{
    int p1x = p1.x;
    int p1y = p1.y;
    int p2x = p2.x;
    int p2y = p2.y;
    return (Collision) {
        .hit = p1x == p2x && p1y == p2y,
        .shapes = {
            { .type = POINT, .point = p1, },
            { .type = POINT, .point = p2, },
        },
    };
}

Collision point_collide_line(Point p, Line l) { return collision_miss; }
Collision point_collide_circle(Point p, Circle c) { return collision_miss; }
Collision point_collide_triangle(Point p, Triangle t) { return collision_miss; }
Collision point_collide_rect(Point p, Rect r) { return collision_miss; }
Collision point_collide_poly(Point p, Poly poly) { return collision_miss; }

Collision line_collide(Line l1, Line l2) { return collision_miss; }
Collision line_collide_point(Line l, Point p) { return collision_miss; }
Collision line_collide_circle(Line l, Circle c) { return collision_miss; }
Collision line_collide_triangle(Line l, Triangle t) { return collision_miss; }
Collision line_collide_rect(Line l, Rect r) { return collision_miss; }
Collision line_collide_poly(Line l, Poly poly) { return collision_miss; }

Collision circle_collide(Circle c1, Circle c2)
{ 
  // get distance between the circle's centers
  // use the Pythagorean Theorem to compute the distance
  double distX = c1.center.x - c2.center.x;
  double distY = c1.center.y - c2.center.y;
  double distance = sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the sum of the circle's
  // radii, the circles are touching!
  return (Collision) {
    .hit = distance <= c1.radius+c2.radius,
    .shapes = {
        { .type = CIRCLE, .circle = c1, },
        { .type = CIRCLE, .circle = c2, },
    },
    /* .dir = vec2_add(c1.center, c2.center), */
  };
}

Collision circle_collide_line(Circle c, Line l) { return collision_miss; }
Collision circle_collide_point(Circle c, Point p) { return collision_miss; }
Collision circle_collide_triangle(Circle p, Triangle t) { return collision_miss; }
Collision circle_collide_rect(Circle p, Rect r) { return collision_miss; }
Collision circle_collide_poly(Circle p, Poly poly) { return collision_miss; }

Collision rect_collide(Rect r1, Rect r2) { return collision_miss; }
Collision rect_collide_point(Rect r, Point p) { return collision_miss; }
Collision rect_collide_line(Rect r, Line l) { return collision_miss; }
Collision rect_collide_circle(Rect r, Circle c) { return collision_miss; }
Collision rect_collide_triangle(Rect r, Triangle t) { return collision_miss; }
Collision rect_collide_poly(Rect r, Poly poly) { return collision_miss; }

Collision triangle_collide(Triangle t1, Triangle t2) { return collision_miss; }
Collision triangle_collide_point(Triangle t, Point p) { return collision_miss; }
Collision triangle_collide_line(Triangle t, Line l) { return collision_miss; }
Collision triangle_collide_circle(Triangle t, Circle c) { return collision_miss; }
Collision triangle_collide_rect(Triangle t, Rect r) { return collision_miss; }
Collision triangle_collide_poly(Triangle t, Poly poly) { return collision_miss; }

Collision poly_collide(Poly p1, Poly p2) { return collision_miss; }
Collision poly_collide_point(Poly poly, Point point) { return collision_miss; }
Collision poly_collide_line(Poly p, Line l) { return collision_miss; }
Collision poly_collide_circle(Poly p, Circle c) { return collision_miss; }
Collision poly_collide_rect(Poly p, Rect r) { return collision_miss; }
Collision poly_collide_triangle(Poly p, Triangle poly) { return collision_miss; }

Collision shape_collide(Shape s1, Shape s2)
{
    if (s1.type == POINT && s2.type == POINT) return point_collide(s1.point, s2.point);
    if (s1.type == POINT && s2.type == LINE) return point_collide_line(s1.point, s2.line);
    if (s1.type == POINT && s2.type == CIRCLE) return point_collide_circle(s1.point, s2.circle);
    if (s1.type == POINT && s2.type == TRIANGLE) return point_collide_triangle(s1.point, s2.triangle);
    if (s1.type == POINT && s2.type == RECT) return point_collide_rect(s1.point, s2.rect);
    if (s1.type == POINT && s2.type == POLY) return point_collide_poly(s1.point, s2.poly);

    if (s1.type == LINE && s2.type == LINE) return line_collide(s1.line, s2.line);
    if (s1.type == LINE && s2.type == POINT) return line_collide_point(s1.line, s2.point);
    if (s1.type == LINE && s2.type == CIRCLE) return line_collide_circle(s1.line, s2.circle);
    if (s1.type == LINE && s2.type == TRIANGLE) return line_collide_triangle(s1.line, s2.triangle);
    if (s1.type == LINE && s2.type == RECT) return line_collide_rect(s1.line, s2.rect);
    if (s1.type == LINE && s2.type == POLY) return line_collide_poly(s1.line, s2.poly);

    if (s1.type == CIRCLE && s2.type == LINE) return circle_collide_line(s1.circle, s2.line);
    if (s1.type == CIRCLE && s2.type == POINT) return circle_collide_point(s1.circle, s2.point);
    if (s1.type == CIRCLE && s2.type == CIRCLE) return circle_collide(s1.circle, s2.circle);
    if (s1.type == CIRCLE && s2.type == TRIANGLE) return circle_collide_triangle(s1.circle, s2.triangle);
    if (s1.type == CIRCLE && s2.type == RECT) return circle_collide_rect(s1.circle, s2.rect);
    if (s1.type == CIRCLE && s2.type == POLY) return circle_collide_poly(s1.circle, s2.poly);

    if (s1.type == RECT && s2.type == LINE) return rect_collide_line(s1.rect, s2.line);
    if (s1.type == RECT && s2.type == POINT) return rect_collide_point(s1.rect, s2.point);
    if (s1.type == RECT && s2.type == CIRCLE) return rect_collide(s1.rect, s2.rect);
    if (s1.type == RECT && s2.type == TRIANGLE) return rect_collide_triangle(s1.rect, s2.triangle);
    if (s1.type == RECT && s2.type == RECT) return rect_collide(s1.rect, s2.rect);
    if (s1.type == RECT && s2.type == POLY) return rect_collide_poly(s1.rect, s2.poly);

    if (s1.type == TRIANGLE && s2.type == LINE) return triangle_collide_line(s1.triangle, s2.line);
    if (s1.type == TRIANGLE && s2.type == POINT) return triangle_collide_point(s1.triangle, s2.point);
    if (s1.type == TRIANGLE && s2.type == CIRCLE) return triangle_collide(s1.triangle, s2.triangle);
    if (s1.type == TRIANGLE && s2.type == TRIANGLE) return triangle_collide(s1.triangle, s2.triangle);
    if (s1.type == TRIANGLE && s2.type == RECT) return triangle_collide(s1.triangle, s2.triangle);
    if (s1.type == TRIANGLE && s2.type == POLY) return triangle_collide_poly(s1.triangle, s2.poly);

    return collision_miss;
}

Shape shape_offset(Vec2 start, Shape shape)
{
    Vec2 v1, v2, v3;
    switch (shape.type) {
        case POINT:
            shape.point = vec2_add(start, shape.point);
            break;
        case LINE:
            shape.line.v1 = vec2_add(start, shape.line.v1);
            shape.line.v2 = vec2_add(start, shape.line.v2);
            break;
        case CIRCLE:
            shape.circle.center = vec2_add(start, shape.circle.center);
            break;
        case RECT:
            shape.rect.pos = vec2_add(start, shape.rect.pos);
            break;
        case TRIANGLE:
            shape.triangle.v1 = vec2_add(start, shape.triangle.v1);
            shape.triangle.v2 = vec2_add(start, shape.triangle.v2);
            shape.triangle.v3 = vec2_add(start, shape.triangle.v3);
            break;
        case QUAD:
            shape.quad.v1 = vec2_add(start, shape.quad.v1);
            break;
        case POLY: 
            assert("not implemented");
            break;
    }
    return shape;
}

Vec2 shape_center(Shape s1, Shape s2);

// TODO: delete me, just for testing purposes
static inline double kinamatic(double acc, double vel, double pos, double t)
{
    return 0.5f * acc * t * t * vel * t + pos;
}


Shape *collider()
{
    return NULL;
}

void collider_free(Shape *collier)
{
    arrfree(collier);
}

void collider_add_shape(Shape **collider, Shape shape)
{
    arrput(*collider, shape);
}

Collision collider_detect_collisions(Vec2 pos1, Shape *shapes1, Vec2 pos2, Shape *shapes2)
{
    int n1 = arrlen(shapes1);
    int n2 = arrlen(shapes2);
    for (int i=0; i<n1; i++) {
        for (int j=0; j<n2; j++) {
            Shape s1 = shape_offset(pos1, shapes1[i]);
            Shape s2 = shape_offset(pos2, shapes2[j]);
            Collision collision = shape_collide(s1, s2);
            if (collision.hit) {
                collision.dir = vec2_normalize(vec2_sub(pos1, pos2));
                return collision;
            }
        }
    }
    return (Collision) { .hit = false };
}

#endif // End PHYSICS2D_IMPLEMENTATION

