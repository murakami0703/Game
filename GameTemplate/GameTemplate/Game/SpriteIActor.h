#pragma once

/// <summary>
/// �A�N�^�[�N���X
/// </summary>
/// <remarks>
/// ���̃N���X��2D�ł̉��o�\���ŕK�v�ɂȂ郁���o�ϐ��A�֐����܂Ƃ߂��N���X�ł��B
/// �^�C�g���Ȃǂ̃N���X�͂��̃N���X���p�����Ă��܂��B
/// </remarks>
class SpriteIActor
{
public:
	/// <summary>
	/// SpriteRender�̃A�h���X��������
	/// �ŏ��Ɏ��s���ĂˁI
	/// </summary>
	/// <param name="sp">�|�C���^</param>
	void SpriteRenderSetting(class SpriteRender* sp, int No = -1) {
		m_spriteRender = sp;
	}

	SpriteIActor();
	~SpriteIActor();
	//�X�v���C�g�̊e��@�\��񋟂�����B
	void SpriteSupporter_Update();
	//�ړ�
	void SpriteMove(const CVector2& move, const int& moveTime,	const int& moveDelay, const bool& relative = false);
	void SpriteBound(); //�o�E���h�B

		//��Ԏ擾�p
	//�X�v���C�g�̈ړ����X�g�v�f�����擾
	//�ړ����̃X�v���C�g���ǂ����𔻕ʂ��� �Ȃ�
	int GetSpriteMoveListLen() {
		return static_cast<int>(m_spriteMoveList.size());
	}

private:
	void SpriteMoveUpdate();
	void SpriteDataReturn();

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

protected:
	class SpriteRender* m_spriteRender;				//�X�v���C�g�����_�[�B
	CVector3 m_position = CVector3::Zero();					//���W
	CQuaternion m_rotation = CQuaternion().Identity();		//��]
	CVector3 m_scale = CVector3().One();					//�g�嗦
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };			//��Z�J���[
};

