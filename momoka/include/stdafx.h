// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

#include <d2d1.h>
#include <d2d1helper.h>
#include <dinput.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "dinput8.lib") 
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib,"dxguid.lib")
  

template <class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease
) {
	if (*ppInterfaceToRelease != NULL) {
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

template <class Interface>
inline void SafeUnacquire(
	Interface** ppInterfaceToRelease
) {
	if (*ppInterfaceToRelease != NULL) {
		(*ppInterfaceToRelease)->Unacquire();

		(*ppInterfaceToRelease) = NULL;
	}
}



#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
