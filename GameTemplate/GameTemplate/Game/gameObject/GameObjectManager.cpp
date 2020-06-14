#include "stdafx.h"
#include "GameObjectManager.h"
#include "Player.h"

//GameObjectManager�N���X�̃C���X�^���X�B
GameObjectManager* g_goMgr = nullptr;

//�J�������������B
void GameObjectManager::Init()
{
	//���C�������_�����O�^�[�Q�b�g�̍쐬�B
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	//���C���e�N�X�`���̏������B
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	//�[�x�X�e���V���X�e�[�g�B
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
	d3ddevice->CreateDepthStencilState(&desc, &depthStencilState);
}

void GameObjectManager::Update()
{
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�֐����ĂԁB
	{
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();

		for (auto go : m_goList) {
			go->Update();
		}
		m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
		g_camera2D.Update();

		//�V���h�E�}�b�v���X�V�B
		CVector3 m_playerPos = Player::GetInstance()->GetPosition();
		m_shadowMap.Update(
			{ m_playerPos.x + 400.0f,  (m_playerPos.y + 500.0f),  m_playerPos.z + 200.0f},
			{ m_playerPos.x,  m_playerPos.y ,  m_playerPos.z }
		);

		g_graphicsEngine->GetEffectEngine().Update();
	}
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̕`��֐����ĂԁB
	{
			//�`��J�n�B
			//��O�ɕ`����s���f�v�X�X�e���V���X�e�[�g��ݒ肷��B
			g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(depthStencilState, 0);
			g_graphicsEngine->BegineRender();

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

			// �v�������_�����O�B
			PreRender();
			// �t�H���[�h�����_�����O�B
			ForwordRender();
			// �|�X�g�����_�����O�B
			Post2DRender();

			//�`��I���B
			g_graphicsEngine->EndRender();
	}
	//�S�ẴQ�[���I�u�W�F�N�g��1�t���[�����̏������I����Ă���A�폜����B
	for (auto it = m_goList.begin(); it != m_goList.end();) {
		if ((*it)->IsRequestDelete()) {
			//�폜���N�G�X�g���󂯂Ă���̂ō폜�B
			delete* it;
			it = m_goList.erase(it);
		}
		else {
			//���N�G�X�g���󂯂Ă��Ȃ��B
			it++;
		}
	}
}
/// <summary>
/// �v�������_�����O�B
/// </summary>
void GameObjectManager::PreRender()
{
	//�V���h�E�}�b�v�Ƀ����_�����O
	m_shadowMap.RenderToShadowMap();
}
/// <summary>
/// �t�H���[�h�����_�����O�B
/// </summary>
void GameObjectManager::ForwordRender()
{
	// �t�H���[�h�����_�����O�B
	//���C���̃����_�����O�^�[�Q�b�g�ɐ؂�ւ���B
	g_graphicsEngine->ChangeRenderTarget(&m_mainRenderTarget, &oldViewports);

	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);


	for (auto go : m_goList) {
		go->Render();
	}
}
/// <summary>
/// �|�X�g�����_�����O�B
/// </summary>
void GameObjectManager::Post2DRender()
{
	// �|�X�g�����_�����O�B
	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
		//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂��B
	g_graphicsEngine->ChangeRenderTarget(
		oldRenderTargetView,
		oldDepthStencilView,
		&oldViewports
	);
	//2D�`��
	m_copyMainRtToFrameBufferSprite.Draw();

	for (auto go : m_goList) {
		go->PostRender();
	}
	g_graphicsEngine->GetEffectEngine().EffektRender();


	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();

}
