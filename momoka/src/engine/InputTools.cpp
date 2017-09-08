#include "stdafx.h"
#include "engine/InputTools.h"

// TODO: ʹ��DirectInput�������ķ�װ
// �й�DirectInput�ľ������ݿ��Բο������������
// http://blog.csdn.net/poem_qianmo/article/details/8547531

InputTools::InputTools(HWND& hwnd): m_hwnd_(hwnd),
                                    m_pDirectInput_(nullptr),
                                    m_pMouseDevice_(nullptr),
                                    m_pKeyboardDevice_(nullptr) {
}

HRESULT InputTools::Initialize() {
	HRESULT hr = S_OK;
	hr = DirectInput8Create(
		HINST_THISCOMPONENT,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<void**>(&m_pDirectInput_),
		nullptr
	);

	if(SUCCEEDED(hr)) {
		hr = MouseInitialize();
		if(!SUCCEEDED(hr)) {
			return hr;
		}

		hr = KeyboardInitialize();
		if (!SUCCEEDED(hr)) {
			return hr;
		}
	}

	return hr;
}

void InputTools::Shutdown() {
	SafeUnacquire(&m_pMouseDevice_);
	SafeUnacquire(&m_pKeyboardDevice_);

	SafeRelease(&m_pMouseDevice_);
	SafeRelease(&m_pKeyboardDevice_);
	SafeRelease(&m_pDirectInput_);
}

bool InputTools::GetKeyboardMessage(char* keyStateBuffer) const {
	::ZeroMemory(keyStateBuffer, sizeof(keyStateBuffer));
	const bool result = DeviceRead(m_pKeyboardDevice_, static_cast<LPVOID>(keyStateBuffer), sizeof(keyStateBuffer));
	return result;
}

bool InputTools::GetMouseMessage(DIMOUSESTATE mouseState) const {
	::ZeroMemory(&mouseState, sizeof(mouseState));
	const bool result = DeviceRead(m_pMouseDevice_, static_cast<LPVOID>(&mouseState), sizeof(mouseState));
	return result;
}

HRESULT InputTools::KeyboardInitialize() {
	HRESULT hr = S_OK;
	hr = m_pDirectInput_->CreateDevice(GUID_SysKeyboard, &m_pKeyboardDevice_, nullptr);

	if (SUCCEEDED(hr)) {
		m_pMouseDevice_->SetDataFormat(&c_dfDIKeyboard);
		m_pKeyboardDevice_->SetCooperativeLevel(m_hwnd_, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		// TODO: ����һ���費��Ҫ��Acquire������أ�������Ǹ�����Ҳ��
		m_pKeyboardDevice_->Acquire();
	}

	return hr;
}

HRESULT InputTools::MouseInitialize() {
	HRESULT hr = S_OK;
	hr = m_pDirectInput_->CreateDevice(GUID_SysMouse, &m_pMouseDevice_, nullptr);

	if (SUCCEEDED(hr)) {
		m_pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		m_pMouseDevice_->SetCooperativeLevel(m_hwnd_, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

		m_pMouseDevice_->Acquire();
	}

	return hr;
}

HRESULT InputTools::DeviceRead(IDirectInputDevice8* pDIDevice, void* pBuffer, long lSize) {
	HRESULT hr;
	while (true) {
		pDIDevice->Poll(); // ��ѯ�豸  
		pDIDevice->Acquire(); // ��ȡ�豸�Ŀ���Ȩ  
		if (SUCCEEDED(hr = pDIDevice->GetDeviceState(lSize, pBuffer)))
			break;
		if (hr != DIERR_INPUTLOST || hr != DIERR_NOTACQUIRED)
			return E_FAIL;
		if (FAILED(pDIDevice->Acquire()))
			return E_FAIL;
	}
	return S_OK;
}
