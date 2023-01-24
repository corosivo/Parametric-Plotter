#include "parametricPlotter.h"

// struct definitions

struct parameter // holds parameter for parametricEquation
{
	double start = 0;
	double end = 0;
	double span = -1;
	bool is_set = false;
};


template <class T>
struct dim_type
{
	std::vector<T> coordinates;
	T min = numeric_limits<T>::max();
	T max = numeric_limits<T>::min();
	T origin = 0;
};


struct dimension
{
	dim_type<double> raw;
	dim_type<int> rounded;
	dimension();
};

dimension::dimension()
{
	raw.min = std::numeric_limits<double>::max();
	raw.max = std::numeric_limits<double>::min();

	rounded.min = std::numeric_limits<int>::max();
	rounded.max = std::numeric_limits<int>::min();
}


// controls
void parametricPlotter::prepare_for_deletion()
{
	if (pEquation != nullptr)
		delete pEquation;
	if (X != nullptr)
		delete X;
	if (Y != nullptr)
		delete Y;
	if (t != nullptr)
		delete t;
	if (s != nullptr)
		delete s;
	pEquation = nullptr;
	X = nullptr;
	Y = nullptr;
	t = nullptr;
	s = nullptr;
}
void parametricPlotter::reset_dims()
{
	if (X == nullptr || Y == nullptr)
		return;
	X->raw.max = std::numeric_limits<double>::min();
	X->raw.min = std::numeric_limits<double>::max();

	Y->raw.max = std::numeric_limits<double>::min();
	Y->raw.min = std::numeric_limits<double>::max();
}
void parametricPlotter::clear_outputs()
{
	strvec.clear();
	formatted_string.clear();
	reset_dims();
}


// processing
void parametricPlotter::calculate_solutions(
	dimension& dim,
	sub_equation& f_of,
	parameter& par)
{
	if (!par.is_set)
		throw "ERROR: Parameter was not set, before starting plotter!\n";
	for (double i = 0; i < par.span; i += (par.span / samples))  // get values in span [0,t) and determine each coordinates minimum and maximum
	{
		dim.raw.coordinates.push_back(f_of(i));
		if (dim.raw.coordinates.back() > dim.raw.max)
			dim.raw.max = dim.raw.coordinates.back();
		if (dim.raw.coordinates.back() < dim.raw.min)
			dim.raw.min = dim.raw.coordinates.back();
	}
}

void parametricPlotter::map_solutions(
	dimension& dim1,
	dimension& dim2,
	parameter& par)
{	
	// check if the two vectors of result have managed to stay alligned
	if (dim1.raw.coordinates.size() != dim2.raw.coordinates.size())
		throw "Error: x and y coor vect are of differing length!\n  in parametricPlotter.fit()";
	
	// calculate the coefficient for for follwoing steps
	double x_coef = (
		(pEquation->width - 1) - 0) 
		/ (dim1.raw.max - dim1.raw.min);
	double y_coef = (
		(pEquation->height - 1) - 0) 
		/ (dim2.raw.max - dim2.raw.min);
	
	// map each of the raw x and y into their target ranges,
	// implements mapping via feeding the results of an
	// inverse lerp of the inputs into a lerp to the output
	// ranges    -> lerp(t = (invlerp(input)), out_min, out_max)
	for (int i = 0; i < dim1.raw.coordinates.size(); ++i)
	{
		dim1.raw.coordinates[i] = 0 - x_coef * dim1.raw.min
			+ x_coef * dim1.raw.coordinates[i];
		dim2.raw.coordinates[i] = 0 - y_coef * dim2.raw.min 
			+ y_coef * dim2.raw.coordinates[i];
	}

	// put the origin from mapping in each dimensions POD
	dim1.raw.origin = -x_coef * dim1.raw.min;
	dim2.raw.origin = -y_coef * dim2.raw.min;
	
	return;

}

