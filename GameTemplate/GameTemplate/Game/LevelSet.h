#pragma once
#include "level/Level.h"

class LevelSet : public IGameObject
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
	void Update();
	void Render();
private:
	/// <summary>
	/// ���x���\�z���ɌĂ΂�鏈���B
	/// </summary>
	/// <param name="objData"></param>
	bool OnPreBuildMapchip(LevelObjectData& objData);
	/// <summary>
	/// �}�b�v�`�b�v�\�z��ɌĂ΂�鏈���B
	/// </summary>
	/// <returns></returns>
	void OnPostBuildMapChip(LevelObjectData& objData, MapChip& mapchip);
private:
	Level m_level;	//���x���f�[�^�B
	SkinModel m_model;
	int m_enemyCount = 0;	//�G�l�~�[�̐�
};