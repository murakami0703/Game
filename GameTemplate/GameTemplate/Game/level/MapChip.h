#pragma once

#include "physics/PhysicsStaticObject.h"

class Level;
struct LevelObjectData;

/*!
* @brief	マップチップ。
*/
class MapChip {
public:
	/*!
	* @brief	コンストラクタ。
	*@param[in] objData			オブジェクト情報。
	*/
	MapChip(LevelObjectData& objData,
		std::function<void(LevelObjectData& objData, MapChip& mapchip)> onBuildMapchip
	);
	~MapChip();

	void Update();
	/*!
	* @brief	描画。
	*/
	void Draw();
	/// <summary>
	/// スキンモデルを取得
	/// </summary>
	/// <returns></returns>
	SkinModel& GetSkinModel()
	{
		return m_model;
	}
	/// <summary>
	/// 法線マップの設定。
	/// </summary>
	void SetNormalMap(ID3D11ShaderResourceView* nomal) {
		g_normalMapSRV = nomal;
		m_model.SetNormalMap(g_normalMapSRV);
	}
	void SetSpecularMap(ID3D11ShaderResourceView* specular) {
		g_specularMapSRV = specular;
		m_model.SetSpecularMap(g_specularMapSRV);
	}
	void SetAoMap(ID3D11ShaderResourceView* ao) {
		g_aoMapSRV = ao;
		m_model.SetAmbientMap(g_aoMapSRV);
	}

private:
	SkinModel m_model;		//!<モデル。
	PhysicsStaticObject m_physicsStaticObject;	//!<静的物理オブジェクト。

	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;
	ID3D11ShaderResourceView* g_specularMapSRV = nullptr;
	ID3D11ShaderResourceView* g_aoMapSRV = nullptr;

	
};