#pragma once

class EffectPlay : public IGameObject
{
public:
	EffectPlay();
	~EffectPlay();

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

	void SetTuibiFlag(bool flag) {
		P_TuibiFlag = flag;
	}

	void SetRotFlag(bool flag) {
		P_RotationFlag = flag;
	}
	void SetPostRenderFlag()
	{
		m_isPost = true;
	}
private:
	std::wstring animation;
	CVector3 scale;
	CVector3 position;
	bool m_isPost = false;
	Effect* effect;

	bool P_TuibiFlag = false;
	bool P_RotationFlag = false;

};
