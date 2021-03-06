#pragma once

#include "Skeleton.h"
#include "light/PointLight.h"
#include "SkinModelEffect.h"

/*!
*@brief	FBXの上方向。
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
/*!
*@brief	スキンモデルクラス。
*/
class SkinModel
{
public:
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	ボーンを検索。
	*@param[in]		boneName	ボーンの名前。
	*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	モデルを描画。
	*@param[in]	viewMatrix		カメラ行列。
	*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	*@param[in]	projMatrix		プロジェクション行列。
	*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix , EnRenderMode m_renderMode = enRenderMode_Normal);
	/*!
	*@brief	スケルトンの取得。
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	メッシュを検索する。
	*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}
	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// シャドウレシーバーのフラグを設定。
	/// </summary>
	/// <param name="flag"></param>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}
	/// <summary>
	/// シャドウキャスターのフラグを設定。
	/// </summary>
	/// <param name="flag"></param>
	void SetShadowCaster(bool flag)
	{
	}

	/// <summary>
/// a値の設定
/// </summary>
	void SetAlpha(const float& alpha)
	{
		m_alpha = alpha;
	}
	/// <summary>
	/// a値を取得
	/// </summary>
	float GetAlpha()
	{
		return m_alpha;
	}

	/// <summary>
	/// α値を変位させる
	/// </summary>
	/// <param name="delta">乗算αを変位させる量</param>
	void DeltaAlpha(float delta)
	{
		m_alpha += delta;
		//数値の境界チェック。
		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;
		}
		else if (m_alpha < 0.0f) {
			m_alpha = 0.0f;
		}
	}


	/// <summary>
	/// ライトの設定。
	/// </summary>
	void SetLightColor(CVector4 color) {
		m_light.directionLight.color[0] = color;
	}
	/// <summary>
	/// 法線マップの設定。
	/// </summary>
	void SetNormalMap(ID3D11ShaderResourceView* srv)
	{
		m_normalMapSRV = srv;
	}
	/// <summary>
	/// スぺキュラマップの設定。
	/// </summary>
	void SetSpecularMap(ID3D11ShaderResourceView* srv)
	{
		m_specularSRV = srv;
	}
	/// <summary>
	/// アンビエントマップの設定。
	/// </summary>
	void SetAmbientMap(ID3D11ShaderResourceView* srv)
	{
		m_ambientSRV = srv;
	}

private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState();
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);
	/// <summary>
	/// αブレンディングステートの設定。
	/// </summary>
	void InitAlphaBlendState();

	/// <summary>
	/// ブレンドステートの初期化。
	/// </summary>
	void InitTranslucentBlendState();

	/// <summary>
	/// ディレクションライトの初期化。
	/// </summary>
	void InitDirectionLight();

	static const int Dcolor = 4;

private:
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		CMatrix mLightView;		// ライトビュー行列。
		CMatrix mLightProj;		// ライトプロジェクション行列。
		float alpha;			//α値。
		int isShadowReciever;	// シャドウレシーバーのフラグ。
		int isHasNormalMap;		//法線マップのフラグ
		int isHasSpecularMap;	//スぺキュラマップのフラグ。
		int isHasAmbientMap;	//アンビエントマップのフラグ
	};
	//ディレクションライトの定数バッファ
	struct SDirectionLight {
		CVector4 direction[Dcolor];		//ライトの方向。
		CVector4 color[Dcolor];			//ライトのカラー。
	};
	//シャドウマップの定数バッファ
	struct ShadowMapConstantBuffer {
		CMatrix lightViewProjMatrix;
	};
	//ライト構造体
	struct SLight {
		SDirectionLight		directionLight;		//ディレクションライト
	//	PointLight			pointLight;			//ポイントライト
		CVector3			eyePos;				//視点の座標。
		float				specPow;			//鏡面反射の絞り。
		CVector3			EnvironmentLight = {0.2f,0.2f,0.2f};				//環境光。
	};

	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
	ID3D11Buffer*		m_lightCb = nullptr;			//!<ライト用の定数バッファ。
	SLight				m_light;						//!<ライトの構造体。
	ID3D11Buffer*		m_shadowMapcb = nullptr;		//!<シャドウマップ用の定数バッファ。

	ID3D11BlendState* m_translucentBlendState = nullptr;	//半透明合成用のブレンドステート。
	float						m_alpha = 1.0f;				//!<モデルのα値。
	ID3D11BlendState*			m_blendState = nullptr;		//!<ブレンドステート。

	ID3D11ShaderResourceView* m_normalMapSRV = nullptr;		//法線マップのSRV
	ID3D11ShaderResourceView* m_specularSRV = nullptr;		//スぺキュラマップのSRV
	ID3D11ShaderResourceView* m_ambientSRV = nullptr;		//アンビエントマップのSRV

	bool m_isShadowReciever = false;						//シャドウレシーバーのフラグ。
	bool m_isShadowCaster = false;							//シャドウレシーバーのフラグ。

};

