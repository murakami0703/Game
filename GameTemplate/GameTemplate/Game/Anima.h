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

	SkinModelRender* m_animaModelRender;				//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();			//���W�B
	const CVector3 m_soulScale = { 5.0f,5.0f,5.0f };	//���̊g�嗦�B

	EState m_state = Anima_Appear;//��ԁB
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B

	int m_timer = 0;		//�^�C�}�[
	const float m_destroyTimer = 600.0f;	//���ł���܂ł̎��ԁB
	const float m_GroundYPos = 430.0f;		//�n�ʂ̍��W�B
	const float m_toPlayerPos = 50.0f;		//�n�ʂ̍��W�B
	const float m_moveSpeed = 5.0f;			//���~���x�B


};

