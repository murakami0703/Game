#include "stdafx.h"
#include "Golem.h"
#include "Player.h"
#include "GameData.h"

#include "EffectManager.h"
#include "SoulManager.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////
const float HP_SETACTIVE_TRUE = 1.0f;		//HP表示中。
const float HP_SETACTIVE_FALSE = 0.0f;		//HP非表示。
const CVector2 HP_PIVOT = { 1.0f,0.5f };	//HPバーの基点。

const int TIMER_INITIAL_VALUE_ZERO = 0;		//タイマーの初期化用の値
const float GOLEM_IDLE_TIME = 120.0f;		//休憩時間。
const float GOLEM_ATTACK_LENGTH = 300.0f;	//攻撃する距離。
const float GOLEM_VECTOR_Y_ZERO = 0.0f;		//移動ベクトルのY軸の値。
const float GOLEM_FOLLOW_SPEED = 5.0f;		//追跡中の移動速度。

const CVector3 GOLEM_FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };			//ゴーレムの前ベクトル。
const float GOLEM_ATTACK_EFFECT_POS_Y = 430.0f;						//攻撃エフェクトのY座標。
const CVector3 GOLEM_ATTACK_EFFECT_SCALE = { 50.0f,50.0f,50.0f };	//攻撃エフェクトの拡大率。


Golem::Golem(){}
Golem::~Golem(){}

