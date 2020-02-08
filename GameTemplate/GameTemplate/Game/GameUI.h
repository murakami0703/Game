#pragma once
class GameUI
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

	Sprite m_hpHartFrame;		//HP�̘g
	Sprite m_hpHart1;		//HP1
	Sprite m_hpHart2;		//HP2
	Sprite m_hpHart3;		//HP3
	Sprite m_hpHart4;		//HP4
	Sprite m_hpHart5;		//HP5

	Sprite m_itemSetLog;		//�A�C�e���p�̘g

	CVector3 m_hpHFPos = CVector3().Zero();			//HP�̘g�̍��W
	CVector3 m_hpHPos = CVector3().Zero();			//HP�̍��W
	CVector3 m_itemSLPos = CVector3().Zero();			//�A�C�e���p�̘g�̍��W

};

