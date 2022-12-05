#include <windows.h>
#include <windowsx.h>
#include "Data.h"
#include "Scene2D.h"
#include "Matrix.h"
#include "AffineTransform.h"
#include "Model2D.h"


LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// �������� ������� ���������
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// �������� ���������
{
	// ������ ������������ ����� �������� ��������� - �������� ����: ������� ����������� ������� ����� wc, ����� �������� ���� hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// ��� ������� ���������, ������������ �� ������ �������
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// ������������� ����������, ���������� ����� ������ ���������� ��� ������� ������
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// ���� � ������� ������ �����������
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// ��� �������� ������, ������������ ��� �������� ����������� ����
	RegisterClass(&wc);								// ����������� ������ wc

	HWND hWnd = CreateWindow(						// hWnd - ����������, ���������������� ����; ������� �������� ���� ��������� ���������� hWnd ��������� ���������
		(LPCSTR)"MainWindowClass",					// ��� �������� ������
		(LPCSTR)"Plot2D Viewer",					// ��������� ����
		WS_OVERLAPPEDWINDOW,						// ����� ����
		200, 200, 400, 400,							// ���������� �� ������ ������ �������� ���� ����, ��� ������ � ������
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ������ ������������ ����� �������� ��������� - �������� ���� ��������� ��������� ���������, ������� ������� ��������� � ��������� �� ��������������� �����
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))				// ������� GetMessage �������� �� ������� ��������� � ������� ��� � ��������� msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// ������� DispatchMessage ��������� ������� � ������������� ������ ������� ���������
	}

	return 0;
}

// � �������� ������ ����������� ������ ���� ���������� ���������� - �������� ������ ������ Scene2D
// ��� ���������� �������� �������������� ����������� ��������� � �������, ������������� � ���� ������
Scene2D scene(X0, Y0, px, py, H, W,"vertex","edges",1);

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// ������� ��������� ��������� � ������������ ��� ���������, ������������ ����
{
	switch (msg)
	{
	case WM_PAINT:
	{
		HDC dc = GetDC(hWnd);
		scene.Clear(dc);// ����� �������������� � ������ Camera2D ������, ����������� �� ������� ������� ������� ���� hWnd
		//
		//for (int i = 0; i < 50; i++)
		//{
		//	scene.Plot(dc, Parabola, 0.05*i, 1, i);
		//	scene.Plot_elli(dc, Elli, 2*i, i);// ����� �������������� � ������ Scene2D ������, ����������� �� ��������� ������� ���������
		//	
		//}
		//
		//for (int i = 0; i < 10; i++)
		//{
		//
		//	scene.Plot(dc, Parabola, 0.05 * i, -1, i);		// ����� �������������� � ������ Scene2D ������, ����������� �� ��������� ������� ���������
		//	scene.Plot_elli(dc, Elli, -2*i, -i);
		//}
		

		//scene.Plot_sin(dc, Sinusoid);
		//scene.Plot_param(dc, Butterfly,  false);
		scene.Render(dc);
		
		ReleaseDC(hWnd, dc);
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	case WM_KEYDOWN:
	{
		HDC dc = GetDC(hWnd);
		switch (wParam)
		{
		case VK_LEFT:
		{
			HDC dc = GetDC(hWnd);
			scene.model.Transfer(-0.5, 0);
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		case VK_RIGHT :
		{
			HDC dc = GetDC(hWnd);
			scene.model.Transfer(0.5, 0);
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		case VK_UP :
		{
			HDC dc = GetDC(hWnd);
			scene.model.Transfer(0, 0.5);
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		case VK_DOWN:
		{
			HDC dc = GetDC(hWnd);
			scene.model.Transfer(0, -0.5);
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		case 0x53:
		{
			HDC dc = GetDC(hWnd);
			scene.model.Apply(Scaling(2, 2));
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		case 0x51:
		{
			HDC dc = GetDC(hWnd);
			scene.model.Apply(Scaling(-1, -1));
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		case 0x58:
		{
			HDC dc = GetDC(hWnd);
			scene.model.Apply(Scaling(-1, 1));
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}case 0x59:
		{
			HDC dc = GetDC(hWnd);
			scene.model.Apply(Scaling(1, -1));
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		case 0x4B:
		{
			HDC dc = GetDC(hWnd);
			scene.model.Apply(Rotation(90));
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		case 0x52:
		{
			HDC dc = GetDC(hWnd);
			scene.model.Apply(Rotation(2,2));
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		case 0x49:
		{
			HDC dc = GetDC(hWnd);
			scene.model.Apply(Identity());
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		case 0x54:
		{
			HDC dc = GetDC(hWnd);
			scene.model.Apply(Translation(2, 2));
			scene.Clear(dc);
			scene.Render(dc);
			return 0;
		}
		}
			
		ReleaseDC(hWnd, dc);
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	
		


	case WM_SIZE:
	{
		HDC dc = GetDC(hWnd);
		scene.SetResolution(dc);
		ReleaseDC(hWnd, dc);
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		scene.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		if (scene.IsDragging())
		{
			HDC dc = GetDC(hWnd);
			scene.Drag(dc, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			InvalidateRect(hWnd, nullptr, false);		
		}
		return 0;
	}
	case WM_LBUTTONUP:
	{
		scene.StopDragging();
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		POINT P;
		P.x = GET_X_LPARAM(lParam);
		P.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hWnd, &P);
		if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			scene.Scale(0.75, P.x, P.y);
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			scene.Scale(1.25, P.x, P.y);

		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
	return 0;
}