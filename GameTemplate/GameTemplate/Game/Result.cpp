#include "stdafx.h"
#include "Result.h"

Result* Result::m_instance = nullptr;

Result::Result()
{
	if (m_instance != nullptr) {
			std::abort();//‚·‚Å‚Éo‚Ä‚¢‚é‚½‚ßƒNƒ‰ƒbƒVƒ…
		}
	m_instance = this;

	//‚Ó‚§‚ñ‚Æ
	m_font = g_goMgr->NewGameObject<FontRender>();
	const wchar_t* str = L"‚¨‚í‚è```````";
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
