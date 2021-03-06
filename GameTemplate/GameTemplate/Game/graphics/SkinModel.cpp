#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "ShadowMap.h"

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//定数バッファを解放。
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//サンプラステートを解放。
		m_samplerState->Release();
	}
	
	//ライト用の定数バッファの解放。
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}

}
void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	//スケルトンのデータを読み込む。
	InitSkeleton(filePath);

	//定数バッファの作成。
	InitConstantBuffer();

	//サンプラステートの初期化。
	InitSamplerState();

	//半透明合成のブレンドステートを初期化。
	InitTranslucentBlendState();

	//ディレクションライトの初期化。
	InitDirectionLight();
	//ポイントライトの初期化。
	//m_light.pointLight.InitPointLight();

	//SkinModelDataManagerを使用してCMOファイルのロード。
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{

	//スケルトンのデータを読み込む。
	//cmoファイルの拡張子をtksに変更する。
	std::wstring skeletonFilePath = filePath;
	//文字列から.cmoファイル始まる場所を検索。
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmoファイルを.tksに置き換える。
	skeletonFilePath.replace(pos, 4, L".tks");
	//tksファイルをロードする。
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//スケルトンが読み込みに失敗した。
		//アニメーションしないモデルは、スケルトンが不要なので
		//読み込みに失敗することはあるので、ログ出力だけにしておく。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tksファイルの読み込みに失敗しました。%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitConstantBuffer()
{
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SVSConstantBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);
	//ライト用の定数バッファを作成。
	bufferDesc.ByteWidth = (((sizeof(SLight) - 1) / 16) + 1) * 16;				//SDirectionLightは16byteの倍数になっているので、切り上げはやらない。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);

}
void SkinModel::InitDirectionLight() {
	//ディレクションライトの初期化。

	m_light.directionLight.direction[0] = { 1.0f, -1.0f, 0.0f, 0.0f };
	m_light.directionLight.direction[0].Normalize();	//正規化。
	m_light.directionLight.color[0] = { 0.5f, 0.5f, 0.5f, 1.0f };

	m_light.directionLight.direction[1] = { -1.0f, -1.0f, 0.0f, 0.0f };
	m_light.directionLight.direction[1].Normalize();	//正規化。
	m_light.directionLight.color[1] = { 0.2f, 0.2f, 0.2f, 1.0f };

	m_light.directionLight.direction[2] = { 0.0f, -1.0f, 1.0f, 0.0f };
	m_light.directionLight.direction[2].Normalize();	//正規化。
	m_light.directionLight.color[2] = { 0.2f, 0.2f, 0.2f, 1.0f };

	m_light.directionLight.direction[3] = { 0.0f, -1.0f, -1.0f, 0.0f };
	m_light.directionLight.direction[3].Normalize();	//正規化。
	m_light.directionLight.color[3] = { 0.2f, 0.2f, 0.2f, 1.0f };
	//鏡面反射光の絞り。
	m_light.specPow = 10.0f;
}
void SkinModel::InitSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
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
	//半透明描画用に
	//αブレンディング設定
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
	//例のごとく、作成するブレンドステートの情報を設定する。
	CD3D11_DEFAULT defaultSettings;
	//デフォルトセッティングで初期化する。
	CD3D11_BLEND_DESC blendDesc(defaultSettings);

	//αブレンディングを有効にする。
	blendDesc.RenderTarget[0].BlendEnable = true;

	//ソースカラーのブレンディング方法を指定している。
	//ソースカラーとはピクセルシェーダ―からの出力を指している。
	//この指定では、ソースカラーをSRC(rgba)とすると、
	//最終的なソースカラーは下記のように計算される。
	//最終的なソースカラー = SRC.rgb × SRC.a
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

	//ディスティネーションカラーのブレンディング方法を指定している。
	//ディスティネーションカラーとは、
	//すでに描き込まれているレンダリングターゲットのカラーを指している。
	//この指定では、ディスティネーションカラーをDEST(rgba)、
	//ソースカラーをSRC(RGBA)とすると、最終的なディスティネーションカラーは
	//下記のように計算される。
	//最終的なディスティネーションカラー = DEST.rgb × (1.0f - SRC.a)
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	//最終的にレンダリングターゲットに描き込まれるカラーの計算方法を指定している。
	//この指定だと、�@＋�Aのカラーが書き込まれる。
	//つまり、最終的にレンダリングターゲットに描き込まれるカラーは
	//SRC.rgb × SRC.a + DEST.rgb × (1.0f - SRC.a)
	//となる。
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//この設定で、ブレンドステートを作成すると
	//半透明合成を行えるブレンドステートが作成できる。
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	d3dDevice->CreateBlendState(&blendDesc, &m_translucentBlendState);

}

