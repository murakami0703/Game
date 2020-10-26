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

	bool Start();
	void Update();

	/// <summary>
	/// ���W����ݒ�B
	/// </summary>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
private:
	//��ԁB
	enum EState {
		Anima_Appear,	//�o�����B
		Anima_Get,		//�l���B
		Anima_Destroy	//���ŁB
	};
	//�A�j���[�V�����B
	enum EAnimationClip {
		eAnimation_Move,
		eAnimation_Num
	};

private:
	void Appear();		//�o�����B
	void Get();			//�l��������I�I
	void Destroy();		//���ŁB


	SkinModelRender* m_animaModelRender;			//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();		//���W�B

	EState m_state = Anima_Appear;					//��ԁB
	AnimationClip  m_animClips[eAnimation_Num];		//�A�j���[�V�����N���b�v�B

	int m_timer = 0;		//�^�C�}�[

};

