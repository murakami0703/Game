#include "stdafx.h"
#include "Slaim.h"
#include "GameData.h"
#include "Anima.h"
#include "AnimaManeger.h"
#include "Player.h"
#include "SiegePoint.h"


Slaim::Slaim()
{
	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/slaim/slaim_idle.tka");
	m_animClips[eAnimation_Idle].SetLoopFlag(true);
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/slaim/slaim_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/slaim/slaim_premove.tka");
	m_animClips[eAnimation_Premove2].Load(L"Assets/animData/slaim/slaim_premove2.tka");
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/slaim/slaim_attack.tka");
	m_animClips[eAnimation_Vertigo].Load(L"Assets/animData/slaim/slaim_vertigo.tka");
	m_animClips[eAnimation_Vertigo].SetLoopFlag(true);

	//m_animClips[eAnimation_Death].Load(L"Assets/animData/slaim/slaim_dead.tka");

	//cmoファイルの読み込み。
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/slaim.cmo", m_animClips, eAnimation_Num);
	m_position = { -4200.0f, 410.0f, -2500.0f };
	m_oldPos = m_position;
	m_scale = { 2.0f, 2.0f, 2.0f };

	m_characon.Init(20.0f, 30.0f, m_position);//キャラコン
	m_enemyModelRender->SetShadowMap(true);

}


Slaim::~Slaim()
{

}
void Slaim::Idle()
{
	//待機。

	 if (timer >= a) {
		m_state = eState_Loitering;
	}
	timer++;
	m_enemyModelRender->PlayAnimation(0);
}

void Slaim::Loitering()
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
		walkmove = { 0.0f, 0.0f,1.0f };
		m_rotation.Multiply(walkmove);
		count = 0;
		flag = false;
	}
	else if (count >= randomCount) {
		flag = true;
	}
	moveVec = walkmove * randomSpeed;
	m_position = m_characon.Execute(m_caraTime,moveVec);

	if (diff.Length() < 300.0f) {
		flag = true;
		m_state = eState_Follow;
	}

}
void Slaim::Follow()
{	
	Player* player = Player::GetInstance();
	CVector3 P_Position = player->GetPosition();
	CVector3 diff = P_Position - m_position;
	//追尾ちゅ
	if (diff.Length() > 10.0f) {
		diff.y = 0.0f;
		diff.Normalize();
		moveVec = diff * randomSpeed;
	}
	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };

	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

	//近いので攻撃
	if (m_toPlayerVec.Length() <= 100.0f) {
		EneAttackflag = true;
		m_state = eState_Premove;
	}
	//遠くなったのでその場で徘徊。
	if (m_toPlayerVec.Length() > 500.0f) {
		m_state = eState_Loitering;
	}

	m_position = m_characon.Execute(m_caraTime, moveVec);
	m_enemyModelRender->PlayAnimation(1);
}
void Slaim::Premove()
{
	m_enemyModelRender->PlayAnimation(2);
	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		m_state = eState_Premove2;

	}
}
void Slaim::Premove2()
{
	m_enemyModelRender->PlayAnimation(3,0.5f);
	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		//離れまーーーーース
		dddd.Normalize();
		moveVec = dddd * 4000.0f ;

		//m_position.y += 50.0f;
		if (m_position.y >= 1000.0f) {
			Player* player = Player::GetInstance();
			CVector3 P_Position = player->GetPosition();
			P_Position.y += 500.0f;

			m_position = P_Position;
			m_state = eState_Attack;
		}
	}
	else {
		Player* player = Player::GetInstance();
		CVector3 P_Position = player->GetPosition();
		P_Position.y += 500.0f;
		dddd = P_Position - m_position;

	}
	m_position = m_characon.Execute(m_caraTime, moveVec);

}

void Slaim::Attack()
{
	if (m_position.y >= 450.0f) {
		//Player* player = Player::GetInstance();
		//Vector3 P_Position = player->GetPosition();
		//dddd = P_Position - m_position;
		dddd.y -= 2000.0f;
		m_enemyModelRender->PlayAnimation(0);
	}
	else {
		m_enemyModelRender->PlayAnimation(4,0.5f);
		timer1++;
		if (timer1 >= 20) {
			m_state = eState_Vertigo;
		}
		else if (timer1>=5) {
			m_position.x += 1.0f;
			m_position.z += 1.0f;

		}
	}
	m_position = m_characon.Execute(m_caraTime, dddd);
	
}
void Slaim::Vertigo()
{
	m_enemyModelRender->PlayAnimation(5,0.5f);
	timer2++;
	if (timer2 >= 60) {
		m_state = eState_Loitering;
	}
}

void Slaim::Return()
{}
void Slaim::Dead()
{
	//m_enemyModelRender->PlayAnimation(2);
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

void Slaim::Update()
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

	switch (m_state)
	{
	case Slaim::eState_Idle:
		Idle();
		break;
	case Slaim::eState_Loitering:
		Loitering();		//徘徊中
		break;
	case Slaim::eState_Follow:
		Follow();			//プレイヤーを追跡
		break;
	case Slaim::eState_Premove:
		Premove();			//予備動作
		break;
	case Slaim::eState_Premove2:
		Premove2();			//予備動作
		break;
	case Slaim::eState_Attack:
		Attack();			//攻撃
		break;
	case Slaim::eState_Vertigo:
		Vertigo();
		break;
	case Slaim::eState_Return:
		Return();			//徘徊位置に戻る
		break;
	case Slaim::eState_Dead:
		Dead();				//死
		break;
	}

	//ワールド行列の更新。
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

}

