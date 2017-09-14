#include "stdafx.h"
#include "Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	Engine* pEngine;
	bool result;

	// ����Engine����
	pEngine = new Engine();
	if (!pEngine) {
		return 0;
	}

	//��ʼ��������Engine����
	result = pEngine->Initialize();
	if (result) {
		pEngine->Run();
	}

	return 0;
}
