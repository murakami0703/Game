#pragma once
//各UI処理クラス。
#include "ui/PlayerHPUI.h"
#include "itemui/ItemUI.h"
#include "ui/SoulUI.h"

class GameUI final : public IGameObject
{
public:
	GameUI();
	~GameUI();

	bool Start() override;
	void Update() override;

	/// <summary>
	/// インスタンスの取得。
	/// </summary>
	/// <returns>インスタンス</returns>
	static GameUI* GetInstance()
	{
		return m_instance;
	}

private:
	static GameUI* m_instance;					//インスタンス。

private:
	void ScalingSelectCase();					//選択枠の拡大縮小処理。
	void OnlyDelete();							//全削除。

private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* r;							//スプライトレンダー。

	PlayerHPUI* m_playeHPUi;					//プレイヤーHPUI。
	ItemUI*		m_itemUi;						//アイテムUI。
	SoulUI*		m_soulUi;						//魂UI。

	//アイテム関連
	int m_scalingCount = 0;										//選択枠拡大縮小用カウント
	CVector3 m_itemSelectFrameScale = { 0.7f,0.7f,0.7f };		//ZL,選択枠拡大率

	//魂獲得数
	int m_soulNowNum = 0;			//現在のHPを格納
	int m_soulSpNum = 0;			//現在のHPを格納
};

