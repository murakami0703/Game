#pragma once
class Result : public IGameObject
{
	static Result* m_instance;

public:
	Result();
	~Result();

	//�C���X�^���X�̎擾
	static Result* Result::GetInstance() {
		return m_instance;
	}

	void Update();

private:
	FontRender* m_font;

};

