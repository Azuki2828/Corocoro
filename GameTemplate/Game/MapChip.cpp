#include "stdafx.h"
#include "MapChip.h"

struct LevelObjectData;

MapChip::MapChip(const LevelObjectData& objData) {

	char objName[256];
	wcstombs(objName, objData.name, 256);


	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->SetFileNametks("Assets/modelData/Player_N.tks");
	m_skinModelRender->Init(true, false);

	//ファイルパスを作成。
	char filePathtkm[256];
	printf_s(filePathtkm, L"modelData/%s.tkm", objData.name);
	m_skinModelRender->SetFileNametkm(static_cast<const char*>(filePathtkm));

	char filePathtks[256];
	printf_s(filePathtks, L"modelData/%s.tks", objData.name);
	m_skinModelRender->SetFileNametkm(static_cast<const char*>(filePathtks));

	m_physicsStaticObject.CreateFromModel(
		*m_skinModelRender->GetModel(),
		m_skinModelRender->GetModel()->GetWorldMatrix()
	);
}