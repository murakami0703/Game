#include "stdafx.h"
#include "Bat.h"
#include "Player.h"
#include "SiegePoint.h"


Bat::Bat()
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
	m_position = { -4500.0f, 450.0f, -2500.0f };
	m_scale = { 5.0f,5.0f,5.0f };
	m_enemyModelRender->SetShadowMap(true);

}


Bat::~Bat()
{
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
		m_state = eState_Premove;
	}
	//モデルの前方向。
	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };
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
	//攻撃。
	m_enemyModelRender->PlayAnimation(2);	//攻撃アニメの再生。
	//エフェクト再生（攻撃）

	//アニメが終わったので徘徊状態に遷移。
	if (m_enemyModelRender->IsPlayingAnimation() != true)
	{
		m_state = eState_Loitering;

	}
}
void Bat::Dead()
{
	m_enemyModelRender->PlayAnimation(3);
	if (m_enemyModelRender->IsPlayingAnimation() != true) {
		//アニメーションの再生が終わったので消しま
		//消えなさい。
		g_goMgr->DeleteGameObject(this);
		g_goMgr->DeleteGameObject(m_enemyModelRender);
	}
}

void Bat::Update()
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
