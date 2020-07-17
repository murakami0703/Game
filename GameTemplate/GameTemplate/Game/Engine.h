#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

extern GraphicsEngine* g_graphicsEngine;	//�O���t�B�b�N�X�G���W���B
extern HWND			g_hWnd;				//�E�B���h�E�n���h���B

class Engine
{
public:
	Engine();
	~Engine();

	void Init();	//�������B

	//�Q�[���̏������B
	void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
	//�E�B���h�E���b�Z�[�W���f�B�X�p�b�`�Bfalse���Ԃ��Ă�����A�Q�[���I���B
	bool DispatchWindowMessage();

	/// <summary>
	/// �C���X�^���X���擾�B
	/// </summary>
	static Engine& GetInstance()
	{
		static Engine* instance = nullptr;
		if (instance == nullptr) {
			instance = new Engine;
		}
		return *instance;
	}

	/// <summary>
	/// Engine�̃C���X�^���X���擾
	/// </summary>
	/// <returns></returns>
	static inline Engine& EngineInstance()
	{
		return Engine::GetInstance();
	}

	/// <summary>
	///SoundEngine���擾�B
	/// </summary>
	CSoundEngine& GetSoundEngine()
	{
		return m_soundEngine;
	}
private:
	CSoundEngine			m_soundEngine;				//�T�E���h�G���W���B

};


