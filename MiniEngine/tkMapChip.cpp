/*!
 *@brief	マップチップ
 */
//#include "tkEngine/tkEnginePreCompile.h"
#include "MiniEngine.h"
#include "tkMapChip.h"
#include "tkLevel.h"

namespace tkEngine{
	CMapChip::CMapChip(const LevelObjectData& objData/*, CMapChipRender* mapChipRender*/)
	{
		char objName[256];
		wcstombs(objName, objData.name, 256);
		
		//ファイルパスを作成。
		wchar_t filePath[256];
		swprintf_s(filePath, L"modelData/%s.tkm", objData.name);
		//m_mapChipRender = mapChipRender;
		m_physicsStaticObject.CreateMesh( 
			objData.position, 
			objData.rotation,
			objData.scale
			//mapChipRender->GetSkinModelRender()
		);
	}
}
