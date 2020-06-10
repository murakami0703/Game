#pragma once
class Result : public IGameObject
{
	static Result* m_instance;

public:
	Result();
	~Result();

	//�C���X�^���X�̎擾
	static Result* Result::GetInstance() {
		return m_instance;
	}
	//�X�V
	void Update();

private:
	void SpriteBound(SpriteRender* m_sprite);

	void Bound();
	void TopLeft();
	void Soul();
	void Total();
	void Jewelry();

private:
	enum eState {
		Result_Bound,		//Resultsprite��Bound�\���B
		Result_TopLeft,		//Resultsprite���k���A����ɁB
		Result_Soul,		//stage�ŃQ�b�g�������̐��J�E���g
		Result_Total,		//���v���̃J�E���g
		Result_Jewelry,		//�{�X���r�o������Ώ���

	};
private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_itemSprite;

	FontRender* m_font;
	
	//���U���gsprite�֘A
	const float m_startYPos = 760.0f;
	const float m_startXPos1 = 100.0f;
	const float m_startXPos2 = 300.0f;
	const float m_startXPos3 = 500.0f;
	float m_a = (760.0f / 60.0f);

	eState m_state = Result_Bound;

};

