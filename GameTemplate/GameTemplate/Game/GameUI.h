#pragma once

class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();

	bool Start();
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();

	/// <summary>
	/// �C���X�^���X�̎擾�B
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static GameUI* GetInstance()
	{
		return m_instance;
	}
private:
	void HPCalc();
private:

	static GameUI* m_instance;
	
	void ScalingSelectCase();					//�I��g�̊g��k��
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* r;
	FontRender* m_font;
	
	//�A�C�e���֘A
	CVector3 m_itemC1Pos = { 460.0f,-240.0f,0.0f };		//�g1�̍��W
	CVector3 m_itemC2Pos = { 560.0f,-120.0f,0.0f };		//�g2�̍��W
	CVector3 m_itemC3Pos = { 475.0f,-50.0f,0.0f };		//�g3�̍��W
	CVector3 m_itemC4Pos = { 545.0f,-3.0f,0.0f };		//�g4�̍��W

	CVector3 m_itemC1Scale = { 0.8f,0.8f,0.8f };		//�g1�g�嗦
	CVector3 m_itemC24Scale = { 0.7f,0.7f,0.7f };		//�g2�`4�g�嗦

	CVector3 m_itemSCPos = { 460.0f,-240.0f,0.0f };		//�I��g�̍��W
	CVector3 m_itemHPos = { 505.0f,14.0f,0.0f };		//�[�̍��W
	CVector3 m_itemLPos = { 585.0f,-250.0f,0.0f };		//L�̍��W
	CVector3 m_itemZLPos = { 605.0f,20.0f,0.0f };		//ZL�̍��W

	CVector3 m_itemLScale = { 0.8f,0.8f,0.8f };			//L�g�嗦
	CVector3 m_itemZSCScale = { 0.7f,0.7f,0.7f };		//ZL,�I��g�g�嗦
	CVector3 m_itemHScale = { 0.6f,0.6f,0.6f };			//�[�g�嗦

	int m_scalingCount = 0;								//�I��g�g��k���p�J�E���g
	const int m_bigCountValue = 30;
	const int m_smallCountValue = 60;
	CVector3 m_scalingValue = { 0.002f,0.002f,0.002f };			//�I��g�g��l

	//HP�֘A
	CVector3 m_hpPos = { -600.0f,330.0f,0.0f };		//HP�̌Œ���W
	CVector3 m_hpScale = { 0.15f,0.15f,0.15f };		//HP�̊g�嗦
	const float m_hpvAddXPos = 50.0f;					//HP2�ȏ��X���W�̕ω��l
	float m_setHP = 0.0f;		//�ŏ���HP��
	float m_nowHp = 0.0f;			//���݂�HP���i�[
	int m_spriteNum = 7;			//�Q�[���J�n����sprite�̐����i�[�B
};

