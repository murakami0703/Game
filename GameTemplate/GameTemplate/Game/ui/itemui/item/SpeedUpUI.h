#pragma once
#include "ui/itemui/ItemUIBase.h"
#include "item/SpeedUp.h"

/// <summary>
/// 攻撃力アップUIクラス
/// </summary>
/// <remarks>
/// このクラスはTemplateMethodパターンのConcreteClass役です。
/// </remarks>
class SpeedUpUI : public ItemUIBase
{
private:
	void NowItemSelect() override;			//選択中のアイテム。
	void FirstItemSelect() override;		//次1のアイテム。
	void SecondItemSelect() override;		//次2のアイテム。
	void ThirdItemSelect() override;		//次3のアイテム。

	void UseItem(FontRender* itemContRender) override;		//アイテム使用中。
	void OnNowItem(FontRender* itemContRender) override;	//現在のアイテムになったときに呼ばれる処理。
	void ItemUseEnd() override;								//アイテム使用後。

public:
	SpeedUpUI();
	~SpeedUpUI();

	bool Start() override;

private:
	SpeedUp* speedUp;
};

