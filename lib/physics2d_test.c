#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include "physics2d.h"

void test_start(char *test_name)
{
    printf(" - %s test: ", test_name);
}

void test_passed()
{
    printf("PASSED\n");
}

void all_test_start()
{
    printf("\n*********** Running tests *************\n\n");
}

void all_test_passed()
{
    printf("\n*********** All test passed ***********\n\n");
}

double roundp(double var, int percision)
{ 
    // 37.66666 * 100 =3766.66 
    // 3766.66 + .5 =3767.16    for rounding off value 
    // then type cast to int so value is 3767 
    // then divided by 100 so the value converted into 37.67 
    int multi = pow(10, percision);
    double value = (int)(var * multi + 0.5); 
    return (double) value / multi; 
}

void test_max()
{
    test_start("max");

    typedef struct {
        double a;
        double b;
        double want;
    } test;

    test tests[] =  {
        {.a=0.0, .b=1.0, .want=1.0},
        {.a=20.0, .b=1.0, .want=20.0},
        {.a=0.0, .b=0.0, .want=0.0},
        {.a=-0.01, .b=0.1, .want=0.1},
    };

    for (int i=0; i < sizeof(tests)/sizeof(test); i++) {
        test t = tests[i];
        double got = max(t.a, t.b);
        assert(roundp(got, 2) == roundp(t.want,2));
    }
    test_passed();
}

void test_min()
{
    test_start("min");

    typedef struct {
        double a;
        double b;
        double want;
    } test;

    test tests[] =  {
        {.a=0.0, .b=1.0, .want=0.0},
        {.a=20.0, .b=1.0, .want=1.0},
        {.a=0.0, .b=0.0, .want=0.0},
        {.a=-0.01, .b=0.1, .want=-0.01},
    };

    for (int i=0; i < sizeof(tests)/sizeof(test); i++) {
        test t = tests[i];
        double got = min(t.a, t.b);
        assert(roundp(got, 2) == roundp(t.want,2));
    }
    test_passed();
}

void test_map()
{
    test_start("map");

    typedef struct {
        double value;
        double start1;
        double end1;
        double start2;
        double end2;
        double result;
        bool expected;
    } test;

    test tests[] =  {
        {45, 0, 100, 0, 1000, 450.00, true},
        {45, 1, 100, 0, 1000, 450.00, false},
        {145, 100, 200, 200, 300, 245.00, true},
        {145, 100, 200, 1000, 2000, 1450.00, true},
        {50, 0, 100, 500, 1000, 750.00, true},  
    };

    for (int i=0; i < sizeof(tests)/sizeof(test); i++) {
        test t = tests[i];
        double got = map(t.value, t.start1, t.end1, t.start2, t.end2);
        assert((roundp(got, 2) == t.result) == t.expected);
    }
    test_passed();
}

void test_vec2_add()
{
    test_start("vec2_add");

    typedef struct {
        Vec2 a;
        Vec2 b;
        Vec2 want;
    } test;

    test tests[] =  {
        {.a=vec2(4.0, 8.0), .b=vec2(3.0, 9.0), .want=vec2(7.0, 17.0)},
        {.a=vec2(0.0, 0.0), .b=vec2(3.0, 9.0), .want=vec2(3.0, 9.0)},
    };

    for (int i=0; i < sizeof(tests)/sizeof(test); i++) {
        test t = tests[i];
        Vec2 got = vec2_add(t.a, t.b);
        assert(vec2_equalp(got, t.want, 2));
    }
    test_passed();
}

void test_vec2_sub()
{
    test_start("vec2_sub");

    typedef struct {
        Vec2 a;
        Vec2 b;
        Vec2 want;
    } test;

    test tests[] =  {
        {.a=vec2(4.0, 8.0), .b=vec2(3.0, 9.0), .want=vec2(1.0, -1.0)},
        {.a=vec2(0.0, 0.0), .b=vec2(3.0, 9.0), .want=vec2(-3.0, -9.0)},
    };

    for (int i=0; i < sizeof(tests)/sizeof(test); i++) {
        test t = tests[i];
        Vec2 got = vec2_sub(t.a, t.b);
        assert(vec2_equalp(got, t.want, 2));
    }
    test_passed();
}

void test_rect_to_quad()
{
    test_start("rect_to_quad");

    typedef struct {
        Rect rect;
        Quad want;
    } test;

    test tests[] =  {
        {.rect={0,0, 5, 5}, .want={0,0, -5,0, -5,-5, -5,0}},
    };

    for (int i=0; i < sizeof(tests)/sizeof(test); i++) {
        test t = tests[i];
        Quad got = rect_to_quad(t.rect);
        assert(vec2_equalp(got.v1, t.want.v1, 2));
        assert(vec2_equalp(got.v2, t.want.v2, 2));
        assert(vec2_equalp(got.v3, t.want.v3, 2));
        assert(vec2_equalp(got.v4, t.want.v4, 2));
    }
    test_passed();
}



int main()
{
    all_test_start();

    test_max();
    test_min();
    test_map();
    test_vec2_add();
    test_vec2_sub();
    test_rect_to_quad();

    all_test_passed();

    return 0;
}
