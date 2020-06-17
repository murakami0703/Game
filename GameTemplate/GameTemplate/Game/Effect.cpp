#include "stdafx.h"
#include "Effect.h"


Effect::Effect()
{

}

Effect::~Effect()
{
}
bool Effect::Start() {
	return true;
}

void Effect::Release()
{
	if (m_handle != -1) {
		g_graphicsEngine->GetEffectEngine().Stop(m_handle);
		m_handle = -1;
	}
}

void Effect::Play(const wchar_t* filePath)
{
	//int nameKey = UtilMakeHash(filePath);

	EffectEngine& ee = g_graphicsEngine->GetEffectEngine();
	if (m_effect == nullptr) {
		//���o�^�B
		m_effect = ee.CreateEffekseerEffect(filePath);
		if (m_effect == nullptr) {
			char message[256];
			sprintf(message, "�G�t�F�N�g�̃��[�h�Ɏ��s���܂����B%ls", filePath);
		}
	}
	m_handle = g_graphicsEngine->GetEffectEngine().Play(m_effect);
}
void Effect::Update()
{
	CMatrix mTrans, mRot, mScale, mBase;
	mTrans.MakeTranslation(m_position);
	mRot.MakeRotationFromQuaternion(m_rotation);
	mScale.MakeScaling(m_scale);
	mBase = mScale * mRot;
	mBase = mBase * mTrans;
	g_graphicsEngine->GetEffectEngine().GetEffekseerManager().SetBaseMatrix(m_handle, mBase);
	if (IsPlay() == false) {
		//�Đ�����������I���B
		g_goMgr->DeleteGameObject(this);
	}
}