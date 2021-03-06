#pragma once
#include "ui/itemui/ItemUIBase.h"
#include "item/HpRecovery.h"


/// <summary>
/// 回復薬UIクラス
/// </summary>
/// <remarks>
/// このクラスはTemplateMethodパターンのConcreteClass役です。
/// </remarks>
class HpRecoveryUI : public ItemUIBase
{
public:
	HpRecoveryUI();
	~HpRecoveryUI();
	bool Start() override;


	void NowItemSelect() override;			//選択中のアイテム。
	void FirstItemSelect() override;		//次1のアイテム。
	void SecondItemSelect() override;		//次2のアイテム。
	void ThirdItemSelect() override;		//次3のアイテム。

	void UseItem(FontRender* itemContRender) override;		//アイテム使用中。
	void OnNowItem(FontRender* itemContRender) override;	//現在のアイテムになったときに呼ばれる処理。
	void ItemUseEnd();										//アイテム使用後。

private:
	HpRecovery* hpRecovery;
};

