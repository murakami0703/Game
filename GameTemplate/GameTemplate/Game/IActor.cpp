#include "stdafx.h"
#include "IActor.h"


IActor::IActor()
{
}


IActor::~IActor()
{
}
void IActor::CalcAngleAndLength(float& angle, float& distance, const CVector3& actorForward, const CVector3& toObject)
{
	//����p����
	//�I�u�W�F�N�g�Ɍ������ĐL�т�x�N�g�������߂�B
	CVector3 toObjectDir = toObject;

	//���K�����s���O�ɁA�I�u�W�F�N�g�܂ł̋��������߂Ă����B
	distance = toObjectDir.Length();
	//���K��
	toObjectDir.Normalize();

	//toObjectDir��actorForward�Ƃ̓��ς��v�Z����B
	float d = actorForward.Dot(toObjectDir);

	//���ς̌��ʂ�acos�֐��ɓn���āAtoObjectDir��actorForward�̂Ȃ��p�����߂�B
	angle = acos(d);

}