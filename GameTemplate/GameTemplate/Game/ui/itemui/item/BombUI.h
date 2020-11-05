#pragma once
#include "ui/itemui/ItemUIBase.h"
#include "item/Bomb.h"

/// <summary>
/// ���eUI�N���X
/// </summary>
/// <remarks>
/// ���̃N���X��TemplateMethod�p�^�[����ConcreteClass���ł��B
/// </remarks>
class BombUI : public ItemUIBase
{
public:
	BombUI();
	~BombUI();
	bool Start() override;

	void NowItemSelect() override;			//�I�𒆂̃A�C�e���B
	void FirstItemSelect() override;		//��1�̃A�C�e���B
	void SecondItemSelect() override;		//��2�̃A�C�e���B
	void ThirdItemSelect() override;		//��3�̃A�C�e���B

	void UseItem(FontRender* itemContRender) override;		//�A�C�e���g�p���B
	void OnNowItem(FontRender* itemContRender) override;	//���݂̃A�C�e���ɂȂ����Ƃ��ɌĂ΂�鏈���B
	void ItemUseEnd();										//�A�C�e���g�p��B

private:
	Bomb* bomb;
};

