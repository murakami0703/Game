#include "stdafx.h"
#include "enemy/Slaim.h"
#include "data/GameData.h"
#include "soul/Soul.h"
#include "player/Player.h"
#include "siegepoint/SiegePoint.h"
#include "manager/EffectManager.h"
#include "manager/SoulManager.h"


/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////
const float SLAIM_COLLISION_RADIUS = 60.0f;	//スライムのカプセルコリジョンの半径。
const float SLAIM_COLLISION_HEIGHT = 30.0f;	//スライムのカプセルコリジョンの高さ。
const float CHARACON_TIME = (1.0f / 60.0f);	//キャラコンの経過時間。
const int SLAIM_MOVEROTATION_RANGE = 360;	//スライムの移動方向の角度の範囲。
const int TIMER_INITIAL_VALUE_ZERO = 0;		//タイマーの初期化用の値
const int CHANG_DIRECTION_TIME = 120;		//方向転換する時間。
const int TIMER_SET_ONE = 1;				//方向転換完了時にタイマーに代入する値
const float SLAIM_FOLLOW_LENGTH = 300.0f;	//追跡を始める距離。
const CVector3 SRAIM_FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };	//エネミーの前ベクトル。
const float SRAIM_LOITERING_MOVESPEED = 120.0f;				//徘徊の時の速度。

const float SRAIM_LOITERING_LENGTH = 500.0f;			//徘徊に戻る距離。
const float SRAIM_PREMOVE_LENGTH = 50.0f;				//予備動作開始距離。
const float FOLLOW_Y_REMOVAL = 0.0f;					//Y成分の除去。
const CVector3 SRAIM_STOP_MOVE = { 0.0f, 0.0f, 0.0f };	//移動停止させる。
const float SRAIM_FOLLOW_MOVESPEED = 250.0f;			//徘徊の時の速度。

const float SRAIM_FALLPOINT_SPEED = 4000.0f;			//落下地点への移動速度。
const float FALLPOINT_POSY_ADDVALUE = 500.0f;			//落下地点のY座標に足す値。
const float SLAIM_ATTACK_LENGTH = 1000.0f;				//攻撃を始める距離。


const float SRAIM_DEAD_LENGTH = 200.0f;					//死亡判定の距離
const CVector3 SPLITSRAIM_SCALE = { 1.5f,1.5f,1.5f };	//分割モデルの拡大率。
const float EF_SOUL_SET_POSY = 430.0f;						//エフェクト、魂出現時のY軸の高さ。
const CVector3 SMOKE_SCALE = { 20.0f,20.0f,20.0f };			//煙エフェクトの拡大率。
const CVector3 YELLOWLIGHT_SCALE = { 10.0f,10.0f,10.0f };	//光エフェクトの拡大率。

const float INTERPOLATE_TIME = 0.5f;					//補間時間。

Slaim::Slaim()
{
}


Slaim::~Slaim()
{

}

bool Slaim::Start()
{
	//アニメーションクリップのロードとループフラグの設定。
	//通常モデルのアニメーション
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/slaim/slaim_idle.tka");
	m_animClips[eAnimation_Idle].SetLoopFlag(true);
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/slaim/slaim_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Premove].Load(L"Assets/animData/slaim/slaim_premove.tka");
	m_animClips[eAnimation_Premove2].Load(L"Assets/animData/slaim/slaim_premove2.tka");
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/slaim/slaim_attack.tka");
	m_animClips[eAnimation_Vertigo].Load(L"Assets/animData/slaim/slaim_vertigo.tka");
	m_animClips[eAnimation_Vertigo].SetLoopFlag(true);
	//分割モデルのアニメーション
	m_animClips2[eAnimation2_Death].Load(L"Assets/animData/slaim/slaim_dead.tka");

	//cmoファイルの読み込み。
	m_enemyModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemyModelRender->Init(L"Assets/modelData/slaim.cmo", m_animClips, eAnimation_Num);
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

	//キャラコン
	m_characon.Init(
		SLAIM_COLLISION_RADIUS, 
		SLAIM_COLLISION_HEIGHT, 
		m_position
	);

	m_enemyModelRender->SetShadowCaster(true);

	return true;
}

