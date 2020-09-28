#pragma once
class AttackUp : public IGameObject
{
public:
	AttackUp();
	~AttackUp();

	bool Start();
	void Update();

	enum eState {
		In_Use,
		End_Use
	};

private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_Sprite;

};

