#include "stdafx.h"
#include "Result.h"

Result* Result::m_instance = nullptr;

Result::Result()
{
	if (m_instance != nullptr) {
			std::abort();//すでに出ているためクラッシュ
		}
	m_instance = this;

	//ふぉんと
	m_font = g_goMgr->NewGameObject<FontRender>();
	const wchar_t* str = L"「あなただけのデッサン人形」 を作成しポーズを取らせよう！\nデザインドールは3D空間の人体モデルを自在に操るソフトウェアです。\n人物モデルのポーズ集 や 3Dモデルエクスポータ としても\nご利用いただけるソフトウェアです。";
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
