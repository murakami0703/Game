#pragma once
class SoulManager : public IGameObject
{
	static SoulManager* m_instance;
public:
	SoulManager();
	~SoulManager();

	bool Start();
	//�X�V
	void Update();
	//���̐���
	void SoulGenerated(CVector3 position);

	//�C���X�^���X�̎擾
	static SoulManager* SoulManager::GetInstance() {
		return m_instance;
	}

private:
	CVector3 m_position = CVector3::Zero();	//���W

};