void parametricPlotter::convert_to_int(
	dimension& dim)
{
	// convert raw origin, min, and max to integers, no more processing on them
	dim.rounded.origin = static_cast<int>(round(dim.raw.origin));
	dim.rounded.max = static_cast<int>(round(dim.raw.max));
	dim.rounded.min = static_cast<int>(round(dim.raw.min));

	// match processed vector's size to raw vector's size
	dim.rounded.coordinates.resize(dim.raw.coordinates.size());

	for (int i = 0; i < dim.rounded.coordinates.size(); ++i)
	{
		// round->cast->assign
		dim.rounded.coordinates[i] = 
			static_cast<int>(round(dim.raw.coordinates[i]));
		
		//double-check that everyting is clamped to the proper range
		if (dim.rounded.coordinates.back() > dim.rounded.max-1)
			dim.rounded.coordinates.back() = dim.rounded.max-1;
		else if (dim.rounded.coordinates.back() < dim.rounded.min)
			dim.rounded.coordinates.back() = dim.rounded.min;
	}
	return;
}


// formatting
std::vector<std::string> parametricPlotter::string_vectorize(
	dimension& dim1,
	dimension& dim2)
{

	std::vector<std::string> str;
	str.resize(pEquation->height);
	for (auto i = str.begin(); i != str.end(); ++i)
	{
		i->resize(pEquation->width + 1, ' ');
		i->back() = '\n';
	}
 
	str_frames.resize(samples);
	for (auto i = str_frames.begin(); i < str_frames.end(); ++i)
	{
		i->resize(pEquation->height * pEquation->width);
		i->assign(flatten_string_vector(str));
	}

	str[dim2.rounded.origin].assign(std::string(pEquation->width, '-') + "\n");

	for (int i = 0; i < pEquation->height; ++i)
		str[i][dim1.rounded.origin] = '|';

	for (int i = 0; i < dim1.rounded.coordinates.size()-1; ++i)
	{
		str[dim2.rounded.coordinates[i]].at(dim1.rounded.coordinates[i]) = 'X';
		str_frames[i] = flatten_string_vector(str);
	}

	return str;
}

std::string parametricPlotter::flatten_string_vector(
	std::vector<std::string>& vec)
{
	std::string str = "";
	for (auto it = vec.rbegin(); it != vec.rend(); ++it)
	{
		str += *it;
	}
	return str;
}


// ctor, dtor, operators
parametricPlotter::parametricPlotter(const parametricEquation& PE) :
	pEquation(new parametricEquation(PE)),
	X(new dimension),
	Y(new dimension),
	t(new parameter),
	s(new parameter)
{

}

parametricPlotter::~parametricPlotter()
{
	prepare_for_deletion();
}

parametricPlotter::parametricPlotter(const parametricPlotter& rhs) :
		X(new dimension(*rhs.X)),
		Y(new dimension(*rhs.Y)),
		t(new parameter(*rhs.t)),
		s(new parameter(*rhs.s))
{
		pEquation = new parametricEquation(*(rhs.pEquation));
		formatted_string = std::string(rhs.formatted_string);
		samples = rhs.samples;
}

const parametricPlotter& parametricPlotter::operator=(const parametricPlotter& rhs)
{
	if (this == &rhs)
	{
		// don't copy self into self
	}
	else
	{
		prepare_for_deletion();
		pEquation = new parametricEquation(*(rhs.pEquation));
		formatted_string = std::string(rhs.formatted_string);
		samples = rhs.samples;
		X = new dimension(*rhs.X);
		Y = new dimension(*rhs.Y);
		t = new parameter(*rhs.t);
		s = new parameter(*rhs.s);
	}
	return *this;
}



// interface
void parametricPlotter::set_t_param(double end, double start = 0)
{
	t->end = end;
	t->start = start;
	t->span = end - start;
	t->is_set = true;
}
void parametricPlotter::set_s_param(double end, double start = 0)
{

	s->end = end;
	s->start = start;
	s->span = end - start;
	s->is_set = true;
}

void parametricPlotter::compute_plot() 
{
	parametricPlotter::clear_outputs();
	parametricPlotter::calculate_solutions(*X, *(pEquation->x_of), *t);
	parametricPlotter::calculate_solutions(*Y, *(pEquation->y_of), *t);
	parametricPlotter::map_solutions(*X, *Y, *t);
	parametricPlotter::convert_to_int(*X);
	parametricPlotter::convert_to_int(*Y);
	strvec = parametricPlotter::string_vectorize(*X, *Y);
	formatted_string = parametricPlotter::flatten_string_vector(strvec);
}
std::string parametricPlotter::get_output() const
{
	return formatted_string;
}

const std::vector<std::string>& parametricPlotter::get_frames() const
{
	return str_frames;
}
