/*!
 *@brief	マップチップ
 */

#pragma once

#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkMapChipRender.h"

	struct LevelObjectData;
	class CMapChipRender;
	/*!
	 *@brief	マップチップ。
	 */
	class CMapChip : Noncopyable{
	public:
		CMapChip(const LevelObjectData& objData, CMapChipRender* mapChipRender);
		~CMapChip()
		{
		}
		/*!
		*@brief	スキンモデルレンダラーを取得。
		*/
		prefab::CSkinModelRender* GetSkinModelRender()
		{
			if (m_mapChipRender == nullptr ){
				return nullptr;
			}
			return m_mapChipRender->GetSkinModelRender();
		}
		
	private:
		CMapChipRender* m_mapChipRender = nullptr;			//マップチップレンダラー。
		CPhysicsStaticObject m_physicsStaticObject;			//!<静的物理オブジェクト。
	};
