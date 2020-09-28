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
	SkinModelRender* m_bumModelRender;				//スキンモデル。
	CVector3 m_position = CVector3().Zero();		//座標。

	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_Sprite;

};

