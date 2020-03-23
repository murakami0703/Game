#include "stdafx.h"
#include "Font.h"


Font::Font()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_spriteFont = g_graphicsEngine->GetSpriteFont();
	auto& ge = GraphicsEngine();
	m_scaleMat.MakeScaling(
		{
			FRAME_BUFFER_W / static_cast<float>(FRAME_BUFFER_W),
			FRAME_BUFFER_H / static_cast<float>(FRAME_BUFFER_H),
			1.0f
		}
	);
}


Font::~Font()
{
	if (m_translucentBlendState != nullptr) {
		m_translucentBlendState->Release();
	}
}
void Font::InitTranslucentBlendState() {

	//��̂��Ƃ��A�쐬����u�����h�X�e�[�g�̏���ݒ肷��B
	CD3D11_DEFAULT defaultSettings;
	//�f�t�H���g�Z�b�e�B���O�ŏ���������B
	CD3D11_BLEND_DESC blendDesc(defaultSettings);

	//���u�����f�B���O��L���ɂ���B
	blendDesc.RenderTarget[0].BlendEnable = true;

	//�\�[�X�J���[�̃u�����f�B���O���@���w�肵�Ă���B
	//�\�[�X�J���[�Ƃ̓s�N�Z���V�F�[�_�\����̏o�͂��w���Ă���B
	//���̎w��ł́A�\�[�X�J���[��SRC(rgba)�Ƃ���ƁA
	//�ŏI�I�ȃ\�[�X�J���[�͉��L�̂悤�Ɍv�Z�����B
	//�ŏI�I�ȃ\�[�X�J���[ = SRC.rgb �~ SRC.a�E�E�E�E�E�E�@�@
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

	//�f�B�X�e�B�l�[�V�����J���[�̃u�����f�B���O���@���w�肵�Ă���B
	//�f�B�X�e�B�l�[�V�����J���[�Ƃ́A
	//���łɕ`�����܂�Ă��郌���_�����O�^�[�Q�b�g�̃J���[���w���Ă���B
	//���̎w��ł́A�f�B�X�e�B�l�[�V�����J���[��DEST(rgba)�A
	//�\�[�X�J���[��SRC(RGBA)�Ƃ���ƁA�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[��
	//���L�̂悤�Ɍv�Z�����B
	//�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[ = DEST.rgb �~ (1.0f - SRC.a)�E�E�E�E�E�A
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	//�ŏI�I�Ƀ����_�����O�^�[�Q�b�g�ɕ`�����܂��J���[�̌v�Z���@���w�肵�Ă���B
	//���̎w�肾�ƁA�@�{�A�̃J���[���������܂��B
	//�܂�A�ŏI�I�Ƀ����_�����O�^�[�Q�b�g�ɕ`�����܂��J���[��
	//SRC.rgb �~ SRC.a + DEST.rgb �~ (1.0f - SRC.a)
	//�ƂȂ�B
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//���̐ݒ�ŁA�u�����h�X�e�[�g���쐬�����
	//�������������s����u�����h�X�e�[�g���쐬�ł���B
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);

}

void Font::Begin()
{
	auto d3dDevice = g_graphicsEngine->GetD3DDeviceContext();
	float bf[4];
	UINT samplerMask;
	d3dDevice->OMGetBlendState(&m_blendStateBackup, bf, &samplerMask);
	d3dDevice->RSGetState(&m_rasterrizerStateBackup);
	d3dDevice->OMGetDepthStencilState(&m_depthStencilStateBackup, 0);

	//�X�e�[�g�̐ݒ�
	InitTranslucentBlendState();

	m_spriteBatch->Begin(
		DirectX::SpriteSortMode_Deferred,
		m_translucentBlendState,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		m_scaleMat
	);
}
void Font::End()
{
	m_spriteBatch->End();

	auto d3dDevice = g_graphicsEngine->GetD3DDeviceContext();
	//�����_�����O�X�e�[�g�𕜊�������B
	d3dDevice->OMSetBlendState(m_blendStateBackup, 0, 0xFFFFFFFF);
	d3dDevice->RSSetState(m_rasterrizerStateBackup);
	d3dDevice->OMSetDepthStencilState(m_depthStencilStateBackup, 0);
}

void Font::Draw(wchar_t const* text,const CVector2& position,const CVector4& color,float rotation,float scale,CVector2 pivot)
{
	if (text == nullptr) {
		return;
	}
	pivot.y = 1.0f - pivot.y;
	DirectX::XMFLOAT2 tkFloat2Zero(0, 0);
	//���W�n���X�v���C�g�ƍ��킹��B
	CVector2 pos = position;
	float frameBufferHalfWidth = FRAME_BUFFER_W * 0.5f;
	float frameBufferHalfHeight = FRAME_BUFFER_H * 0.5f;
	pos.x += frameBufferHalfWidth;
	pos.y = -pos.y + frameBufferHalfHeight;


	if (m_isDrawShadow) {
		//�e�������B
		CVector2 offsetTbl[] = {
			{ m_shadowOffset , 0.0f },
		{ -m_shadowOffset , 0.0f },
		{ 0.0f , m_shadowOffset },
		{ 0.0f , -m_shadowOffset },

		{ m_shadowOffset ,  m_shadowOffset },
		{ m_shadowOffset ,  -m_shadowOffset },
		{ -m_shadowOffset , m_shadowOffset },
		{ -m_shadowOffset , -m_shadowOffset },
		};
		for (auto offset : offsetTbl) {
			DirectX::FXMVECTOR xmv = DirectX::XMLoadFloat4(&m_shadowColor.vec);
			CVector2 sPos = pos;
			sPos.x += offset.x;
			sPos.y += offset.y;
			m_spriteFont->DrawString(
				m_spriteBatch,
				text,
				sPos.vec,
				xmv,
				rotation,
				DirectX::XMFLOAT2(pivot.x, pivot.y),
				scale
			);
		}

	}

	End();

	Begin();

	m_spriteFont->DrawString(
		m_spriteBatch,
		text,
		pos.vec,
		color,
		rotation,
		DirectX::XMFLOAT2(pivot.x, pivot.y),
		scale
	);

}