bool Golem::Start()
{
	//アニメーションクリップのロードとループフラグの設定。
	m_animClips[eAnimation_Idle].Load(L"Assets/animData/golem_Boss/golem_idle.tka");
	m_animClips[eAnimation_Idle].SetLoopFlag(true);
	m_animClips[eAnimation_Walk].Load(L"Assets/animData/golem_Boss/golem_walk.tka");
	m_animClips[eAnimation_Walk].SetLoopFlag(true);
	m_animClips[eAnimation_Attack].Load(L"Assets/animData/golem_Boss/golem_attack.tka");
	m_animClips[eAnimation_Back].Load(L"Assets/animData/golem_Boss/golem_back.tka");
	m_animClips[eAnimation_Damage].Load(L"Assets/animData/golem_Boss/golem_damage.tka");
	m_animClips[eAnimation_Death].Load(L"Assets/animData/golem_Boss/golem_dead.tka");

	//cmoファイルの読み込み。
	m_skinModelRender = g_goMgr->NewGameObject<SkinModelRender>();
	m_skinModelRender->Init(L"Assets/modelData/Golem_Boss.cmo", m_animClips, eAnimation_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_skinModelRender->SetShadowCaster(true);	//シャドウキャスターに登録。

	//HP
	{
		//0番→Hpフレーム
		m_hpbarSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_hpbarSprite->Init(L"Assets/sprite/Boss_Hpframe.dds", 150.0f, 50.0f);
		m_hpbarSprite->SetAlpha(HP_SETACTIVE_FALSE);
		m_spriteRender.push_back(m_hpbarSprite);
		//1番→Hpバー
		m_hpbarSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_hpbarSprite->Init(L"Assets/sprite/Boss_Hp.dds", 150.0f, 50.0f);
		m_hpbarSprite->SetAlpha(HP_SETACTIVE_FALSE);
		m_hpbarSprite->SetPivot(HP_PIVOT);
		m_spriteRender.push_back(m_hpbarSprite);
	}

	return true;
}

void Golem::Idle()
{
	//休憩。
	m_timer++;
	//追跡再開。
	if (m_timer >= GOLEM_IDLE_TIME) {
		m_timer = TIMER_INITIAL_VALUE_ZERO;
		m_damegeFlag = false;
		m_state = eState_Follow;
	}
	m_skinModelRender->PlayAnimation(eAnimation_Idle);
	
}
void Golem::Follow()
{
	//プレイヤーを追跡。
	m_move = m_toPlayerVec;

	if (m_toPlayerVec.Length() <= GOLEM_ATTACK_LENGTH) {
		//攻撃状態に遷移。
		m_state = eState_Attack;
	}
	else {
		//移動。
		m_move.y = GOLEM_VECTOR_Y_ZERO;
		m_move.Normalize();
		m_position += m_move * GOLEM_FOLLOW_SPEED;

	}

	CVector3 enemyForward = GOLEM_FORWARD_VECTOR;

	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = Player::GetInstance()->GetPosition() - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = GOLEM_VECTOR_Y_ZERO;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

	m_skinModelRender->PlayAnimation(eAnimation_Walk);
}
void Golem::Attack()
{
	//攻撃。
	EffectManager* effect = EffectManager::GetInstance();
	m_skinModelRender->PlayAnimation(eAnimation_Attack);

	if (m_skinModelRender->IsPlayingAnimation() == false)
	{
		//攻撃
		m_attacktimer++;
		//波紋エフェクト流す。
		if (m_attacktimer <= 1) {
			effect->EffectPlayer(
				EffectManager::Golem_Attack,
				{ m_position.x ,GOLEM_ATTACK_EFFECT_POS_Y ,m_position.z },
				GOLEM_ATTACK_EFFECT_SCALE
			);
		}
		float m_DamageX = m_position.x + m_damageLen;
		float m_DamageZ = m_position.z + m_damageLen;

		//エフェクト範囲内の時プレーヤーにダメージ
		if (m_isDamageFlag == false &&
			m_position.x < m_DamageX &&
			m_position.x > -m_DamageX &&
			m_position.z < m_DamageZ &&
			m_position.z > -m_DamageZ
			)
		{
			GameData::GetInstance()->HPCalc(-1.0f);
			m_isDamageFlag = true;
		}
		//攻撃終了です。
		if (m_attacktimer >= m_attackEndTime) {
			m_attacktimer = 0;
			m_isDamageFlag = false;
			m_state = eState_Back;
		}
	}
}
void Golem::Back()
{
	//拳を戻す。
	m_skinModelRender->PlayAnimation(3);

	if (m_skinModelRender->IsPlayingAnimation() == false)
	{
		//休憩する。
		m_timer = 0;
		m_state = eState_Idle;
	}
}
void Golem::MoveHPGage() {
	//寿命ゲージを動かす
	//寿命を計算
	HP -= SUB_HP;
	m_lifeY = (float)HP / (float)MAX_HP;
	//???
	LifeScale = { m_lifeY,1.0f,1.0f };
	m_spriteRender[1]->SetScale(LifeScale);
	count++;
	m_moveGageEndflag = true;
}

void Golem::Damage()
{
	//ダメージ受。
	if (m_moveGageEndflag == false) {
		MoveHPGage();
		if (HP < 0) {
			HP = 0;
		}
	}
	else{
		m_moveGageEndflag = false;
		m_state = eState_Follow;//追従します。
	}

}
void Golem::Dead()
{
	//死。
	EffectManager* effect = EffectManager::GetInstance();
	SoulManager* soul = SoulManager::GetInstance();
	m_skinModelRender->PlayAnimation(5);

	if (m_skinModelRender->IsPlayingAnimation() == false) {
		//アニメーションの再生が終わったので消しま
		//エフェクト再生とSoul出現
		effect->EffectPlayer(EffectManager::Enemy_Dead, { m_position.x ,430.0f ,m_position.z }, { 2.0f ,2.0f ,2.0f });
		soul->SoulGenerated({ m_position.x ,430.0f ,m_position.z });
		//エネミーの数減らします
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		m_gamedate->SetResultFlag(true);

		//消えなさい。
		g_goMgr->DeleteGameObject(m_skinModelRender);
		g_goMgr->DeleteGameObject(this);
	}

}

void Golem::HPBarSaid()
{
	m_spriteRender[0]->SetAlpha(1.0f);
	m_spriteRender[1]->SetAlpha(1.0f);
	atamaNoPos = m_position;
	atamaNoPos.y += 300.0f;
	g_camera3D.CalcScreenPositionFromWorldPosition2(screenPos, atamaNoPos);

	if (screenPos.z > 0.0f) {
		screenPos.z = 0.0f;
		m_spriteRender[0]->SetPosition(screenPos);
		hoge = screenPos;
		if (count == 0) {
			hoge.x -= 150.0f;

		}
		else if (count == 1) {
			hoge.x -= 125.0f;

		}
		else if (count == 2) {
			hoge.x -= 98.0f;

		}

		m_spriteRender[1]->SetPosition(hoge);
	}
}
void Golem::Update()
{
	GameData* m_gamedate = GameData::GetInstance();
	if (m_gamedate->GetEnemyCount() < 10) {

		//プレイヤーとの距離。
		m_playerPos = Player::GetInstance()->GetPosition();
		m_toPlayerVec = m_playerPos - m_position;
		//攻撃が当たった。
		if (Player::GetInstance()->GetAttackflag() == true) {
			if (m_damegeFlag == false && m_state != eState_Attack && m_toPlayerVec.Length() < m_damageLength) {
				m_damegeFlag = true;
				m_state = eState_Damage;
			}
		}
		//HPバーの表示処理。
		cameraPos = g_camera3D.GetPosition();
		Pos = cameraPos - m_position;
		float len = Pos.Length();
		if (len < 1000.0f) {
			HPBarSaid();
		}
		else {
			m_spriteRender[0]->SetAlpha(0.0f);
			m_spriteRender[1]->SetAlpha(0.0f);
		}

		if (HP <= 0) {
			m_state = eState_Dead;//死にます。
		}

		switch (m_state)
		{
		case Golem::eState_Idle:
			Idle();			//待機。
			break;
		case Golem::eState_Follow:
			Follow();		//プレイヤーを追跡。
			break;
		case Golem::eState_Attack:
			Attack();		//攻撃。
			break;
		case Golem::eState_Back:
			Back();			//拳を戻す。
			break;
		case Golem::eState_Damage:
			Damage();		//ダメージ受。
			break;
		case Golem::eState_Dead:
			Dead();			//死。
			break;

		}
		//ワールド行列の更新。
		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetRotation(m_rotation);
		m_skinModelRender->SetScale(m_scale);
	}
}
