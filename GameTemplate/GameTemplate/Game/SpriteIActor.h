#pragma once

/// <summary>
/// アクタークラス
/// </summary>
/// <remarks>
/// このクラスは2Dでの演出表現で必要になるメンバ変数、関数をまとめたクラスです。
/// タイトルなどのクラスはこのクラスを継承しています。
/// </remarks>
class SpriteIActor : public IGameObject
{
public:
	SpriteIActor();
	~SpriteIActor();

protected:
	SpriteRender* m_spriteRender;				//スプライトレンダー。

};

