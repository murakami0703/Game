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
	void Draw();

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

	enum SelectItemState
	{
		Fire,
		Nuts,
		Lanp,
		SPtime,
		Num,
	};

	enum HPState {
		HP_1,
		HP_2,
		HP_3,
		HP_4,
		HP_5,
	};

	//HP�֘A
	Sprite m_hpHartFrame;		//HP�̘g
	Sprite m_hpHart1;		//HP1
	Sprite m_hpHart2;		//HP2
	Sprite m_hpHart3;		//HP3
	Sprite m_hpHart4;		//HP4
	Sprite m_hpHart5;		//HP5

	CVector3 m_hpHFPos = CVector3().Zero();			//HP�̘g�̍��W
	CVector3 m_hpHPos = CVector3().Zero();			//HP�̍��W

	CVector3 m_hpHFScale = CVector3().Zero();			//HP�̘g�̍��W
	CVector3 m_hpScale = CVector3().Zero();			//HP�̍��W

	//�A�C�e���֘A
	Sprite m_itemSetLog;		//�g
	Sprite m_itemSelect;		//�A�C�e���I��
	Sprite m_itemFire;		//(��)
	Sprite m_itemKinomi;		//(�؂̎�)
	Sprite m_itemLight;		//(�����v)
	Sprite m_itemTimeSP;		//(���Ԓ�~)

	CVector3 m_itemSLPos = CVector3().Zero();			//�g�̍��W
	CVector3 m_itemSPos = CVector3().Zero();			//�A�C�e���I���̍��W
	CVector3 m_itemFPos = CVector3().Zero();			//(��)�̍��W
	CVector3 m_itemKPos = CVector3().Zero();			//(�؂̎�)�̍��W
	CVector3 m_itemLPos = CVector3().Zero();			//(�����v)�̍��W
	CVector3 m_itemTSPos = CVector3().Zero();			//(���Ԓ�~)�̍��W

	CVector3					m_itemSLScale = CVector3::One();				//�g�嗦
	CVector3					m_itemSScale = CVector3::One();				//�g�嗦
	CVector3					itemFScale = CVector3::One();				//�g�嗦
	CVector3					m_itemKScale = CVector3::One();				//�g�嗦
	CVector3					m_itemLScale = CVector3::One();				//�g�嗦
	CVector3					m_itemTSScale = CVector3::One();				//�g�嗦

	//�A�C�e���I���֘A
	CVector3					m_nowSelect = { 0.75f,0.75f,0.75f };				//�I�𒆂̑傫��
	CVector3					m_NoSelect = { 0.4f,0.4f,0.4f };				//�I�𒆂̑傫��

	SelectItemState m_SIstate = Fire;	//�I�𒆂̃A�C�e��
	//HP�����֘A
	HPState m_HPstate;
	float HP = 0.0f;		//���݂�HP�����炤�B
	float m_hpCount = 0.0f;		//���݂�HP�����炤�B

};

