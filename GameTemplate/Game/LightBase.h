#pragma once
#include "stdafx.h"
#include "../../ExEngine/gameObject/IGameobject.h"

class LightBase : public IGameObject
{
	bool Start();
public:
	~LightBase();
	virtual bool StartSub() = 0;
	//���C�g�̃f�[�^���擾����֐��B
	virtual void* GetLigData() = 0;
};

