#pragma once
class PlayerHP
{
public:
	PlayerHP();
	~PlayerHP();
	//�X�V
	void Update();
	//�`��
	void Draw();

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void PlayerHP::SetHPPosition(CVector3 pos)
	{
		m_hpHFPos = pos;
		m_hpHPos = pos;
	}
	/// <summary>
	/// �g�嗦��ݒ�B
	/// </summary>
	void PlayerHP::SetHPScale(CVector3 scale)
	{
		m_hpHFScale = scale;
		m_hpScale = scale;
	}

private:
	//HP�֘A
	Sprite m_hpHartFrame;		//HP�̘g1
	Sprite m_hpHart;		//HP1

	CVector3 m_hpHFPos = CVector3().Zero();			//HP�̘g�̍��W
	CVector3 m_hpHPos = CVector3().Zero();			//HP�̍��W

	CVector3 m_hpHFScale = CVector3().Zero();			//HP�̘g�̍��W
	CVector3 m_hpScale = CVector3().Zero();			//HP�̍��W

};

