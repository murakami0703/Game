#pragma once
#include "ItemBase.h"
/// <summary>
/// �񕜖�B
/// </summary>
class HpRecovery : public ItemBase
{
public:
	HpRecovery();
	~HpRecovery();


	bool Start() override;

	void InUse() override;		//�g�p���B
	void Flashing() override;	//�_�ŁB
	void EndUse() override;		//�I���B
private:
};

