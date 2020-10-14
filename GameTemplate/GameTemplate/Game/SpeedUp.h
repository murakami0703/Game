#pragma once
#include "ItemBase.h"
class SpeedUp : public ItemBase
{
public:
	SpeedUp();
	~SpeedUp();

	bool Start() override;
	


	void InUse() override;		//�_�ŁB
	void Flashing() override;	//�_�ŁB
	void EndUse() override;		//�_�ŁB

private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_Sprite;
};

