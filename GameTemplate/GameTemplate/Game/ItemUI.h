#pragma once
class ItemUI : public IGameObject
{
public:
	ItemUI();
	~ItemUI();
	bool Start();
	void Update();

private:
	//�I�����
	enum eSelectState {
		Item_Use,
		Item_Move,
		Item_Now,
		Item_InUse,
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
	void ItemInUse();		//���ݑI������Ă���A�C�e��

private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_itemSprite;

	FontRender* m_itemCountFont;
	eSelectState m_state = Item_Now;			//�I�����
	eItemState m_itemState = Item_HpRecovery;			//�I�𒆂̃A�C�e��

private:

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

