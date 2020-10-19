#pragma once
#include "ItemBase.h"
/// <summary>
/// �U���̓A�b�v�B
/// </summary>
class AttackUp : public ItemBase
{
public:
	AttackUp();
	~AttackUp();

	bool Start() override;

	void InUse() override;		//�g�p���B
	void EndUse() override;		//�I���B
private:
	SpriteRender* m_frameSprite;
	SpriteRender* m_itemSprite;
};

