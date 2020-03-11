#pragma once
/// <summary>
/// 3D���f����\������@�\��񋟂���N���X�B
/// </summary>
class SkinModelRender : public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="filePath">���[�h������cmo�t�@�C���̃t�@�C���p�X</param>
	/// <param name="animationClips">�A�j���[�V�����N���b�v�̔z��̐擪�A�h���X</param>
	/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐�</param>
	/// <param name="fbxUpAxis">fbx�̏����</param>
	void Init(const wchar_t* filePath, AnimationClip* animationClips = nullptr,int numAnimationClips = 0, EnFbxUpAxis fbxUpAxis = enFbxUpAxisZ);

	/// <summary>
	/// �A�j���[�V�����̍Đ��B
	/// </summary>
	/// <param name="animNo">�A�j���[�V�����N���b�v�̔ԍ��B</param>
	/// <param name="interpolateTime">�⊮����</param>
	void PlayAnimation(int animNo, float interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	/// <summary>
	/// �A�j���[�V�����̏������B
	/// </summary>
	/// <param name="animationClips">�A�j���[�V�����N���b�v�̔z��̐擪�A�h���X</param>
	/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐�</param>
	void InitAnimation(AnimationClip* animationClips, int numAnimationClips);

	/// <summary>
	/// �X�L�����f���擾�B
	/// </summary>
	/// <returns>�X�L�����f��</returns>
	SkinModel& GetSkinModel()
	{
		return m_skinModel;
	}

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	/// <param name="rotation">��]</param>
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// �g�嗦��ݒ�B
	/// </summary>
	/// <param name="scl">�g�嗦</param>
	void SetScale(const CVector3& scl)
	{
		m_scale = scl;
	}
	/// <summary>
	/// �g�嗦��ݒ�B
	/// </summary>
	/// <param name="scl">�g�嗦</param>
	void SetSilhouette(bool flag)
	{
		m_silhouetteflag = flag;
	}

	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �`��B
	/// </summary>
	void Render();

 private:
	CVector3 m_position;			//���W�B
	CQuaternion m_rotation;			//��]�B
	CVector3 m_scale = CVector3().One();			//�g�嗦�B
	AnimationClip*				m_animationClips = nullptr;			//�A�j���[�V�����N���b�v�B
	int							m_numAnimationClips = 0;			//�A�j���[�V�����N���b�v�̐��B
	SkinModel					m_skinModel;						//�X�L�����f���B
	Animation					m_animation;						//�A�j���[�V�����B

	bool m_silhouetteflag = false;
};

