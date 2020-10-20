#pragma once
#include "ItemUIBase.h"

class AttackUpUI : public ItemUIBase
{
public:
	AttackUpUI();
	~AttackUpUI();
	bool Start() override;

	void NowItemSelect() override;			//�I�𒆂̃A�C�e���B
	void FirstItemSelect() override;		//��1�̃A�C�e���B
	void SecondItemSelect() override;		//��2�̃A�C�e���B
	void ThirdItemSelect() override;		//��3�̃A�C�e���B
	void UseItem(FontRender* itemContRender) override;					//�A�C�e���g�p���B
	void OnNowItem(FontRender* itemContRender) override;

};

