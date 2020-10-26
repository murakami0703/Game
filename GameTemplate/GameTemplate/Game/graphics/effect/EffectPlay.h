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
	/// ��]�̐ݒ�B
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}

private:
	std::wstring animation;
	CVector3 m_position = CVector3().Zero();			//!<���W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//!<��]�B
	CVector3 m_scale = CVector3().One();				//!<�g�嗦�B
	Effect* effect;
};
