#pragma once
class TreasureBox : public IGameObject
{
public:
	TreasureBox();
	~TreasureBox();

	bool Start();
	void Update(); //更新。

	/// <summary>
	/// 座標を設定。
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転率を設定。
	/// </summary>
	void TreasureBox::SetScale(CVector3 sca)
	{
		m_scale = sca;
	}
private:
	void Open();
	void Opened();

	enum eState {
		eState_Idle,
		eState_Open,
		eState_Opened,
	};
	enum EAnimationClip {
		eAnimation_Close,
		eAnimation_Open,
		eAnimation_Num
	};
private:
	SkinModelRender* m_BoxModelRender;				//宝箱スキンモデルレンダー。
	SkinModelRender* m_ItemModelRender;				//アイテムスキンモデルレンダー。

	CVector3 m_position = CVector3().Zero();			//座標。
	CVector3 m_fowardVector = CVector3().Zero();		//宝箱の前ベクトル。
	CQuaternion m_rotation = CQuaternion().Identity();	//回転。
	CVector3 m_scale = CVector3().One();				//拡大率。

	eState m_state = eState_Idle;
	AnimationClip  m_animClips[eAnimation_Num];			//アニメーションクリップ。

	//開封関連
	CVector3 m_toPlayerVec = CVector3().Zero();			//プレーヤーと箱のベクトル。
	const float m_openYVec = 200.0f;						//開封用距離。
	const int m_randNum[4] = { 0,1,2,3 };				//開封用距離。
	int m_rand = 0;										//ランダム数の格納。

};

