#include "stdafx.h"
#include "Engine.h"


Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Init()
{
	//サウンドエンジンを初期化。
	m_soundEngine.Init();
}
