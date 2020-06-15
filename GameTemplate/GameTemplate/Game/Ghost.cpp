#include "stdafx.h"
#include "Ghost.h"
#include "GameData.h"
#include "Anima.h"
#include "AnimaManeger.h"
#include "Player.h"
#include "SiegePoint.h"



Ghost::Ghost()
{
}

Ghost::~Ghost()
{
}

bool Ghost::Start()
{

	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/ghost/ghost_Idle.tka");
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/ghost/ghost_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/ghost/ghost_premove.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/ghost/ghost_death.tka");
	//cmoファイルの読み込み。
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/ghosts.cmo", m_animClips, eAnimation_Num);
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

	m_characon.Init(20.0f, 20.0f, m_position);
	m_enemyModelRender->SetShadowMap(true);

	return true;
}

void Ghost::Idle()
{
	//待機。

	if (timer >= a) {
		m_state = eState_Loitering;
	}
	timer++;
	m_enemyModelRender->PlayAnimation(1);
}

void Ghost::Follow()
{
	//追尾ちゅ
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > 50.0f) {
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		moveVec = m_toBPVec * 20.0f;

	}
	/*else if (m_toBPVec.Length() < 10.0f) {
		//BPいますよ
		m_battlePosflag = true;
	}*/
	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };

	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

	m_position = m_characon.Execute(m_caraTime, moveVec);
	//近いので攻撃
	if (m_battlePoint != nullptr) {
		if (m_toPlayerVec.Length() <= 200.0f) {
			EneAttackflag = true;
			m_state = eState_Premove;
		}
	}
	//遠くなったのでその場で徘徊。
	if (m_toPlayerVec.Length() > 600.0f) {
		m_battlePoint->enemyCount = 0;
		m_battlePoint = nullptr;
		m_state = eState_Loitering;
	}
	m_enemyModelRender->PlayAnimation(1);

}

void Ghost::Loitering()
{
	//徘徊。
	Player* player = Player::GetInstance();
	CVector3 P_Position = player->GetPosition();
	CVector3 diff = P_Position - m_position;
	count++;
	if (flag == true) {
		//ランダムで方向を決定して動きます
		wrandom = rand() % 360;
		m_rotation.SetRotation(CVector3::AxisY(), (float)wrandom);
		walkmove = { 0.0f, 0.0f,-1.0f };
		m_rotation.Multiply(walkmove);
		count = 0;
		flag = false;
	}
	else if (count >= randomCount) {
		flag = true;
	}
	moveVec = walkmove * 10.0f;

	if (diff.Length() < 500.0f) {
		//プレイヤーとの距離が近くなったら追跡します
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//空いてるバトルポイントに向かっていくぅ
		if (m_battlePoint != nullptr) {
			flag = true;
			m_state = eState_Follow;
		}
	}
	m_position = m_characon.Execute(m_caraTime, moveVec);
	m_enemyModelRender->PlayAnimation(1);
	
}
void Ghost::Premove()
{	

	CVector3 diff = m_toPlayerVec;
	diff.Normalize();

	timer1++;
	if (timer1 <= 10) {
		moveVec += diff * 20.0f;
		moveVec.y -= 2.0f;

	}
	else if (timer1 >= 10 && timer1 <= 50) {
		moveVec += diff * 10.0f;
		moveVec.y += 3.0f;
	}
	else {
		timer1 = 0;
		dff = m_toPlayerVec;
		dff.Normalize();
		m_state = eState_Attack;

	}


	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };

	//回転の処理
	if (fabsf(m_position.x) < 0.001f
		&& fabsf(m_position.z) < 0.001f) {
		//わからん
		return;
	}
	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = m_toPlayerVec;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;
	m_position = m_characon.Execute(m_caraTime, moveVec);

	m_enemyModelRender->PlayAnimation(2,0.5f);
}
void Ghost::Attack()
{
	//攻撃するよ！！！

	//急降下します


	/*if (baund==true && m_position.y >= 400.0f) {
		moveVec += dff * 50.0f;
	}
	else {
		baund = false;
		if (m_position.y <= 450.0f) {
			moveVec -= dff * 30.0f;
		}
		else {
			baund = true;
			m_battlePoint->enemyCount = 0;
			m_battlePoint = nullptr;
			m_state = eState_Loitering;
		}
	}
	*/
	if ((Player::GetInstance()->GetPosition() - m_position).Length() < 10.f) {
		//近距離で攻撃したら
		//HP減らす
		GameData::GetInstance()->HPCalc(-0.5f);
	}
	m_position = m_characon.Execute(m_caraTime, moveVec);
	m_enemyModelRender->PlayAnimation(0);

}

void Ghost::Dead()
{
	m_enemyModelRender->PlayAnimation(3);
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
	case Ghost::eState_Idle:
		Idle();
		break;
	case Ghost::eState_Loitering:
		Loitering();		//徘徊中
		break;
	case Ghost::eState_Follow:
		Follow();			//プレイヤーを追跡
		break;
	case Ghost::eState_Premove:
		Premove();			//徘徊位置に戻る
		break;
	case Ghost::eState_Attack:
		Attack();			//攻撃
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
