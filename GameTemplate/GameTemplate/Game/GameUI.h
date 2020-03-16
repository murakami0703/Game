#pragma once
//class HPSetPoint;

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
	float GameUI::GetCount()
	{
		return m_hpCount;		//�\��HP�J�E���g�B

	}
private:
	// �A�C�e���I��g�̐ݒ�
	void CaseSet();


private:

	//FontRender* m_font;
	static GameUI* m_instance;

	//�A�C�e���֘A
	Sprite m_itemCase1;		//�g1
	Sprite m_itemCase2;		//�g2
	Sprite m_itemCase3;		//�g3
	Sprite m_itemCase4;		//�g4

	CVector3 m_itemC1Pos = { 460.0f,-240.0f,0.0f };			//�g1�̍��W
	CVector3 m_itemC2Pos = { 560.0f,-120.0f,0.0f };		//�g2�̍��W
	CVector3 m_itemC3Pos = { 475.0f,-50.0f,0.0f };		//�g3�̍��W
	CVector3 m_itemC4Pos = { 545.0f,-3.0f,0.0f };	//�g4�̍��W

	CVector3					m_itemC1Scale = { 0.8f,0.8f,0.8f };				//�g1�g�嗦
	CVector3					m_itemC24Scale = { 0.7f,0.7f,0.7f };				//�g4�g�嗦

	//HPSetPoint* m_hpPoint = nullptr;		//�|�C���g��

	float HP = 0.0f;		//���݂�HP�����炤�B
	float m_hpCount = 0.0f;		//�\��HP�J�E���g�B

};

