#pragma once
#include "level/Level.h"
class LevelSet
{
	static LevelSet* m_instance;
public:
	LevelSet();
	~LevelSet();
	void LevelSetting();

	//�C���X�^���X�̎擾
	static LevelSet* LevelSet::GetInstance() {
		return m_instance;
	}

private:
	Level m_level;	//���x���f�[�^�B
};