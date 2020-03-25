#pragma once
#include "Font.h"
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
	void SetText(const wchar_t* text, CVector2 pos)
	{
		if (wcscmp(m_text.c_str(), text) != 0) {
			//�����񂪕ς�����B
			m_text = text;
		}
		m_position.x = pos.x;
		m_position.y = pos.y;
	}
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector2& pos)
	{
		m_position.x = pos.x;
		m_position.y = pos.y;
	}
	/// <summary>
	/// �t�H���g�̃J���[��ݒ�B
	/// </summary>
	/// <param name="color">�F</param>
	void SetColor(const CVector3& color)
	{
		m_color = color;
	}
	void SetAlpha(float alpha) {
		m_color.w = alpha;
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
		m_pivot.x = pivot.x;
		m_pivot.y = pivot.y;
	}
	/// <summary>
	/// �Q�[���t�H���g���擾
	/// </summary>
	/// <returns>�ӂ���ƂɁH</returns>
	Font* GetFont() {
		return &m_font;
	}

	/// <summary>
	/// ���b�Z�[�W���蒆�Ȃ�true��Ԃ�
	/// </summary>
	/// <returns>���b�Z�[�W����t���O</returns>
	bool GetMessageOkuriFlag() {
		return m_okuriFlag;
	}

	/// <summary>
	/// �e�L�X�g���艉�o
	/// </summary>
	/// <param name="text">�\������e�L�X�g</param>
	/// <param name="Interval">1�������Ƃ̃C���^�[�o��</param>
	void SetTextOkuri(const wchar_t* text, int Interval);

	/// <summary>
	/// �e�L�X�g�������u�ōŌ�܂ōs���܂�
	/// </summary>
	/// <remarks>
	/// m_okuriFlag�͂����ł͕ύX���ꂸ�AUpdate�̃e�L�X�g����I�������Ɉ�x����������܂�
	/// </remarks>
	void TextOkuriEnd() {
		m_textOkuri_NowLen = m_textOkuri_Len;
		m_textOkuri_Timer = m_textOkuri_Interval;
	}

private:
	Font m_font;
	std::wstring m_text;	//�e�L�X�g�B
	CVector2 m_position = CVector2::Zero();	//���W�B
	float m_rotation = 0.0f;		//��]�B
	float m_scale = 1.0f;			//�g�嗦�B
	CVector2 m_pivot;				//�s�{�b�g�B
	CVector4 m_color = CVector4::White();	//�J���[�B

	//���񂾂�\���V�X�e��
	wchar_t m_text_stock[256] = L"";			//!<�\���e�L�X�g�B
	int m_textOkuri_Interval = 0;				//!<�e�L�X�g����̃C���^�[�o���t���[��
	int m_textOkuri_Timer = 0;					//!<�e�L�X�g����^�C�}�[
	bool m_okuriFlag = false;					//!<���b�Z�[�W���菈���̃t���O
	int m_textOkuri_Len = 0;					//!<�\���e�L�X�g�̕�����
	int m_textOkuri_NowLen = 0;					//!<���݂̕�����

};

