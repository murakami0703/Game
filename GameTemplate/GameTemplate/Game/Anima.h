#pragma once

class Anima : public IGameObject
{
	/// <summary>
	/// ���B
	/// �G�l�~�����񂾂Ƃ��ɐ����B
	/// </summary>
public:
	Anima();
	~Anima();
	enum AniAnimation {
		eAnimation_Move,
		eAnimation_Num
	};

	enum EState {
		Anima_Appear,
		Anima_Get,
		Anima_Destroy
	};

	bool Start();
	void Update();

	/// <summary>
	/// ���W����ݒ�B
	/// </summary>
	void Anima::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

private:
	void Appear();		//�o�����B
	void Get();			//�擾������I�I
	void Destroy();		//���Ԍo�߂̂��ߏ��ŁB

	SkinModelRender* m_animaModelRender;		//�X�L�����f��
	CVector3 m_position = CVector3().Zero();			//���W
	CQuaternion m_rotation = CQuaternion().Identity();	//��]
	CVector3 m_scale = CVector3().One();			//�g�嗦

	EState m_state = Anima_Appear;//���
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B


	const CVector3 m_soulScale = { 3.0f,3.0f,3.0f };			//���̑傫��
	int m_timer = 0;		//�^�C�}�[
	const float m_destroyTimer = 600.0f;	//���ł���܂ł̎���



};

