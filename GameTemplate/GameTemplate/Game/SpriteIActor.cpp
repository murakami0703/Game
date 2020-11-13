#include "stdafx.h"
#include "SpriteIActor.h"

SpriteIActor::SpriteIActor()
{
}


SpriteIActor::~SpriteIActor()
{
}

void SpriteIActor::SpriteBound()
{
	//バウンド。
}

//void SpriteIActor::SpriteMove(const CVector2& move, const int& moveTime, const int& moveDelay, const bool& relative = false)
//{
//	//リストに追加
//	//SpriteMoveSet set = { move,{0.0f,0.0f},moveTime,moveDelay,0,relative,false };
//	//m_spriteMoveList.push_back(set);
//}

void SpriteIActor::SpriteMoveUpdate()
{
	//リスト分ループ
	for (auto go = m_spriteMoveList.begin();
		go != m_spriteMoveList.end();
		go++) {
		//タイマーが0以上なら実行中
		if (go->m_spriteMoveTimer >= 0) {

			if (go->m_spriteMoveTimer >= go->m_spriteMoveDelay) { //ディレイを考慮

				//移動距離を計算
				if (go->m_spriteMoveTimer == go->m_spriteMoveDelay) {
					if (go->m_spriteMoveRelative == false) { //指定された座標へ移動
						go->m_spriteMoveSpeed.x = go->m_spriteMovePos.x - m_position.x;
						go->m_spriteMoveSpeed.y = go->m_spriteMovePos.y - m_position.y;
					}
					else { //相対移動
						go->m_spriteMoveSpeed.x = go->m_spriteMovePos.x;
						go->m_spriteMoveSpeed.y = go->m_spriteMovePos.y;
					}
					go->m_spriteMoveSpeed.x /= (float)go->m_spriteMoveLimit;
					go->m_spriteMoveSpeed.y /= (float)go->m_spriteMoveLimit;
				}

				m_position.x += go->m_spriteMoveSpeed.x;
				m_position.y += go->m_spriteMoveSpeed.y;

			}

			go->m_spriteMoveTimer++;

			if (go->m_spriteMoveTimer >= go->m_spriteMoveLimit + go->m_spriteMoveDelay) {
				//おしまい
				go->m_spriteMoveDeleteFlag = true;
				go->m_spriteMoveTimer = -1;
			}
		}
	}

	//削除処理
	std::list<SpriteMoveSet>::iterator it;
	it = m_spriteMoveList.begin();
	while (it != m_spriteMoveList.end()) {
		if (it->m_spriteMoveDeleteFlag == true) {
			it = m_spriteMoveList.erase(it); //erase関数は削除されたイテレータの次を返してくるので、eraseの戻り値を使う。
		}
		else {
			it++; //それ以外は次へ。
		}
	}


}

void SpriteIActor::SpriteSupporter_Update()
{
	//更新。
	m_position = m_spriteRender->GetPosition();
	m_rotation = m_spriteRender->GetRotation();
	m_scale = m_spriteRender->GetScale();
	m_mulColor = m_spriteRender->GetMulColor();
	SpriteMoveUpdate();
	SpriteDataReturn();
}

void SpriteIActor::SpriteDataReturn() 
{
	// スプライトの情報を返す 最後に実行しよう
	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetRotation(m_rotation);
	m_spriteRender->SetScale(m_scale);
	m_spriteRender->SetMulColor(m_mulColor);
}
