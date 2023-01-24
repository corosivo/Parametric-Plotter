#pragma once
#include <cmath>
#include "../source/parametricEquation.h"
using namespace std;

/// 
/// cycloid
/// 

class sub_cycloid_x : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return r * (t - sin(t));
    }
};
class sub_cycloid_y : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return r * (1 - cos(t));
    }
};
class parametricCycloid : public parametricEquation  // Cycloid derived class
{
protected:

public:
    parametricCycloid(int wid = 240, int hei = 30) :
        parametricEquation(wid, hei)
    {
        parametricEquation::x_of = new sub_cycloid_x;
        parametricEquation::y_of = new sub_cycloid_y;
    }
};