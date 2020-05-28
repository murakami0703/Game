#include "stdafx.h"
#include "Camera2D.h"

Camera2D g_camera2D;	//2Dカメラ

Camera2D::Camera2D()
{
}


Camera2D::~Camera2D()
{
}

void Camera2D::Update()
{
	/// <summary>
	/// 平行投影行列
	/// </summary>
	m_projMatrix.MakeOrthoProjectionMatrix(
		m_viewVolumeWidth,		//ビューボリュームの幅。
		m_viewVolumeHeight,		//ビューボリュームの高さ
		m_near,
		m_far
	);
	//ビュー行列を計算
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);

}