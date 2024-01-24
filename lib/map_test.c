#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include "map.h"

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

void test_lerp()
{
    test_start("lerp");

    typedef struct {
        double start;
        double end;
        double amount;
        double want;
    } test;

    test tests[] =  {
        {.start=2.0, .end=4.0, .amount=0.5, .want=3.0},
        {.start=2.0, .end=8.0, .amount=1.5, .want=11.0},
    };

    for (int i=0; i < sizeof(tests)/sizeof(test); i++) {
        test t = tests[i];
        double got = lerp(t.start, t.end, t.amount);
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




int main()
{
    all_test_start();

    test_max();
    test_min();
    test_map();
    test_lerp();

    all_test_passed();

    return 0;
}
