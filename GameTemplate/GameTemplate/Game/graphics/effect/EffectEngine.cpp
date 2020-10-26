#include "stdafx.h"
#include "graphics/effect/EffectEngine.h"


EffectEngine::EffectEngine()
{
}

EffectEngine::~EffectEngine()
{
	if (m_effekseerManager != nullptr) {
		m_effekseerManager->Destroy();

	}
	if (m_effekseerRenderer != nullptr) {
		m_effekseerRenderer->Destroy();
	}
	if (m_effekseerManager2D != nullptr) {
		m_effekseerManager2D->Destroy();

	}
	if (m_effekseerRenderer2D != nullptr) {
		m_effekseerRenderer2D->Destroy();
	}

}
Effekseer::Effect* EffectEngine::CreateEffekseerEffect(const wchar_t* filePath)
{
	return Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)filePath);
}
Effekseer::Handle EffectEngine::Play(Effekseer::Effect* effect, CVector3 pos)
{
	return m_effekseerManager->Play(effect, pos.x, pos.y, pos.z);
}
void EffectEngine::Stop(Effekseer::Handle handle)
{
	m_effekseerManager->StopEffect(handle);
}

void EffectEngine::InitEffekseer()
{
	//Effekseer�̏������B
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

}
void EffectEngine::Update()
{
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

}
void EffectEngine::EffektRender()
{
	//�G�t�F�N�g�͕s�����I�u�W�F�N�g��`�悵����ŕ`�悷��B
	m_effekseerRenderer->BeginRendering();
	m_effekseerManager->Draw();
	m_effekseerRenderer->EndRendering();

}


/////////////////////////2D��Ԃɕ`��///////////////////////////////////////
Effekseer::Effect* EffectEngine::CreateEffekseerEffect2D(const wchar_t* filePath)
{
	return Effekseer::Effect::Create(m_effekseerManager2D, (const EFK_CHAR*)filePath);
}
Effekseer::Handle EffectEngine::Play2D(Effekseer::Effect* effect, CVector3 pos)
{
	return m_effekseerManager2D->Play(effect, pos.x, pos.y, pos.z);
}
void EffectEngine::Stop2D(Effekseer::Handle handle)
{
	m_effekseerManager2D->StopEffect(handle);
}

void EffectEngine::InitEffekseer2D()
{
	//Effekseer�̏������B
	//�����_���[���������B
	m_effekseerRenderer2D = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3D�f�o�C�X�B
		g_graphicsEngine->GetD3DDeviceContext(),	//D3D�f�o�C�X�R���e�L�X�g�B
		20000										//�|���̍ő吔�B
	);
	//�G�t�F�N�g�}�l�[�W�����������B
	m_effekseerManager2D = Effekseer::Manager::Create(10000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	m_effekseerManager2D->SetSpriteRenderer(m_effekseerRenderer2D->CreateSpriteRenderer());
	m_effekseerManager2D->SetRibbonRenderer(m_effekseerRenderer2D->CreateRibbonRenderer());
	m_effekseerManager2D->SetRingRenderer(m_effekseerRenderer2D->CreateRingRenderer());
	m_effekseerManager2D->SetTrackRenderer(m_effekseerRenderer2D->CreateTrackRenderer());
	m_effekseerManager2D->SetModelRenderer(m_effekseerRenderer2D->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	m_effekseerManager2D->SetTextureLoader(m_effekseerRenderer2D->CreateTextureLoader());
	m_effekseerManager2D->SetModelLoader(m_effekseerRenderer2D->CreateModelLoader());

}
void EffectEngine::Update2D()
{
	//Effekseer�J�����s���ݒ�B
	//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
	Effekseer::Matrix44 efCameraMat;
	g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
	Effekseer::Matrix44 efProjMat;
	g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
	//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
	m_effekseerRenderer2D->SetCameraMatrix(efCameraMat);
	m_effekseerRenderer2D->SetProjectionMatrix(efProjMat);
	//Effekseer���X�V�B
	m_effekseerManager2D->Update();

}
void EffectEngine::EffektRender2D()
{
	//�G�t�F�N�g�͕s�����I�u�W�F�N�g��`�悵����ŕ`�悷��B
	m_effekseerRenderer2D->BeginRendering();
	m_effekseerManager2D->Draw();
	m_effekseerRenderer2D->EndRendering();
}