#pragma once
#include <cmath>
#include "../source/parametricEquation.h"
using namespace std;

/// 
/// Spiral
/// 

class sub_Spiral_x : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return (1 - t / (4 * constants.pi)) * sin(t);
    }
};
class sub_Spiral_y : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return (1 - t / (4 * constants.pi)) * cos(t);
    }
};
class parametricSpiral : public parametricEquation  // Spiral derived class
{
protected:

public:
    parametricSpiral(int wid = 40, int hei = 20) :
        parametricEquation(wid, hei)
    {
        parametricEquation::x_of = new sub_Spiral_x;
        parametricEquation::y_of = new sub_Spiral_y;
    }
};
