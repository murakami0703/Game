#include "stdafx.h"
#include "Bat.h"
#include "Player.h"
#include "SiegePoint.h"
#include "EffectManager.h"
#include "GameData.h"
#include "SoulManager.h"


Bat::Bat()
{

}


Bat::~Bat()
{
}

bool Bat::Start()
{
	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/bat/bat_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/bat/bat_premove.tka");
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/bat/bat_attack.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/bat/bat_dead.tka");
	//cmoファイルの読み込み。
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/bat.cmo", m_animClips, eAnimation_Num);
	m_enemyModelRender->PlayAnimation(0);
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

	m_enemyModelRender->SetShadowMap(true);

	return true;
}

void Bat::Loitering()
{
	m_enemyModelRender->PlayAnimation(0);
	m_state = eState_Follow;
}
void Bat::Follow()
{
	//追尾中。
	CVector3 m_toEPVec = m_toPlayerVec;

	//一定の距離まで近づきます。
	if (m_toEPVec.Length() > m_toPlyaerLength) {
		m_toEPVec.y = 0.0f;
		m_toEPVec.Normalize();
		m_position += m_toEPVec * 1.0f;
	}
	//近づいたので予備動作状態に遷移します。
	else if (m_toEPVec.Length() <= m_toPlyaerLength)
	{
		EneAttackflag = true;
		EffectManager* effect = EffectManager::GetInstance();
		effect->EffectPlayer(EffectManager::bat_pre, { m_position.x ,m_position.y + 80.0f ,m_position.z }, { 5.0f,5.0f,5.0f }, m_rotation);
		m_state = eState_Premove;
	}
	//モデルの前方向。
	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

	//遠くなったのでその場で徘徊する。
	if (m_toPlayerVec.Length() > m_returnLength) {
		m_state = eState_Loitering;
	}

	m_enemyModelRender->PlayAnimation(0);

}
void Bat::Premove()
{
	//予備動作。
	m_enemyModelRender->PlayAnimation(1);	//予備動作アニメの再生。
	//予備動作アニメが終わったので攻撃状態に遷移。
	if (m_enemyModelRender->IsPlayingAnimation() != true)
	{
		m_state = eState_Attack;

	}
}
void Bat::Attack()
{
	EffectManager* effect = EffectManager::GetInstance();
	//攻撃。
	m_enemyModelRender->PlayAnimation(2);	//攻撃アニメの再生。
	//エフェクト再生（攻撃）
	m_timer++;
	//アニメが終わったので徘徊状態に遷移。
	if (m_timer <= 1)
	{
		effect->EffectPlayer(EffectManager::Bat_Attack, { m_position.x ,m_position.y + 80.0f ,m_position.z }, { 10.0f,10.0f,10.0f }, m_rotation);
	}
	else if (EneAttackflag == true && m_timer <= 20)
	{
		CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
		m_rotation.Multiply(enemyForward);

		//エネミーからプレイヤーに伸びるベクトルを求める。
		CVector3 toPlayerDir = m_toPlayerVec;

		//正規化を行う前に、プレイヤーまでの距離を求めておく。
		float toPlayerLen = toPlayerDir.Length();
		//正規化
		toPlayerDir.Normalize();

		//enemyForwardとtoPlayerDirとの内積を計算する。
		float d = enemyForward.Dot(toPlayerDir);

		//内積の結果をacos関数に渡して、enemyForwardとtoPlayerDirのなす角を求める。
		float angle = acos(d);


		//視野角判定
		//fabsfは絶対値を求める関数！
		//角度はマイナスが存在するから、絶対値にする。
		if (EneAttackflag == true && fabsf(angle) < CMath::DegToRad(45.0f) && toPlayerLen < 200.0f){
			//近距離で攻撃したら
			//HP減らす
			GameData::GetInstance()->HPCalc(-1.0f);
			EneAttackflag = false;
		}
	}
	else if (m_enemyModelRender->IsPlayingAnimation() != true && m_timer>=20)
	{
		m_timer = 0;
		m_state = eState_Loitering;
	}

}
void Bat::Dead()
{
	EffectManager* effect = EffectManager::GetInstance();
	SoulManager* soul = SoulManager::GetInstance();

	m_enemyModelRender->PlayAnimation(3);
	if (m_enemyModelRender->IsPlayingAnimation() != true) {
		//アニメーションの再生が終わったので消しま
	//エフェクト再生とSoul出現
		effect->EffectPlayer(EffectManager::Enemy_Dead, { m_position.x ,420.0f,m_position.z }, { 20.0f,20.0f,20.0f });
		effect->EffectPlayer(EffectManager::Item_Get, { m_position.x ,430.0f,m_position.z }, { 10.0f,10.0f,10.0f });
		soul->SoulGenerated({ m_position.x ,430.0f,m_position.z });
		//エネミーの数減らします
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();

		//アニメーションの再生が終わったので消しま
		//消えなさい。
		g_goMgr->DeleteGameObject(m_enemyModelRender);
		g_goMgr->DeleteGameObject(this);
	}
}

void Bat::Update()
{

	//プレイヤーとの距離を調べる。
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;

	//攻撃が当たったので死ぬ。
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 120.0f) {
			m_state = eState_Dead;
		}
	}

	switch (m_state)
	{
	case Bat::eState_Loitering:
		Loitering();		//徘徊中
		break;
	case Bat::eState_Follow:
		Follow();			//プレイヤーを追跡
		break;
	case Bat::eState_Premove:
		Premove();			//予備動作
		break;
	case Bat::eState_Attack:
		Attack();			//攻撃
		break;
	case Bat::eState_Dead:
		Dead();				//死
		break;
	}

	//ワールド行列の更新。
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);
	
}
