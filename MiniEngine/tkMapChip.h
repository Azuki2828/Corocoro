/*!
 *@brief	マップチップ
 */

#pragma once

#include "physics/PhysicsStaticObject.h"
//#include "tkEngine/physics/tkPhysicsStaticObject.h"
//#include "tkEngine/level/tkMapChipRender.h"

namespace tkEngine{
	struct LevelObjectData;
	//class CMapChipRender;
	/*!
	 *@brief	マップチップ。
	 */
	class CMapChip{
	public:
		CMapChip(const LevelObjectData& objData/*, CMapChipRender* mapChipRender*/);
		/*!
		*@brief	スキンモデルレンダラーを取得。
		*/
		//prefab::CSkinModelRender* GetSkinModelRender()
		//{
		//	if (m_mapChipRender == nullptr ){
		//		return nullptr;
		//	}
		//	return m_mapChipRender->GetSkinModelRender();
		//}
		
	private:
		//CMapChipRender* m_mapChipRender = nullptr;			//マップチップレンダラー。
		PhysicsStaticObject m_physicsStaticObject;			//!<静的物理オブジェクト。
	};
}
