#pragma once

/// <summary>
/// アクタークラス
/// </summary>
/// <remarks>
/// このクラスは多くのスプライトで必要になるメンバ変数、関数をまとめたクラスです。
/// タイトルなどのクラスはこのクラスを継承しています。
/// </remarks>

class SpriteIActor : public IGameObject
{
public:
	SpriteIActor();
	~SpriteIActor();
};

