#pragma once

/// <summary>
/// �A�N�^�[�N���X
/// </summary>
/// <remarks>
/// ���̃N���X��2D�ł̉��o�\���ŕK�v�ɂȂ郁���o�ϐ��A�֐����܂Ƃ߂��N���X�ł��B
/// �^�C�g���Ȃǂ̃N���X�͂��̃N���X���p�����Ă��܂��B
/// </remarks>
class SpriteIActor : public IGameObject
{
public:
	SpriteIActor();
	~SpriteIActor();

protected:
	SpriteRender* m_spriteRender;				//�X�v���C�g�����_�[�B

};

