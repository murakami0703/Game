#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	bool Start();
	void Update();

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void Item::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void Item::SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	///�O�x�N�g����ݒ�B
	/// </summary>
	void Item::SetFowardVector(CVector3 fowVec)
	{
		m_fowardVector = fowVec;
	}

	/// <summary>
	/// �A�C�e���g�p�����H
	/// </summary>
	/// <param name="flag">false	���g�p</param>
	/// <param name="flag">true		�g�p��</param>
	void Item::SetIsItemUse(bool flag) {
		m_ItemUseFlag = flag;
	}

private:
	//���
	enum EState {
		Item_Appear,
		Item_Get,
		Item_Destroy
	};

private:
	void ItemAppear();	//�A�C�e���o��
	void ItemGet();		//�A�C�e���l���B
	void ItemDestroy();	//�A�C�e���폜�B

private:
	SkinModelRender* m_ItemModelRender;				//�X�L�����f���B
	CVector3 m_position = CVector3().Zero();		//���W�B
	CVector3 m_fowardVector = CVector3().Zero();	//�O�x�N�g���B

	CQuaternion m_rotation = CQuaternion().Identity();	//��]�B

	const CVector3 m_Scale = { 5.0f,5.0f,5.0f };	//�g�嗦�B

	EState m_state = Item_Appear;				//��ԁB
	int m_itemNum = 0;		//�A�C�e���w��p�̒l

	int m_timer = 0;	//�^�C�}�[
	const int ITEM_APPEAR_TIME = 300;	//�^�C�}�[

	bool m_ItemUseFlag = false;		//�A�C�e���g�p���t���O
};

