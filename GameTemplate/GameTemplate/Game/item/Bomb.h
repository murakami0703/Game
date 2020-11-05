#pragma once
#include "item/ItemBase.h"

/// <summary>
/// ���e�B
/// </summary>
class Bomb : public ItemBase
{
public:
	Bomb();
	~Bomb();
	bool Start() override;

	void InUse() override;		//�g�p���B
	void EndUse() override;		//�I���B

private:
	void Parabolic();			//�z�u��̏����B
	void MoveBomb();			//�ړ��̏����B

private:
	CVector3 disPosition = CVector3::Zero();	//�z�u�ꏊ�̊i�[�B

	bool m_bombMoveFlag = false;		//���e�ړ���������p�t���O�B

};

