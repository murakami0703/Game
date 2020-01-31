#pragma once
class GameData
{
	/// <summary>
	/// �f�[�^�B
	/// </summary>
public:
	GameData();
	~GameData();

	//�̗͎擾
	float GameData::GetHitPoint() {
		return HP;
	}
	//���͎擾
	float GameData::GetMagicPoint() {
		return MP;
	}
	//�U���͎擾
	float GameData::GetATK() {
		return ATK;
	}
	//�ő�̗͎擾
	float GameData::GetMAXHitPoint() {
		return MAXHP;
	}
	//�ő喂�͎擾
	float GameData::GetMAXMagicPoint() {
		return MAXMP;
	}

	//�����ɐݒ肵���l��̗͂ɉ��Z����@���̐���ݒ肵���猸������
	void  GameData::tiryokugennsyou(int x) {
		HP += x;
		if (HP < 0) {
			HP = 0;
		}
		if (MAXHP < HP) {
			HP = MAXHP;
		}
	}

	/// <summary>
	/// �C���X�^���X�̎擾�B
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static GameData* GetInstance()
	{
		return m_instance;
	}

private:
	static GameData* m_instance;

	float HP = 3.0f;	//�f�t�H���gHP
	const float MAXHP = 12.0f;	//�ő�HP
	float MP = 50.0f;	//�f�t�H���gMP
	const float MAXMP = 400.0f;	//�ő�MP

	float ATK = 30.0f;	//��b�U����

	//���܂���
	float Soul = 0.0f;	//�G������Ⴆ�鍰
	int BigSoul = 0;	//�{�X����Ⴆ�鍰

};

