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
	static Title* m_instance;

	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* r;

};