void Slaim::Idle()
{
	//待機。
	m_timer++;
	//一定時間経つと徘徊します。
	if (m_timer >= m_idleTime) {
		m_timer = TIMER_INITIAL_VALUE_ZERO;
		m_state = eState_Loitering;
	}
	m_enemyModelRender->PlayAnimation(eAnimation_Idle);
}
void Slaim::Loitering()
{
	//徘徊。
	//タイマーが0の時ランダムで方向を決定して回転させる
	if (m_timer == TIMER_INITIAL_VALUE_ZERO) {
		m_randRot = rand() % SLAIM_MOVEROTATION_RANGE;
		m_rotation.SetRotation(CVector3::AxisY(), (float)m_randRot);
		m_enemyForward = SRAIM_FORWARD_VECTOR;
		m_rotation.Multiply(m_enemyForward);
		m_timer = TIMER_SET_ONE;
	}
	else if (m_timer > CHANG_DIRECTION_TIME) {
		//タイマーを0に戻す。
		m_timer = TIMER_INITIAL_VALUE_ZERO;
	}
	else {
		m_timer++;
	}

	//距離が近く、BPが空いていると追跡状態へ。
	if (m_toPlayerVec.Length() < SLAIM_FOLLOW_LENGTH) {
		m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
		//空いてるバトルポイントに向かっていくぅ
		if (m_battlePoint != nullptr) {
			m_timer = TIMER_INITIAL_VALUE_ZERO;
			m_state = eState_Follow;
		}
	}
	m_moveVec = m_enemyForward * SRAIM_LOITERING_MOVESPEED;
	m_position = m_characon.Execute(CHARACON_TIME, m_moveVec);
	m_enemyModelRender->PlayAnimation(eAnimation_Walk);

}
void Slaim::Follow()
{	
	//追尾ちゅ
	//BPと自分との距離を調べる
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	//バトルポイントに向かって移動しますぅ
	if (m_toBPVec.Length() > SRAIM_PREMOVE_LENGTH) {
		m_toBPVec.y = FOLLOW_Y_REMOVAL;
		m_toBPVec.Normalize();
	}
	else {
		//近いので停止
		m_toBPVec = SRAIM_STOP_MOVE;
	}

	//バトルポイントが決まってる！
	if (m_battlePoint != nullptr) {
		//距離が近いので、予備動作へ。
		if (m_toPlayerVec.Length() <= SRAIM_PREMOVE_LENGTH) {
			m_state = eState_Premove;
		}
	}
	//距離が遠いので、徘徊に戻る。
	if (m_toPlayerVec.Length() > SRAIM_LOITERING_LENGTH) {
		//
		m_battlePoint = nullptr;
		m_state = eState_Loitering;
	}

	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = m_toPlayerVec;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = FOLLOW_Y_REMOVAL;
	targetVector.Normalize();
	m_enemyForward = SRAIM_FORWARD_VECTOR;
	CQuaternion qRot;
	qRot.SetRotation(m_enemyForward, targetVector);
	m_rotation = qRot;

	m_moveVec = m_toBPVec * SRAIM_FOLLOW_MOVESPEED;
	m_position = m_characon.Execute(CHARACON_TIME, m_moveVec);
	m_enemyModelRender->PlayAnimation(eAnimation_Walk);
}
void Slaim::Premove()
{
	//予備動作その1
	m_enemyModelRender->PlayAnimation(eAnimation_Premove);
	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		m_state = eState_Premove2;
	}
}
void Slaim::Premove2()
{
	//予備動作その2。
	m_enemyModelRender->PlayAnimation(eAnimation_Premove2, INTERPOLATE_TIME);

	if (m_enemyModelRender->IsPlayingAnimation() == false) {
		//プレイヤーの上に離れます
		m_setMoveVec.Normalize();
		m_moveVec = m_setMoveVec * SRAIM_FALLPOINT_SPEED;

		//だいぶ上に行ったので攻撃します。
		if (m_position.y >= SLAIM_ATTACK_LENGTH) {
			m_setMoveVec = m_toPlayerVec;
			//攻撃状態に遷移。
			m_state = eState_Attack;
		}
	}
	else {
		//プレイヤーとの距離を調べ向かわせる方向のベクトルを求めます。
		m_playerPos.y += FALLPOINT_POSY_ADDVALUE;
		m_setMoveVec = m_toPlayerVec - m_position;

	}
	m_position = m_characon.Execute(CHARACON_TIME, m_moveVec);
}
void Slaim::Attack()
{
	//攻撃
	//落下します。
	if (m_position.y >= 450.0f) {
		m_setMoveVec.y -= 400.0f;
		m_enemyModelRender->PlayAnimation(0);
	}
	else {
		//バウンドするよ！
		m_enemyModelRender->PlayAnimation(4,0.5f);
		timer1++;
		if (timer1 >= 20) {
			timer1 = 0;
			m_state = eState_Vertigo;
		}
		else if (timer1>=5) {
			m_position.x += 1.0f;
			m_position.z += 1.0f;

		}
	}
	m_position = m_characon.Execute(CHARACON_TIME, m_setMoveVec);
	
}
void Slaim::Vertigo()
{
	//めまい
	EffectManager* effect = EffectManager::GetInstance();
	effect->EffectPlayer(EffectManager::Bat_memai, m_position, { 5.0f,5.0f,5.0f });

	m_enemyModelRender->PlayAnimation(eAnimation_Vertigo, INTERPOLATE_TIME);
	m_vertigoTimer++;
	//一定時間が経ったら追尾状態に遷移。
	if (m_vertigoTimer >= 60) {
		m_timer = TIMER_INITIAL_VALUE_ZERO;
		m_vertigoTimer = 0;
		m_state = eState_Loitering;
	}
}

