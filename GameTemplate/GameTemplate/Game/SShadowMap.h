#pragma once
#include "SRenderTarget.h"

class SShadowMap
{
public:
	SShadowMap();
	~SShadowMap();

	/// <summary>
/// ���C�g�r���[�s����擾�B
/// </summary>
/// <returns></returns>
	CMatrix GetLighViewMatrix() const
	{
		return m_lightViewMatrix;
	}

	/// <summary>
	/// ���C�g�v���W�F�N�V�����s����擾�B
	/// </summary>
	/// <returns></returns>
	CMatrix GetLightProjMatrix() const
	{
		return m_lightProjMatrix;
	}

	/// <summary>
	/// �X�V(���C�g�J�����̒����_���w�肷��o�[�W�����B)
	/// </summary>
	/// <remarks>
	/// ���C�g�r���[�s���A���C�g�v���W�F�N�V�����s���
	/// �X�V���܂��BUpdateFromLightTarget��UpdateFromLightDirection�̂ǂ��炩��
	/// ���t���[���Ăяo���Ă��������B
	/// </remarks>
	/// <param name="pos">���C�g�J�����̎��_�̍��W</param>
	/// <param name="target">���C�g���߂�̒����_�̍��W</param>
	void UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget);

	/// <summary>
	/// �X�V(���C�g�J�����̌������w�肷��o�[�W�����B
	/// </summary>
	/// <remarks>
	/// ���C�g�r���[�s���A���C�g�v���W�F�N�V�����s���
	/// �X�V���܂��BUpdateFromLightTarget��UpdateFromLightDirection�̂ǂ��炩��
	/// ���t���[���Ăяo���Ă��������B
	/// </remarks>
	/// <param name="lightCameraPos">���C�g�J�����̎��_�̍��W</param>
	/// <param name="lightDir">���C�g�̕���</param>
	void UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir);

	/// <summary>
	/// �V���h�E�}�b�v�ɃV���h�E�L���X�^�[�������_�����O�B
	/// ���t���[���Ăяo���ĉ������B
	/// </summary>
	/// <remarks>
	/// �V���h�E�}�b�v�ɕ`�悳���V���h�E�L���X�^�[��
	/// RegistShadowCaster�֐����g�p���ēo�^���ꂽ�L���X�^�[�݂̂ł��B
	/// ���̊֐����Ăяo���ƁA�V���h�E�L���X�^�[�̃��X�g�̓N���A����܂��B
	/// </remarks>
	void RenderToShadowMap();

	/// <summary>
	/// �V���h�E�L���X�^�[��o�^�B
	/// </summary>
	/// <remarks>
	/// ���̊֐����g���āA�o�^���ꂽ�L���X�^�[��
	/// �V���h�E�}�b�v�ɕ`�悳��܂��B
	/// �o�^���ꂽ�L���X�^�[�̃��X�g��RenderToShadowMap���Ăяo������
	/// �N���A����邽�߁A��ɉe�𐶐��������ꍇ�́A
	/// ���t���[�����̊֐����Ăяo���K�v������܂��B
	/// </remarks>
	/// <param name="shadowCaster">�V���h�E�L���X�^�[</param>
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}

	/// <summary>
	/// �V���h�E�}�b�v��SRV���擾�B
	/// </summary>
	/// <returns>�V���h�E�}�b�v��SRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();	//���C�g�J�����̎��_�B
	CVector3 m_lightCameraTarget = CVector3::Zero();	//���C�g�J�����̒����_�B
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//���C�g�r���[�s��B
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//���C�g�v���W�F�N�V�����s��B
	SRenderTarget m_shadowMapRT;						//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g�B
	std::vector< SkinModel*> m_shadowCasters;	//�V���h�E�L���X�^�[�̔z��B

};

