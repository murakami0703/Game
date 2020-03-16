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
	void PostRender();

private:
	Level m_level;	//レベルデータ。
};