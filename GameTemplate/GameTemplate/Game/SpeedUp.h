#pragma once
#include "ItemBase.h"
/// <summary>
/// �ړ����x�A�b�v�B
/// </summary>
class SpeedUp : public ItemBase
{
public:
	SpeedUp();
	~SpeedUp();

	bool Start() override;
	
	void InUse() override;		//�g�p���B
	void Flashing() override;	//�_�ŁB
	void EndUse() override;		//�I���B

private:
	SpriteRender* m_frameSprite;
	SpriteRender* m_itemSprite;

	float m_flashingTimer = 0;		//���C�g�p�^�C�}�[�B
};

