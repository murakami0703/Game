#pragma once
/// <summary>
/// 2D�J����
/// </summary>
class Camera2D
{
public:
	Camera2D();
	~Camera2D();
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �J�����s����擾�B
	/// </summary>
	CMatrix GetViewMatrix()
	{
		return m_viewMatrix;
	}
	/// <summary>
	/// �v���W�F�N�V�����s����擾�B
	/// </summary>
	CMatrix GetProjectionMatrix()
	{
		return m_projMatrix;
	}
	/// <summary>
	/// ���_���擾�B
	/// </summary>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// �����_���擾�B
	/// </summary>
	CVector3 GetTarget()
	{
		return m_target;
	}

	/// <summary>
	/// �J�����̏�������擾�B
	/// </summary>
	CVector3 GetUp()
	{
		return m_up;
	}

	/// <summary>
	/// ���_��ݒ�B
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �����_��ݒ�B
	/// </summary>
	void SetTarget(CVector3 target)
	{
		m_target = target;
	}

	/// <summary>
	/// �J�����̏������ݒ�B
	/// </summary>
	void SetUp(CVector3 up)
	{
		m_up = up;
	}

	/// <summary>
	/// �����ʂ�ݒ�B
	/// </summary>
	void SetFar(float f)
	{
		m_far = f;
	}

	/// <summary>
	/// �ߕ��ʂ�ݒ�B
	/// </summary>
	void SetNear(float n)
	{
		m_near = n;
	}

	/// <summary>
	/// ��p��ݒ�B
	/// </summary>
	void SetViewAngle(float angle)
	{
		m_viewAngle = angle;
	}

	/// <summary>
	/// �r���[�{�����[���̕���ݒ�B
	/// </summary>
	void SetViewVolumeWidth(float w)
	{
		m_viewVolumeWidth = w;
	}

	/// <summary>
	/// �r���[�{�����[���̍�����ݒ�B
	/// </summary>
	void SetViewVolumeHeight(float h)
	{
		m_viewVolumeHeight = h;
	}

	/// <summary>
	/// �r���[�{�����[���̕����擾�B
	/// </summary>
	float SetViewVolumeWidth()
	{
		return m_viewVolumeWidth;
	}

	/// <summary>
	/// �r���[�{�����[���̍������擾�B
	/// </summary>
	float GetViewVolumeHeight()
	{
		return m_viewVolumeHeight;
	}

private:
	CMatrix	m_viewMatrix = CMatrix::Identity();		//�r���[�s��B
	CMatrix m_projMatrix = CMatrix::Identity();		//�v���W�F�N�V�����s��B
	CVector3 m_target = CVector3::Zero();			//�����_�B
	CVector3 m_position = CVector3::Zero();			//���_�B
	CVector3 m_up = CVector3::Up();					//������B
	float m_viewAngle = CMath::DegToRad(60.0f);		//��p�B
	float m_far = 10000.0f;							//�������ʂ܂ł̋����B
	float m_near = 1.0f;							//�ߕ��ʂ܂ł̋����B
	float m_viewVolumeWidth = 500;					//�r���[�{�����[���̕��B
	float m_viewVolumeHeight = 500;					//�r���[�{�����[���̍����B

};

