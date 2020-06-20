#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	bool Start();
	void Update();
private:
	//�I�����
	enum eSelectState {
		Item_Use,
		Item_Move,
		Item_Now
	};
	//�A�C�e���̎��
	enum eItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp
	};
private:
	void ItemMoveSet(eItemState& m_State);	//�A�C�e��sprite�̈ړ��g��ݒ�B

	void ItemUse(eItemState& m_State);		//�A�C�e���g�p
	void ItemMove(eItemState& m_State);	//�A�C�e���ړ�
	void ItemNow();		//���ݑI������Ă���A�C�e��

private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_itemSprite;

	FontRender* m_itemCountFont;
	eSelectState m_state = Item_Now;			//�I�����
	eItemState m_itemState = Item_HpRecovery;			//�I�𒆂̃A�C�e��
private:
	//�A�C�e���֘A
	CVector3 m_item1Pos = { 460.0f,-240.0f,0.0f };		//�A�C�e��1�̍��W
	CVector3 m_item2Pos = { 560.0f,-120.0f,0.0f };		//�A�C�e��2�̍��W
	CVector3 m_item3Pos = { 475.0f,-50.0f,0.0f };		//�A�C�e��3�̍��W
	CVector3 m_item4Pos = { 545.0f,-3.0f,0.0f };		//�A�C�e��4�̍��W

	CVector3 m_item1Scale = { 0.55f,0.55f ,0.55f };			//�A�C�e��1�̊g�嗦
	CVector3 m_item2Scale = { 0.35f,0.35f ,0.35f };			//�A�C�e��2�̊g�嗦
	CVector3 m_item3Scale = { 0.25f,0.25f ,0.25f };			//�A�C�e��3�̊g�嗦
	CVector3 m_item4Scale = { 0.15f,0.15f ,0.15f };			//�A�C�e��4�̊g�嗦

	bool m_itemMoveEndFlag = false;		//�ړ�����
	/// <summary>
	/// �㉺�I���t���O
	/// </summary>
	/// <param name="flag">true   ��     false    ��</param>
	bool m_upDounFlag = true;
	//�t�H���g�֘A
	CVector2 m_fontMovePos = CVector2().Zero();			//�t�H���g�̍��W
	wchar_t ItemHpRecText[256];
};

