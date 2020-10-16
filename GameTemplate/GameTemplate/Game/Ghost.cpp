#include "stdafx.h"
#include "Ghost.h"
#include "GameData.h"
#include "Player.h"

#include "SiegePoint.h"

#include "EffectManager.h"
#include "SoulManager.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const CVector3 GHOST_FORWARD_VECTOR = { 0.0f, 0.0f, -1.0f };		//ゴーストの前ベクトル。
const float GHOST_HORIANGLE = 90.0f;					//視野角判定の角度。
const float GHOST_HORILONG = 500.0f;					//視野角判定の距離。

const float GHOST_IDLE_TIME = 30.0f;					//待機時間。
const float GHOST_TIMER_RESET = 0.0f;					//タイマーを初期状態に戻す。
const int GHOST_RAND_TIMER = 120;						//方向転換する時間。
const int GHOST_RAND_RANGE = 360;						//方向転換する範囲。
const int GHOST_RAND_CALC_TIME = 0;						//方向転換の向きを計算する時間。

const float FOLLOW_LENGTH = 500.0f;						//追跡を始める距離。
const float FOLLOW_Y_REMOVAL = 0.0f;					//Y成分の除去。
const float FOLLOW_MOVE_SPEED = 5.0f;					//追尾中の移動速度。

Ghost::Ghost(){}
Ghost::~Ghost(){}

bool Ghost::Start()
{
	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/ghost/ghost_Idle.tka");
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/ghost/ghost_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/ghost/ghost_premove.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/ghost/ghost_death.tka");
	//cmoファイルの読み込み。
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/ghosts.cmo", m_animClips, eAnimation_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_skinModelRender->SetShadowCaster(true);		//シャドウマップに描画。

	return true;
}

void Ghost::Horizon()
{
	//エネミーの前方方向を求める。
	//前方方向は{0, 0, 1}のベクトルをm_rotationで回して求める。
	CVector3 enemyForward = GHOST_FORWARD_VECTOR;
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
	//角度は絶対値にする。
	if (fabsf(angle) < CMath::DegToRad(GHOST_HORIANGLE) && toPlayerLen < GHOST_HORILONG)
	{
		//近い！！！！！
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//空いてるバトルポイントに向かっていくぅ
		if (m_battlePoint != nullptr) {
			m_state = eState_Follow;
		}

	}

}
void Ghost::Idle()
{
	//待機。
	m_timer++;
	//一定時間経つと徘徊します。
	if (m_timer >= GHOST_IDLE_TIME) {
		m_timer = GHOST_TIMER_RESET;
		m_state = eState_Loitering;
	}

	Horizon();	//視野角判定

	m_skinModelRender->PlayAnimation(eAnimation_Idle);
}
void Ghost::Loitering()
{
	//徘徊。
	//一定時間ごとに方向転換する。
	if (m_timer <= GHOST_RAND_CALC_TIME) {
		//ランダムで方向を決定して動きます
		m_randRot = rand() % GHOST_RAND_RANGE;
		m_rotation.SetRotation(CVector3::AxisY(), (float)m_randRot);
		m_frontmove = GHOST_FORWARD_VECTOR;
		m_rotation.Multiply(m_frontmove);
		m_timer++;
	}
	else if (m_timer > GHOST_RAND_TIMER) {
		//タイマーの初期化。
		m_timer = GHOST_TIMER_RESET;
	}
	else {
		m_timer++;
	}

	m_position += m_frontmove * m_loiteringSpeed;
	Horizon();	//視野角判定

	m_skinModelRender->PlayAnimation(eAnimation_Walk);

}

void Ghost::Follow()
{
	//追尾ちゅ
	//バトルポイントとの距離を調べる。
	CVector3 m_toBPVec = m_battlePoint->position - m_position;

	if (m_toBPVec.Length() > FOLLOW_LENGTH) {
		m_toBPVec.y = FOLLOW_Y_REMOVAL;
		m_toBPVec.Normalize();
		m_position += m_toBPVec * FOLLOW_MOVE_SPEED;

	}
	/*else if (m_toBPVec.Length() < 10.0f) {
		//BPいますよ
		m_battlePosflag = true;
	}*/

	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(GHOST_FORWARD_VECTOR, targetVector);
	m_rotation = qRot;
	//近いので攻撃
	if (m_battlePoint != nullptr) {
		if (m_toPlayerVec.Length() <= 200.0f) {
			EneAttackflag = true;
			m_timer = 0;
			m_state = eState_Premove;
		}
	}
	//遠くなったのでその場で徘徊。
	if (m_toPlayerVec.Length() > 600.0f) {
		m_battlePoint->enemyCount = 0;
		m_battlePoint = nullptr;
		m_state = eState_Loitering;
	}
	m_skinModelRender->PlayAnimation(1);

}

void Ghost::Premove()
{	

	CVector3 diff = m_toPlayerVec;
	diff.Normalize();

	timer1++;
	if (timer1 <= 10) {
		m_position += diff * 1.0f;
		m_position.y -= 3.0f;

	}
	else if (timer1 >= 10 && timer1 <= 50) {
		m_position += diff * 4.0f;
		m_position.y += 8.0f;
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

	m_skinModelRender->PlayAnimation(2,0.5f);
}
void Ghost::Attack()
{
	//攻撃するよ！！！

	//急降下します
	EffectManager* effect = EffectManager::GetInstance();


	if (baund==true && m_position.y >= 410.0f) {
		m_position += dff * 60.0f;
		m_position.y -= 3.0f;
	}
	else {
		baund = false;
		m_timer++;
		if (m_timer<=1){
			effect->EffectPlayer(EffectManager::bund, { m_position.x ,430.0f,m_position.z }, { 30.0f,30.0f,30.0f });

		}
		else if (baund == false && m_position.y <= 410.0f) {
			m_position += dff * 1.0f;
			m_position.y += 3.0f;
			if (EneAttackflag == true && (Player::GetInstance()->GetPosition() - m_position).Length() < 80.0f) {
				//近距離で攻撃したら
				//HP減らす
				GameData::GetInstance()->HPCalc(-1.0f);
				EneAttackflag = false;
			}

		}
		else if (m_timer <= 60.0f) {
			m_position = m_position;
		}
		else {
			m_timer = 0;
			baund = true;
			m_battlePoint->enemyCount = 0;
			m_battlePoint = nullptr;
			m_state = eState_Loitering;
		}
	}
	m_skinModelRender->PlayAnimation(0);

}

void Ghost::Dead()
{
	EffectManager* effect = EffectManager::GetInstance();
	SoulManager* soul = SoulManager::GetInstance();
	m_skinModelRender->PlayAnimation(3);
	m_scale -= m_smallValue;

	if (m_skinModelRender->IsPlayingAnimation() == false) {
		//アニメーションの再生が終わったので消しま
		//エフェクト再生とSoul出現
		effect->EffectPlayer(EffectManager::Enemy_Dead, { m_position.x ,m_effectEneDeadYPos ,m_position.z }, m_effectEneDeadSca);
		effect->EffectPlayer(EffectManager::Item_Get, { m_position.x ,430.0f,m_position.z }, { 12.0f,12.0f,12.0f });
		soul->SoulGenerated({ m_position.x ,m_soulSetYPos ,m_position.z });
		//エネミーの数減らします
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		//消えなさい。
		g_goMgr->DeleteGameObject(m_skinModelRender);
		g_goMgr->DeleteGameObject(this);
	}

}

void Ghost::Update()
{
	//プレイヤーとの距離を調べる。
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;

	//攻撃が当たったので死ぬ。
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < m_deadLength) {
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
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
}
