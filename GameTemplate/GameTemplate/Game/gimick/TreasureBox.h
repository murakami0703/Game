#pragma once
class TreasureBox : public IActor
{
public:
	TreasureBox();
	~TreasureBox();

	bool Start();
	void Update(); //�X�V�B

	
private:
	void Open();
	void Opened();

	enum eState {
		eState_Idle,
		eState_Open,
		eState_Opened,
	};
	enum EAnimationClip {
		eAnimation_Close,
		eAnimation_Open,
		eAnimation_Num
	};
private:
	SkinModelRender* m_BoxModelRender;				//�󔠃X�L�����f�������_�[�B
	SkinModelRender* m_ItemModelRender;				//�A�C�e���X�L�����f�������_�[�B

	
	CVector3 m_fowardVector = CVector3().Zero();		//�󔠂̑O�x�N�g���B

	eState m_state = eState_Idle;
	AnimationClip  m_animClips[eAnimation_Num];			//�A�j���[�V�����N���b�v�B

	//�J���֘A
	CVector3 m_toPlayerVec = CVector3().Zero();			//�v���[���[�Ɣ��̃x�N�g���B
	const float m_openYVec = 200.0f;						//�J���p�����B
	const int m_randNum[4] = { 0,1,2,3 };				//�J���p�����B
	int m_rand = 0;										//�����_�����̊i�[�B

};

