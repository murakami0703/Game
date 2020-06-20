#pragma once
class EffectManager : public IGameObject
{
	static EffectManager* m_instance;
public:

	//�G�t�F�N�g���O
	enum EffectName {
		Null,
		test, //�A�C�e�����莞�̃G�t�F�N�g
		Bat_Attack, //�A�C�e�����莞�̃G�t�F�N�g
		Bat_memai, //�A�C�e�����莞�̃G�t�F�N�g
	};

	EffectManager();
	~EffectManager();

	//����1���Đ�����G�t�F�N�g�i��ނ̓w�b�_�[�Ɂj
	//����2��position
	//����3��scale
	void EffectPlayer(EffectName EF, CVector3 position, CVector3 scale);

	//�C���X�^���X�̎擾
	static EffectManager* EffectManager::GetInstance() {
		return m_instance;
	}

	bool Start();
	void Update();
private:

	//�G�t�F�N�g�t�@�C����
	wchar_t DetaBase[17][40]{
		{ L"" },//Null�Ȃ̂ŉ����Ȃ�
		{ L"Assets/effect/test.efk" },
		{ L"Assets/effect/bat_attackEfk.efk" },
		{ L"Assets/effect/bat_vertigo.efk" }
	};

	CVector3 m_scale = CVector3::One();
	CVector3 m_position = CVector3::Zero();

	EffectName m_stete = Null;		 //�G�t�F�N�g���
	wchar_t EF_Name[30] = { L"" };	//�G�t�F�N�g���ۊǗp
};

