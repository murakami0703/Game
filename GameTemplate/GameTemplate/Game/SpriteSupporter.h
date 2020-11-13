#pragma once

/// <summary>
/// �X�v���C�g�̈ړ��≉�o�������R�}���h�ł���Ă����
/// </summary>
class SpriteSupporter
{
public:
	SpriteSupporter();
	~SpriteSupporter();

	/// <summary>
	/// SpriteRender�̃A�h���X��������
	/// �ŏ��Ɏ��s���ĂˁI
	/// </summary>
	/// <param name="sp">�|�C���^</param>
	void SpriteRenderSetting(class SpriteRender* sp ,int No = -1) {
		m_spriteRender = sp;
		m_spriteNo = No;
	}

	//�X�V�iSpriteRender���Ăԁj
	void SpriteSupporter_Update();

	/// <summary>
	/// �X�v���C�g�̉��o��S�ă��Z�b�g����
	/// </summary>
	void SpriteDelayReset();

	//���s����R�}���h
	void SpriteMove(const CVector2& move, const int& moveTime,
		const int& moveDelay, const bool& relative = false);
	void SpriteRotation(const float& rot, const int& moveTime,
		const int& moveDelay, const bool& loopflag = false);
	void SpriteScale(const CVector3& scale, const int& moveTime, const int& moveDelay);
	void SpriteScale(const float& scale, const int& moveTime, const int& moveDelay);
	void SpriteColor(const CVector4& color, const int& moveTime, const int& moveDelay);
	void SpriteShake(const CVector2& move, const int& moveTime, const int& moveCount);
	void SpritePattern(const int& moveTime, const bool& loopflag = false,
		const int& overLimit = 0);

	/// <summary>
	/// ���̃t���O��true ���� ���̃X�v���C�g���S�������Ă��Ȃ��ꍇ
	/// �X�v���C�g�͎�����DeleteGO�����
	/// </summary>
	/// <param name="flag">�t���O</param>
	void SetAutoDeathFlag(const bool& flag) {
		m_autoDeathFlag = flag;
	}

	//��Ԏ擾�p
	//�X�v���C�g�̈ړ����X�g�v�f�����擾
	//�ړ����̃X�v���C�g���ǂ����𔻕ʂ��� �Ȃ�
	int GetSpriteMoveListLen() {
		return static_cast<int>(m_spriteMoveList.size());
	}
	int GetSpriteScaleListLen() {
		return static_cast<int>(m_spriteScaleList.size());
	}

private:
	//�����ƕЕt��
	void SpriteDataUpdate();
	void SpriteDataReturn();
	//�A�b�v�f�[�g�p
	void SpriteMoveUpdate();
	void SpriteRotationUpdate();
	void SpriteScaleUpdate();
	void SpriteColorUpdate();
	void SpriteShakeUpdate();
	void SpritePatternUpdate();

