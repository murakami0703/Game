#include "stdafx.h"
#include "Bat.h"
#include "Player.h"
#include "SiegePoint.h"
#include "EffectManager.h"
#include "GameData.h"
#include "SoulManager.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////
const CVector3 BAT_FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };	//コウモリの前ベクトル。
const float BAT_HORIANGLE = 45.0f;						//視野角判定の角度。
const float BAT_HORILONG = 200.0f;						//視野角判定の距離。
const float FOLLOW_HORIANGLE = 90.0f;					//追従の視野角判定の角度。
const float FOLLOW_HORILONG = 500.0f;					//追従の視野角判定の距離。

const float GHOST_IDLE_TIME = 30.0f;					//待機時間。
const int TIMER_RESET = 0;								//タイマーを初期状態に戻す。
const int RAND_TIMER = 120;								//方向転換する時間。
const int RAND_RANGE = 360;								//方向転換する範囲。
const int RAND_CALC_TIME = 0;							//方向転換の向きを計算する時間。
const float LOITERING_SPEED = 2.0f;						//徘徊速度。

const float BAT_PREMOVE_LENGTH = 250.0f;						//予備動作開始距離。
const float FOLLOW_Y_REMOVAL = 0.0f;							//Y成分の除去。
const float BAT_FOLLOW_MOVESPEED = 1.0f;						//追尾中のコウモリの移動速度。
const float EF_SOUL_SET_POSY = 430.0f;							//エフェクト、魂出現時のY軸の高さ。

const CVector3 PREMOVE_EFFECT_SCALE = { 5.0f,5.0f,5.0f };		//予備動作エフェクトの拡大率。
const float EFFECT_ADD_POSY = 80.0f;							//エフェクト出現時のY軸に加算する値。
const float LOITERING_RETURN_LENGTH = 800.0f;					//追従状態から徘徊状態に戻る距離
const int ATTACK_EFFECT_STARTPLAY_TIME = 1;						//攻撃エフェクトを再生させる時間。
const CVector3 ATTACK_EFFECT_SCALE = { 10.0f,10.0f,10.0f };		//攻撃エフェクトの拡大率。
const float ATTACK_TIME =20.0f;									//攻撃する時間。単位：frame

const CVector3 SMOKE_SCALE = { 20.0f,20.0f,20.0f };			//煙エフェクトの拡大率。
const CVector3 YELLOWLIGHT_SCALE = { 10.0f,10.0f,10.0f };	//光エフェクトの拡大率。

const float BAT_DEAD_RANGE = 120.0f;		//攻撃が当たる範囲。

Bat::Bat(){}
Bat::~Bat(){}

bool Bat::Start()
{
	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/bat/bat_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/bat/bat_premove.tka");
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/bat/bat_attack.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/bat/bat_dead.tka");

	//cmoファイルの読み込み。
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/bat.cmo", m_animClips, eAnimation_Num);
	m_skinModelRender->PlayAnimation(0);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_skinModelRender->SetShadowCaster(true);	//シャドウキャスターに描画。

	return true;
}

void Bat::Horizon()
{
	//視野角判定
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toPlayerDir = m_toPlayerVec;

	//正規化を行う前に、プレイヤーまでの距離を求めておく。
	float toPlayerLen = toPlayerDir.Length();
	//正規化
	toPlayerDir.Normalize();

	//enemyForwardとtoPlayerDirとの内積を計算する。
	float d = BAT_FORWARD_VECTOR.Dot(toPlayerDir);

	//内積の結果をacos関数に渡して、enemyForwardとtoPlayerDirのなす角を求める。
	float angle = acos(d);

	//視野角判定。
	//fabsfは絶対値を求める関数！
	//角度はマイナスが存在するから、絶対値にする。

	//徘徊中。
	if (fabsf(angle) < CMath::DegToRad(FOLLOW_HORIANGLE) && toPlayerLen < FOLLOW_HORILONG)
	{
			m_state = eState_Follow;
	}

	//攻撃。
	if (EneAttackflag == true && fabsf(angle) < CMath::DegToRad(BAT_HORIANGLE) && toPlayerLen < BAT_HORILONG) {
		//近距離で攻撃したら
		//プレイヤーのHP減らす
		GameData::GetInstance()->HPDecrease();
		EneAttackflag = false;
	}
}

