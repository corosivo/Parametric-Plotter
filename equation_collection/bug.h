#pragma once
#include <cmath>
#include "../source/parametricEquation.h"
using namespace std;

/// 
/// a bug?
/// 

class sub_Bug_x : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return pow(cos(t), 3) + cos(3 * t);
    }
};
class sub_Bug_y : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return pow(sin(t), 3) + sin(4 * t);
    }
};
class parametricBug : public parametricEquation  // Bug derived class
{
protected:

public:
    parametricBug(int wid = 60, int hei = 30) :
        parametricEquation(wid, hei)
    {
        parametricEquation::x_of = new sub_Bug_x;
        parametricEquation::y_of = new sub_Bug_y;
    }
};