#pragma once
#include "stdafx.h"

class GraphicsTools {

public:
	GraphicsTools();
	~GraphicsTools();

public:
	HRESULT Initialize(const HWND& hwnd);
	void Shutdown();

	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	void GetDpi(FLOAT &dpiX, FLOAT &dpiY);

private:
	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
};

/*
�豸������Դ������

ID2D1DrawingStateBlock
ID2D1Factory
ID2D1Geometry ���ɴ˼̳ж����Ľӿ�
ID2D1GeometrySink and ID2D1SimplifiedGeometrySink
ID2D1StrokeStyle
�豸������Դ������

ID2D1Brush ���ɴ˼̳ж����Ľӿ�
ID2D1Layer
ID2D1RenderTarget ���ɴ˼̳ж����Ľӿ�
������Դ
*/