#pragma once
class HpRecovery : public IGameObject
{
public:
	HpRecovery();
	~HpRecovery();

	bool Start();
	void Update();

	enum eState {
		In_Use,
		End_Use
	};

private:

	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_Sprite;

};

