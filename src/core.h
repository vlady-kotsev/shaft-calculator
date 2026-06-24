#pragma once
#include <stdlib.h>
#include <math.h>

#define APP_NAME "Shaft Calculator"

typedef enum
{
    _C35 = 50,
    _40Cr = 75,
    _C45 = 60,
    _42CrMo4 = 90
} Sigmadop;

typedef struct
{
    double mv;
    double mh;
    double mb;
    double meq;
    double d;
} ShaftResult;



void calculate_shaft(double p_kw, double n_rpm, Sigmadop material, double gear_x, double gear_d, double alpha, double a_x, double b_x, ShaftResult *result);