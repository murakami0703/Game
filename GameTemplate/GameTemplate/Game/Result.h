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
	void SpriteMove(SpriteRender* m_sprite);

	void Bound();
	void TopLeft();
	void Soul();
	void Total();
	void Jewelry();

private:
	enum eState {
		Result_Background,		//Backgraund��\���B
		Result_SpriteMove,		//Resultsprite����ɕ\���B
		Result_Soul,		//stage�ŃQ�b�g�������̐��J�E���g
		Result_Total,		//���v���̃J�E���g
		Result_Jewelry,		//�{�X���r�o������Ώ���

	};
private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_itemSprite;

	FontRender* m_font;
	
	//background
	const CVector3 m_bgStartPos = {720.0f,0.0f,0.0f };

	//���U���gsprite�֘A
	const float m_resultSetYPos = 350.0f;

	const CVector3 m_resultPos1 = { 100.0f,500.0f,0.0f };
	const CVector3 m_resultPos2 = { 150.0f,500.0f,0.0f };
	const CVector3 m_resultPos3 = { 200.0f,500.0f,0.0f };
	const CVector3 m_resultPos4 = { 250.0f,500.0f,0.0f };
	const CVector3 m_resultPos5 = { 300.0f,500.0f,0.0f };
	const CVector3 m_resultPos6 = { 350.0f,500.0f,0.0f };

	const CVector3 m_resultScale = { 0.3f,0.3f,0.3f };
	eState m_state = Result_Background;

};

