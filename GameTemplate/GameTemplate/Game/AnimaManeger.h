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
		//���悤�Ȃ�
		auto it = std::find(m_animas.begin(), m_animas.end(), ani);
		if (it != m_animas.end()) {
			m_animas.erase(it);
			delete ani;
		}
	}
	/// <summary>
	/// �C���X�^���X�̎擾�B
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static AnimaManeger* GetInstance()
	{
		return m_instance;
	}
	
private:
	static AnimaManeger* m_instance;
	std::vector<Anima*> m_animas;	//�G�l�~�p�̓��I�z��

};

