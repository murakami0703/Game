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
	void BackMove();								//�w�i�X�v���C�g�̈ړ������B
	void SpriteMove(SpriteRender* m_sprite);		//�X�v���C�g�̉��~�ړ������B
	void SpriteIndicate(SpriteRender* m_sprite);	//�X�v���C�g�̕\�������B
	void SpriteScaleUp(SpriteRender* m_sprite);		//�X�v���C�g�̊g��\�������B

	void BackTable();		//Backgraund��\���B
	void FallMove();		//Result�t�H���g��\���B
	void Frame();			//�t���[���̕\���B
	void StageName();		//�Q�[���X�e�[�W���̕\���B
	void GetSoul();			//�l�����̕\���B
	void SoulNumber();		//�l�����̐��B
	void GetItem();			//�l���A�C�e������̕\���B
	void Next();			//Next�̕\���B
	void Removal();			//��U�S���r���B
	void GetJewelry();		//��Ε\���B
	void SelectNext();		//SelsctNext�̕\���B

private:
	enum eState {
		Result_BackTable,		//Backgraund��\���B
		Result_FallMove,		//Result�t�H���g��\���B
		Result_Frame,			//�t���[���̕\���B
		Result_StageName,		//�Q�[���X�e�[�W���̕\���B
		Result_GetSoul,			//�l�����̕\���B
		Result_SoulNumber,		//�l�����̐��B
		Result_GetItem,			//�l���A�C�e������̕\���B
		Result_Next,			//Next�̕\���B
		Result_Removal,			//��U�S���r���B
		Result_GetJewelry,		//��Ε\���B
		Result_SelectNext,		//SelsctNext�̕\���B
	};
private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_itemSprite;

	FontRender* m_stageNameFont;
	FontRender* m_soulNumFont;

	//background�֘A
	const float m_backTexAlpha = 0.5f;					//�w�i�̓����x�B
	const float m_backTexXPos = 1280.0f;				//�񖇖ڂ�X���W�̈ʒu�B
	CVector3 m_backTexpos1 = CVector3().Zero();			//�w�i�̍��W1�B
	CVector3 m_backTexpos2 = CVector3().Zero();			//�w�i�̍��W2�B
	const float m_backMove = -2.0f;						//�w�i�̈ړ����x�B

	//���U���g����֘A
	const float m_tableSpeed = 30.0f;					///���U���g����̈ړ����x�B
	const float m_boundStopXPos = 40.0f;				///���U���g����̃o�E���h��~X���W�B
	const float m_boundSpeed = 10.0f;					///���U���g����̃o�E���h���x�B
	bool bound = false;									//�o�E���h�p�t���O�B

	//���U���g�����֘A
	const CVector3 m_resultFontPos = { 310.0f,505.0f,0.0f };		//���U���g�����̏������W�B
	const float m_resultFontYPos = 310.0f;							//Y���W�̒�~�ʒu�B
	int m_timer = 0;												//���ԍ��p�^�C�}�[
	const int m_timeLag[7] = { 0,5,10,15,20,25,40 };				//���ԍ��̊e�^�C���B

	//�g�֘A
	const CVector3 m_dotLinePos = { 320.0f,175.0f,0.0f };			//�_���̍��W�B
	const CVector3 m_soulFramePos = { 320.0f,75.0f,0.0f };			//���p�g�̍��W�B
	const CVector3 m_itemFramePos = { 320.0f,-100.0f,0.0f };		//�A�C�e���p�g�̍��W�B

	//�X�e�[�W���֘A
	const float m_nameStopXPos = 50.0f;					//X���W�̒�~�ʒu�B
	const float m_nameSpeed = 40.0f;					//�����̈ړ����x�B

	//���֘A
	const CVector3 m_soulPos = { 215.0f,75.0f,0.0f };		//���̍��W�B
	const CVector3 m_soulScale = { 0.32f,0.32f,0.32f };		//���̊g�嗦�B
	const CVector3 m_soulFontPos = { 290.0f,35.0f,0.0f };	//���t�H���g�̊g�嗦�B

	int m_soulNumber = 0;									//�l��������������́B
	const CVector2 m_soulNumPos = { 340.0f,100.0f };		//�l�������̍��W�B
	const CVector3 m_soulNumColor = { 0.3f,0.27f,0.2f };	//�l�������̃J���[�B
	const float m_soulNumScale = 2.0f;					//�l�������̊g�嗦�B

	const float m_soulNumStopYPos = 100.0f;					//������Y���W�̒�~�ʒu�B
	const float m_soulNumYPos = 120.0f;						//������Y���W�̐܂�Ԃ��n�_�B
	const float m_soulNumSpeed = 5.0f;						//�����̈ړ����x�B

	//�A�C�e���֘A
	const CVector3 m_itemFontPos = { 320.0f,-50.0f,0.0f };			//�A�C�e��Get�t�H���g�̍��W�B
	const CVector3 m_itemTablePos1 = { 100.0f,-200.0f,0.0f };		//�A�C�e������̍��W1�B
	const CVector3 m_itemTablePos2 = { 250.0f,-150.0f,0.0f };		//�A�C�e������̍��W2�B
	const CVector3 m_itemTablePos3 = { 400.0f,-150.0f,0.0f };		//�A�C�e������̍��W3�B
	const CVector3 m_itemTablePos4 = { 550.0f,-200.0f,0.0f };		//�A�C�e������̍��W4�B
	const int m_itemtimeLag[5] = { 10,15,20,25,35 };				//���ԍ��̊e�^�C���B

	//Next�֘A
	const CVector3 m_nextFontPos = { 500.0f,-325.0f,0.0f };			//Next�t�H���g�̍��W�B
	const CVector3 m_trianglePos = { 600.0f,-325.0f,0.0f };			//�O�p�̍��W�B
	const float m_triangleStopXPos = 600.0f;						//�O�p��X���W�̒�~�ʒu�B
	const float m_triangleXPos = 610.0f;							//�O�p��X���W�̐܂�Ԃ��n�_�B
	const float m_triangleSpeed = 0.5f;								//�O�p�̈ړ����x�B

	//�S�̎g�p
	const float m_startAlpha = 0.0f;				//��̂̏��������x�B
	const float m_fallMoveSpeed = -15.0f;			//���~���x�B
	const float m_Indicate = 0.1f;				//�\��������l�B

	//���U���gsprite�֘A
	const CVector3 m_bgStartPos = { 720.0f,0.0f,0.0f };


	eState m_state = Result_BackTable;		//�t���[���̕\���B
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;				//!<�X�v���C�g�t�H���g�B

};

