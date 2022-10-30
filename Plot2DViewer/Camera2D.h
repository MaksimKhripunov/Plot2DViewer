#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double X0, Y0;						// �������� ���������� ������ ������� ������� ���������
	double px, py;						// ������� �������� ������� ������� ���������, ���������� � ��������
	int W, H;							// ���������� ������� ������� ����

	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return ((X - L()) / (R() - L())) * W;
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return ((T() - Y) / (T() - B())) * H;
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return L() + (R() - L()) * (X + 0.5) / W;
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return T() - (T() - B()) * (Y + 0.5) / H;
	}
	double L()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return -(X0 / px);
	}
	double R()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	{
		return (W - X0) / px;
	}
	double T()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return Y0 / py;
	}
	double B()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
	{
		return (Y0 - H) / py;
	}
private:
	bool isDragging;
	double posX, posY;					// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
public:
	Camera2D(double X0, double Y0, double px, double py, double H, double W) : X0(X0), Y0(Y0), px(px), py(py), posX(0), posY(0), H(H), W(W)
	{
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		Rectangle(dc, 0, 0, r.right, r.bottom);
		// ������� ������� ������� ����
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

		// ������ ��������� ���������� ��� ��������� �������� ����
		// � ��� �������� �������� ������� W, H, � ����� ������������� �������� ���������� X0, Y0, px, py ����� �������, ����� ���������� ���������� �������� �� ������������ ����
	}
	//void MoveTo(double X, double Y)
	//{
	//	// ����������� ������������ ������� (posX, posY)
	//	// �������� ��������, ��� �� ��������� � ������� �����������
	//}
	//void LineTo(HDC dc, double X, double Y)
	//{
	//	// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
	//	// �������� ��������, ��� �� ��������� � ������� �����������
	//	// ��� ��������� ����� ����� ���� ������������ WinApi �������
	//	// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
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