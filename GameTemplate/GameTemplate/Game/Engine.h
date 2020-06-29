#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Init();	//初期化。

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

extern Engine* g_engine;

