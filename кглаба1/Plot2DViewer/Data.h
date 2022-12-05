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

double Parabola(double x, double a, double c)
{
	return a*x * x + c;
}

double Sinusoid(double x)
{
	return sin(x);
}
pair <double, double> Butterfly(double t)
{
	pair <double, double> res;
	res.first = sin(t)*(pow(M_E,cos(t))-2*cos(4*t)+pow(sin(1/12 * t),5));
	res.second = cos(t) * (pow(M_E, cos(t)) - 2 * cos(4 * t) + pow(sin(1 / 12 * t), 5));
	return res;

}
pair <double, double> Elli(double t, double a, double b)
{
	pair <double, double> res;
	res.first = a * cos(t);
	res.second = b* sin(t) ;
	return res;

}



