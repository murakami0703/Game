#pragma once

#include "physics/PhysicsStaticObject.h"

class Level;
struct LevelObjectData;

/*!
* @brief	�}�b�v�`�b�v�B
*/
class MapChip {
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*@param[in] objData			�I�u�W�F�N�g���B
	*/
	MapChip(LevelObjectData& objData,
		std::function<void(LevelObjectData& objData, MapChip& mapchip)> onBuildMapchip
	);
	/*!
	* @brief	�`��B
	*/
	void Draw();
	/// <summary>
	/// �X�L�����f�����擾
	/// </summary>
	/// <returns></returns>
	SkinModel& GetSkinModel()
	{
		return m_model;
	}

private:
	SkinModel m_model;		//!<���f���B
	PhysicsStaticObject m_physicsStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B
	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;

	
};