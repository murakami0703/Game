#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	void Update();

private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_itemSprite;


};

