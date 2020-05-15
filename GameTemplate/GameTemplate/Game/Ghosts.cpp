#include "stdafx.h"
#include "Ghosts.h"
#include "Player.h"
#include "SiegePoint.h"

Ghosts::Ghosts()
{
	m_animClips[Ghosts_walk].Load(L"Assets/animData/ghost_walk.tka");

	//ループフラグの設定。
	m_animClips[Ghosts_walk].SetLoopFlag(true);
	//cmoファイルの読み込み。
	m_enemy = g_goMgr->NewGameObject<SkinModelRender>();
	m_enemy->Init(L"Assets/modelData/ghosts.cmo");
	m_oldPos = m_position;
	m_animation.Init(m_enemy->GetSkinModel(), m_animClips, num);	//アニメーションの初期化


}


Ghosts::~Ghosts()
{
}

void Ghosts::Follow()
{
}

void Ghosts::move()
{
	//追尾ちゅ
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > 10.0f){
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		m_position += m_toBPVec * m_follSpeed;
	}
	else if (m_toBPVec.Length() < 10.0f) {
		//BPいますよ
		m_battlePosflag = true;
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
	

	m_animation.Play(Ghosts_walk);
}

void Ghosts::Attack()
{
	m_state = eState_Haikai;
}

void Ghosts::Return()
{
}
void Ghosts::Dead()
{
}

void Ghosts::Update()
{
	//死亡判定
	/*p_pos = player->GetPosition();
	m_toPlayerVec = p_pos - m_position;

	if (player->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 60.0f) {
			m_state = eState_Dead;
		}
	}
	*/


	switch (m_state) {
	case eState_Haikai:
		//徘徊中
		move();
		if (m_toPlayerVec.Length() < m_tuisekiLength) {
			//攻撃範囲に近づいたときバトルポイントが空いてたら追従します。
			m_battlePoint = SiegePoint::GetInstance()->TryGetBattlePoint(m_position);
			if (m_battlePoint != nullptr) {
				m_state = eState_TuisekiPlayer;
			}
		}
		break;
	case eState_Attack:
		Attack();
		break;
	case eState_TuisekiPlayer:
		//プレイヤーを追跡
		Follow();
		if (m_battlePoint != nullptr) {
			//近いので攻撃
			if (m_toPlayerVec.Length() < 80.0f) {
				EneAttackflag = true;
				m_state = eState_Attack;
			}
		}
		//遠くなったので徘徊位置に戻る
		if (m_toPlayerVec.Length() > m_ReturnLength) {
			m_state = eState_Haikai;
		}
		break;
	case eState_Return:
		//徘徊位置に戻る
		break;
	case eState_Dead:
		//死
		Dead();
		break;
	}
	m_animation.Update(0.05f);//アニメーション再生

	//ワールド行列の更新。
	m_enemy->SetPosition(m_position);
	m_enemy->SetRotation(m_rotation);
	m_enemy->SetScale(m_scale);

}
void Ghosts::Render()
{
}

void Ghosts::PostRender()
{

}
