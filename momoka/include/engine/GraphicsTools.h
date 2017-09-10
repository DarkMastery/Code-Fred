#pragma once
#include "stdafx.h"

class GraphicsTools {

public:
	explicit GraphicsTools(HWND& hwnd);
	~GraphicsTools();

public:
	HRESULT Initialize();
	void Shutdown();

	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();
	void GetDpi(FLOAT &dpiX, FLOAT &dpiY) const;
	HRESULT DrawDemo(WCHAR* fpsStr, FLOAT posX, FLOAT posY);

	void OnResize(UINT width, UINT height) const;

private:
	const HWND& m_hwnd_;  // ͨ�����ð�engine�е�m_hwnd_
	ID2D1Factory* m_pDirect2DFactory_;
	IDWriteFactory* m_pDWriteFactory_;

	ID2D1HwndRenderTarget* m_pRenderTarget_;

	ID2D1SolidColorBrush* m_pLightSlateGrayBrush_;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush_;

	IDWriteTextFormat* m_pITextFormat_;
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