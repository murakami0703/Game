#pragma once
#include "item/ItemBase.h"
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
	void EndUse() override;		//�I���B
private:

};

