#pragma once
#include "Effect.h"

class EffectPlay : public IGameObject
{
public:
	EffectPlay();
	~EffectPlay();

	bool Start();
	void Update();

	void SetAnimation(std::wstring Animetion) {
		animation = Animetion;
	}
	void SetPosition(CVector3 Position) {
		position = Position;
	}
	void SetScale(CVector3 Scale) {
		scale = Scale;
	}
private:
	std::wstring animation;
	CVector3 scale;
	CVector3 position;
	Effect* effect;

};
