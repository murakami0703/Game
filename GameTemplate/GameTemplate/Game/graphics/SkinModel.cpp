#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "ShadowMap.h"

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//�萔�o�b�t�@������B
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//�T���v���X�e�[�g������B
		m_samplerState->Release();
	}
	
	//���C�g�p�̒萔�o�b�t�@�̉���B
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}

}
void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//�X�P���g���̃f�[�^��ǂݍ��ށB
	InitSkeleton(filePath);

	//�萔�o�b�t�@�̍쐬�B
	InitConstantBuffer();

	//�T���v���X�e�[�g�̏������B
	InitSamplerState();

	//�����������̃u�����h�X�e�[�g���������B
	InitTranslucentBlendState();

	//�f�B���N�V�������C�g�̏������B
	InitDirectionLight();
	//�|�C���g���C�g�̏������B
	//m_light.pointLight.InitPointLight();

	//SkinModelDataManager���g�p����CMO�t�@�C���̃��[�h�B
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{

	//�X�P���g���̃f�[�^��ǂݍ��ށB
	//cmo�t�@�C���̊g���q��tks�ɕύX����B
	std::wstring skeletonFilePath = filePath;
	//�����񂩂�.cmo�t�@�C���n�܂�ꏊ�������B
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmo�t�@�C����.tks�ɒu��������B
	skeletonFilePath.replace(pos, 4, L".tks");
	//tks�t�@�C�������[�h����B
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//�X�P���g�����ǂݍ��݂Ɏ��s�����B
		//�A�j���[�V�������Ȃ����f���́A�X�P���g�����s�v�Ȃ̂�
		//�ǂݍ��݂Ɏ��s���邱�Ƃ͂���̂ŁA���O�o�͂����ɂ��Ă����B
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tks�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitConstantBuffer()
{
	//�쐬����o�b�t�@�̃T�C�Y��sizeof���Z�q�ŋ��߂�B
	int bufferSize = sizeof(SVSConstantBuffer);
	//�ǂ�ȃo�b�t�@���쐬����̂�������bufferDesc�ɐݒ肷��B
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//�O�ŃN���A�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�őz�肳��Ă���A�ǂݍ��݂���я������ݕ��@�B
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//�o�b�t�@��16�o�C�g�A���C�����g�ɂȂ��Ă���K�v������B
																//�A���C�����g���ā��o�b�t�@�̃T�C�Y��16�̔{���Ƃ������Ƃł��B
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//�o�b�t�@���ǂ̂悤�ȃp�C�v���C���Ƀo�C���h���邩���w�肷��B
																//�萔�o�b�t�@�Ƀo�C���h����̂ŁAD3D11_BIND_CONSTANT_BUFFER���w�肷��B
	bufferDesc.CPUAccessFlags = 0;								//CPU �A�N�Z�X�̃t���O�ł��B
																//CPU�A�N�Z�X���s�v�ȏꍇ��0�B
	//�쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);
	//���C�g�p�̒萔�o�b�t�@���쐬�B
	bufferDesc.ByteWidth = (((sizeof(SLight) - 1) / 16) + 1) * 16;				//SDirectionLight��16byte�̔{���ɂȂ��Ă���̂ŁA�؂�グ�͂��Ȃ��B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);

}
void SkinModel::InitDirectionLight() {
	//�f�B���N�V�������C�g�̏������B

	m_light.directionLight.direction[0] = { 1.0f, -1.0f, 0.0f, 0.0f };
	m_light.directionLight.direction[0].Normalize();	//���K���B
	m_light.directionLight.color[0] = { 0.5f, 0.5f, 0.5f, 1.0f };

	m_light.directionLight.direction[1] = { -1.0f, -1.0f, 0.0f, 0.0f };
	m_light.directionLight.direction[1].Normalize();	//���K���B
	m_light.directionLight.color[1] = { 0.2f, 0.2f, 0.2f, 1.0f };

	m_light.directionLight.direction[2] = { 0.0f, -1.0f, 1.0f, 0.0f };
	m_light.directionLight.direction[2].Normalize();	//���K���B
	m_light.directionLight.color[2] = { 0.2f, 0.2f, 0.2f, 1.0f };

	m_light.directionLight.direction[3] = { 0.0f, -1.0f, -1.0f, 0.0f };
	m_light.directionLight.direction[3].Normalize();	//���K���B
	m_light.directionLight.color[3] = { 0.2f, 0.2f, 0.2f, 1.0f };
	//���ʔ��ˌ��̍i��B
	m_light.specPow = 10.0f;
}
void SkinModel::InitSamplerState()
{
	//�e�N�X�`���̃T���v�����O���@���w�肷�邽�߂̃T���v���X�e�[�g���쐬�B
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
	
}
void SkinModel::InitAlphaBlendState()
{
	//�������`��p��
	//���u�����f�B���O�ݒ�
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_BLUE | D3D11_COLOR_WRITE_ENABLE_GREEN;

	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	pd3d->CreateBlendState(&blendDesc, &m_blendState);

}
void SkinModel::InitTranslucentBlendState()
{
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
	//�ŏI�I�ȃ\�[�X�J���[ = SRC.rgb �~ SRC.a
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

	//�f�B�X�e�B�l�[�V�����J���[�̃u�����f�B���O���@���w�肵�Ă���B
	//�f�B�X�e�B�l�[�V�����J���[�Ƃ́A
	//���łɕ`�����܂�Ă��郌���_�����O�^�[�Q�b�g�̃J���[���w���Ă���B
	//���̎w��ł́A�f�B�X�e�B�l�[�V�����J���[��DEST(rgba)�A
	//�\�[�X�J���[��SRC(RGBA)�Ƃ���ƁA�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[��
	//���L�̂悤�Ɍv�Z�����B
	//�ŏI�I�ȃf�B�X�e�B�l�[�V�����J���[ = DEST.rgb �~ (1.0f - SRC.a)
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

void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMax�Ǝ������킹�邽�߂̃o�C�A�X�B
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//���s�ړ��s����쐬����B
	transMatrix.MakeTranslation( position );
	//��]�s����쐬����B
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//�g��s����쐬����B
	scaleMatrix.MakeScaling(scale);
	//���[���h�s����쐬����B
	//�g��~��]�~���s�ړ��̏��Ԃŏ�Z����悤�ɁI
	//���Ԃ��ԈႦ���猋�ʂ��ς���B
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//�X�P���g���̍X�V�B
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Update()
{
	//�X�V�B
	//���C�g��]���Ă邾���B�B
	/*CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	for (int i = 0; i < Dcolor; i++) {
		qRot.Multiply(m_light.directionLight.direction[i]);
	}*/

}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix, EnRenderMode m_renderMode)
{
		ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
		DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

		auto shadowMap = g_goMgr->GetShadowMap();
		//�萔�o�b�t�@�̓��e���X�V�B
		SVSConstantBuffer vsCb;
		vsCb.mWorld = m_worldMatrix;
		vsCb.mProj = projMatrix;
		vsCb.mView = viewMatrix;
		// ���C�g�J�����̃r���[�A�v���W�F�N�V�����s��𑗂�B
		vsCb.mLightProj = shadowMap->GetLightProjMatrix();
		vsCb.mLightView = shadowMap->GetLightViewMatrix();

		//�V���h�E�}�b�v���g�p���邩�ǂ���
		if (m_isShadowReciever == true) {
			vsCb.isShadowReciever = 1;
		}
		else {
			vsCb.isShadowReciever = 0;
		}
		//�@���}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
		if (m_normalMapSRV != nullptr) {
			vsCb.isHasNormalMap = true;
		}
		else {
			vsCb.isHasNormalMap = false;
		}
		//�X�؃L�����}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
		if (m_specularSRV != nullptr) {
			vsCb.isHasSpecularMap = true;
		}
		else {
			vsCb.isHasSpecularMap = false;
		}
		//�A���r�G���g�}�b�v���g�p���邩�ǂ����̃t���O�𑗂�B
		if (m_ambientSRV != nullptr) {
			vsCb.isHasAmbientMap = true;
		}
		else {
			vsCb.isHasAmbientMap = false;
		}

		//�萔�o�b�t�@�̍X�V
		d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
		//���_�̐ݒ�B
		m_light.eyePos = g_camera3D.GetPosition();
		//���C�g�p�̒萔�o�b�t�@���X�V�B
		d3dDeviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);
		//�萔�o�b�t�@��GPU�ɓ]���B
		d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
		d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
		//�萔�o�b�t�@���V�F�[�_�[�X���b�g�ɐݒ�B
		d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
		d3dDeviceContext->PSSetConstantBuffers(2, 1, &m_shadowMapcb);

		//�T���v���X�e�[�g��ݒ�B
		d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
		//�{�[���s���GPU�ɓ]���B
		m_skeleton.SendBoneMatrixArrayToGPU();
		//�u�����h�X�e�[�g��ݒ�B
		d3dDeviceContext->OMSetBlendState(m_blendState, 0, 0xFFFFFFFF);
		//�A���x�h�e�N�X�`����ݒ肷��B
		ID3D11ShaderResourceView* m_shadowMapSRV = g_goMgr->GetShadowMap()->GetShadowMapSRV();
		
		d3dDeviceContext->PSSetShaderResources(2, 1, &m_shadowMapSRV);

		//�G�t�F�N�g�ɃN�G�����s���B
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			auto modelMaterial = reinterpret_cast<SkinModelEffect*>(material);
			modelMaterial->SetRenderMode(m_renderMode);
		});
		if (m_normalMapSRV != nullptr) {
			//�@���}�b�v���ݒ肳��Ă���������W�X�^t3�ɐݒ肷��B
			d3dDeviceContext->PSSetShaderResources(3, 1, &m_normalMapSRV);
		}
		if (m_specularSRV != nullptr) {
			//�X�؃L�����}�b�v���ݒ肳��Ă���������W�X�^t4�ɐݒ肷��B
			d3dDeviceContext->PSSetShaderResources(4, 1, &m_specularSRV);
		}
		if (m_ambientSRV != nullptr) {
			//�A���r�G���g�}�b�v���ݒ肳��Ă���������W�X�^t5�ɐݒ肷��B
			d3dDeviceContext->PSSetShaderResources(5, 1, &m_ambientSRV);
		}

		//�`��B
		m_modelDx->Draw(
			d3dDeviceContext,
			state,
			m_worldMatrix,
			viewMatrix,
			projMatrix
		);
}