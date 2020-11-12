#pragma once
//�eUI�����N���X�B
#include "ui/PlayerHPUI.h"
#include "itemui/ItemUI.h"
#include "ui/SoulUI.h"

class GameUI final : public IGameObject
{
public:
	GameUI();
	~GameUI();

	bool Start() override;
	void Update() override;

	/// <summary>
	/// �C���X�^���X�̎擾�B
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static GameUI* GetInstance()
	{
		return m_instance;
	}

private:
	static GameUI* m_instance;					//�C���X�^���X�B

private:
	void ScalingSelectCase();					//�I��g�̊g��k�������B
	void OnlyDelete();							//�S�폜�B

private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* r;							//�X�v���C�g�����_�[�B

	PlayerHPUI* m_playeHPUi;					//�v���C���[HPUI�B
	ItemUI*		m_itemUi;						//�A�C�e��UI�B
	SoulUI*		m_soulUi;						//��UI�B

	//�A�C�e���֘A
	int m_scalingCount = 0;										//�I��g�g��k���p�J�E���g
	CVector3 m_itemSelectFrameScale = { 0.7f,0.7f,0.7f };		//ZL,�I��g�g�嗦

	//���l����
	int m_soulNowNum = 0;			//���݂�HP���i�[
	int m_soulSpNum = 0;			//���݂�HP���i�[
};

