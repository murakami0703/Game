#pragma once

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
	static GameUI* m_instance;

private:
	void ScalingSelectCase();					//�I��g�̊g��k���B
	void OnlyDelete();							//�S�폜�B

private:

	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* r;							//�X�v���C�g�����_�[�B

	//�A�C�e���֘A
	int m_scalingCount = 0;								//�I��g�g��k���p�J�E���g

	//HP�֘A
	CVector3 m_hpPos = { -600.0f,330.0f,0.0f };		//HP�̌Œ���W
	float m_setHP = 0.0f;		//�ŏ���HP��
	float m_nowHp = 0.0f;			//���݂�HP���i�[

	int m_spriteNum = 8;			//�Q�[���J�n����sprite�̐����i�[�B
	CVector3 m_itemZSCScale = { 0.7f,0.7f,0.7f };		//ZL,�I��g�g�嗦

	//���l����
	int m_soulNowNum = 0;			//���݂�HP���i�[
	int m_soulSpNum = 0;			//���݂�HP���i�[
};

