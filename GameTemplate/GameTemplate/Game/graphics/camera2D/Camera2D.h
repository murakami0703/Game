#pragma once
/// <summary>
/// 2Dカメラ
/// </summary>
class Camera2D
{
public:
	Camera2D();
	~Camera2D();
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// カメラ行列を取得。
	/// </summary>
	CMatrix GetViewMatrix()
	{
		return m_viewMatrix;
	}
	/// <summary>
	/// プロジェクション行列を取得。
	/// </summary>
	CMatrix GetProjectionMatrix()
	{
		return m_projMatrix;
	}
	/// <summary>
	/// 視点を取得。
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// 注視点を取得。
	/// </summary>
	CVector3 GetTarget()
	{
		return m_target;
	}

	/// <summary>
	/// カメラの上方向を取得。
	/// </summary>
	CVector3 GetUp()
	{
		return m_up;
	}

	/// <summary>
	/// 視点を設定。
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// 注視点を設定。
	/// </summary>
	void SetTarget(CVector3 target)
	{
		m_target = target;
	}

	/// <summary>
	/// カメラの上方向を設定。
	/// </summary>
	void SetUp(CVector3 up)
	{
		m_up = up;
	}

	/// <summary>
	/// 遠平面を設定。
	/// </summary>
	void SetFar(float f)
	{
		m_far = f;
	}

	/// <summary>
	/// 近平面を設定。
	/// </summary>
	void SetNear(float n)
	{
		m_near = n;
	}

	/// <summary>
	/// 画角を設定。
	/// </summary>
	void SetViewAngle(float angle)
	{
		m_viewAngle = angle;
	}

	/// <summary>
	/// ビューボリュームの幅を設定。
	/// </summary>
	void SetViewVolumeWidth(float w)
	{
		m_viewVolumeWidth = w;
	}

	/// <summary>
	/// ビューボリュームの高さを設定。
	/// </summary>
	void SetViewVolumeHeight(float h)
	{
		m_viewVolumeHeight = h;
	}

	/// <summary>
	/// ビューボリュームの幅を取得。
	/// </summary>
	float SetViewVolumeWidth()
	{
		return m_viewVolumeWidth;
	}

	/// <summary>
	/// ビューボリュームの高さを取得。
	/// </summary>
	float GetViewVolumeHeight()
	{
		return m_viewVolumeHeight;
	}

private:
	CMatrix	m_viewMatrix = CMatrix::Identity();		//ビュー行列。
	CMatrix m_projMatrix = CMatrix::Identity();		//プロジェクション行列。
	CVector3 m_target = CVector3::Zero();			//注視点。
	CVector3 m_position = CVector3::Zero();			//視点。
	CVector3 m_up = CVector3::Up();					//上方向。
	float m_viewAngle = CMath::DegToRad(60.0f);		//画角。
	float m_far = 10000.0f;							//遠い平面までの距離。
	float m_near = 1.0f;							//近平面までの距離。
	float m_viewVolumeWidth = 500;					//ビューボリュームの幅。
	float m_viewVolumeHeight = 500;					//ビューボリュームの高さ。

};

