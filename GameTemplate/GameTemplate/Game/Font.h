#pragma once
class Font
{
	/// <summary>
	/// �t�H���g
	/// </summary>
public:
	Font();
	~Font();
	/// <summary>
	/// �t�H���g��ݒ�B
	/// </summary>
	/// <param name="font">�����ւ������t�H���g</param>
	void SetFont(DirectX::SpriteFont* font) {
		m_spriteFont = font;
	}
	//�`��J�n�B
	void Begin();
	//�`��I���B�B
	void End();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="text">�\���������e�L�X�g</param>
	/// <param name="position">���W</param>
	/// <param name="color">�J���[</param>
	/// <param name="rotation">��]</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="pivot">�s�{�b�g</param>
	void Draw(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color = CVector4::White(),
		float rotation = 0.0f,
		float scale = 1.0f,
		CVector2 pivot = { 0.5f, 0.5f }
	);
	/*!
	*@brief	�e�̃p�����[�^��ݒ�B
	*@param[in]	isDrawShadow		�e��`���H
	*@param[in]	shadowOffset		�e��`���Ƃ��̃s�N�Z���̃I�t�Z�b�g�ʁB
	*@param[in]	shadowColor			�e�̐F�B
	*/
	void SetShadowParam(bool isDrawShadow, float shadowOffset, const CVector4& shadowColor = { 0.2f,0.2f,0.2f,1.0f })
	{
		m_isDrawShadow = isDrawShadow;
		m_shadowOffset = shadowOffset;
		m_shadowColor = shadowColor;
	}

private:
	void InitTranslucentBlendState();
	ID3D11Buffer* m_cb = nullptr;		//�萔�o�b�t�@
	ID3D11BlendState* m_translucentBlendState = nullptr;	//�����������p�̃u�����h�X�e�[�g�B

	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//�X�v���C�g�o�b�`�B
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//�X�v���C�g�t�H���g�B

	const CVector4 ShadowColorDef = { 1.0f,1.0f,1.0f,1.0f };	//�e�̏����F

	bool m_isDrawShadow = false;						//!<�e�������H
	float m_shadowOffset = 0.0f;						//!<�e�������Ƃ��̃s�N�Z���̃I�t�Z�b�g�ʁB
	CVector4 m_shadowColor = ShadowColorDef;			//!<�e�̐F�B
	CMatrix m_scaleMat;

	ID3D11DepthStencilState*	m_depthStencilStateBackup = nullptr;	//!<���݂̃f�v�X�X�e���V���X�e�[�g�B
	ID3D11RasterizerState*		m_rasterrizerStateBackup = nullptr;		//!<���݂̃��X�^���C�U�X�e�[�g�B
	ID3D11BlendState*			m_blendStateBackup = nullptr;			//!<���݂̃u�����h�X�e�[�g�B

};

