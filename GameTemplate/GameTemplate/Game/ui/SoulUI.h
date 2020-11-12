#pragma once
class SoulUI final : public IGameObject
{
public:
	SoulUI();
	~SoulUI();

	bool Start() override;
	void Update() override;

private:
	enum eSoulMoveState {
		SoulUI_Default,			//通常状態。(非表示）
		SoulUI_GetMove,			//魂獲得時所持バーの出現処理。
		SoulUI_SoulCount,		//魂の数をカウントする。
		SoulUI_FontBoundMove,	//魂獲得時フォントのカウントをバウンドさせる処理。
		SoulUI_Indicate,		//一定時間だけ表示状態のまま保つ。
		SoulUI_Return			//元の状態に戻す。
	};
private:

	void SoulUIDefault();				//通常状態。(非表示）
	void SoulUIGetMove();				//魂獲得時所持バーの出現処理。
	void SoulCount();					//魂の数をカウントする。
	void FontBoundMove();				//魂獲得時フォントのカウントをバウンドさせる処理。
	void SoulUIIndicate();				//一定時間だけ表示状態のまま保つ。
	void SoulUIReturn();				//元の状態に戻す。

private:
	std::vector<SpriteRender*> m_spriteRender;		//スプライトの動的配列
	SpriteRender* m_soulRender;						//スプライトレンダー。

	FontRender* m_soulFont;							//魂の数表記用フォント。
	wchar_t soulNum[MAX_PATH];						//魂カウントフォントテキスト。

	CVector2 m_fontPos = CVector2().Zero();
	eSoulMoveState m_soulUiState = SoulUI_Default;	//状態。
	bool bound = false;								//バウンド用フラグ。

	//Fout関係
	int m_soulNowNum = 0;							//現在の魂の数を格納

	int m_indicateTimer = 0;						//魂獲得UIの表示タイマー。単位:フレーム
};

