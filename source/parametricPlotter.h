#ifndef PARAMETRICPLOTTER_H
#define PARAMETRICPLOTTER_H

#include <iosfwd>
#include <string>
#include <vector>
#include "parametricEquation.h"
#include "../equation_collection/equation_collection.h"

class sub_equation;  // fwd decl
class parametricEquation;  // fwd decl
struct parameter;  // fwd decl

template <class T>
struct dim_type;  // fwd decl
struct dimension;  // fwd decl

/// <summary>
/// Takes an instance of a class with base type = parametricEquation.
/// takes information on how to plot said equation( parameter start,stop,etc).
/// Processes the data therein into a string that can be printed to a stream
/// that contains a formatted plot of the parametric equation.
/// </summary>
class parametricPlotter
{

private:
	parametricEquation * pEquation;
	std::vector<std::string> strvec;
	std::vector<std::string> str_frames;
	std::string formatted_string;
	int samples = 400;
	
	parameter * t;
	parameter * s;

	dimension * X;
	dimension * Y;	

	//controls
	void prepare_for_deletion();  // in impl: should delete pEquation and assign to nullptr if not nullptr
	void clear_outputs();
	void reset_dims();

	// processing
	void calculate_solutions(dimension& dim, sub_equation& f_of,parameter& par); 
	void map_solutions(dimension& dim, dimension& dim2, parameter& par);
	void convert_to_int(dimension& dim);
	// formatting
	std::vector<std::string> string_vectorize(dimension& xdim, dimension& ydim);
	std::string flatten_string_vector(std::vector<std::string>& strvec);

public:
	parametricPlotter() = delete; // explicitly deleted
	parametricPlotter(const parametricEquation& PE);					// take existing parametricEquation and copy it to a new internal ptr

	~parametricPlotter();

	parametricPlotter(const parametricPlotter& rhs);					// copy ctor
	const parametricPlotter& operator=(const parametricPlotter& rhs);	// copy operator=


	void set_t_param(double end, double start);
	void set_s_param(double end, double start);

	void compute_plot();
	std::string get_output() const;
	const std::vector<std::string>& get_frames() const;

};
#endif