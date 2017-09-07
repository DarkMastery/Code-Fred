#include "stdafx.h"
#include "engine/Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	Engine* pEngine;
	bool result;

	// ����system����
	pEngine = new Engine();
	if (!pEngine) {
		return 0;
	}

	//��ʼ��������system����
	result = pEngine->Initialize();
	if (result) {
		pEngine->Run();
	}

	// �رղ��ͷ�system����
	pEngine->Shutdown();

	delete pEngine;
	pEngine = nullptr;
	return 0;
}