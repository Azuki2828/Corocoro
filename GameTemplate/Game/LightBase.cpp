#include "stdafx.h"
#include "LightBase.h"

bool LightBase::Start() {

	//���C�g�}�l�[�W���[�Ƀ��C�g��ǉ�����B
	LightManager::GetInstance()->AddLight(this);
	return StartSub();
}

LightBase::~LightBase() {

	//���C�g�}�l�[�W���[���烉�C�g���폜����B
	LightManager::GetInstance()->RemoveLight(this);
}
