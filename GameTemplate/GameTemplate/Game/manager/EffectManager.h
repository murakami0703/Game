#pragma once
class EffectManager : public IGameObject
{
	static EffectManager* m_instance;
public:

	//エフェクト名前
	enum EffectName {
		Null,
		open,			//アイテム入手時のエフェクト
		Bat_Attack,		//アイテム入手時のエフェクト
		Bat_memai,		//アイテム入手時のエフェクト
		Item_Get,		//アイテム入手時のエフェクト
		bat_pre,		//アイテム入手時のエフェクト
		Enemy_Dead,		//アイテム入手時のエフェクト
		bund,
		Golem_Attack,	//ゴーレム攻撃時のエフェクト
		NumEffect,		//エフェクトの数。
	};

	EffectManager();
	~EffectManager();

	//引数1→再生するエフェクト（種類はヘッダーに）
	//引数2→position
	//引数3→scale
	void EffectPlayer(EffectName EF, CVector3 position, CVector3 scale, CQuaternion m_rotation);
	void EffectPlayer(EffectName EF, CVector3 position, CVector3 scale);

	//インスタンスの取得
	static EffectManager* EffectManager::GetInstance() {
		return m_instance;
	}

	bool Start();
	void Update();
private:

	//エフェクトファイル名
	wchar_t DetaBase[NumEffect][MAX_PATH]{
		{ L"" },//Nullなので何もない
		{ L"Assets/effect/open_Box.efk" },
		{ L"Assets/effect/bat_attackEfk.efk" },
		{ L"Assets/effect/bat_vertigo.efk" },
		{ L"Assets/effect/item_Appear.efk" },
		{ L"Assets/effect/bat_premove.efk" },
		{ L"Assets/effect/enemy_dead.efk" },
		{ L"Assets/effect/baund.efk" },
		{ L"Assets/effect/Golem_Attack.efk" }
	};

	CVector3 m_scale = CVector3::One();
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion().Identity();	//!<回転。

	EffectName m_stete = Null;		 //エフェクト状態
	wchar_t EF_Name[30] = { L"" };	//エフェクト名保管用
};

