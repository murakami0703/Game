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
	~MapChip();

	void Update();
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
	/// <summary>
	/// �@���}�b�v�̐ݒ�B
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
	SkinModel m_model;		//!<���f���B
	PhysicsStaticObject m_physicsStaticObject;	//!<�ÓI�����I�u�W�F�N�g�B

	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;
	ID3D11ShaderResourceView* g_specularMapSRV = nullptr;
	ID3D11ShaderResourceView* g_aoMapSRV = nullptr;

	
};