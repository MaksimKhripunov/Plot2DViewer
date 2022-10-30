#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double X0, Y0;						// Экранные координаты начала мировой системы координат
	double px, py;						// Единицы масштаба мировой системы координат, выраженные в пикселях
	int W, H;							// Разрешение рабочей области окна

	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return ((X - L()) / (R() - L())) * W;
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return ((T() - Y) / (T() - B())) * H;
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		return L() + (R() - L()) * (X + 0.5) / W;
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		return T() - (T() - B()) * (Y + 0.5) / H;
	}
	double L()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return -(X0 / px);
	}
	double R()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return (W - X0) / px;
	}
	double T()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return Y0 / py;
	}
	double B()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return (Y0 - H) / py;
	}
private:
	bool isDragging;
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
public:
	Camera2D(double X0, double Y0, double px, double py, double H, double W) : X0(X0), Y0(Y0), px(px), py(py), posX(0), posY(0), H(H), W(W)
	{
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		Rectangle(dc, 0, 0, r.right, r.bottom);
		// Очистка рабочей области окна
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
	
		double _W = (r.right - 1), _H = (r.bottom - 1) , _X0,_Y0,_px,_py;

		/*double _py = double(py * _H / H);
		double _Y0 = double(Y0 * _H / H);
		double _X0 = double(_W / 2) - double(_py * (W - 2 * X0) / (px * 2));
		X0 = _X0;
		W = _W;
		H = _H;
		py = _py;
		px = py;
		Y0 = _Y0;*/

		/*double newL=L(), newR=R(), newB, newT;
		newB = (B() + T()) / 2 - ((R() - L()) / 2) * (H / W);
		newT = (B() + T()) / 2 + ((R() - L()) / 2) * (H / W);*/
		_Y0 = double(((2*Y0-H)/(2*py)) * (_H / H)* px) + double(_H / 2);
		_X0 =X0 * (_W / W);
		//_px = ((_W - _X0) * px) / (W - X0);
		_py = px * (_H / H);

		px = _py;
		py = _py;
		Y0 = _Y0;
		X0 = _X0;
		W = _W;
		H = _H;

		// Данная процедура вызывается при изменении размеров окна
		// В ней задаются значения величин W, H, а также настраиваются значения параметров X0, Y0, px, py таким образом, чтобы обеспечить одинаковые масштабы по координатным осям
	}
	//void MoveTo(double X, double Y)
	//{
	//	// Перемещение графического курсора (posX, posY)
	//	// Обратите внимание, что мы действуем в мировых координатах
	//}
	//void LineTo(HDC dc, double X, double Y)
	//{
	//	// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
	//	// Обратите внимание, что мы действуем в мировых координатах
	//	// При отрисовке линии могут быть использованы WinApi функции
	//	// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)
	//}
	void Axes(HDC dc)
	{
		COLORREF pencol = RGB(255, 0, 0);
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, pencol));
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		MoveToEx(dc, X0, 0, NULL);
		LineTo(dc, X0, r.bottom);
		MoveToEx(dc, 0, Y0, NULL);
		LineTo(dc, r.right, Y0);
		DeleteObject(SelectObject(dc, pen));
		pencol = RGB(0, 0, 0);
		pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, pencol));
		double _X = X0 + px ;
		double _Y = Y0 + py;
		int i = 0;
		while (i < 15)
		{
			Ellipse(dc, r.left+i*10, r.top + i * 10, r.right-i*10, r.bottom - i * 10);
			i += 1;
		}
		/*while (_X < W)
		{
			MoveToEx(dc, _X, 0, NULL);
			LineTo(dc, _X, r.bottom);
			_X += px;
		}
		_X = X0 - px ;
		while (_X > 0)
		{
			MoveToEx(dc, _X, 0, NULL);
			LineTo(dc, _X, r.bottom);
			_X -= px;
		}
		double _Y = Y0 + py ;
		while (_Y < H)
		{
			
			MoveToEx(dc, 0, _Y, NULL);
			LineTo(dc, r.right, _Y);
			_Y += py;
		}
		_Y = Y0 - py ;
		while (_Y > 0)
		{
			MoveToEx(dc, 0, _Y, NULL);
			LineTo(dc, r.right, _Y);
			_Y -= py;
		}*/
		DeleteObject(SelectObject(dc, pen));
	}
	void Drag(HDC dc, int X, int Y)
	{
		X0 = posX;
		Y0 = posY;
		posX = X;
		posY = Y;
	}
	void StartDragging(int X, int Y)
	{
		isDragging = true;
		posX = X;
		posY = Y;
	}
	void StopDragging()
	{
		isDragging = false;
	}
	bool IsDragging()
	{
		return isDragging;
	}
	
	void Scale( double k, int X, int Y)
	{
		/*double newL, newR, newB, newT;
		newL = X - ((X - L()) / k);
		newR = X + ((R()-X) / k);
		newB = Y - ((Y - B()) / k);
		newT = Y + ((T() - Y) / k);
		px = W / (k * newR - k * newL);
		X0 = -px * (k * newL - (k - 1) * X);
		py = -H / (k * newB - k * newT);
		Y0 = py * (k * newT - (k - 1) * Y);*/

		X0 = X - (X - X0) * k;
		Y0 = Y - (Y - Y0) * k;
		px *= k;
		py *= k;
	}
};

#endif CAMERA_2D_H