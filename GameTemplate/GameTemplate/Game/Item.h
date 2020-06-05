#pragma once
class Item : public IGameObject
{
public:
	Item();
	~Item();

	void Update();
private:
	void ItemCountMove(FontRender* m_font);	//アイテム増減時に上に動かす。
private:
	std::vector<SpriteRender*> m_spriteRender;	//スプライトの動的配列
	SpriteRender* m_itemSprite;

	FontRender* m_itemFont1;
	FontRender* m_itemFont2;
	FontRender* m_itemFont3;
	FontRender* m_itemFont4;

private:
	CVector3 m_itemC1Pos = { 460.0f,-240.0f,0.0f };		//アイテム1の座標
	CVector3 m_itemC2Pos = { 560.0f,-120.0f,0.0f };		//アイテム2の座標
	CVector3 m_itemC3Pos = { 475.0f,-50.0f,0.0f };		//アイテム3の座標
	CVector3 m_itemC4Pos = { 545.0f,-3.0f,0.0f };		//アイテム4の座標

	//アイテム関連
};

