#pragma once

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
	static GameUI* m_instance;

private:
	void ScalingSelectCase();					//選択枠の拡大縮小。
	void OnlyDelete();							//全削除。

private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* r;							//スプライトレンダー。

	//アイテム関連
	int m_scalingCount = 0;								//選択枠拡大縮小用カウント
	CVector3 m_itemSelectFrameScale = { 0.7f,0.7f,0.7f };		//ZL,選択枠拡大率

	//魂獲得数
	int m_soulNowNum = 0;			//現在のHPを格納
	int m_soulSpNum = 0;			//現在のHPを格納
};

