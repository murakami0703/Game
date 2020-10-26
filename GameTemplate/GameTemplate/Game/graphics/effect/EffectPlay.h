#pragma once
#include "graphics/effect/Effect.h"

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
		m_position = Position;
	}
	void SetScale(CVector3 Scale) {
		m_scale = Scale;
	}
	/// <summary>
	/// âÒì]ÇÃê›íËÅB
	/// </summary>
	/// <param name="rot">âÒì]</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}

private:
	std::wstring animation;
	CVector3 m_position = CVector3().Zero();			//!<ç¿ïWÅB
	CQuaternion m_rotation = CQuaternion().Identity();	//!<âÒì]ÅB
	CVector3 m_scale = CVector3().One();				//!<ägëÂó¶ÅB
	Effect* effect;
};
