#pragma once
#include <cmath>
#include "../source/parametricEquation.h"
using namespace std;

/// 
/// circle
/// 

class sub_circle_x : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return r * cos(t);
    }
};
class sub_circle_y : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return r * sin(t);
    }
};
class parametricCircle : public parametricEquation  // Circle derived class
{
protected:

public:
    parametricCircle(int wid = 60, int hei = 30) :
        parametricEquation(wid, hei)
    {
        parametricEquation::x_of = new sub_circle_x;
        parametricEquation::y_of = new sub_circle_y;
    }
};