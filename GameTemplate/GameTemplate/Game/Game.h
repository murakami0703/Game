#pragma once
class Game : public IGameObject
{
public:
	Game();
	~Game();

	void Update();
	void Render();
	void PostRender();

};

