#pragma once
#include "ItemBase.h"
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
	void Flashing() override;	//点滅。
	void EndUse() override;		//終わり。
private:
	SpriteRender* m_frameSprite;
	SpriteRender* m_itemSprite;
};

