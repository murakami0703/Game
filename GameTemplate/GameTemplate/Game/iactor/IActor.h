#pragma once
/// <summary>
/// アクタークラス
/// </summary>
/// <remarks>
/// このクラスは多くのゲームキャラクターで必要になるメンバ変数、関数をまとめたクラスです。
/// プレイヤーなどのクラスはこのクラスを継承しています。
/// </remarks>
class IActor : public IGameObject
{
public:
	IActor();
	~IActor();

	/// <summary>
	/// 座標を取得。
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}

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
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// 回転率を設定。
	/// </summary>
	void SetScale(CVector3 sca)
	{
		m_scale = sca;
	}
	/// <summary>
	/// アクターの前方方向と指定されたオブジェクトとの角度を計算します。
	/// </summary>
	/// <param name="angle">角度の格納先</param>
	/// <param name="distance">距離の格納先</param>
	/// <param name="actorForward">アクターの前方方向</param>
	/// <param name="toObject">オブジェクトまでの距離</param>
	void CalcAngleAndLength(float& angle, float& distance, const CVector3& actorForward, const CVector3& toObject);
protected:
	SkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダー。
	CVector3 m_position = CVector3::One();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	CVector3 m_scale = CVector3::One();				//拡大率。
};

