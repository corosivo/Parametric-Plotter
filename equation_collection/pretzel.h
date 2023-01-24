#pragma once
#include <cmath>
#include "../source/parametricEquation.h"
using namespace std;


/// 
/// pretzel
/// 

class sub_pretzel_x : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return r * pow(cos(2 * t), 2);
    }
};
class sub_pretzel_y : public sub_equation
{
public:
    virtual double operator()(double t, double r = 1)const override
    {
        return r * sin(3 * t);
    }
};
class parametricPretzel : public parametricEquation  // Pretzel derived class
{
protected:

public:
    parametricPretzel(int wid = 60, int hei = 30) :
        parametricEquation(wid, hei)
    {
        parametricEquation::x_of = new sub_pretzel_x;
        parametricEquation::y_of = new sub_pretzel_y;
    }
};

