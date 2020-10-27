#pragma once
#include "item/ItemBase.h"
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
	void Flashing();			//�_�ŁB
private:
	SpriteRender* m_frameSprite;
	SpriteRender* m_itemiconSprite;

	int m_timer = 0;				//�A�C�e���g�p���̃^�C�}�[�B
	float m_flashingTimer = 0;		//�_�ŗp�^�C�}�[�B

};

