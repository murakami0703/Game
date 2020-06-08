#pragma once
class Result : public IGameObject
{
	static Result* m_instance;

public:
	Result();
	~Result();

	//インスタンスの取得
	static Result* Result::GetInstance() {
		return m_instance;
	}
	//更新
	void Update();

private:
	void SpriteBound(SpriteRender& m_sprite);
private:
	enum eState {
		Result_Bound,
		Result_Topleft,
		Result_

	};
	enum eResultSprite {
		Result_R,
		Result_e,
		Result_s,
		Result_u,
		Result_l,
		Result_t
	};
private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_itemSprite;

	FontRender* m_font;

};

