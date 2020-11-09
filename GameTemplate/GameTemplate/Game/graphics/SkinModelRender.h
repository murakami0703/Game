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
	/// �A�j���[�V�����̍Đ����H
	/// </summary>
	/// <returns>true	�A�j���[�V�������Đ����B</returns>
	/// <returns>false	�A�j���[�V�����͍Đ����Ă��Ȃ��B</returns>
	bool IsPlayingAnimation() const
	{
		return m_animation.IsPlaying();
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
	/// �V���G�b�g�`��t���O
	/// </summary>
	/// <param name="flag">true�Ȃ�`��</param>
	void SetSilhouette(bool flag)
	{
		m_silhouetteflag = flag;
	}
	/// <summary>
	/// �V���h�E�L���X�^�[�`��t���O
	/// </summary>
	/// <param name="flag">true�Ȃ�`��</param>
	void SetShadowCaster(bool flag)
	{
		m_shadowMapFlag = flag;
	}
	/// <summary>
	/// �V���h�E���V�[�o�[�̃t���O��ݒ�B
	/// </summary>
	/// <param name="flag"></param>
	void SetShadowReciever(bool flag);

	/// <summary>
	/// ���C�g�̐ݒ�B
	/// </summary>
	void SetLightColor(CVector4 color) {
		m_skinModel.SetLightColor(color);
	}

	/// <summary>
	/// a�l�̐ݒ�
	/// </summary>
	void SetAlpha(const float& alpha)
	{
		m_skinModel.SetAlpha(alpha);
	}
	/// <summary>
	/// a�l���擾
	/// </summary>
	float GetAlpha()
	{
		return m_skinModel.GetAlpha();
	}

	/// <summary>
	/// ���l��ψʂ�����
	/// </summary>
	/// <param name="delta">��Z����ψʂ������</param>
	void DeltaAlpha(float delta)
	{
		m_skinModel.DeltaAlpha(delta);
	}

	/// <summary>
	/// �@���}�b�v�̐ݒ�B
	/// </summary>
	void SetNormalMap(const wchar_t* filePath)
	{
		//�@���}�b�v���܂�
		DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), filePath, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_normalMapSRV
		);
		m_skinModel.SetNormalMap(g_normalMapSRV);
	}
	/// <summary>
	/// �X�؃L�����}�b�v�̐ݒ�B
	/// </summary>
	void SetSpecularMap(const wchar_t* filePath)
	{
		//�@���}�b�v���܂�
		DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), filePath, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_specularMapSRV
		);
		m_skinModel.SetSpecularMap(g_specularMapSRV);
	}
	/// <summary>
	/// �A���r�G���g�}�b�v�̐ݒ�B
	/// </summary>
	void SetAmbientMap(const wchar_t* filePath)
	{
		//�@���}�b�v���܂�
		DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(), filePath, 0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0,
		false, nullptr, &g_ambientMapSRV
		);
		m_skinModel.SetAmbientMap(g_ambientMapSRV);
	}

	bool Start();
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �`��B
	/// </summary>
	void Render();

 private:
	 std::wstring m_filepath;
	SkinModel					m_skinModel;						//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();			//���W
	CQuaternion m_rotation = CQuaternion().Identity();	//��]
	CVector3 m_scale = CVector3().One();			//�g�嗦�B
	AnimationClip*				m_animationClips = nullptr;			//�A�j���[�V�����N���b�v�B
	int							m_numAnimationClips = 0;			//�A�j���[�V�����N���b�v�̐��B
	Animation					m_animation;						//�A�j���[�V�����B
	bool m_shadowMapFlag = false;		//�V���h�E�}�b�v�`��t���O
	bool m_silhouetteflag = false;		//�V���G�b�g�`��t���O

	//�e��}�b�v�̐ݒ�B
	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;				//�@���}�b�v�B
	ID3D11ShaderResourceView* g_specularMapSRV = nullptr;			//�X�؃L�����}�b�v�B
	ID3D11ShaderResourceView* g_ambientMapSRV = nullptr;			//�A���r�G���g�}�b�v

};

