#include "stdafx.h"
#include "Result.h"

Result* Result::m_instance = nullptr;

Result::Result()
{
	if (m_instance != nullptr) {
			std::abort();//���łɏo�Ă��邽�߃N���b�V��
		}
	m_instance = this;

	//�ӂ����
	m_font = g_goMgr->NewGameObject<FontRender>();
	const wchar_t* str = L"�u���Ȃ������̃f�b�T���l�`�v ���쐬���|�[�Y����点�悤�I\n�f�U�C���h�[����3D��Ԃ̐l�̃��f�������݂ɑ���\�t�g�E�F�A�ł��B\n�l�����f���̃|�[�Y�W �� 3D���f���G�N�X�|�[�^ �Ƃ��Ă�\n�����p����������\�t�g�E�F�A�ł��B";
	m_font->SetText(str);
	m_font->SetPosition({ -500.0f,0.0f });

	m_font->SetPivot({ 0.2f,0.2f });
	
}
Result::~Result()
{
	m_instance = nullptr;

}
void Result::Update()
{

}
void Result::Render()
{
}

void Result::PostRender() {}
