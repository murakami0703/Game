#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManeger.h"


Enemy::Enemy()
{

	//アニメーションクリップのロード。
	m_animClips[eneidle].Load(L"Assets/animData/eneIdle.tka");
	m_animClips[enewalk].Load(L"Assets/animData/eneWalk.tka");
	m_animClips[eneAttack_1].Load(L"Assets/animData/eneAT1.tka");
	m_animClips[eneDead].Load(L"Assets/animData/eneDeath.tka");

	//ループフラグの設定。
	m_animClips[eneidle].SetLoopFlag(true);
	m_animClips[enewalk].SetLoopFlag(true);

	//cmoファイルの読み込み。
	m_enemy.Init(L"Assets/modelData/Footman_Default.cmo");
	m_oldPos = m_position;
	m_scale = { 50.0f,50.0f,50.0f };

	//法線マップつけます
	DirectX::CreateDDSTextureFromFileEx(
	g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Normal.dds", 0,
	D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
	false, nullptr, &g_normalMapSRV
	);
	//スぺキュラマップつけます
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/Specular.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_specularMapSRV
	);
	//アンビエントマップつけます
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), L"Assets/sprite/AO.dds", 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_ambientMapSRV
	);

	//モデルに法線マップ、スぺキュラマップ、アンビエントマップを設定する。
	m_enemy.SetNormalMap(g_normalMapSRV);
	//m_enemy.SetSpecularMap(g_specularMapSRV);
	//m_enemy.SetAmbientMap(g_ambientMapSRV);

	m_animation.Init(m_enemy, m_animClips, num);	//アニメーションの初期化

}

Enemy::~Enemy()
{
	// 法線マップを解放。
	if (g_normalMapSRV != nullptr) {
		g_normalMapSRV->Release();
	}

}

void Enemy::Follow(Player* player)
{
	//追尾ちゅ
	CVector3 m_toBPVec = m_battlePoint->position - m_position;
	if (m_toBPVec.Length() > m_follSpeed){
		m_toBPVec.y = 0.0f;
		m_toBPVec.Normalize();
		m_position += m_toBPVec * m_follSpeed;
	}
	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };

	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = player->GetPosition() - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

}

void Enemy::move()
{
	//徘徊中
	m_moveCount++;
	m_position.z += m_moveSpeed;
	//上下徘徊
	if (m_moveCount == 100) {
		m_moveSpeed = -m_moveSpeed;
	}
	if (m_moveCount == 200) {
		m_moveSpeed = m_moveSpeed;
		m_moveCount = 0;
	}


}
void Enemy::Attack()
{
	m_animation.Play(eneAttack_1);//歩き
	if (m_animation.IsPlaying() == false) {
		if (m_battlePoint != nullptr) {
			m_state = eState_TuisekiPlayer;
		}
		else {
			m_state = eState_Haikai;
		}
	}
}

void Enemy::Return()
{
	//徘徊位置に戻る。
	CVector3 diff = m_position - m_oldPos;
	diff.y = 0.0f;
	diff.Normalize();
	m_position += diff * m_moveSpeed;
	if (diff.Length() < 1.0f) {
		m_state = eState_Haikai;
	}

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = m_oldPos - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;

}
void Enemy::Dead()
{
	m_animation.Play(eneDead);//歩き
	if (m_animation.IsPlaying() == false) {
		EnemyManager::GetInstance()->DeleteEnemy(this);
	}
}

void Enemy::Update(Player* player)
{
	
	p_pos = player->GetPosition();
	m_toPlayerVec = p_pos - m_position;

	if (player->GetAttackflag() == true) {
		if (m_toPlayerVec.Length() < 60.0f) {
			m_state = eState_Dead;
		}
	}

	m_animation.Update(0.05f);//アニメーション再生

	switch (m_state) {
	case eState_Haikai:
		//徘徊中
		m_animation.Play(enewalk);//歩き
		move();
		if (m_toPlayerVec.Length() < m_tuisekiLength ) {
			m_battlePoint = EnemyManager::GetInstance()->TryGetBattlePoint(m_position);
			if(m_battlePoint!= nullptr){
				m_state = eState_TuisekiPlayer;
			}
		}
		break;
	case eState_Attack:
		Attack();
		break;
	case eState_TuisekiPlayer:
		//プレイヤーを追跡
		m_animation.Play(enewalk);//歩き
		Follow(player);
		//近いので攻撃
		if (m_battlePoint != nullptr) {
			if(m_battlePoint)
			if (m_toPlayerVec.Length() < 80.0f) {
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
		m_animation.Play(enewalk);//歩き
		Return();
		break;
	case eState_Dead:
		//死
		Dead();
		break;
	}

	//ワールド行列の更新。
	m_enemy.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_enemy.Update();

}
void Enemy::Draw(EnRenderMode m_renderMode)
{
	m_enemy.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		m_renderMode
	);
}