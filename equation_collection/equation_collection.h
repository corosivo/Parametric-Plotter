#pragma once
#include <cmath>
#include "../source/parametricEquation.h"
#include "circle.h"
#include "cycloid.h"
#include "spiral.h"
#include "pretzel.h"
#include "bug.h"
using namespace std;

/// 
/// NAME (template)
/// 

class sub_NAME_x : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return 0; // x(t,s) goes here
    }
};
class sub_NAME_y : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return 0; // y(t,s) goes here
    }
};
class parametricNAME : public parametricEquation  // NAME derived class
{
protected:

public:
    parametricNAME(int wid = 0, int hei = 0) :  // Replace 'Wid' and 'hei' with default plot geometry
        parametricEquation(wid, hei)
    {
        parametricEquation::x_of = new sub_NAME_x;
        parametricEquation::y_of = new sub_NAME_y;
    }
};
