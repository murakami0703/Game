#pragma once
class SoulManager : public IGameObject
{
	static SoulManager* m_instance;
public:
	SoulManager();
	~SoulManager();

	bool Start();
	//更新
	void Update();
	//魂の生成
	void SoulGenerated(CVector3 position);

	//インスタンスの取得
	static SoulManager* SoulManager::GetInstance() {
		return m_instance;
	}

};

