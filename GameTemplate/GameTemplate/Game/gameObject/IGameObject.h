#pragma once

typedef unsigned char	GameObjectPrio;

class IGameObject
{
public:
	IGameObject() :
		m_priority(0),
		m_isStart(false)
	{
	}
	/// <summary>
	/// Update�̒��O�ŌĂ΂��J�n����
	/// </summary>
	/// <returns></returns>
	virtual bool Start() { return true; }

	/// <summary>
	/// �X�V�B
	/// </summary>

	virtual void Update() = 0;

	/// <summary>
	/// �`��B
	/// </summary>
	
	virtual void Render() {}

	virtual void PostRender(){}

	/// <summary>
	/// ���s�D��x���擾
	/// </summary>
	GameObjectPrio GetPriority() const
	{
		return m_priority;
	}

	/// <summary>
	/// �폜���N�G�X�g
	/// </summary>
	
	void RequestDelete() {
		isReqDelete = true;
	}
	/// <summary>
	/// �폜���N�G�X�g���󂯂Ă��邩���ׂ�B
	/// </summary>
	/// <returns>
	/// true���Ԃ��Ă�����A���N�G�X�g���󂯂Ă���B
	/// </returns>
	
	bool IsRequestDelete() {
		return isReqDelete;
	}
private:
	bool m_isStart;						//Start�̊J�n�t���O�B
	bool isReqDelete = false;		//�폜���N�G�X�g�B
	GameObjectPrio m_priority;		//���s�D��x�B
	

};

