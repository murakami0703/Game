/*!
 * @brief	�A�j���[�V�����Đ��R���g���[���B
 */

#pragma once

class Skeleton;
class AnimationClip;
class Bone;
class Animation;

/*!
* @brief	�A�j���[�V�����̍Đ��R���g���[���B
* @details
*  ��̃A�j���[�V�����N���b�v�ɑ΂��ăA�j���[�V������i�߂āA���[�J���|�[�Y���v�Z���܂��B
*/
class AnimationPlayController{
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	AnimationPlayController()
	{
	}
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~AnimationPlayController()
	{
	}
	/*!
	*@brief	�������B
	*/
	void Init(Skeleton* skeleton, int footStepBoneNo);
	/*!
	* @brief	�A�j���[�V�����N���b�v�̕ύX�B
	*/
	void ChangeAnimationClip(AnimationClip* clip)
	{
		m_isFirst = true;
		m_animationClip = clip;
		m_currentKeyFrameNo = 0;
		m_time = 0.0f;
		m_isPlaying = true;
		m_freezeBoneTranslate = CVector3::Zero();
		//�A�j���[�V�����C�x���g�̔����t���O��S��false�ɂ���B
		auto& animEventArray = m_animationClip->GetAnimationEvent();
		for (auto i = 0; i < m_animationClip->GetNumAnimationEvent(); i++) {
			animEventArray[i].SetInvokedFlag(false);
		}

	}
	void SetInterpolateTime(float interpolateTime)
	{
		if (interpolateTime < 0.0f) {
			interpolateTime = 0.0f;
		}
		m_interpolateEndTime = interpolateTime;
		m_interpolateTime = 0.0f;
	}
	/*!
	*@brief	�⊮�����擾�B
	*/
	float GetInterpolateRate() const
	{
		if (m_interpolateEndTime <= 0.0f) {
			return 1.0f;
		}
		return min( 1.0f, m_interpolateTime / m_interpolateEndTime );
	}
	/*!
	* @brief	�A�j���[�V������i�߂�B
	*@param[in]	deltaTime		�A�j���[�V������i�߂鎞�ԁB
	*/
	void Update(float deltaTime, Animation* animation);
	/*!
	* @brief	���[�J���{�[���s����擾�B
	*/
	const std::vector<CMatrix>& GetBoneLocalMatrix() const
	{
		return m_boneMatrix;
	}
	AnimationClip* GetAnimClip() const
	{
		return m_animationClip;
	}
	/*!
	* @brief	�Đ����H
	*/
	bool IsPlaying() const
	{
		return m_isPlaying;
	}
	CVector3 GetDeltaValueFootstepBone() const
	{
		return m_deltaValueFootstepBoneOneFrame;
	}
	
private:
	/// <summary>
	/// �A�j���[�V�����C�x���g���N������B
	/// </summary>
	void InvokeAnimationEvent(Animation* animation);
	/*!
	*@brief	���[�v�Đ��J�n���鎞�̏����B
	*/
	void StartLoop();
	void UpdateBoneWorldMatrix(Bone& bone, const CMatrix& parentMatrix);

private:
	AnimationClip*		m_animationClip = nullptr;		//!<�A�j���[�V�����N���b�v�B
	int						m_currentKeyFrameNo = 0;		//!<���ݍĐ����̃L�[�t���[���ԍ��B
	float					m_time = 0.0f;
	std::vector<CMatrix>	m_boneMatrix;					//!<���̃R���g���[���ōĐ����̃A�j���[�V�����̃{�[���s��B
	float					m_interpolateTime;					//!<�⊮����
	float					m_interpolateEndTime;				//!<�⊮�I������
	bool					m_isPlaying = false;					//!<�Đ����H
	bool					m_isFirst = true;						//�Đ��B
	int m_footstepBoneNo = -1;								//footstep�{�[���̔ԍ��B-1�Ȃ�footstep���Ȃ��B
	Skeleton* m_skelton = nullptr;							// �X�P���g��
	CVector3 m_deltaValueFootstepBoneOneFrame = CVector3::Zero();	//footstep�{�[����1�t���[���ł̕ω���
	CVector3 m_freezeBoneTranslate = CVector3::Zero();						//�t���[�Y���Ă���{�[���̕��s�ړ��ʁB
	CVector3 m_deltaValueFootstepBone = CVector3::Zero();					//footstep�̈ړ��ʁB
};
