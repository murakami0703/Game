#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();

	static Title* GetInstance()
	{
		return m_instance;
	}
private:
	void SelectButtun(FontRender* m_font);	//�I�𒆂̃{�^��
	void LightFlashing();		//���C�g�̓_��

	enum ETitleMove {
		Title_Fadein,
		Title_Gametitle,
		Title_Backgraund,
	};

	enum ESelectButtun {
		Title_Set,
		Game_Start,
		Game_Load
	};

private:
	static Title* m_instance;

	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_titleSprite;

	FontRender* m_startFont;
	FontRender* m_loadFont;

	ESelectButtun m_select = Game_Start;	//�I�����

	//���C�g�̓_��
	float m_flashingTimer = 0;		//���C�g�p�^�C�}�[�B
	const float m_lightsUpTime = 45.0f;
	const float m_lightsOffTime = 90.0f;
	const float m_lightAlpha = 0.7f / 45.0f;

	//�����̓���


	//�t�H���g�ʒu
	const CVector2 m_startFontPos = { -550.0f,-270.0f };	//�u�͂��߂�v�̍��W
	const CVector2 m_loadFontPos = { 400.0f,-270.0f };		//�u�Â���v�̍��W

	CSoundSource m_titleBgm;						//�^�C�g��BGM�B

};

