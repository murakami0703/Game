/*!
 * @brief	�A�j���[�V�����Đ��R���g���[���B
 */

#include "stdafx.h"
#include "graphics/animation/AnimationPlayController.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/skeleton.h"


	
	
void AnimationPlayController::Init(Skeleton* skeleton, int footStepBoneNo)
{
	m_footstepBoneNo = footStepBoneNo;
	int numBones = skeleton->GetNumBones();
	//�{�[���s����o�V�b�Ɗm�ہB
	m_boneMatrix.resize(numBones);
	m_skelton = skeleton;
}
	
void AnimationPlayController::InvokeAnimationEvent(Animation* animation)
{
	auto& animEventArray = m_animationClip->GetAnimationEvent();
	for (auto i = 0; i < m_animationClip->GetNumAnimationEvent(); i++) {
		if (m_time > animEventArray[i].GetInvokeTime()
			&& animEventArray[i].IsInvoked() == false) {
			//�A�j���[�V�����̋N�����Ԃ��߂��Ă��邩�A�C�x���g���܂��N�����Ă��Ȃ��B
			animation->NotifyAnimationEventToListener(
				m_animationClip->GetName(), animEventArray[i].GetEventName()
			);
			animEventArray[i].SetInvokedFlag(true);
		}
	}
}
	
void AnimationPlayController::StartLoop()
{
	m_currentKeyFrameNo = 0;
	m_time = 0.0f;
	//�A�j���[�V�����C�x���g��S�Ė������ɂ���B
	auto& animEventArray = m_animationClip->GetAnimationEvent();
	for (auto i = 0; i < m_animationClip->GetNumAnimationEvent(); i++) {
		animEventArray[i].SetInvokedFlag(false);
	}
}
void AnimationPlayController::UpdateBoneWorldMatrix(Bone& bone, const CMatrix& parentMatrix)
{
	//���[���h�s����v�Z����B
	auto& mBoneWorld = m_boneMatrix[bone.GetNo()];
	CMatrix localMatrix = m_boneMatrix[bone.GetNo()];
	//�e�̍s��ƃ��[�J���s�����Z���āA���[���h�s����v�Z����B
	mBoneWorld.Mul(localMatrix, parentMatrix);
	
	//�q���̃��[���h�s����v�Z����B
	std::vector<Bone*>& children = bone.GetChildren();
	for (int childNo = 0; childNo < children.size(); childNo++) {
		//���̍��̃��[���h�s���UpdateBoneWorldMatrix�ɓn���āA����Ɏq���̃��[���h�s����v�Z����B
		UpdateBoneWorldMatrix(*children[childNo], mBoneWorld);
	}
}
void AnimationPlayController::Update(float deltaTime, Animation* animation)
{
	if(m_animationClip == nullptr){
		
		return ;
	}
	const auto& topBoneKeyFrameList = m_animationClip->GetTopBoneKeyFrameList();
	m_time += deltaTime;

	//�A�j���[�V�����C�x���g�̔���
	InvokeAnimationEvent(animation);
	//�⊮���Ԃ��i�߂Ă����B
	m_interpolateTime = min(1.0f, m_interpolateTime + deltaTime);
	while (true) {
		if (m_currentKeyFrameNo >= (int)topBoneKeyFrameList.size()) {
			//�I�[�܂ōs�����B
			if (m_animationClip->IsLoop()) {
				//���[�v�B
				StartLoop();
			}
			else {
				//�����V���b�g�Đ��B
				m_currentKeyFrameNo--;
				m_isPlaying = false;	//�Đ��I���B
			}
			break;
		}
		if (topBoneKeyFrameList.at(m_currentKeyFrameNo)->time >= m_time) {
			//�I���B
			break;
		}
		//���ցB
		m_currentKeyFrameNo++;
	}
	//�{�[���s����v�Z���Ă����B
	const auto& keyFramePtrListArray = m_animationClip->GetKeyFramePtrListArray();
	for (const auto& keyFrameList : keyFramePtrListArray) {
		if (keyFrameList.size() == 0) {
			continue;
		}
		//���ݍĐ����̃L�[�t���[��������Ă���B
		Keyframe* keyframe = keyFrameList.at(m_currentKeyFrameNo);
		if (keyframe->boneIndex < m_boneMatrix.size()) {
			m_boneMatrix[keyframe->boneIndex] = keyframe->transform;
		}
		else {
#ifdef _DEBUG			
			MessageBox(NULL, "AnimationPlayController::Update : ���݂��Ȃ��{�[���ɒl�������������Ƃ��Ă��܂��B���̂悤�Ȍ������l�����܂��B\n"
				"�@ tka�t�@�C�����o�͂��鎞�ɁA�I���������[�g�{�[�����X�P���g���̃��[�g�{�[���ƈقȂ��Ă���B\n"
				"�A �قȂ�X�P���g���̃A�j���[�V�����N���b�v���g���Ă���B\n"
				"������xtka�t�@�C�����o�͂��Ȃ����Ă��������B", "error", MB_OK);
			std::abort();
#endif
		}
	}
	//�X�P���g����Ԃ̍s����v�Z����B
	int numBone = m_skelton->GetNumBones();
	for (int boneNo = 0; boneNo < numBone; boneNo++) {
		//�e�̍�����������B
		auto bone = m_skelton->GetBone(boneNo);
		if (bone->GetParentId() != -1) {
			continue;
		}
		UpdateBoneWorldMatrix(*bone, CMatrix::Identity());
	}

	for (int boneNo = 0; boneNo < numBone; boneNo++) {
		auto bone = m_skelton->GetBone(boneNo);
		if (m_footstepBoneNo == bone->GetNo()) {
			
			auto deltaValueFootStepBoneLastFrame = m_deltaValueFootstepBone;
			auto mat = m_boneMatrix[bone->GetNo()];

			m_deltaValueFootstepBone.x = mat.m[3][0];
			m_deltaValueFootstepBone.y = mat.m[3][1];
			m_deltaValueFootstepBone.z = mat.m[3][2];

			if (m_isFirst == true) {
				m_deltaValueFootstepBoneOneFrame = CVector3::Zero();
				m_isFirst = false;
			}
			else {
				m_deltaValueFootstepBoneOneFrame = m_deltaValueFootstepBone - deltaValueFootStepBoneLastFrame;
			}
		}
	}
	//footstep�{�[����xz���ʂł̈ړ��ʂ����Z�B
	for (int boneNo = 0; boneNo < numBone; boneNo++) {
		auto bone = m_skelton->GetBone(boneNo);
		m_boneMatrix[bone->GetNo()].m[3][0] -= m_deltaValueFootstepBone.x;
		m_boneMatrix[bone->GetNo()].m[3][1] -= m_deltaValueFootstepBone.y;
		m_boneMatrix[bone->GetNo()].m[3][2] -= m_deltaValueFootstepBone.z;
	}
}

