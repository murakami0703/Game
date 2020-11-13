#pragma once

/// <summary>
/// アクタークラス
/// </summary>
/// <remarks>
/// このクラスは2Dでの演出表現で必要になるメンバ変数、関数をまとめたクラスです。
/// タイトルなどのクラスはこのクラスを継承しています。
/// </remarks>
class SpriteIActor
{
public:
	/// <summary>
	/// SpriteRenderのアドレスを代入する
	/// 最初に実行してね！
	/// </summary>
	/// <param name="sp">ポインタ</param>
	void SpriteRenderSetting(class SpriteRender* sp, int No = -1) {
		m_spriteRender = sp;
	}

	SpriteIActor();
	~SpriteIActor();
	//スプライトの各種機能を提供させる。
	void SpriteSupporter_Update();
	//移動
	void SpriteMove(const CVector2& move, const int& moveTime,	const int& moveDelay, const bool& relative = false);
	void SpriteBound(); //バウンド。

		//状態取得用
	//スプライトの移動リスト要素数を取得
	//移動中のスプライトかどうかを判別する など
	int GetSpriteMoveListLen() {
		return static_cast<int>(m_spriteMoveList.size());
	}

private:
	void SpriteMoveUpdate();
	void SpriteDataReturn();

	//Move
	struct SpriteMoveSet {
		CVector2 m_spriteMovePos = { 0.0f,0.0f };			//スプライトの移動先
		CVector2 m_spriteMoveSpeed = { 0.0f,0.0f };			//スプライトの移動量
		int m_spriteMoveLimit = -1;							//スプライトの移動時間（-1は移動中ではない）
		int m_spriteMoveDelay = -1;							//スプライトの移動ディレイ
		int m_spriteMoveTimer = -1;							//スプライトの移動タイマー
		bool m_spriteMoveRelative = false;					//スプライトの相対移動フラグ（trueなら相対移動）
		bool m_spriteMoveDeleteFlag = false;				//削除フラグ（いじらないでね）
	};
	std::list<SpriteMoveSet> m_spriteMoveList;				//移動のリスト

protected:
	class SpriteRender* m_spriteRender;				//スプライトレンダー。
	CVector3 m_position = CVector3::Zero();					//座標
	CQuaternion m_rotation = CQuaternion().Identity();		//回転
	CVector3 m_scale = CVector3().One();					//拡大率
	CVector4 m_mulColor = { 1.0f,1.0f,1.0f,1.0f };			//乗算カラー
};