void Bat::Loitering()
{
	//徘徊。
	//一定時間ごとに方向転換する。
	if (m_timer <= RAND_CALC_TIME) {
		//ランダムで方向を決定して動きます
		m_randRot = rand() % RAND_RANGE;
		m_rotation.SetRotation(CVector3::AxisY(), (float)m_randRot);
		m_frontmove = BAT_FORWARD_VECTOR;
		m_rotation.Multiply(m_frontmove);
		m_timer++;
	}
	else if (m_timer > RAND_TIMER) {
		//タイマーの初期化。
		m_timer = TIMER_RESET;
	}
	else {
		m_timer++;
	}

	m_position += m_frontmove * LOITERING_SPEED;
	Horizon();		//視野角判定。

	m_skinModelRender->PlayAnimation(eAnimation_Walk);
}
void Bat::Follow()
{
	//追尾中。
	m_toFollowEPVec = m_toPlayerVec;

	//一定の距離まで近づきます。
	if (m_toFollowEPVec.Length() > BAT_PREMOVE_LENGTH) {
		m_toFollowEPVec.y = FOLLOW_Y_REMOVAL;
		m_toFollowEPVec.Normalize();
		m_position += m_toFollowEPVec * BAT_FOLLOW_MOVESPEED;
	}
	//近づいたので予備動作状態に遷移します。
	else if (m_toFollowEPVec.Length() <= BAT_PREMOVE_LENGTH)
	{
		EneAttackflag = true;
		EffectManager* effect = EffectManager::GetInstance();
		effect->EffectPlayer(
			EffectManager::bat_pre,
			{ m_position.x ,m_position.y + EFFECT_ADD_POSY ,m_position.z },
			PREMOVE_EFFECT_SCALE, m_rotation
		);

		m_state = eState_Premove;
	}
	//モデルの前方向。
	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = m_toPlayerVec;
	//　Y成分は除去して正規化する。
	targetVector.y = FOLLOW_Y_REMOVAL;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(BAT_FORWARD_VECTOR, targetVector);
	m_rotation = qRot;

	//遠くなったのでその場で徘徊する。
	if (m_toPlayerVec.Length() > LOITERING_RETURN_LENGTH) {
		m_state = eState_Loitering;
	}

	m_skinModelRender->PlayAnimation(eAnimation_Walk);

}
void Bat::Premove()
{
	//予備動作。
	m_skinModelRender->PlayAnimation(eAnimation_Premove);	//予備動作アニメの再生。
	//予備動作アニメが終わったので攻撃状態に遷移。
	if (m_skinModelRender->IsPlayingAnimation() != true)
	{
		m_state = eState_Attack;

	}
}
void Bat::Attack()
{
	EffectManager* effect = EffectManager::GetInstance();
	//攻撃。
	m_skinModelRender->PlayAnimation(eAnimation_Attack);	//攻撃アニメの再生。
	//エフェクト再生（攻撃）
	m_timer++;
	if (m_timer <= ATTACK_EFFECT_STARTPLAY_TIME)
	{
		effect->EffectPlayer(
			EffectManager::Bat_Attack,
			{ m_position.x ,m_position.y + EFFECT_ADD_POSY ,m_position.z },
			ATTACK_EFFECT_SCALE,
			m_rotation
		);
	}
	else if (EneAttackflag == true && m_timer <= ATTACK_TIME)
	{
		//使うかわからん奴。要確認。
		/////////////////////////////////////////////////
		/*CVector3 enemyForward = BAT_FORWARD_VECTOR;
		m_rotation.Multiply(enemyForward);*/
		/////////////////////////////////////////////////

		//視野角判定
		Horizon();
	}
	else if (m_skinModelRender->IsPlayingAnimation() != true && m_timer >= ATTACK_TIME)
	{
		//アニメーションが終わったので徘徊状態に遷移。
		m_timer = TIMER_RESET;
		m_state = eState_Loitering;
	}
}
void Bat::Dead()
{
	EffectManager* effect = EffectManager::GetInstance();
	SoulManager* soul = SoulManager::GetInstance();

	m_skinModelRender->PlayAnimation(eAnimation_Death);
	if (m_skinModelRender->IsPlayingAnimation() != true) {
		//アニメーションの再生が終わったので消しま
		//エフェクト再生とSoul出現
		effect->EffectPlayer(EffectManager::Enemy_Dead, { m_position.x ,EF_SOUL_SET_POSY,m_position.z }, SMOKE_SCALE);			//煙。
		effect->EffectPlayer(EffectManager::Item_Get, { m_position.x ,EF_SOUL_SET_POSY,m_position.z }, YELLOWLIGHT_SCALE);		//光。
		soul->SoulGenerated({ m_position.x ,EF_SOUL_SET_POSY,m_position.z });
		//エネミーの数減らします
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();

		//アニメーションの再生が終わったので消しま。
		//消えなさい。
		g_goMgr->DeleteGameObject(m_skinModelRender);
		g_goMgr->DeleteGameObject(this);
	}
}

void Bat::Update()
{

	//プレイヤーとの距離を調べる。
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;

	//攻撃が当たったので死ぬ。
	//////////////////////////////////////////////////
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < BAT_DEAD_RANGE) {
			m_state = eState_Dead;
		}
	}
	//////////////////////////////////////////////////

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
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
	
}
