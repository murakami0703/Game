#pragma once
class PointLight
{
public:
	PointLight();
	~PointLight();
	void Update();		//更新。
	/// <summary>
	/// ポイントライトの初期化。
	/// </summary>
	void InitPointLight();

	static const int NUM_POINT_LIGHT = 4;

	//ポイントライトの定数バッファ
	struct SPointLight {
		CVector3 position[NUM_POINT_LIGHT];		//ライトの位置。
		CVector4 color[NUM_POINT_LIGHT];			//ライトのカラー。
		CVector4 attn[NUM_POINT_LIGHT];			//ライトの減衰用パラメーター。
	};
private:
	SPointLight	light;

};

