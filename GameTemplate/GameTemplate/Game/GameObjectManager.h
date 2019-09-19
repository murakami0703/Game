#pragma once
#include "IGameObject.h"
class GameObjectManager
{
public:
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̒ǉ��B
	/// </summary>
	template <class T>
	T* NewGameObject()
	{
		T* newObj = new T;
		m_goList.push_back(newObj);
		return newObj;
	}
	/// <summary>
	/// �Q�[���I�u�W�F�N�g�����X�g����폜����B
	/// </summary>
	/// <param name="go">�폜����Q�[���I�u�W�F�N�g</param>
	void DeleteGameObject(IGameObject* go) {
		//���X�g���猟�����āB����������폜�B
		//���X�g���猟�����āA����������폜����B
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				//�폜���N�G�X�g�𑗂�B
				go->RequestDelete();
				return;
			}
		}
	}
private:
	std::vector< IGameObject* > m_goList;
};
extern GameObjectManager g_goMgr;
