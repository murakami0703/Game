#pragma once
#include "physics/PhysicsGhostObject.h"
class StageGate : public IGameObject
{
public:
	StageGate();
	~StageGate();

	bool Start();
	void Update();

	/// <summary>
	/// �Q�[�g�o����������B
	/// </summary>
	bool IsGate() const
	{
		return m_isGate;
	}

private:
	PhysicsGhostObject m_ghostObject1;

	bool m_isGate = false;
};

