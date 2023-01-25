#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include <string>
#include "parametricPlotter.h"
using namespace std;

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