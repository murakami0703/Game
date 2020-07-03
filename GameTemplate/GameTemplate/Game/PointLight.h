#pragma once
class PointLight
{
public:
	PointLight();
	~PointLight();
	void Update();		//�X�V�B
	/// <summary>
	/// �|�C���g���C�g�̏������B
	/// </summary>
	void InitPointLight();

	static const int NUM_POINT_LIGHT = 4;

	//�|�C���g���C�g�̒萔�o�b�t�@
	struct SPointLight {
		CVector3 position[NUM_POINT_LIGHT];		//���C�g�̈ʒu�B
		CVector4 color[NUM_POINT_LIGHT];			//���C�g�̃J���[�B
		CVector4 attn[NUM_POINT_LIGHT];			//���C�g�̌����p�p�����[�^�[�B
	};
private:
	SPointLight	light;

};

