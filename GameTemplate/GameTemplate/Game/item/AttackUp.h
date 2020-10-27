#pragma once
#include "item/ItemBase.h"
/// <summary>
/// 攻撃力アップ。
/// </summary>
class AttackUp : public ItemBase
{
public:
	AttackUp();
	~AttackUp();

	bool Start() override;

	void InUse() override;		//使用中。
	void EndUse() override;		//終わり。

private:
	void Flashing();			//点滅。
private:
	SpriteRender* m_frameSprite;
	SpriteRender* m_itemiconSprite;

	int m_timer = 0;				//アイテム使用中のタイマー。
	float m_flashingTimer = 0;		//点滅用タイマー。

};

