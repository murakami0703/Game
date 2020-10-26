#include "stdafx.h"
#include "boss/Golem.h"
#include "player/Player.h"
#include "data/GameData.h"

#include "manager/EffectManager.h"
#include "manager/SoulManager.h"

/////////////////////////////////////////////////////////
/// 定数
/////////////////////////////////////////////////////////

const float HP_SPRITE_W = 150.0f;			//HPスプライトの幅。
const float HP_SPRITE_H = 50.0f;			//HPスプライトの高さ。
const float HP_SETACTIVE_TRUE = 1.0f;		//HP表示中。
const float HP_SETACTIVE_FALSE = 0.0f;		//HP非表示。
const CVector2 HP_PIVOT = { 1.0f,0.5f };	//HPバーの基点。
const int MAX_HP = 120;		//最大HP

///////////////////////
///sprite
const int HP_FRAME = 0;
const int HP_BAR = 1;
///////////////////////

const int TIMER_INITIAL_VALUE_ZERO = 0;		//タイマーの初期化用の値
const float GOLEM_IDLE_TIME = 120.0f;		//休憩時間。
const float GOLEM_ATTACK_LENGTH = 300.0f;	//攻撃する距離。
const float GOLEM_VECTOR_Y_ZERO = 0.0f;		//移動ベクトルのY軸の値。
const float GOLEM_FOLLOW_SPEED = 5.0f;		//追跡中の移動速度。

const CVector3 GOLEM_FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f };			//ゴーレムの前ベクトル。
const int EFFECT_STARTPLAY_TIME = 1;								//エフェクトを再生させる時間。
const float GOLEM_ATTACK_EFFECT_POS_Y = 430.0f;						//攻撃エフェクトのY座標。
const CVector3 GOLEM_ATTACK_EFFECT_SCALE = { 50.0f,50.0f,50.0f };	//攻撃エフェクトの拡大率。
const float GOLEM_DAMAGE_RANGE = 300.0f;							//ダメージ判定の範囲。
const int GOLEM_ATTACK_ENDTIME = 60;								//攻撃状態終了タイム。 単位:frame

const float HP_SPRITE_SCALE_ONE = 1.0f;		//HPの拡大率。
const float GOLEM_DAMAGE_LENGTH = 250.0f;	//ダメージを受ける距離。
const int REDUCE_HP = 40;					//減少させるHPの値。
const int HP_LOWEST_VALUE = 0;				//HPの最低値。

const float EF_SOUL_SET_POSY = 430.0f;						//エフェクト、魂出現時のY軸の高さ。
const CVector3 SMOKE_SCALE = { 2.0f,2.0f,2.0f };			//煙エフェクトの拡大率。

const float HPBAR_ACTIVE_TRUE = 1.0f;				//透明度(表示)。
const float HPBAR_ACTIVE_FALSE = 0.0f;				//透明度(非表示)。

const float HPBAR_ADD_POSY = 300.0f;				//HPバー表示のY軸の加算値。
const float HPBAR_REMOVAL_POSZ = 0.0f;				//HPバーZ軸の数値の除去。
const int GOLEM_DAMAGE_FIRST = 0;					//ダメージ1回目。
const int GOLEM_DAMAGE_SECOND = 1;					//ダメージ2回目。
const int GOLEM_DAMAGE_THIRD = 2;					//ダメージ3回目。
const float DAMAGE_FIRST_SETHPBAR_POSX = 150.0f;	//ダメージ1回目のHPバーのX軸の位置。
const float DAMAGE_SECOND_SETHPBAR_POSX = 125.0f;	//ダメージ2回目のHPバーのX軸の位置。
const float DAMAGE_THIRD_SETHPBAR_POSX = 98.0f;		//ダメージ3回目のHPバーのX軸の位置。

const float HPBAR_ACTIVE_LENGTH = 1000.0f;			//HPバーを表示させる範囲。

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
		m_hpbarSprite->Init(L"Assets/sprite/Boss_Hpframe.dds", HP_SPRITE_W, HP_SPRITE_H);
		m_hpbarSprite->SetAlpha(HP_SETACTIVE_FALSE);
		m_spriteRender.push_back(m_hpbarSprite);
		//1番→Hpバー
		m_hpbarSprite = g_goMgr->NewGameObject<SpriteRender>();
		m_hpbarSprite->Init(L"Assets/sprite/Boss_Hp.dds", HP_SPRITE_W, HP_SPRITE_H);
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
		if (m_attacktimer <= EFFECT_STARTPLAY_TIME) {
			effect->EffectPlayer(
				EffectManager::Golem_Attack,
				{ m_position.x ,GOLEM_ATTACK_EFFECT_POS_Y ,m_position.z },
				GOLEM_ATTACK_EFFECT_SCALE
			);
		}
		//プレイヤーの位置から攻撃のエフェクトダメージ範囲を設定する。
		float m_DamageX = m_position.x + GOLEM_DAMAGE_RANGE;
		float m_DamageZ = m_position.z + GOLEM_DAMAGE_RANGE;

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
		if (m_attacktimer >= GOLEM_ATTACK_ENDTIME) {
			m_attacktimer = TIMER_INITIAL_VALUE_ZERO;
			m_isDamageFlag = false;
			m_state = eState_Back;
		}
	}
}
void Golem::Back()
{
	//拳を戻す。
	m_skinModelRender->PlayAnimation(eAnimation_Back);

	if (m_skinModelRender->IsPlayingAnimation() == false)
	{
		//休憩する。
		m_timer = TIMER_INITIAL_VALUE_ZERO;
		m_state = eState_Idle;
	}
}

