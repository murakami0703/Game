#pragma once
class Game : public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
private:
	//���֌W
	CSoundSource* m_titleBgm;					//�^�C�g��BGM�B

};

