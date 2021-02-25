#pragma once

#include "MapChip.h"
#include "TklFile.h"

struct LevelObjectData {
	Vector3 position;		//<座標。
	Quaternion rotation;	//!<回転。
	Vector3 scale;			//!<拡大率。
	const wchar_t* name;	//!<名前。
	/*!
	* @brief	引数で渡したオブジェクト名のオブジェクトか調べる。
	*@param[in]	objName		調べる名前。
	*@return	名前が同じ場合にtrueを返します。
	*/
	bool EqualObjectName(const wchar_t* objName)
	{
		return wcscmp(objName, name) == 0;
	}
	/*!
	* @brief	名前が前方一致するか調べる。
	*/
	bool ForwardMatchName(const wchar_t* n)
	{
		auto len = wcslen(n);
		auto namelen = wcslen(name);
		if (len > namelen) {
			//名前が長い。不一致。
			return false;
		}
		return wcsncmp(n, name, len) == 0;
	}
};

class Level
{
public:
	void Init(const char* filePath, std::function<bool(LevelObjectData& objData)> hookFunc);
	void Draw(RenderContext& rc);
private:
	TklFile m_tklFile;
	std::vector<std::unique_ptr<MapChip>> m_mapChipPtrs;			//マップチップの可変長配列。
};

