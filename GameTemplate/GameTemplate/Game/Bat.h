#pragma once
class Bat : public IGameObject
{
public:
	Bat();
	~Bat();
	/// <summary>
	/// �������U��
	/// </summary>
	void Update();
	void Render();
	void PostRender();

private:
	// ���
	enum EState {
		eState_Loitering,	//�p�j�B
		eState_Follow,		//�v���C���[��ǐՁB
		eState_Premove,		//�\������B
		eState_Attack,		//�U���B
		eState_Return,	//�p�j�ʒu�ɖ߂�B
		eState_Dead	//���B
	};

private:

	void Loitering();	//�p�j�B
	void Follow();		//�v���C���[��ǐՁB
	void Premove();		//�\������B
	void Attack();		//�U���B
	void Return();		//�p�j�ʒu�ɖ߂�B
	void Dead();		//���B

private:

	SkinModelRender* m_enemyModelRender;				//�X�L�����f�������_�[�B
	CVector3 m_position = CVector3().Zero();			//���W�B
	CVector3 m_oldPos = CVector3().Zero();				//�������W�B
	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B
	CVector3 m_scale = CVector3().One();				//�g�嗦�B

	EState m_state = eState_Loitering;					//��ԁB

};

