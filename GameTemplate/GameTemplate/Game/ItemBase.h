#pragma once
#
class ItemBase : public IActor
{
public:
	enum eState {
		In_Use,
		End_Use
	};

	enum eItemState {
		Item_HpRecovery,
		Item_Bum,
		Item_AttackUp,
		Item_SpeedUp
	};

	ItemBase();
	~ItemBase();
	void Update() override;

	//void SetItemMove(const eItemState& state);

	eState GetState() {
		return m_state;
	}

	void SetState(const eState& state) {
		m_state = state;
	}

	virtual void InUse() = 0;
	virtual void EndUse() = 0;	
	
private:
	eState m_state = In_Use;		//��ԁB
protected:
	SpriteRender* m_itemSprite;		//�X�v���C�g�����_�[�B
	int m_number = 0;				//�����̈ʒu�ԍ�
	FontRender* m_itemCountFont;

	/////////////////////////////////////////////////////////
	/// �萔
	/////////////////////////////////////////////////////////

	const CVector3 NOW_ITEM_SCALE = { 0.45f, 0.45f ,0.45f };			//�I�𒆃A�C�e���̊g�嗦
	const CVector3 NEXT1_ITEM_SCALE = { 0.35f,0.35f ,0.35f };			//��1�A�C�e���̊g�嗦
	const CVector3 NEXT2_ITEM_SCALE = { 0.25f,0.25f ,0.25f };			//��2�A�C�e���̊g�嗦
	const CVector3 NEXT3_ITEM_SCALE = { 0.15f,0.15f ,0.15f };			//��3�A�C�e���̊g�嗦

	const CVector3 NOW_ITEM_POSITION = { 460.0f,-240.0f,0.0f };			//�I�𒆃A�C�e���̍��W
	const CVector3 NEXT1_ITEM_POSITION = { 560.0f,-120.0f,0.0f };		//��1�A�C�e���̍��W
	const CVector3 NEXT2_ITEM_POSITION = { 475.0f,-50.0f,0.0f };		//��2�A�C�e���̍��W
	const CVector3 NEXT3_ITEM_POSITION = { 545.0f,-3.0f,0.0f };			//��3�A�C�e���̍��W


};

