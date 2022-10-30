#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
using namespace std;


double					// Исходные значения параметров X0, Y0, px, py
X0 = 100,//200
Y0 = 100,//200
px = 100,	//50
H = 200 - 1,
W=200-1,
py = 100;

double Parabola(double x)
{
	return x * x - 2;
}

double Sinusoid(double x)
{
	return sin(x);
}


