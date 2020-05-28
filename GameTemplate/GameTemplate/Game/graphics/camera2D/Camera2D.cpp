#include "stdafx.h"
#include "Camera2D.h"

Camera2D g_camera2D;	//2D�J����

Camera2D::Camera2D()
{
}


Camera2D::~Camera2D()
{
}

void Camera2D::Update()
{
	/// <summary>
	/// ���s���e�s��
	/// </summary>
	m_projMatrix.MakeOrthoProjectionMatrix(
		m_viewVolumeWidth,		//�r���[�{�����[���̕��B
		m_viewVolumeHeight,		//�r���[�{�����[���̍���
		m_near,
		m_far
	);
	//�r���[�s����v�Z
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);

}