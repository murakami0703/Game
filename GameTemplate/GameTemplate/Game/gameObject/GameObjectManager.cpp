#include "stdafx.h"
#include "GameObjectManager.h"

//GameObjectManager�N���X�̃C���X�^���X�B
GameObjectManager* g_goMgr = nullptr;

void GameObjectManager::Start()
{
	//���C�������_�����O�^�[�Q�b�g�̏������B
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R8G8B8A8_UNORM
	);
	//���C���e�N�X�`���̏������B
	g_mainSprite.Init(
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
	isStartflag = true;
}

void GameObjectManager::Update()
{
	if (isStartflag == false) {
		Start();
	}
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
		g_mainSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
		g_camera2D.Update();

		//�V���h�E�}�b�v���X�V�B
		m_shadowMap.Update(
			{ 0.0f, 1000.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f }
		);
	}
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̕`��֐����ĂԁB
		{
			//�`��J�n�B
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
			PostRender();

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

	//��O�ɕ`����s���f�v�X�X�e���V���X�e�[�g��ݒ肷��B
	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(depthStencilState, 0);

	for (auto go : m_goList) {
		go->Render();
	}
}
/// <summary>
/// �|�X�g�����_�����O�B
/// </summary>
void GameObjectManager::PostRender()
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
	g_mainSprite.Draw();

	for (auto go : m_goList) {
		go->PostRender();
	}

	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();

}
