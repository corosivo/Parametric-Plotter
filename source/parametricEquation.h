#pragma once


class sub_equation  // sub_equation Base Class
{
public:
	virtual double operator()(double, double=1)const
	{
		return -1;
	}
};

class parametricEquation  // Parametric Equation Base Class
{
private:
protected:
	bool allocated = false;
public:
	parametricEquation(int wid = -1, int hei = -1) :
		width(wid),
		height(hei),
		x_of(nullptr),
		y_of(nullptr)
	{}
	parametricEquation(const parametricEquation&) = default;
	parametricEquation& operator=(const parametricEquation&) = default;
	~parametricEquation()
	{
		if (allocated)
		{
			delete x_of;
			delete y_of;
		}
		//if (x_of != nullptr)
		//{
		//	delete x_of;
		//}
		//if (y_of != nullptr)
		//{
		//	delete y_of;
		//}
	}
	
	int width;
	int height;

	sub_equation* x_of;
	sub_equation* y_of;
};

// Constants
struct
{
	const long double pi =
		3.14159265358979323846264338327950288419716939937510;
}constants;