void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMaxと軸を合わせるためのバイアス。
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//平行移動行列を作成する。
	transMatrix.MakeTranslation( position );
	//回転行列を作成する。
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//拡大行列を作成する。
	scaleMatrix.MakeScaling(scale);
	//ワールド行列を作成する。
	//拡大×回転×平行移動の順番で乗算するように！
	//順番を間違えたら結果が変わるよ。
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//スケルトンの更新。
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Update()
{
	//更新。
	//ライト回転してるだけ。。
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
		//定数バッファの内容を更新。
		SVSConstantBuffer vsCb;
		vsCb.mWorld = m_worldMatrix;
		vsCb.mProj = projMatrix;
		vsCb.mView = viewMatrix;
		// ライトカメラのビュー、プロジェクション行列を送る。
		vsCb.mLightProj = shadowMap->GetLightProjMatrix();
		vsCb.mLightView = shadowMap->GetLightViewMatrix();

		//シャドウマップを使用するかどうか
		if (m_isShadowReciever == true) {
			vsCb.isShadowReciever = 1;
		}
		else {
			vsCb.isShadowReciever = 0;
		}
		//法線マップを使用するかどうかのフラグを送る。
		if (m_normalMapSRV != nullptr) {
			vsCb.isHasNormalMap = true;
		}
		else {
			vsCb.isHasNormalMap = false;
		}
		//スぺキュラマップを使用するかどうかのフラグを送る。
		if (m_specularSRV != nullptr) {
			vsCb.isHasSpecularMap = true;
		}
		else {
			vsCb.isHasSpecularMap = false;
		}
		//アンビエントマップを使用するかどうかのフラグを送る。
		if (m_ambientSRV != nullptr) {
			vsCb.isHasAmbientMap = true;
		}
		else {
			vsCb.isHasAmbientMap = false;
		}

		//定数バッファの更新
		d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
		//視点の設定。
		m_light.eyePos = g_camera3D.GetPosition();
		//ライト用の定数バッファを更新。
		d3dDeviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);
		//定数バッファをGPUに転送。
		d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
		d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
		//定数バッファをシェーダースロットに設定。
		d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
		d3dDeviceContext->PSSetConstantBuffers(2, 1, &m_shadowMapcb);

		//サンプラステートを設定。
		d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
		//ボーン行列をGPUに転送。
		m_skeleton.SendBoneMatrixArrayToGPU();
		//ブレンドステートを設定。
		d3dDeviceContext->OMSetBlendState(m_blendState, 0, 0xFFFFFFFF);
		//アルベドテクスチャを設定する。
		ID3D11ShaderResourceView* m_shadowMapSRV = g_goMgr->GetShadowMap()->GetShadowMapSRV();
		
		d3dDeviceContext->PSSetShaderResources(2, 1, &m_shadowMapSRV);

		//エフェクトにクエリを行う。
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			auto modelMaterial = reinterpret_cast<SkinModelEffect*>(material);
			modelMaterial->SetRenderMode(m_renderMode);
		});
		if (m_normalMapSRV != nullptr) {
			//法線マップが設定されていたらをレジスタt3に設定する。
			d3dDeviceContext->PSSetShaderResources(3, 1, &m_normalMapSRV);
		}
		if (m_specularSRV != nullptr) {
			//スぺキュラマップが設定されていたらをレジスタt4に設定する。
			d3dDeviceContext->PSSetShaderResources(4, 1, &m_specularSRV);
		}
		if (m_ambientSRV != nullptr) {
			//アンビエントマップが設定されていたらをレジスタt5に設定する。
			d3dDeviceContext->PSSetShaderResources(5, 1, &m_ambientSRV);
		}

		//描画。
		m_modelDx->Draw(
			d3dDeviceContext,
			state,
			m_worldMatrix,
			viewMatrix,
			projMatrix
		);
}