/*!
 * @brief	�x�N�g���N���X�B
 */

#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"




/*!
*@brief	�s�񂩂�N�H�[�^�j�I�����쐬�B
*/
void CQuaternion::SetRotation(const CMatrix& m)
{
	DirectX::XMStoreFloat4(&vec, DirectX::XMQuaternionRotationMatrix(m));
}
/*!
*@brief	from�x�N�g������to�x�N�g���ɉ�]������N�H�[�^�j�I�����쐬�B
*/
void CQuaternion::SetRotation(CVector3 from, CVector3 to)
{
	from.Normalize();
	to.Normalize();
	auto t = from.Dot(to);
	CVector3 rotAxis;
	if (t > 0.998f) {
		//�قړ��������Ȃ̂ŒP�ʃN�H�[�^�j�I���ɂ���B
		*this = CQuaternion::Identity();
	}
	else if (t < -0.998f) {
		//�قڋt�����Ȃ̂ŁA
		if (fabsf(to.x) < 1.0f) {
			//
			rotAxis.Cross(CVector3::AxisX(), to);
		}
		else {
			rotAxis.Cross(CVector3::AxisY(), to);
		}
	}
	else {
		rotAxis.Cross(from, to);
	}
	rotAxis.Normalize();
	SetRotation(rotAxis, acos(t));
}

