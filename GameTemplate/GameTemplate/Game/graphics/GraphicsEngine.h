#pragma once

#include "EffectEngine.h"

/// <summary>
/// �����_�����O���[�h�B
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//�s���ȃ����_�����O���[�h�B
	enRenderMode_Normal,			//�ʏ탌���_�����O�B
	enRenderMode_silhouette,		//�V���G�b�g�`��
	enRenderMode_CreateShadowMap,	//�V���h�E�}�b�v�����B
	enRenderMode_Num,				//�����_�����O���[�h�̐��B
};
class RenderTarget;

/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/// <summary>
	/// �X���b�v�`�F�C�����擾
	/// </summary>
	/// 	
	IDXGISwapChain*	GetSwapChain()
	{
		return m_pSwapChain;
	}
	/// <summary>
	/// �o�b�N�o�b�t�@���擾
	/// </summary>
	ID3D11RenderTargetView* GetRTargetView()
	{
		return m_backBuffer;
	}

	/// <summary>
	/// EffectEngine�N���X�̃C���X�^���X���擾�B
	/// </summary>
	EffectEngine& GetEffectEngine()
	{
		return m_effectEngine;
	}

	/// <summary>
	/// SpriteBatch�̎擾
	/// </summary>
	DirectX::SpriteBatch* GetSpriteBatch() const
	{
		return m_spriteBatch.get();
	}
	/// <summary>
	/// SpriteFont�̎擾�B
	/// </summary>
	DirectX::SpriteFont* GetSpriteFont() const
	{
		return m_spriteFont.get();
	}

	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();

	/// <summary>
	/// �����_�����O�^�[�Q�b�g�̐؂�ւ�
	/// </summary>
	/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
	/// <param name="viewport">�r���[�|�[�g</param>
	void ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);

private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B
	EffectEngine			m_effectEngine;								//!<�G�t�F�N�g�G���W���B

	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;				//!<�X�v���C�g�o�b�`�B
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;				//!<�X�v���C�g�t�H���g�B

};

extern GraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��