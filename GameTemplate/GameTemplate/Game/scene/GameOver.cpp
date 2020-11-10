#include "stdafx.h"
#include "scene/GameOver.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const float ACTIVE_TRUE = 1.0f;					//透明度(表示)。
const float ACTIVE_FALSE = 0.0f;					//透明度(非表示)。
GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}


bool GameOver::Start()
{

	//0番→GameOver
	m_gameOverSprite = g_goMgr->NewGameObject<SpriteRender>();
	m_gameOverSprite->Init(L"Assets/sprite/gameover.dds", 700.0f, 150.0f);
	m_gameOverSprite->SetPosition({ 0.0f,m_startYPos ,0.0f });
	m_gameOverSprite->SetAlpha(ACTIVE_FALSE);
	m_spriteRender.push_back(m_gameOverSprite);

	return true;
}


void GameOver::BackGDDark()
{
	//背景を暗くしますぅ。
	if (m_mulColor > m_SetMulColor) {
		m_mulColor -= 0.1f;
		g_goMgr->SetMainSpriteMulColor({ m_mulColor,m_mulColor, m_mulColor, 1.0f });
	}
	else {
		//次の処理へ。
		m_state = Sprite_Set;
	}
}
void GameOver::GameOverSet()
{
	//ゲームオーバーの文字を出す。

	CVector3 m_position = m_spriteRender[0]->GetPosition();

	if (m_position.y > m_moveYPos && m_bound == false) {
		m_position.y -= m_overSpeed;
	}
	else {
		m_bound = true;
		//ここからバウンド処理
		if (m_bound == true && m_position.y < m_setYPos) {
			m_position.y += m_overSpeed;
		}
		else {
			//バウンド終了、次の処理へ...。
			m_bound = false;
			m_state = Font_Set;
		}

	}
	m_spriteRender[0]->SetAlpha(1.0f);
	m_spriteRender[0]->SetPosition(m_position);

}
void GameOver::NextSet()
{
	//Next表示しま。

}

void GameOver::Update()
{
	switch (m_state)
	{
	case GameOver::BackGD_Dark:
		BackGDDark();
		break;
	case GameOver::Sprite_Set:
		GameOverSet();
		break;
	case GameOver::Font_Set:
		NextSet();
		break;
	}

}

