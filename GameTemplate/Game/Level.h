#pragma once

#include "MapChip.h"
#include "TklFile.h"

struct LevelObjectData {
	Vector3 position;		//<���W�B
	Quaternion rotation;	//!<��]�B
	Vector3 scale;			//!<�g�嗦�B
	const wchar_t* name;	//!<���O�B
	/*!
	* @brief	�����œn�����I�u�W�F�N�g���̃I�u�W�F�N�g�����ׂ�B
	*@param[in]	objName		���ׂ閼�O�B
	*@return	���O�������ꍇ��true��Ԃ��܂��B
	*/
	bool EqualObjectName(const wchar_t* objName)
	{
		return wcscmp(objName, name) == 0;
	}
	/*!
	* @brief	���O���O����v���邩���ׂ�B
	*/
	bool ForwardMatchName(const wchar_t* n)
	{
		auto len = wcslen(n);
		auto namelen = wcslen(name);
		if (len > namelen) {
			//���O�������B�s��v�B
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
	std::vector<std::unique_ptr<MapChip>> m_mapChipPtrs;			//�}�b�v�`�b�v�̉ϒ��z��B
};

