#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

extern GraphicsEngine* g_graphicsEngine;	//グラフィックスエンジン。
extern HWND			g_hWnd;				//ウィンドウハンドル。

class Engine
{
	static Engine* m_instance;
public:
	Engine();
	~Engine();


	void Init();	//初期化。

	//ゲームの初期化。
	void InitGame(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
	//ウィンドウメッセージをディスパッチ。falseが返ってきたら、ゲーム終了。
	bool DispatchWindowMessage();

	void GameUpdate();	//ゲームの更新
	//インスタンスの取得
	static Engine* GetInstance() {
		return m_instance;
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



