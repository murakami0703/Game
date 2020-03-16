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

private:
	DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//�X�v���C�g�o�b�`�B
	DirectX::SpriteFont*	m_spriteFont = nullptr;		//�X�v���C�g�t�H���g�B

};

