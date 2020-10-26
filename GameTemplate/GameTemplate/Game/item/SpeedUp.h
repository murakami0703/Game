#pragma once
#include "item/ItemBase.h"
/// <summary>
/// 移動速度アップ。
/// </summary>
class SpeedUp : public ItemBase
{
public:
	SpeedUp();
	~SpeedUp();

	bool Start() override;
	void Update() override;

	void InUse() override;		//使用中。
	void EndUse() override;		//終わり。

private:
	SpriteRender* m_frameSprite;
	SpriteRender* m_itemiconSprite;

	float m_flashingTimer = 0;		//ライト用タイマー。
};

