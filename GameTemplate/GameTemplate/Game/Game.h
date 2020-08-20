#pragma once
class Game : public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
private:
	//音関係
	CSoundSource* m_titleBgm;					//タイトルBGM。

};