void Golem::MoveHPGage() {
	//HPを計算
	HP -= REDUCE_HP;
	m_lifeY = (float)HP / (float)MAX_HP;
	//HPゲージを動かす
	m_spriteRender[HP_BAR]->SetScale({ m_lifeY,HP_SPRITE_SCALE_ONE,HP_SPRITE_SCALE_ONE });
	m_damageCount++;
	m_moveGageEndflag = true;
}
void Golem::Damage()
{
	//ダメージ受。
	if (m_moveGageEndflag == false) {
		//HPバーの移動処理をします。
		MoveHPGage();
		if (HP < HP_LOWEST_VALUE) {
			HP = HP_LOWEST_VALUE;
		}
	}
	else{
		//HPゲージの移動処理が終了したので追尾状態に戻ります。
		//攻撃を受けたときは無条件で追尾状態です。
		m_moveGageEndflag = false;
		m_state = eState_Follow;//追従します。
	}

}

void Golem::Dead()
{
	//死。
	EffectManager* effect = EffectManager::GetInstance();
	SoulManager* soul = SoulManager::GetInstance();
	m_skinModelRender->PlayAnimation(eAnimation_Death);

	if (m_skinModelRender->IsPlayingAnimation() == false) {
		//アニメーションの再生が終わったので消しま
		//エフェクト再生とSoul出現

		//////////////////////////
		effect->EffectPlayer(EffectManager::Enemy_Dead, { m_position.x ,EF_SOUL_SET_POSY ,m_position.z }, SMOKE_SCALE);
		//////////////////////////
		
		soul->SoulGenerated({ m_position.x ,EF_SOUL_SET_POSY ,m_position.z });

		//エネミーの数減らします
		//////////////////////////
		GameData* m_gamedate = GameData::GetInstance();
		m_gamedate->EnemyReduce();
		m_gamedate->SetResultFlag(true);
		//////////////////////////
		
		//消えなさい。
		g_goMgr->DeleteGameObject(m_skinModelRender);
		g_goMgr->DeleteGameObject(this);
	}

}

void Golem::HPBarSaid()
{
	//HPバーの表示位置
	m_spriteRender[HP_FRAME]->SetAlpha(HPBAR_ACTIVE_TRUE);
	m_spriteRender[HP_BAR]->SetAlpha(HPBAR_ACTIVE_TRUE);
	m_headPos = m_position;
	m_headPos.y += HPBAR_ADD_POSY;
	g_camera3D.CalcScreenPositionFromWorldPosition2(m_screenPos, m_headPos);

	if (m_screenPos.z > HPBAR_REMOVAL_POSZ) {
		//減少ごとにHPの位置の調整をしています。
		m_screenPos.z = HPBAR_REMOVAL_POSZ;
		m_spriteRender[HP_FRAME]->SetPosition(m_screenPos);
		m_hpBarSetPos = m_screenPos;
		if (m_damageCount == GOLEM_DAMAGE_FIRST) {
			m_hpBarSetPos.x -= DAMAGE_FIRST_SETHPBAR_POSX;

		}
		else if (m_damageCount == GOLEM_DAMAGE_SECOND) {
			m_hpBarSetPos.x -= DAMAGE_SECOND_SETHPBAR_POSX;

		}
		else if (m_damageCount == GOLEM_DAMAGE_THIRD) {
			m_hpBarSetPos.x -= DAMAGE_THIRD_SETHPBAR_POSX;

		}

		m_spriteRender[HP_BAR]->SetPosition(m_hpBarSetPos);
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
			if (m_damegeFlag == false && m_state != eState_Attack && m_toPlayerVec.Length() < GOLEM_DAMAGE_LENGTH) {
				m_damegeFlag = true;
				m_state = eState_Damage;
			}
		}

		//HPバーの表示処理。
		m_cameraPos = g_camera3D.GetPosition();
		m_hpSpritePos = m_cameraPos - m_position;
		if (m_hpSpritePos.Length() < HPBAR_ACTIVE_LENGTH) {
			//プレイヤーとの距離が1000.0f以下なら表示させる。
			HPBarSaid();
		}
		else {
			m_spriteRender[HP_FRAME]->SetAlpha(HPBAR_ACTIVE_FALSE);
			m_spriteRender[HP_BAR]->SetAlpha(HPBAR_ACTIVE_FALSE);
		}

		//死にます。
		if (HP <= HP_LOWEST_VALUE) {
			m_state = eState_Dead;
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
