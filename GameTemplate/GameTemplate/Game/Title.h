#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();

	bool Start();		
	void Update();	

	static Title* GetInstance()
	{
		return m_instance;
	}
private:
	//���
	enum EState {
		Title_FadeIn,		//�t�F�[�h�C���B
		Title_GameTitle,	//�����̕\���B
		Title_Select,		//�{�^���I���B
		Title_FadeOut,		//�t�F�[�h�A�E�g�B
	};

	//���l�̈ړ�
	enum EVillainMove {
		Villain_SideWays1,	//���ړ�1�B
		Villain_Forward,	//����ړ��B
		Villain_Stay,		//���܂�B
		Villain_Back,		//�E���ړ��B
		Villain_SideWays2,	//���ړ�2�B
		Villain_Stop,		//��~�B
		Villain_SideWays3	//���ړ�3�B
	};

	//�I���{�^��
	enum EButton {
		Button_Start,
		Button_Load
	};
private:
	void TitleFadeIn();			//�t�F�[�h�C���B
	void TitleGameTitle();		//�����̕\���B
	void TitleSelect();			//�{�^���I���B
	void TitleFadeOut();		//�t�F�[�h�A�E�g�B

	//���l
	void ChangeSprite(SpriteRender* m_sprite1, SpriteRender* m_sprite2, float moveX = 0.0f, float moveY = 0.0f);		//�X�v���C�g�̐؂�ւ��B
	void SpriteSetAlpha(SpriteRender* m_nextSprite, SpriteRender* m_invisible1, SpriteRender* m_invisible2);

	void VillainSideWays1();	//���ړ�1�B
	void VillainForward();		//����ړ��B
	void VillainStay();			//���܂�B
	void VillainBack();			//�E���ړ��B
	void VillainSideWays2();	//���ړ�2�B
	void VillainStop();			//��~�B
	void VillainSideWays3();	//���ړ�3�B

	void LightFlashing();		//���C�g�̓_��


private:

	static Title* m_instance;

	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��B
	SpriteRender* m_titleSprite;				//�X�v���C�g�����_�[�B

	FontRender* m_startFont;					//Start�t�H���g�B
	FontRender* m_loadFont;						//Load�t�H���g�B

	EState m_state = Title_FadeIn;						//��ԁB
	EVillainMove m_villainState = Villain_SideWays1;	//���l�̈ړ���ԁB
	EButton m_buttonState = Button_Start;				//�I�𒆂̃{�^����ԁB

	//���֌W
	CSoundSource* m_titleBgm;					//�^�C�g��BGM�B
	CSoundSource* m_se;					//�^�C�g��BGM�B

	//���C�g�̓_��
	float m_flashingTimer = 0;		//���C�g�p�^�C�}�[�B
	int m_fontTimer = 0;			//�����p�^�C�}�[�B
	int count = 0;
	int m_stopTimer = 0;			//��~���ԗp�^�C�}�[�B
	bool movestart = false;
};

