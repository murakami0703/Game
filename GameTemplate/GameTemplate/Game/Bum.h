#pragma once
#include "ItemBase.h"
/// <summary>
/// ���e�B
/// </summary>
class Bum : public ItemBase
{
public:
	Bum();
	~Bum();

	bool Start() override;

	void InUse() override;		//�g�p���B
	void Flashing() override;	//�_�ŁB
	void EndUse() override;		//�I���B
private:

};

