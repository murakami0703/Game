#include "stdafx.h"
#include "GameOver.h"


GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}


bool GameOver::Start()
{
	return true;
}

void GameOver::SpriteMove(SpriteRender* m_sprite)
{
	//Sprite‰º~ˆ—
	CVector3 m_position = m_sprite->GetPosition();
	if (m_position.y > 0.0f) {
		m_position.y += 20.0f;

	}
	m_sprite->SetPosition(m_position);
}

void GameOver::Update()
{

}

