#pragma once
#include "item/ItemBase.h"
/// <summary>
/// �ړ����x�A�b�v�B
/// </summary>
class SpeedUp : public ItemBase
{
public:
	SpeedUp();
	~SpeedUp();

	bool Start() override;
	void Update() override;

	void InUse() override;		//�g�p���B
	void EndUse() override;		//�I���B

private:
	SpriteRender* m_frameSprite;
	SpriteRender* m_itemiconSprite;

	float m_flashingTimer = 0;		//���C�g�p�^�C�}�[�B
};

