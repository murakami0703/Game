#pragma once
class EffectManager
{
	static EffectManager* m_instance;
public:

	//�G�t�F�N�g���O
	enum Effect {
		Null,
		ItemGet, //�A�C�e�����莞�̃G�t�F�N�g
		spawn,//�o�����̃G�t�F�N�g
		star,//�ړ���ɏo�����5
		enemySpawn,//�G�������ۂ�ۂ�
		ItemSpawn, //�A�C�e�����o�����������I
		Bakuhatu, //�ǂ��[��
		Beam, //�r�[������
		BeamHassya, //�r�[������
		Gao,//�����[
	};

	EffectManager();
	~EffectManager();

	//����1���Đ�����G�t�F�N�g�i��ނ̓w�b�_�[�Ɂj
	//����2��position
	//����3��scale
	void EffectPlayer(Effect EF, CVector3 position, CVector3 scale);

	//�C���X�^���X�̎擾
	static EffectManager* EffectManager::GetInstance() {
		return m_instance;
	}

private:

	//�G�t�F�N�g�t�@�C����
	wchar_t DetaBase[10][30]{
		{ L"" },//Null�Ȃ̂ŉ����Ȃ�
		{ L"effect/Item.efk" },
		{ L"effect/spawn.efk" },
		{ L"effect/star.efk" },
		{ L"effect/enemySpawn.efk" },
		{ L"effect/itemSpawn.efk" },
		{ L"effect/bakuha.efk" },
		{ L"effect/beam.efk" },
		{ L"effect/beam_hassya.efk" },
		{ L"effect/gao.efk" },

	};

	CVector3 m_scale = CVector3::One();
	CVector3 m_position = CVector3::Zero();

	Effect m_stete = Null;		 //�G�t�F�N�g���
	wchar_t EF_Name[30] = { L"" };	//�G�t�F�N�g���ۊǗp
};

