#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
public:
	Scene2D(double X0, double Y0, double px, double py,  double H, double W) : Camera2D(X0, Y0, px, py,H,W)
	{
	}
	void Plot(HDC dc, Func f, bool axes = true)
	{
		if (axes)
			Axes(dc);
		COLORREF pencol = RGB(0, 0, 255);
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, pencol));
		int _X = 0;
		double x = ScreenToWorldX(0);
		double y = f(x);
		int _Y = WorldToScreenY(y);
		MoveToEx(dc, _X, _Y, NULL);
		for (int i = 1; i < W; i++)
		{
			_X = i;
			x = ScreenToWorldX(i);
			y = f(x);
			_Y = WorldToScreenY(y);
			LineTo(dc, _X, _Y);
		}
		DeleteObject(SelectObject(dc, pen));
		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
	}
	

};

#endif SCENE_2D_H