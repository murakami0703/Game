#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "sprite/Sprite.h"
#include "Map.h"
#include "enemy/Enemy.h"
#include "GameCamera.h"
#include "gameObject/GameObjectManager.h"
#include "ShadowMap.h"
#include "RenderTarget.h"
#include "enemy/EnemyManeger.h"
#include "ItemManeger.h"
#include "Fade.h"
#include "Font.h"
#include "GameUI.h"
#include "GameData.h"
#include "Anima.h"
#include "AnimaManeger.h"

/// <summary>
/// �O���[�o���ϐ�
/// </summary>


Camera2D g_camera2D;	//2D�J����



/// ///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);
	//2D�J�������������B
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	//�r���[�{�����[���̕��ƍ������w�肷��B
	g_camera2D.SetViewVolumeHeight(FRAME_BUFFER_H);
	g_camera2D.SetViewVolumeWidth(FRAME_BUFFER_W);

	ShadowMap m_shadowMap;	//�V���h�E�}�b�v�B

	//�v���C���[
	Player* player = new Player;
	//�}�b�v
	Map* map = new Map;
	//�Q�[���J����
	GameCamera Gcamera;
	//�Q�[���f�[�^
	GameData* date = new GameData;
	//�G�l�~
	EnemyManager m_eneMane;
	AnimaManeger m_aniMane;

	/*{Enemy* enemy = new Enemy;
	enemy->SetPosition({ 150.0f,30.0f,200.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ -300.0f,30.0f,20.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 250.0f,30.0f,-150.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 150.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 190.0f,30.0f,-170.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 100.0f,30.0f,-250.0f });
	m_eneMane.RegistEnemy(enemy);


	}*/
	Enemy* enemy = new Enemy;
	enemy->SetPosition({ 150.0f,30.0f,200.0f });
	m_eneMane.RegistEnemy(enemy);
	Sprite g_Main;		//�X�v���C�g�B

	Sprite g_sprite;		//�X�v���C�g�B
	CVector3 g_spritePos = CVector3::Zero();	//�X�v���C�g�̍��W�B

	//����
	Fade fad;
	Font font;
	GameUI ui;
	//Effekseer�}�l�[�W���Ǘ��B
	Effekseer::Manager*	m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer*	m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_sampleEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;


	RenderTarget m_mainRenderTarget;		//���C�������_�����O�^�[�Q�b�g�B
	//���C�������_�����O�^�[�Q�b�g�̏������B
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);
	//���C���e�N�X�`���̏������B
	g_Main.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);


	//�����_���[���������B
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3D�f�o�C�X�B
		g_graphicsEngine->GetD3DDeviceContext(),	//D3D�f�o�C�X�R���e�L�X�g�B
		20000										//�|���̍ő吔�B
	);
	//�G�t�F�N�g�}�l�[�W�����������B
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());


	//sprite
	g_sprite.Init(L"Assets/sprite/test.dds", 240.0f, 240.0f);
	g_spritePos = { -200.0f,50.0f,0.0f };

	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�B
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	//�t���[���o�b�t�@�̂̃r���[�|�[�g
	D3D11_VIEWPORT oldViewports;

	//�[�x�X�e���V���X�e�[�g�B
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc = D3D11_COMPARISON_GREATER;
	desc.StencilEnable = false;
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//D3D�f�o�C�X���擾�B
	auto d3ddevice = g_graphicsEngine->GetD3DDevice();

	//�f�v�X�X�e���V���X�e�[�g���쐬�B
	ID3D11DepthStencilState* depthStencilState;
	d3ddevice->CreateDepthStencilState(&desc, &depthStencilState);

	//�T���v���̃G�t�F�N�g�����[�h����B
	m_sampleEffect = Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)L"Assets/effect/test.efk");
	//�G�t�F�N�g���Đ�����B
	m_playEffectHandle = m_effekseerManager->Play(m_sampleEffect, 0.0f, 0.0f, 0.0f);


	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{

		//�X�V����
		{
			//�Q�[���p�b�h�̍X�V�B	
			for (auto& pad : g_pad) {
				pad.Update();
			}
			//�����G���W���̍X�V�B
			g_physics.Update();

			if (m_eneMane.GetInstance()->DeadFlag() == true) {
				Anima* anima = new Anima;
				anima->SetPosition({ m_eneMane.GetPosition() });
				m_aniMane.RegistAnima(anima);
				m_eneMane.GetInstance()->EndFlag();
			}

			//�v���C���[�̍X�V�B
			player->Update();
			//�}�b�v�̕`��B
			map->Update();
			//�G�̕`��ƍX�V�B
			m_eneMane.Update(player);
			m_aniMane.Update(player);

			//�Q�[���J�����̍X�V
			Gcamera.Update(player);

			//Sprite��Update�֐����Ăяo���B
			g_sprite.Update(g_spritePos, CQuaternion::Identity(), CVector3::One());
			g_Main.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
			g_camera2D.Update();

			ui.Update();

			//Effekseer�J�����s���ݒ�B
			//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
			Effekseer::Matrix44 efCameraMat;
			g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
			Effekseer::Matrix44 efProjMat;
			g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
			//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
			m_effekseerRenderer->SetCameraMatrix(efCameraMat);
			m_effekseerRenderer->SetProjectionMatrix(efProjMat);
			//Effekseer���X�V�B
			m_effekseerManager->Update();


			//�t�[�h
			/*if (g_pad[0].IsTrigger(enButtonA)) {
				fad.SetSprite(g_sprite);
				fad.SetState(Fade::Fadein);
			}
			fad.Update();*/

			//�V���h�E�L���X�^�[��o�^�B
			m_shadowMap.RegistShadowCaster(player->GetPlayerSkinModel());
			m_shadowMap.RegistShadowCaster(map->GetMapSkinModel());
			//�V���h�E�}�b�v���X�V�B
			m_shadowMap.Update(
				{ 0.0f, 1000.0f, 0.0f },
				{ 0.0f, 0.0f, 0.0f }
			);

		}
		//�`�揈���̃u���b�N�B
		{
			//�`��J�n�B
			g_graphicsEngine->BegineRender();
			{
				// �v�������_�����O
				{
					//�V���h�E�}�b�v�ւ̕`��
					auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
					//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
					d3dDeviceContext->OMGetRenderTargets(
						1,
						&oldRenderTargetView,
						&oldDepthStencilView
					);
					//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
					unsigned int numViewport = 1;
					d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

					//�V���h�E�}�b�v�Ƀ����_�����O
					m_shadowMap.RenderToShadowMap();
				}
				// �t�H���[�h�����_�����O 
				{
					//���C���̃����_�����O�^�[�Q�b�g�ɐ؂�ւ���B
					auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
					ID3D11RenderTargetView* rtTbl[] = {
					m_mainRenderTarget.GetRenderTargetView()
					};
					//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
					d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_mainRenderTarget.GetDepthStensilView());
					if (&oldViewports != nullptr) {
						//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
						d3dDeviceContext->RSSetViewports(1, &oldViewports);
					}
					//���C�������_�����O�^�[�Q�b�g���N���A����B
					float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
					m_mainRenderTarget.ClearRenderTarget(clearColor);

					//��O�ɕ`����s���f�v�X�X�e���V���X�e�[�g��ݒ肷��B
					g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(depthStencilState, 0);

					map->Draw(enRenderMode_Normal);
					m_eneMane.Draw(enRenderMode_Normal);
					m_aniMane.Draw(enRenderMode_Normal);
					//�V���G�b�g�`��
					player->Draw(enRenderMode_silhouette);
					//�ʏ�`��
					player->Draw(enRenderMode_Normal);


				}
				// �|�X�g�����_�����O
				{
					//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
					auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
					//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
					ID3D11RenderTargetView* rtTbl[] = {
					oldRenderTargetView
					};
					d3dDeviceContext->OMSetRenderTargets(1, rtTbl, oldDepthStencilView);
					if (&oldViewports != nullptr) {
						//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
						d3dDeviceContext->RSSetViewports(1, &oldViewports);
					}

					g_Main.Draw();

					float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
					//�����������̃u�����h�X�e�[�g��ݒ肷��B
					d3dDeviceContext->OMSetBlendState(
						g_sprite.GetID3D11BlendState(),	//�ݒ肷��u�����f�B���O�X�e�[�g
						blendFactor,				//�u�����f�B���O�t�@�N�^�[�B�C�ɂ��Ȃ��Ă悢
						0xffffffff					//�T���v�����O�}�X�N�B�C�ɂ��Ȃ��Ă悢�B
					);

					//Sprite��Draw�֐����Ăяo���B
					/*g_sprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					g_sprite.Draw();*/
					ui.Draw();
					//�G�t�F�N�g�͕s�����I�u�W�F�N�g��`�悵����ŕ`�悷��B
					m_effekseerRenderer->BeginRendering();
					m_effekseerManager->Draw();
					m_effekseerRenderer->EndRendering();


					//�J�����̍X�V�B
					//g_camera3D.Update();
					//�����o���Ă�
					//font.Draw(L"");

					//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
					oldRenderTargetView->Release();
					oldDepthStencilView->Release();
				}
				//�`��I���B
				g_graphicsEngine->EndRender();
			}
		}
	}
};
