#pragma once
#
class ItemBase : public IActor
{
public:
	enum eState {
		In_Use,
		Flashing_Use,
		End_Use
	};

	ItemBase();
	~ItemBase();
	void Update() override;

	eState GetState() {
		return m_state;
	}

	void SetState(const eState& state) {
		m_state = state;
	}

	virtual void InUse() = 0;
	virtual void Flashing() = 0;
	virtual void EndUse() = 0;	
private:
	eState m_state = In_Use;

};

