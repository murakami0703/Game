#pragma once
class EffectManager : public IGameObject
{
	static EffectManager* m_instance;
public:

	//エフェクト名前
	enum EffectName {
		Null,
		test, //アイテム入手時のエフェクト
	};

	EffectManager();
	~EffectManager();

	//引数1→再生するエフェクト（種類はヘッダーに）
	//引数2→position
	//引数3→scale
	void EffectPlayer(EffectName EF, CVector3 position, CVector3 scale);

	//インスタンスの取得
	static EffectManager* EffectManager::GetInstance() {
		return m_instance;
	}

	bool Start();
	void Update();
private:

	//エフェクトファイル名
	wchar_t DetaBase[17][30]{
		{ L"" },//Nullなので何もない
		{ L"Assets/effect/test.efk" },
	};

	CVector3 m_scale = CVector3::One();
	CVector3 m_position = CVector3::Zero();

	EffectName m_stete = Null;		 //エフェクト状態
	wchar_t EF_Name[30] = { L"" };	//エフェクト名保管用
};

