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

	void InUse();		//点滅。
	void Flashing();	//点滅。
	void EndUse();		//点滅。

private:

	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_Sprite;
	eState m_state = In_Use;
};

