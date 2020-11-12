#pragma once
class SoulUI final : public IGameObject
{
public:
	SoulUI();
	~SoulUI();

	bool Start() override;
	void Update() override;

private:
	enum eSoulMoveState {
		SoulUI_Default,			//�ʏ��ԁB(��\���j
		SoulUI_GetMove,			//���l���������o�[�̏o�������B
		SoulUI_SoulCount,		//���̐����J�E���g����B
		SoulUI_FontBoundMove,	//���l�����t�H���g�̃J�E���g���o�E���h�����鏈���B
		SoulUI_Indicate,		//��莞�Ԃ����\����Ԃ̂܂ܕۂB
		SoulUI_Return			//���̏�Ԃɖ߂��B
	};
private:

	void SoulUIDefault();				//�ʏ��ԁB(��\���j
	void SoulUIGetMove();				//���l���������o�[�̏o�������B
	void SoulCount();					//���̐����J�E���g����B
	void FontBoundMove();				//���l�����t�H���g�̃J�E���g���o�E���h�����鏈���B
	void SoulUIIndicate();				//��莞�Ԃ����\����Ԃ̂܂ܕۂB
	void SoulUIReturn();				//���̏�Ԃɖ߂��B

private:
	std::vector<SpriteRender*> m_spriteRender;		//�X�v���C�g�̓��I�z��
	SpriteRender* m_soulRender;						//�X�v���C�g�����_�[�B

	FontRender* m_soulFont;							//���̐��\�L�p�t�H���g�B
	wchar_t soulNum[MAX_PATH];						//���J�E���g�t�H���g�e�L�X�g�B

	CVector2 m_fontPos = CVector2().Zero();
	eSoulMoveState m_soulUiState = SoulUI_Default;	//��ԁB
	bool bound = false;								//�o�E���h�p�t���O�B

	//Fout�֌W
	int m_soulNowNum = 0;							//���݂̍��̐����i�[

	int m_indicateTimer = 0;						//���l��UI�̕\���^�C�}�[�B�P��:�t���[��
};

