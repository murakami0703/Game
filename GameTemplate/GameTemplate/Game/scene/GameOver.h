#pragma once
#include "SpriteIActor.h"

class GameOver : public SpriteIActor
{
public:
	GameOver();
	~GameOver();

	bool Start();
	void Update();

private:

	enum eState {
		BackGD_Dark,			//ゲームシーンを灰色に。
		GameOver_Set,			//GAMEOVERの文字出す。
		SelectButton_Set,		//選択ボタンの表示。
		Button_Select,			//ボタン選択。
		Scene_Switching			//シーン切り替え。
	};

	//選択ボタン
	enum EButton {
		Button_Continuity,
		Button_Exit
	};

private:

	void BackGDDark();			//ゲームシーンを灰色に。
	void GameOverSet();			//GAMEOVERの文字出す。
	void SelectButtonSet();		//選択ボタンの表示。
	void ButtonSelect();		//ボタン選択。
	void SceneSwitching();		//シーン切り替え。

	void Continuity();			//コンティニュー。
	void Exit();				//終わり。
private:
	std::vector<SpriteRender*> m_spriteRenderArray;		//スプライトの動的配列

	eState m_state = BackGD_Dark;					//状態。
	EButton m_buttonState = Button_Continuity;		//Buttonの選択状態。

	bool m_bound = false;				//バウンド判定。

	float m_mulColor = 1.0f;			//BGの乗算カラー
	
	int m_buttonActiveTimer = 0;		//ボタンを表示させるときに使うタイマー。
};

