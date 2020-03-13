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
/// �X�V�O�ɌĂ΂��֐�
/// </summary>
bool SkinModelRender::Start()
{
	return true;
}
/// <summary>
/// �X�V
/// </summary>
void SkinModelRender::Update()
{
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

/// <summary>
/// �A�j���[�V�����̏������B
/// </summary>
void SkinModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips)
{
	m_animationClips = animationClips;
	m_numAnimationClips = numAnimationClips;
	if (m_animationClips != nullptr) {
		m_animation.Init(m_skinModel, m_animationClips, m_numAnimationClips);
	}
}