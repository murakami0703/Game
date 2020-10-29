#pragma once
#include "item/ItemBase.h"
/// <summary>
/// ���e�B
/// </summary>
class Bum : public ItemBase
{
public:
	Bum();
	~Bum();

	bool Start() override;

	void InUse() override;		//�g�p���B
	void EndUse() override;		//�I���B

private:
	void Parabolic();			//�������̏����B
private:
	CVector3 m_StartPoint = CVector3::Zero();			//�n�_�B
	CVector3 m_middlePoint1 = CVector3::Zero();			//���Ԓn�_1�B
	CVector3 m_middlePoint2 = CVector3::Zero();			//���Ԓn�_2�B
	CVector3 m_endPoint = CVector3::Zero();			//�I�_�B

	//CVector3 m_correction = CVector3::Zero();			//�␳�B
	float m_catmull_U;			//�␳�B

};

