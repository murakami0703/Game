#pragma once
class PlayerHP
{
public:
	PlayerHP();
	~PlayerHP();
	//更新
	void Update();
	//描画
	void Draw();

	/// <summary>
	/// 座標を設定。
	/// </summary>
	void PlayerHP::SetHPPosition(CVector3 pos)
	{
		m_hpHFPos = pos;
		m_hpHPos = pos;
	}
	/// <summary>
	/// 拡大率を設定。
	/// </summary>
	void PlayerHP::SetHPScale(CVector3 scale)
	{
		m_hpHFScale = scale;
		m_hpScale = scale;
	}

private:
	//HP関連
	Sprite m_hpHartFrame;		//HPの枠1
	Sprite m_hpHart;		//HP1

	CVector3 m_hpHFPos = CVector3().Zero();			//HPの枠の座標
	CVector3 m_hpHPos = CVector3().Zero();			//HPの座標

	CVector3 m_hpHFScale = CVector3().Zero();			//HPの枠の座標
	CVector3 m_hpScale = CVector3().Zero();			//HPの座標

};

