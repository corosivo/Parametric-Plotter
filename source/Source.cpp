#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <string>
#include "parametricPlotter.h"
using namespace std;


//void old_version();

fstream file("log.txt", ios::out);

const long double pi =
3.14159265358979323846264338327950288419716939937510;

int main()
{
	double end = 2 * pi;


	parametricEquation* equation = new parametricBug;
	parametricPlotter Plot(*equation);

	Plot.set_t_param(4 * pi, 0);
	Plot.compute_plot();

	// animated graphing test; using modified string_vectorize()
	std::vector<std::string> frames = Plot.get_frames();

	chrono::milliseconds ms(100);
	auto t = chrono::steady_clock::now();
	for (auto it = frames.begin(); it != frames.end(); it+=4)
	{
		system("cls");
		cout << *it;
		while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - t) < ms);
		t = chrono::steady_clock::now();
	}

	return 0;
}

/*
void old_version()
{
	fstream file("log.txt", ios::out);

	const double pi = 3.14;
	double span = 2 * pi;
	int width, height, samples = 400;
	bool debug = false;


	width = 180;
	height = 32;
	// parametric equation of the x coordinate
	auto x = [&](double t, double r = 10)
	{
		return r * (t - sin(t));
	};
	// parametric equation of the y coordinate
	auto y = [&](double t, double r = 10)
	{
		return r * (1 - cos(t));
	};

	//width = 60;
	//height = 30;
	//auto x = [](double t, double r = 10)
	//{
	//	return r * cos(t);
	//};
	//auto y = [](double t, double r = 10)
	//{
	//	return r * sin(t);
	//};

	//width = 60;	// ITS A PRETZEL
	//height = 30;
	//auto x = [](double t, double r = 10)
	//{
	//	return r * pow(cos(2 * t),2);
	//};
	//auto y = [](double t, double r = 10)
	//{
	//	return r * sin(3*t);
	//};

	vector<double> x_coords;
	vector<double> y_coords;
	double x_max = numeric_limits<double>::min(),
		x_min = numeric_limits<double>::max(),
		y_max = numeric_limits<double>::min(),
		y_min = numeric_limits<double>::max();

	// place the solutions of each of the parametric equations into two synchronized vectors
	auto get_solution_vects = [&](vector<double>& x_vec, vector<double>& y_vec)
	{
		for (double i = 0; i < span; i += (span / samples))  // get values in span [0,t) and determine each coordinates minimum and maximum
		{
			x_vec.push_back(x(i));
			if (x_vec.back() > x_max)
				x_max = x_vec.back();
			if (x_vec.back() < x_min)
				x_min = x_vec.back();

			y_vec.push_back(y(i));
			if (y_vec.back() > y_max)
				y_max = y_vec.back();
			if (y_vec.back() < y_min)
				y_min = y_vec.back();
		}



		/// debug file output
		auto debug_ = [&]()
		{
			if (!debug)
				return 0;

			// printed output relooped if necessary
			file << " get_solution_vects debug:\n" << setprecision(3) << fixed;
			int I = 0;
			for (double i = 0; i < span; i += (span / samples), ++I)
				file << "    x(" << setw(6) << i << "): " << setw(7) << x(i) << setw(8) << "y(i): " << y(i) << "\n";
			return 0;
		}();

	};

	get_solution_vects(x_coords, y_coords);


	// map each pair into output range
	auto fit = [&](vector<double>& x_vec, vector<double>& y_vec)
	{
		// ratio of output span : input span
		double x_coef = ((width - 1) - 0) / (x_max - x_min);
		double y_coef = ((height - 1) - 0) / (y_max - y_min);
		auto scale = [&]()
		{
			for (int i = 0; i < x_vec.size(); ++i)
			{
				x_vec[i] = 0 - x_coef * x_min + x_coef * x_vec[i];
				y_vec[i] = 0 - y_coef * y_min + y_coef * y_vec[i];
			}
		};

		/// debug file output
		auto debug_ = [&]()
		{
			if (!debug)
				return 0;

			// printed output relooped if necessary
			file << "\nFit():\n";
			file << "  x_coef: " << x_coef << "\n  y_coef: " << y_coef << "\n";
			for (int i = 0; i < x_vec.size(); ++i)
			{
				file << "    x(" << setw(3) << i << "): " << setw(7) << x_vec[i] << setw(8) << "y(i): " << y_vec[i] << "\n";
			}
			return 0;
		}();

		scale();
		// returns a vector with the origin of the input space mapped to the output space
		vector<double> out({ -x_coef * x_min , -y_coef * y_min });
		return out;

	}(x_coords, y_coords);

	vector<int> origin = {
		static_cast<int>(round(fit[0])),
		static_cast<int>(round(fit[1]))
	};

	// takes a vector of doubles and converts to a vector of ints, clamps
	auto convert_to_int = [&](vector<double>& input, double max, double min = 0)
	{
		vector<int> output(input.size() - 1);

		for (int i = 0; i < output.size(); ++i)
		{
			output[i] = static_cast<int>(round(input[i]));
			if (output.back() > static_cast<int>(round(max)))
				output.back() = static_cast<int>(round(max));
			else if (output.back() < static_cast<int>(round(min)))
				output.back() = static_cast<int>(round(min));
		}

		/// debug file output
		auto debug_ = [&]()
		{
			static char ch = 'x'; //
			if (!debug)
				return 0;

			// printed output relooped if necessary
			file << "\nRounded:\n";
			for (int i = 0; i < output.size(); ++i)
				file << "    " << ch << "(" << setw(3) << i << "): " << setw(7) << output[i] << "\n";
			++ch;
			return 0;
		}();

		return output;

	};

	vector<int> x_processed = convert_to_int(x_coords, width - 1);
	vector<int> y_processed = convert_to_int(y_coords, height - 1);

	// use a vector of strings to create the output array without having to faff with array indexing
	auto vectorized_output = [&](vector<int>& x_proc, vector<int>& y_proc)
	{
		vector<std::string> str(height, string(string((width), ' ') + "\n"));

		str[origin[1]].assign(string(width, '-') + "\n");

		for (int i = 0; i < height; ++i)
			str[i][origin[0]] = '|';

		for (int i = 0; i < x_proc.size(); ++i)
		{
			str[y_proc[i]].at(x_proc[i]) = 'X';
		}


		/// debug file output
		auto debug_ = [&]()
		{
			if (!debug)
				return 0;

			// printed output relooped if necessary
			file << " x_proc len: " << x_proc.size() << '\n';
			file << " y_proc len: " << y_proc.size() << '\n';
			for (auto i = 0; i != str.size(); ++i)
			{
				file << "\n   Size of string[" << i << "] : " << str[i].size() << "\n";
				file << "-->" + str[i] + "<--\n";
			}
			return 0;
		}();


		return str;
	}(x_processed, y_processed);

	// take a vector of strings and cat them in sequence to one huge string to print
	auto flatten_vec = [&](vector<string>& vec)
	{
		string str = "";
		for (auto it = vec.rbegin(); it != vec.rend(); ++it)
		{
			str += *it;
		}
		return str;
	};

	string printable = flatten_vec(vectorized_output);

	file << "\n\n" << printable << "\n\n";

	file.close();
	return;
}
*/