	//�����o�ϐ�
	class SpriteRender* m_spriteRender;
	CVector3 m_position = CVector3::Zero();					//���W
	CQuaternion m_rotation = CQuaternion().Identity();		//��]
	CVector3 m_scale = CVector3().One();					//�g�嗦
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };			//��Z�J���[
	int m_maxPattern = -1;									//�ő�p�^�[��
	int m_nowPattern = -1;									//���݃p�^�[��
	int m_spriteNo = -1;									//�X�v���C�g�ԍ��i�T�u�X�v���C�g�֘A�j
	//Move
	struct SpriteMoveSet {
		CVector2 m_spriteMovePos = { 0.0f,0.0f };			//�X�v���C�g�̈ړ���
		CVector2 m_spriteMoveSpeed = { 0.0f,0.0f };			//�X�v���C�g�̈ړ���
		int m_spriteMoveLimit = -1;							//�X�v���C�g�̈ړ����ԁi-1�͈ړ����ł͂Ȃ��j
		int m_spriteMoveDelay = -1;							//�X�v���C�g�̈ړ��f�B���C
		int m_spriteMoveTimer = -1;							//�X�v���C�g�̈ړ��^�C�}�[
		bool m_spriteMoveRelative = false;					//�X�v���C�g�̑��Έړ��t���O�itrue�Ȃ瑊�Έړ��j
		bool m_spriteMoveDeleteFlag = false;				//�폜�t���O�i������Ȃ��łˁj
	};
	std::list<SpriteMoveSet> m_spriteMoveList;				//�ړ��̃��X�g
	//Rotation
	CQuaternion m_spriteRotation = CQuaternion().Identity();	//1�t���[���̉�]��
	int m_spriteRotationLimit = -1;							//�X�v���C�g�̉�]���ԁi-1�͈ړ����ł͂Ȃ��j
	int m_spriteRotationDelay = -1;							//�X�v���C�g�̉�]�f�B���C
	int m_spriteRotationTimer = -1;							//�X�v���C�g�̉�]�^�C�}�[
	bool m_spriteLoopRotationFlag = false;					//true�Ȃ�i���ɉ��X�Ƀt�H�[�G�o�[�������
	//Scale
	struct SpriteScaleSet {
		CVector3 m_spriteScale = CVector3().Zero();			//�ڕW�̑傫��
		CVector3 m_spriteScaleMove = CVector3().Zero();		//1�t���[���̕ω���
		int m_spriteScaleLimit = -1;						//�X�v���C�g�̊g�厞�ԁi-1�͈ړ����ł͂Ȃ��j
		int m_spriteScaleDelay = -1;						//�X�v���C�g�̊g��f�B���C
		int m_spriteScaleTimer = -1;						//�X�v���C�g�̊g��^�C�}�[
		bool m_spriteScaleDeleteFlag = false;				//�폜�t���O�i������Ȃ��łˁj
	};
	std::list<SpriteScaleSet> m_spriteScaleList;			//�g��k���̃��X�g
	//MulColor
	CVector4 m_spriteColor = CVector4().White();			//�ڕW�̐F
	CVector4 m_spriteColorMove = CVector4().White();		//1�t���[���̕ω���
	int m_spriteColorLimit = -1;							//�X�v���C�g�̐F�ύX���ԁi-1�͕ω����ł͂Ȃ��j
	int m_spriteColorDelay = -1;							//�X�v���C�g�̕ω��f�B���C
	int m_spriteColorTimer = -1;							//�X�v���C�g�̕ω��^�C�}�[
	//Shake
	CVector2 m_spriteShakeMove = { 0.0f,0.0f };				//�V�F�C�N�ł̈ړ�����
	CVector2 m_spriteShakeMove_OneFlame = { 0.0f,0.0f };	//�V�F�C�N��1�t���[���ړ�����
	int m_spriteShakeLimit = -1;							//�X�v���C�g�̃V�F�C�N�Ԋu�i-1�͕ω����ł͂Ȃ��j
	int m_spriteShakeCount = -1;							//�X�v���C�g�̃V�F�C�N�񐔁i0�̏ꍇ�A�~�߂�܂Ń��[�v����j
	int m_spriteShakeCounter = -1;							//�X�v���C�g�̃V�F�C�N�񐔃J�E���^�[
	int m_spriteShakeTimer = -1;							//�X�v���C�g�̃V�F�C�N�^�C�}�[
	//Pattern
	int m_patternLimit = -1;								//�ŏI�p�^�[��
	int m_patternTimer = -1;								//�p�^�[���p�^�C�}�[
	int m_patternOverLimit = -1;							//�p�^�[���I����̑҂����ԁi�p�^�[���I������u�ŏ������肷��̂Łj
	bool m_patternLoopFlag = false;							//false�Ȃ�p�^�[���I�����A�A���t�@��������0�ɂ��� true�Ȃ烋�[�v����
	//AutoDeath
	bool m_autoDeathFlag = false;							//�������Ă��Ȃ��ꍇ�A�e�̃X�v���C�g�����_�[���폜����


};

