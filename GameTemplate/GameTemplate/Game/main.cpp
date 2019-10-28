#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "level/Level.h"
#include "Sprite.h"
#include "Map.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "GameObjectManager.h"

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
	float aspect = 1280.0f / 720.0f;
	g_camera2D.SetViewVolumeHeight(300.0f);
	g_camera2D.SetViewVolumeWidth(300.0f * aspect);


	//�v���C���[
	Player* player = new Player;
	//�}�b�v
	Map map;
	//�Q�[���J����
	GameCamera Gcamera;
	Enemy enemy;
	//sprite
	g_sprite.Init(L"Assets/sprite/mikyan.dds", 240.0f, 240.0f);
	g_spritePos = { -200.0f,50.0f,0.0f };

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

	int renderMode = 0;	//�O�Ȃ�ʏ�`��A�P�Ȃ�V���G�b�g�`��B

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//��O�ɕ`����s���f�v�X�X�e���V���X�e�[�g��ݒ肷��B
		g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(depthStencilState, 0);
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();

		renderMode = 0;
		//�}�b�v�̕`��B
		map.Update();
		map.Draw(renderMode);
		//�G�̕`��ƍX�V�B
		enemy.Update(player);
		enemy.Draw(renderMode);

		//�V���G�b�g�`��
		renderMode = 1;
		//�v���C���[�̍X�V�B
		player->Update();
		//�v���C���[�̕`��B
		player->Draw(renderMode);
		//�ʏ�`��
		renderMode = 0;
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
};