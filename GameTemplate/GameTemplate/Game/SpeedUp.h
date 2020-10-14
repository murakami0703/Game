#pragma once
#include "ItemBase.h"
class SpeedUp : public ItemBase
{
public:
	SpeedUp();
	~SpeedUp();

	bool Start() override;
	


	void InUse() override;		//点滅。
	void Flashing() override;	//点滅。
	void EndUse() override;		//点滅。

private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_Sprite;
};

