#include "stdafx.h"
#include "StageGate.h"
#include "Player.h"

StageGate::StageGate()
{
}


StageGate::~StageGate()
{
}

bool StageGate::Start()
{
	//�S�[�X�g�̏������B
	//�S�[�X�g�̃��C���[�t���[���\����L���ɂ���B
	//g_physics.SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	m_ghostObject1.GhostBoxObject(
		{ -500.0f, 100.0f, 0.0f },	//�������͍��W�B
		CQuaternion().Identity(),		//�������͉�]�N�H�[�^�j�I���B
		{ 200.0f, 200.0f, 200.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);
	return true;
}

void StageGate::Update()
{
	Player* player = Player::GetInstance();
	g_physics.ContactTest(player->GetCharacon(), [&](const btCollisionObject& contactObject) {
		if (m_ghostObject1.IsSelf(contactObject) == true) {
			//m_ghostObject�ƂԂ�����
		}
	});
}