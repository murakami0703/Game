#pragma once
#include "Player.h"

class Anima
{
	/// <summary>
	/// ���B
	/// �G�l�~�����񂾂Ƃ��ɐ����B
	/// </summary>
public:
	Anima();
	~Anima();
	enum AniAnimation {
		Anima_Move,
		Anima_Num
	};

	enum EState {
		Anima_Appear,
		Anima_Get,
		Anima_Destroy
	};

	void Update(Player* player);
	void Draw(EnRenderMode renderMode);

	/// <summary>
	/// ���W����ݒ�B
	/// </summary>
	void Anima::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

private:
	void Appear(Player* player);		//�o�����B
	void Get();			//�擾������I�I
	void Destroy();		//���Ԍo�߂̂��ߏ��ŁB

	SkinModel m_animaModel;		//�X�L�����f��
	CVector3 m_position = CVector3().Zero();			//���W
	CQuaternion m_rotation = CQuaternion().Identity();	//��]
	CVector3 m_scale = CVector3().One();			//�g�嗦

	EState m_state = Anima_Appear;//���

	int m_timer = 0;		//�^�C�}�[
	const float m_destroyTimer = 600.0f;	//���ł���܂ł̎���

	//Animation�֘A
	AniAnimation m_anime = Anima_Move;		//�A�j���[�V�������
	Animation	m_animation;					//�A�j���[�V����
	AnimationClip m_animClips[Anima_Num];	//�A�j���[�V�����N���b�v


};

