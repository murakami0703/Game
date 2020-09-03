#pragma once
class SpeedUp : public IGameObject
{
public:
	SpeedUp();
	~SpeedUp();

	bool Start();
	void Update();

	enum eState {
		In_Use,
		Flashing_Use,
		End_Use
	};

	void InUse();		//�_�ŁB
	void Flashing();	//�_�ŁB
	void EndUse();		//�_�ŁB

	bool SpeedUp::GetItemUseFlag() {
		return m_itemInUseFlag;
	}
private:

	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_Sprite;
	eState m_state = In_Use;		//���
	bool m_itemInUseFlag = false;	//�A�C�e���g�p���t���O
	int m_timer = 0;				//�^�C�}�[�B
	int m_changeCount = 0;			//�_�ŗp�̃J�E���g�B
};

