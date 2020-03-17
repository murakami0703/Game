#pragma once

class FontRender : public IGameObject
{
public:
	FontRender();
	~FontRender();

	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �`��B
	/// </summary>
	void Render();
	void PostRender();

public:
	/// <summary>
	/// �t�H���g��ݒ�B
	/// </summary>
	void SetFont(DirectX::SpriteFont* font) {
		m_font.SetFont(font);
	}
	/// <summary>
	/// �e�L�X�g��ݒ�B
	/// </summary>
	void SetText(const wchar_t* text) {
		if (wcscmp(m_text.c_str(), text) != 0) {
			m_text = text;
		}
	}
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector2& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// �t�H���g�̃J���[��ݒ�B
	/// </summary>
	/// <param name="color">�F</param>
	void SetColor(const CVector3& color)
	{
		m_color = color;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	/// <param name="color">��]</param>
	void SetRotation(float rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// �g�嗦��ݒ�B
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(float scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// �s�{�b�g��ݒ�B
	/// </summary>
	/// <param name="pibot">�s�{�b�g</param>
	void SetPibot(const CVector2& pivot)
	{
		m_pivot = pivot;
	}

private:
	Font m_font;
	std::wstring m_text;	//�e�L�X�g�B
	CVector2 m_position = CVector2::Zero();	//���W�B
	float m_rotation = 0.0f;		//��]�B
	float m_scale = 1.0f;			//�g�嗦�B
	CVector2 m_pivot;				//�s�{�b�g�B
	CVector4 m_color = CVector4::White();	//�J���[�B

};

