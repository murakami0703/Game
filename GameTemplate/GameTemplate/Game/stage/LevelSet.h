#pragma once
#include "level/Level.h"

class LevelSet : public IGameObject
{
	static LevelSet* m_instance;
public:
	LevelSet();
	~LevelSet();
	void LevelSetting();

	//インスタンスの取得
	static LevelSet* LevelSet::GetInstance() {
		return m_instance;
	}
	void Update();
	void Render();
private:
	/// <summary>
	/// レベル構築時に呼ばれる処理。
	/// </summary>
	/// <param name="objData"></param>
	bool OnPreBuildMapchip(LevelObjectData& objData);
	/// <summary>
	/// マップチップ構築後に呼ばれる処理。
	/// </summary>
	/// <returns></returns>
	void OnPostBuildMapChip(LevelObjectData& objData, MapChip& mapchip);
private:
	Level m_level;	//レベルデータ。
	SkinModel m_model;
	int m_enemyCount = 0;	//エネミーの数
};