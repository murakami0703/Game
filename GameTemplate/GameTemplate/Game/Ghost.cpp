#include "stdafx.h"
#include "Ghost.h"
#include "GameData.h"
#include "Player.h"
#include "SiegePoint.h"
#include "EffectManager.h"



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

	m_characon.Init(50.0f, 100.0f, m_position);	//キャラコンの初期化。
	m_enemyModelRender->SetShadowMap(true);		//シャドウマップに描画。

	return true;
}

void Ghost::Horizon()
{
	//エネミーの前方方向を求める。
	//前方方向は{0, 0, 1}のベクトルをm_rotationで回して求めてみる。
	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };
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
	if (fabsf(angle) < CMath::DegToRad(horiAngle) && toPlayerLen < horilong)
	{
		//近い！！！！！
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//空いてるバトルポイントに向かっていくぅ
		if (m_battlePoint != nullptr) {
			flag = true;
			m_state = eState_Follow;
		}

	}

}

void Ghost::Idle()
{
	//待機。
	m_timer++;
	//一定時間経つと徘徊します。
	if (m_timer >= m_idleTime) {
		m_timer = 0;
		m_state = eState_Loitering;
	}

	Horizon();	//視野角判定

	m_enemyModelRender->PlayAnimation(1);
}
void Ghost::Loitering()
{
	//徘徊。
	//一定時間ごとに方向転換する。
	if (m_timer == 0) {
		//ランダムで方向を決定して動きます
		m_randRot = rand() % 360;
		m_rotation.SetRotation(CVector3::AxisY(), (float)m_randRot);
		walkmove = { 0.0f, 0.0f,-1.0f };
		m_rotation.Multiply(walkmove);
		m_timer = 1;
		flag = false;
	}
	else if (m_timer > m_randTimer) {
		m_timer = 0;
	}
	else {
		m_timer++;
	}
	moveVec = walkmove * randomSpeed;

	Horizon();	//視野角判定

	m_position = m_characon.Execute(m_caraTime, moveVec);
	m_enemyModelRender->PlayAnimation(1);

}

void Ghost::Follow()
{
	//追尾ちゅ
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > 50.0f) {
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		moveVec = m_toBPVec * 250.0f;

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
	m_position = m_characon.Execute(m_caraTime, moveVec);
	m_enemyModelRender->PlayAnimation(1);

}

void Ghost::Premove()
{	

	CVector3 diff = m_toPlayerVec;
	diff.Normalize();

	timer1++;
	if (timer1 <= 10) {
		moveVec = diff * 5.0f;
		moveVec.y -= 5.0f;

	}
	else if (timer1 >= 10 && timer1 <= 50) {
		moveVec += diff * 5.0f;
		moveVec.y += 15.0f;
	}
	else if (timer1 >= 50 && timer1 <= 60) {
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


	if (baund==true && m_characon.IsOnGround() == false) {
		moveVec = dff * 2000.0f;
		moveVec.y -= 5.0f;
	}
	else {
		baund = false;
		m_timer++;
		if (baund == false && m_position.y <= 440.0f) {
			moveVec = dff * 200.0f;
			moveVec.y += 200.0f;
		}
		else if (m_timer <= 100.0f) {
			moveVec = {0.0f,0.0f,0.0f};
		}
		else {
			m_timer = 0;
			baund = true;
			m_battlePoint->enemyCount = 0;
			m_battlePoint = nullptr;
			m_state = eState_Loitering;
		}
	}
	/*if ((Player::GetInstance()->GetPosition() - m_position).Length() < 10.f) {
		//近距離で攻撃したら
		//HP減らす
		GameData::GetInstance()->HPCalc(-0.5f);
	}*/
	m_position = m_characon.Execute(m_caraTime, moveVec);
	m_enemyModelRender->PlayAnimation(0);

}

void Ghost::Dead()
{
	m_enemyModelRender->PlayAnimation(3);
	EffectManager* effect = EffectManager::GetInstance();
	effect->EffectPlayer(EffectManager::test, m_position, { 10.0f,10.0f,10.0f });

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
