#pragma once
#include "SpriteIActor.h"

/// <summary>
/// ポーズ画面。
/// ゲーム中一時停止したいときに呼ばれる。
/// </summary>
class Pause : public IGameObject
{
public:
	Pause();
	~Pause();

	bool Start() override;
	void Update() override;

private:
	std::vector<SpriteRender*> m_spriteRenderArray;		//スプライトの動的配列

};

