#pragma once
#include "GameObjectManager.h"

#include "Player.h"
#include "Map.h"
#include "level/Level.h"
#include "Sprite.h"
#include "Map.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "SShadowMap.h"
#include "SRenderTarget.h"

class Game
{
public:
	Game();
	~Game();

	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈���B
	/// </summary>
	void Render();
	/// <summary>
	/// �V���h�E�}�b�v���擾�B
	/// </summary>
	/// <returns></returns>
	SShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}
private:
	//�v���C���[
	Player* player = new Player;
	//�}�b�v
	Map* map = new Map;
	//�Q�[���J����
	GameCamera Gcamera;
	Enemy enemy;

	CVector3 m_unityChanPos = { 0.0f, 0.0f, 0.0f };	//���j�e�B�����̍��W�B
	SShadowMap m_shadowMap;					//�V���h�E�}�b�v�B
	Sprite g_sprite;		//�X�v���C�g�B
	CVector3 g_spritePos = CVector3::Zero();	//�X�v���C�g�̍��W�B
	EnRenderMode renderMode = enRenderMode_Invalid;	//�����_�[���[�h
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
};

