#pragma once
#include "ItemUIBase.h"

class SpeedUpUI : public ItemUIBase
{
public:
	SpeedUpUI();
	~SpeedUpUI();

	bool Start() override;

	void NowItemSelect() override;			//選択中のアイテム。
	void FirstItemSelect() override;		//次1のアイテム。
	void SecondItemSelect() override;		//次2のアイテム。
	void ThirdItemSelect() override;		//次3のアイテム。

	void UseItem(FontRender* itemContRender) override;					//アイテム使用中。
	void OnNowItem(FontRender* itemContRender) override;

private:
};

