#pragma once
class Bum : public IGameObject
{
public:
	Bum();
	~Bum();

	bool Start();
	void Update();

	enum eState {
		In_Use,
		End_Use
	};

private:
	SkinModelRender* m_bumModelRender;				//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();		//���W�B

	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_Sprite;

};

