#pragma once
class IActor : public IGameObject
{
public:
	IActor();
	~IActor();
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

protected:
	SkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダー。
	CVector3 m_position = CVector3().Zero();			//座標。
	CQuaternion m_rotation = CQuaternion().Identity();	//回転。
	CVector3 m_scale = CVector3().One();				//拡大率。
};

