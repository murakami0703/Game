#pragma once
#include "SpriteIActor.h"

/// <summary>
/// �|�[�Y��ʁB
/// �Q�[�����ꎞ��~�������Ƃ��ɌĂ΂��B
/// </summary>
class Pause : public IGameObject
{
public:
	Pause();
	~Pause();

	bool Start() override;
	void Update() override;

private:
	std::vector<SpriteRender*> m_spriteRenderArray;		//�X�v���C�g�̓��I�z��

};

