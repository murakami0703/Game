#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

extern GraphicsEngine* g_graphicsEngine;	//グラフィックスエンジン。
extern HWND			g_hWnd;				//ウィンドウハンドル。

class Engine
{
public:
	Engine();
	~Engine();

	void Init();	//初期化。

	//ゲームの初期化。
	void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
	//ウィンドウメッセージをディスパッチ。falseが返ってきたら、ゲーム終了。
	bool DispatchWindowMessage();

	/// <summary>
	/// インスタンスを取得。
	/// </summary>
	static Engine& GetInstance()
	{
		static Engine* instance = nullptr;
		if (instance == nullptr) {
			instance = new Engine;
		}
		return *instance;
	}

	void GameUpdate();	//ゲームの更新
	/// <summary>
	/// Engineのインスタンスを取得
	/// </summary>
	/// <returns></returns>
	static inline Engine& EngineInstance()
	{
		return Engine::GetInstance();
	}

	/// <summary>
	///SoundEngineを取得。
	/// </summary>
	CSoundEngine& GetSoundEngine()
	{
		return m_soundEngine;
	}
private:
	CSoundEngine			m_soundEngine;				//サウンドエンジン。

};



