#include "stdafx.h"
#include "SkinModelRender.h"


SkinModelRender::SkinModelRender()
{
}


SkinModelRender::~SkinModelRender()
{
}

void SkinModelRender::Init(const wchar_t* filePath, AnimationClip* animationClips , int numAnimationClips , EnFbxUpAxis fbxUpAxis)
{
	m_skinModel.Init(filePath, fbxUpAxis);
	InitAnimation(animationClips, numAnimationClips);
}
/// <summary>
/// アニメーションの初期化。
/// </summary>
void SkinModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips)
{
	m_animationClips = animationClips;
	m_numAnimationClips = numAnimationClips;
	if (m_animationClips != nullptr) {
		m_animation.Init(m_skinModel, m_animationClips, m_numAnimationClips);
	}
}

void SkinModelRender::SetShadowReciever(bool flag)
{
	m_skinModel.SetShadowReciever(flag);
}

/// <summary>
/// 更新
/// </summary>
void SkinModelRender::Update()
{
	if (m_shadowMapFlag = true) {
		//trueならシャドウキャスターに登録。
		g_goMgr->GetShadowMap()->RegistShadowCaster(&m_skinModel);
	}
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_skinModel.Update();

}

void SkinModelRender::Render()
{
	m_skinModel.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		EnRenderMode::enRenderMode_Normal
	);
	if (m_silhouetteflag==true) {
		//シルエット描画します。
		m_skinModel.Draw(
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix(),
			EnRenderMode::enRenderMode_silhouette
		);

	}
}
void SkinModelRender::PostRender(){}


