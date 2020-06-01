#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();

	static Title* GetInstance()
	{
		return m_instance;
	}
private:
	void LightFlashing();


private:
	static Title* m_instance;

	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_titleSprite;

	//���C�g�̓_��
	float m_flashingTimer = 0;
	const float m_lightsUpTime = 0;
	const float m_lightsOffTime = 0;
	const float 
	//�����̓���
};

