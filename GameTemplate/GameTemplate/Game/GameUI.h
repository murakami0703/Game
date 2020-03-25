#pragma once

class GameUI : public IGameObject
{
public:
	GameUI();
	~GameUI();
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈���B
	/// </summary>
	void Render();
	void PostRender();

	/// <summary>
	/// �A�C�e���I������
	/// </summary>
	void ItemSelect();
	/// <summary>
	/// HP��������
	/// </summary>
	void HPAdd();


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
	
	std::vector<SpriteRender*> m_spriteRender;
	SpriteRender* r;

	FontRender* m_font;
	//�A�C�e���֘A
	CVector3 m_itemC1Pos = { 460.0f,-240.0f,0.0f };		//�g1�̍��W
	CVector3 m_itemC2Pos = { 560.0f,-120.0f,0.0f };		//�g2�̍��W
	CVector3 m_itemC3Pos = { 475.0f,-50.0f,0.0f };		//�g3�̍��W
	CVector3 m_itemC4Pos = { 545.0f,-3.0f,0.0f };		//�g4�̍��W

	CVector3 m_itemC1Scale = { 0.8f,0.8f,0.8f };		//�g1�g�嗦
	CVector3 m_itemC24Scale = { 0.7f,0.7f,0.7f };		//�g4�g�嗦

	//HP�֘A
	CVector3 m_hpPos = { -600.0f,330.0f,0.0f };		//HP�̌Œ���W
	CVector3 m_hpScale = { 0.15f,0.15f,0.15f };		//HP�̊g�嗦
	const float m_hpvAddXPos = 50.0f;					//HP2�ȏ��X���W�̕ω��l
	float m_setHP = 0.0f;		//�ŏ���HP��
	float m_hp = 0.0f;			//���݂�HP���i�[
};

