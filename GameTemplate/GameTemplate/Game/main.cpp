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

/// <summary>
/// �O���[�o���ϐ�
/// </summary>


Camera2D g_camera2D;	//2D�J����

Sprite g_sprite;		//�X�v���C�g�B
CVector3 g_spritePos = CVector3::Zero();	//�X�v���C�g�̍��W�B



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
	EnemyManager m_eneMane;
	Enemy* enemy = new Enemy;
	enemy->SetPosition({ 150.0f,30.0f,200.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ -300.0f,30.0f,20.0f });
	m_eneMane.RegistEnemy(enemy);

	enemy = new Enemy;
	enemy->SetPosition({ 150.0f,30.0f,-150.0f });
	m_eneMane.RegistEnemy(enemy);
	
	/*Enemy enemy;
	enemy.SetPosition({ 150.0f,30.0f,200.0f });
	Enemy* enemy1 = new Enemy;
	enemy1->SetPosition({ -300.0f,30.0f,20.0f });
	Enemy enemy2;
	enemy2.SetPosition({ 150.0f,30.0f,-150.0f });
	*/
	Sprite g_Main;		//�X�v���C�g�B

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

	//sprite
	g_sprite.Init(L"Assets/sprite/mikyan.dds", 240.0f, 240.0f);
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

			//�v���C���[�̍X�V�B
			player->Update();
			//�}�b�v�̕`��B
			map->Update();
			//�G�̕`��ƍX�V�B
			m_eneMane.Update(player);

			//�Q�[���J�����̍X�V
			Gcamera.Update(player);

			//Sprite��Update�֐����Ăяo���B
			g_sprite.Update(g_spritePos, CQuaternion::Identity(), CVector3::One());
			g_Main.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
			g_camera2D.Update();

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

					//Sprite��Draw�֐����Ăяo���B
					g_sprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					
					g_sprite.Draw();
					//�J�����̍X�V�B
					//g_camera3D.Update();

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
