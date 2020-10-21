#pragma once
class ItemUIBase : public IActor
{
public:
	ItemUIBase();
	~ItemUIBase();

	//�A�C�e���̑I��
	enum eSelectState {
		Now_Item_Select,
		First_Item_Select,
		Second_Item_Select,
		Third_Item_Select,
		Item_Select_Num
	};

	/// <summary>
	/// �A�C�e���̑I����Ԃ̎擾
	/// </summary>
	eSelectState GetState() {
		return m_selectState;
	}
	/// <summary>
	/// �A�C�e���̑I����Ԃ̐ݒ�B
	/// </summary>
	void SetState(const eSelectState& state) {
		m_selectState = state;
	}

	void SetItemMove(const eSelectState& state);	//�A�C�e���ړ��B
	void Update() override;
	virtual void NowItemSelect() = 0;			//�I�𒆂̃A�C�e���B
	virtual void FirstItemSelect() = 0;			//��1�̃A�C�e���B
	virtual void SecondItemSelect() = 0;		//��2�̃A�C�e���B
	virtual void ThirdItemSelect() = 0;			//��3�̃A�C�e���B
	virtual void UseItem(FontRender* itemContRender) = 0;					//�A�C�e���g�p���B
	virtual void OnNowItem(FontRender* itemContRender) = 0;				//���݂̃A�C�e���ɂȂ����Ƃ��ɌĂ΂�鏈���B

private:
	eSelectState m_selectState = Now_Item_Select;
protected:

	SpriteRender* m_itemSprite;
	//�萔
	const CVector3 NOW_ITEM_SCALE = { 0.45f, 0.45f ,0.45f };			//�I�𒆃A�C�e���̊g�嗦
	const CVector3 NEXT1_ITEM_SCALE = { 0.35f,0.35f ,0.35f };			//��1�A�C�e���̊g�嗦
	const CVector3 NEXT2_ITEM_SCALE = { 0.25f,0.25f ,0.25f };			//��2�A�C�e���̊g�嗦
	const CVector3 NEXT3_ITEM_SCALE = { 0.15f,0.15f ,0.15f };			//��3�A�C�e���̊g�嗦

	const CVector3 NOW_ITEM_POSITION = { 460.0f,-240.0f,0.0f };			//�I�𒆃A�C�e���̍��W
	const CVector3 NEXT1_ITEM_POSITION = { 560.0f,-120.0f,0.0f };		//��1�A�C�e���̍��W
	const CVector3 NEXT2_ITEM_POSITION = { 475.0f,-50.0f,0.0f };		//��2�A�C�e���̍��W
	const CVector3 NEXT3_ITEM_POSITION = { 545.0f,-3.0f,0.0f };			//��3�A�C�e���̍��W
};

