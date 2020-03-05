#pragma once
#include "Anima.h"

class AnimaManeger
{
public:
	AnimaManeger();
	~AnimaManeger();

	void Update(Player* player);
	void Draw(EnRenderMode renderMode);

	void RegistAnima(Anima* ani)
	{
		m_animas.push_back(ani);
	}
	void DeleteAnima(Anima* ani)
	{
		//さようなら
		auto it = std::find(m_animas.begin(), m_animas.end(), ani);
		if (it != m_animas.end()) {
			m_animas.erase(it);
			delete ani;
		}
	}
	/// <summary>
	/// インスタンスの取得。
	/// </summary>
	/// <returns>インスタンス</returns>
	static AnimaManeger* GetInstance()
	{
		return m_instance;
	}
	
private:
	static AnimaManeger* m_instance;
	std::vector<Anima*> m_animas;	//エネミ用の動的配列

};

