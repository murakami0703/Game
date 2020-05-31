#include "stdafx.h"
#include "Ghost.h"
#include "GameData.h"
#include "Anima.h"
#include "AnimaManeger.h"
#include "Player.h"
#include "SiegePoint.h"



Ghost::Ghost()
{

	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/ghost/ghost_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/ghost/ghost_attack.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/ghost/ghost_death.tka");
	//cmoファイルの読み込み。
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/ghosts.cmo", m_animClips, eAnimation_Num);

	m_oldPos = m_position;		//初期座標をm_oldPosに設定。
}

Ghost::~Ghost()
{
}

void Ghost::Follow()
{
	//追尾ちゅ
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > 10.0f) {
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		m_position += m_toBPVec * m_follSpeed;
	}
	else if (m_toBPVec.Length() < 10.0f) {
		//BPいますよ
		m_battlePosflag = true;
	}
	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };

	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

	//近いので攻撃
	/*if (m_battlePoint != nullptr) {
		if (m_toPlayerVec.Length() <= 150.0f) {
			EneAttackflag = true;
			m_state = eState_Attack;
		}
	}*/
	//遠くなったので徘徊位置に戻る
	if (m_toPlayerVec.Length() > 1000.0f) {
		m_battlePoint->enemyCount = 0;
		m_battlePoint = nullptr;
		m_state = eState_Return;
	}

}

void Ghost::Loitering()
{
	//徘徊中
	m_moveCount++;
	m_position.z += m_moveSpeed;
	//上下徘徊
	if (m_moveCount == 100) {
		m_moveSpeed = -m_moveSpeed;
	}
	if (m_moveCount == 200) {
		m_moveSpeed = m_moveSpeed;
		m_moveCount = 0;
	}

	if (m_toPlayerVec.Length() < m_tuisekiLength) {
		//プレイヤーとの距離が近くなったら追跡します
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//空いてるバトルポイントに向かっていくぅ
		if (m_battlePoint != nullptr) {
			m_state = eState_Follow;
		}
	}
	
	m_enemyModelRender->PlayAnimation(0);
}

void Ghost::Attack()
{
	//次の行動へ。。
		/*if ((Player::GetInstance()->GetPosition() - m_position).Length() < 150.f) {
			//近距離で攻撃したら
			//HP減らす
			GameData::GetInstance()->HPCalc(-0.5f);
		}
		*/
	if (m_battlePoint != nullptr) {

		m_state = eState_Follow;
	}
	else {
		m_battlePoint->enemyCount = 0;
		m_battlePoint = nullptr;
		m_state = eState_Loitering;
	}
}

void Ghost::Return()
{
	//徘徊位置に戻る。
	CVector3 diff = m_position - m_oldPos;
	diff.y = 0.0f;
	diff.Normalize();
	m_position += diff * m_moveSpeed;

	if (diff.Length() < 1.0f) {
		//初期位置付近なので徘徊に戻る。
		m_state = eState_Loitering;
	}

	CVector3 enemyForward = { 1.0f, 0.0f, 0.0f };
	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = m_oldPos - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

}
void Ghost::Dead()
{
	m_enemyModelRender->PlayAnimation(2);
	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		//アニメーションの再生が終わったので消しま
		//エネミーの数減らします
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		//消えなさい。
		g_goMgr->DeleteGameObject(this);
		g_goMgr->DeleteGameObject(m_enemyModelRender);
	}

}

void Ghost::Update()
{
	//プレイヤーとの距離を調べる。
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;

	//攻撃が当たったので死ぬ。
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 200.0f) {
			m_state = eState_Dead;
		}
	}

	switch (m_state) {
	case Ghost::eState_Loitering:
		Loitering();		//徘徊中
		break;
	case Ghost::eState_Follow:
		Follow();			//プレイヤーを追跡
		break;
	case Ghost::eState_Attack:
		Attack();			//攻撃
		break;
	case Ghost::eState_Return:
		Return();			//徘徊位置に戻る
		break;
	case Ghost::eState_Dead:
		Dead();				//死
		break;
	}

	//ワールド行列の更新。
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);
}
