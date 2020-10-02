#pragma once
class InUseItemUI : public IGameObject
{
public:
	InUseItemUI();
	~InUseItemUI();

	bool Start();
	void Update();

private:
	std::vector<SpriteRender*> m_spriteRender;	//�X�v���C�g�̓��I�z��
	SpriteRender* m_itemSprite;

	CVector3 m_framePos = { 460.0f,-240.0f,0.0f };		//�t���[���̍��W
	CVector3 m_itemPos = { 560.0f,-120.0f,0.0f };		//�A�C�e���̍��W

};

