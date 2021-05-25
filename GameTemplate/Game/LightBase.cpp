#include "stdafx.h"
#include "LightBase.h"

bool LightBase::Start() {

	LightManager::GetInstance()->AddLight(this);
	return StartSub();
}

LightBase::~LightBase() {

	LightManager::GetInstance()->RemoveLight(this);
}
