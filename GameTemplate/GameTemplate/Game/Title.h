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

	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_titleSprite;

	//ライトの点滅
	float m_flashingTimer = 0;
	const float m_lightsUpTime = 0;
	const float m_lightsOffTime = 0;
	const float 
	//星屑の動き
};