void Slaim::Dead()
{
	EffectManager* m_effect = EffectManager::GetInstance();
	SoulManager* m_soul = SoulManager::GetInstance();

	//分割モデルに差し替え
	if (m_modelChangeFlag == false) {
		m_enemyDeadModelRender = g_goMgr->NewGameObject<SkinModelRender>();
		m_enemyDeadModelRender->Init(L"Assets/modelData/slaim_dead.cmo", m_animClips2, eAnimation2_Num);
		m_enemyDeadModelRender->SetPosition(m_position);
		m_enemyDeadModelRender->SetRotation(m_rotation);
		m_enemyDeadModelRender->SetScale(SPLITSRAIM_SCALE);
		g_goMgr->DeleteGameObject(m_enemyModelRender);
		m_modelChangeFlag = true;
	}

	m_enemyDeadModelRender->PlayAnimation(eAnimation2_Death);

	if (m_enemyDeadModelRender->IsPlayingAnimation() == false) {
		//アニメーションの再生が終わったので消しま
		//エフェクト再生
		//煙
		m_effect->EffectPlayer(
			EffectManager::Enemy_Dead,
			{ m_position.x , EF_SOUL_SET_POSY, m_position.z },
			SMOKE_SCALE
		);
		//光
		m_effect->EffectPlayer(
			EffectManager::Item_Get,
			{ m_position.x , EF_SOUL_SET_POSY, m_position.z },
			YELLOWLIGHT_SCALE
		);
		//Soul出現
		m_soul->SoulGenerated({ m_position.x , EF_SOUL_SET_POSY, m_position.z });

		//エネミーの数減らします
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		//消えなさい。
		m_characon.RemoveRigidBoby();
		g_goMgr->DeleteGameObject(m_enemyDeadModelRender);
		g_goMgr->DeleteGameObject(this);
	}
}

void Slaim::Update()
{
	//プレイヤーとの距離を調べる。
	m_playerPos = Player::GetInstance()->GetPosition();
	m_toPlayerVec = m_playerPos - m_position;

	//攻撃が当たったので死ぬ。
	if (Player::GetInstance()->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < SRAIM_DEAD_LENGTH) {
			m_state = eState_Dead;
		}
	}

	switch (m_state)
	{
	case Slaim::eState_Idle:
		Idle();
		break;
	case Slaim::eState_Loitering:
		Loitering();		//徘徊中。
		break;
	case Slaim::eState_Follow:
		Follow();			//プレイヤーを追跡。
		break;
	case Slaim::eState_Premove:
		Premove();			//予備動作。
		break;
	case Slaim::eState_Premove2:
		Premove2();			//予備動作2。
		break;
	case Slaim::eState_Attack:
		Attack();			//攻撃。
		break;
	case Slaim::eState_Vertigo:
		Vertigo();			//めまい。
		break;
	case Slaim::eState_Dead:
		Dead();				//死。
		break;
	}

	//ワールド行列の更新。
	m_enemyModelRender->SetPosition(m_position);
	m_enemyModelRender->SetRotation(m_rotation);
	m_enemyModelRender->SetScale(m_scale);

}

