#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Init();	//�������B

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

extern Engine* g_engine;

