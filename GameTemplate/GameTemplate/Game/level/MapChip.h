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

private:
	SkinModel m_model;		//!<モデル。
	PhysicsStaticObject m_physicsStaticObject;	//!<静的物理オブジェクト。
	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;

	
};