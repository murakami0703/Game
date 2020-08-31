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

private:

	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_Sprite;
	eState m_state = In_Use;
};

