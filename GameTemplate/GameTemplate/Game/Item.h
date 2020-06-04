#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	void Update();

private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_itemSprite;


};

