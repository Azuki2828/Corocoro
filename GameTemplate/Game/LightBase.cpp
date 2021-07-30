#include "stdafx.h"
#include "LightBase.h"

bool LightBase::Start() {

	//ライトマネージャーにライトを追加する。
	LightManager::GetInstance()->AddLight(this);
	return StartSub();
}

LightBase::~LightBase() {

	//ライトマネージャーからライトを削除する。
	LightManager::GetInstance()->RemoveLight(this);
}
