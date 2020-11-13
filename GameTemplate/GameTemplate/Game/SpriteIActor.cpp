#include "stdafx.h"
#include "SpriteIActor.h"

SpriteIActor::SpriteIActor()
{
}


SpriteIActor::~SpriteIActor()
{
}

void SpriteIActor::SpriteBound()
{
	//�o�E���h�B
}

//void SpriteIActor::SpriteMove(const CVector2& move, const int& moveTime, const int& moveDelay, const bool& relative = false)
//{
//	//���X�g�ɒǉ�
//	//SpriteMoveSet set = { move,{0.0f,0.0f},moveTime,moveDelay,0,relative,false };
//	//m_spriteMoveList.push_back(set);
//}

void SpriteIActor::SpriteMoveUpdate()
{
	//���X�g�����[�v
	for (auto go = m_spriteMoveList.begin();
		go != m_spriteMoveList.end();
		go++) {
		//�^�C�}�[��0�ȏ�Ȃ���s��
		if (go->m_spriteMoveTimer >= 0) {

			if (go->m_spriteMoveTimer >= go->m_spriteMoveDelay) { //�f�B���C���l��

				//�ړ��������v�Z
				if (go->m_spriteMoveTimer == go->m_spriteMoveDelay) {
					if (go->m_spriteMoveRelative == false) { //�w�肳�ꂽ���W�ֈړ�
						go->m_spriteMoveSpeed.x = go->m_spriteMovePos.x - m_position.x;
						go->m_spriteMoveSpeed.y = go->m_spriteMovePos.y - m_position.y;
					}
					else { //���Έړ�
						go->m_spriteMoveSpeed.x = go->m_spriteMovePos.x;
						go->m_spriteMoveSpeed.y = go->m_spriteMovePos.y;
					}
					go->m_spriteMoveSpeed.x /= (float)go->m_spriteMoveLimit;
					go->m_spriteMoveSpeed.y /= (float)go->m_spriteMoveLimit;
				}

				m_position.x += go->m_spriteMoveSpeed.x;
				m_position.y += go->m_spriteMoveSpeed.y;

			}

			go->m_spriteMoveTimer++;

			if (go->m_spriteMoveTimer >= go->m_spriteMoveLimit + go->m_spriteMoveDelay) {
				//�����܂�
				go->m_spriteMoveDeleteFlag = true;
				go->m_spriteMoveTimer = -1;
			}
		}
	}

	//�폜����
	std::list<SpriteMoveSet>::iterator it;
	it = m_spriteMoveList.begin();
	while (it != m_spriteMoveList.end()) {
		if (it->m_spriteMoveDeleteFlag == true) {
			it = m_spriteMoveList.erase(it); //erase�֐��͍폜���ꂽ�C�e���[�^�̎���Ԃ��Ă���̂ŁAerase�̖߂�l���g���B
		}
		else {
			it++; //����ȊO�͎��ցB
		}
	}


}

void SpriteIActor::SpriteSupporter_Update()
{
	//�X�V�B
	m_position = m_spriteRender->GetPosition();
	m_rotation = m_spriteRender->GetRotation();
	m_scale = m_spriteRender->GetScale();
	m_mulColor = m_spriteRender->GetMulColor();
	SpriteMoveUpdate();
	SpriteDataReturn();
}

void SpriteIActor::SpriteDataReturn() 
{
	// �X�v���C�g�̏���Ԃ� �Ō�Ɏ��s���悤
	m_spriteRender->SetPosition(m_position);
	m_spriteRender->SetRotation(m_rotation);
	m_spriteRender->SetScale(m_scale);
	m_spriteRender->SetMulColor(m_mulColor);
}
