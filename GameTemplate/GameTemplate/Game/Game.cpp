#include "stdafx.h"
#include "Game.h"

Camera2D g_camera2D;	//2D�J����

Game::Game()
{
	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	//2D�J�������������B
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	//�r���[�{�����[���̕��ƍ������w�肷��B
	float aspect = 1280.0f / 720.0f;
	g_camera2D.SetViewVolumeHeight(300.0f);
	g_camera2D.SetViewVolumeWidth(300.0f * aspect);


	//sprite
	g_sprite.Init(L"Assets/sprite/mikyan.dds", 240.0f, 240.0f);
	g_spritePos = { -200.0f,50.0f,0.0f };

}


Game::~Game()
{

}
void Game::Update()
{
	//�Q�[���p�b�h�̍X�V�B	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	player->Update();
	//�V���h�E�L���X�^�[��o�^�B
	m_shadowMap.RegistShadowCaster(player->GetPlayerSkinModel());
	m_shadowMap.RegistShadowCaster(map->GetMapSkinModel());
	//�V���h�E�}�b�v���X�V�B
	m_shadowMap.UpdateFromLightTarget(
		{ 1000.0f, 1000.0f, 1000.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
}


void Game::Render()
{

	//�����G���W���̍X�V�B
	//g_physics.Update();
	g_graphicsEngine->BegineRender();
	//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	g_graphicsEngine->GetD3DDeviceContext()->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);
	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	g_graphicsEngine->GetD3DDeviceContext()->RSGetViewports(&numViewport, &oldViewports);

	//�V���h�E�}�b�v�Ƀ����_�����O
	m_shadowMap.RenderToShadowMap();

	//���ɖ߂��B
	g_graphicsEngine->GetD3DDeviceContext()->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	g_graphicsEngine->GetD3DDeviceContext()->RSSetViewports(numViewport, &oldViewports);
	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
	
	///////////////////////////////////////////////
	//��������ʏ탌���_�����O�B
	///////////////////////////////////////////////

	renderMode = enRenderMode_Normal;
	//�}�b�v�̕`��B
	map->Update();
	map->Draw(renderMode);
	//�G�̕`��ƍX�V�B
	enemy.Update(player);
	enemy.Draw(renderMode);

	//�V���G�b�g�`��
	renderMode = enRenderMode_Silhouette;
	//�v���C���[�̍X�V�B
	player->Update();
	player->Draw(renderMode);

	//�ʏ�`��
	renderMode = enRenderMode_Normal;
	player->Draw(renderMode);


	//�Q�[���J�����̍X�V
	Gcamera.Update(player);

	//Sprite��Update�֐����Ăяo���B
	g_sprite.Update(g_spritePos, CQuaternion::Identity(), CVector3::One());
	//Sprite��Draw�֐����Ăяo���B
	g_sprite.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
	g_sprite.Draw();
	//�J�����̍X�V�B
	//g_camera3D.Update();
	g_camera2D.Update();


	//�`��I���B
	g_graphicsEngine->EndRender();

}
