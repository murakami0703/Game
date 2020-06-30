#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。

void Camera::Update()
{
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	//プロジェクション行列を計算。
	m_projMatrix.MakeProjectionMatrix(
		m_viewAngle,					//画角。
		FRAME_BUFFER_W / FRAME_BUFFER_H,	//アスペクト比。
		m_near,
		m_far
	);
	//ビュープロジェクション行列の作成。
	m_viewProjectionMatrix = m_viewMatrix * m_projMatrix;

}
/// <summary>
/// 
/// </summary>
/// <param name="screenPos"></param>
/// <param name="worldPos"></param>
void Camera::CalcScreenPositionFromWorldPosition2(CVector3& screenPos, const CVector3& worldPos)
{
	float half_w = (float)FRAME_BUFFER_W * 0.5f;
	float half_h = (float)FRAME_BUFFER_H * 0.5f;
	CVector4 _screenPos;
	_screenPos.Set(worldPos.x, worldPos.y, worldPos.z, 1.0f);
	m_viewProjectionMatrix.Mul(_screenPos);
	screenPos.x = (_screenPos.x / _screenPos.w)*half_w;
	screenPos.y = (_screenPos.y / _screenPos.w)*half_h;
	screenPos.z = _screenPos.w;
}
