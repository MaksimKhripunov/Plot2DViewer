#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"
#include "Model2D.h"
#include <vector>
#include <fstream>


class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double , double, double);
	typedef double (*Func_sin)(double);
	typedef pair <double, double>(*Func_param)(double);
	typedef pair <double, double>(*Func_elli)(double,double,double);
	
public:
	Model2D model;
	Scene2D(double X0, double Y0, double px, double py,  double H, double W,string vertex, string edges, double u3) : Camera2D(X0, Y0, px, py,H,W)
	{
		model = *new Model2D(vertex, edges,u3);
	}
	Scene2D(double X0, double Y0, double px, double py, double H, double W) : Camera2D(X0, Y0, px, py, H, W)
	{
		model = *new Model2D();
	}
	void Plot(HDC dc, Func f, double a, double b, double c, bool axes = true)
	{
		if (axes)
			Axes(dc);
		COLORREF pencol = RGB(0, 100, 0);
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, pencol));
		/*int _X = 0;
		double x = ScreenToWorldX(0);
		double y = f(x,a,b,c);
		int _Y = WorldToScreenY(y);
		MoveToEx(dc, _X, _Y, NULL);
		for (int i = 1; i < W; i++)
		{
			_X = i;
			x = ScreenToWorldX(i);
			y = f(x,a,b,c);
			_Y = WorldToScreenY(y);
			LineTo(dc, _X, _Y);
		}*/



		int _Y = 0;
		double y = ScreenToWorldY(0);
		double x = f(y,a,c);
		int _X = WorldToScreenX(b*x);
		MoveToEx(dc, _X, _Y, NULL);
		for (int i = 1; i < W; i++)
		{
			_Y = i;
			y = ScreenToWorldY(i);
			x = f(y,a,c);
			_X = WorldToScreenX(b*x);
			LineTo(dc, _X, _Y);
		}



		DeleteObject(SelectObject(dc, pen));
		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
	}
	void Plot_sin(HDC dc, Func_sin f,  bool axes = true)
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
	void Plot_param(HDC dc, Func_param f, bool axes = true)
	{
		if (axes)
			Axes(dc);

		COLORREF pencol = RGB(255, 0, 0);
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, pencol));
		pair <double, double> point;
		int _X = WorldToScreenX(point.first);
		int _Y = WorldToScreenY(point.second);
		MoveToEx(dc, _X, _Y, NULL);
		for (double i = 0; i <=12*M_PI; i += 0.01)
		{
			point = f(i);
			_X = WorldToScreenX(point.first);
			_Y = WorldToScreenY(point.second);
			LineTo(dc, _X, _Y);
		}
		DeleteObject(SelectObject(dc, pen));
	}
	void Plot_elli(HDC dc, Func_elli f,double a,double b, bool axes = true)
	{
		if (axes)
			Axes(dc);

		COLORREF pencol = RGB(0, 100, 0);
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, pencol));
		pair <double, double> point;
		int _X = WorldToScreenX(point.first);
		int _Y = WorldToScreenY(point.second);
		MoveToEx(dc, _X, _Y, NULL);
		for (double i = 0; i <= 12 * M_PI; i += 0.01)
		{
			point = f(i,a,b);
			_X = WorldToScreenX(point.first);
			_Y = WorldToScreenY(point.second);
			LineTo(dc, _X, _Y);
		}
		DeleteObject(SelectObject(dc, pen));
	}
	void Render(HDC dc, bool axes = true)
	{
		if (axes)
			Axes(dc);
		COLORREF pencol = RGB(0, 0, 255);
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, pencol));
		int _X, _Y;
		//int _X = WorldToScreenX(model.GetVertexX(model.GetEdges()(1,1) - 1));
		//int _Y = WorldToScreenY(model.GetVertexY(model.GetEdges()(1, 1) - 1));
		//MoveToEx(dc, _X, _Y, NULL);
		
		for (int i = 1; i < model.GetEdges().getRows()+1; i++)
		{
			_X = WorldToScreenX(model.GetVertexX(model.GetEdges()(i, 1) - 1));
			_Y = WorldToScreenY(model.GetVertexY(model.GetEdges()(i, 1) - 1));
			MoveToEx(dc, _X, _Y, NULL);
			_X = WorldToScreenX(model.GetVertexX(model.GetEdges()(i, 2)-1));
			_Y = WorldToScreenY(model.GetVertexY(model.GetEdges()(i, 2)-1));
			LineTo(dc, _X, _Y);
		}
		//LineTo(dc, WorldToScreenX(model.GetVertexX(0)), WorldToScreenY(model.GetVertexY(0)));

		DeleteObject(SelectObject(dc, pen));
		
	
	}

	

};

#endif SCENE_2D_H