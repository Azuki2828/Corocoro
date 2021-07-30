#pragma once
#include "LightBase.h"

/**
 * @brief ディレクションライトの情報。
*/
struct DirectionLigData {
	Vector3 Dir	= Vector3::Zero;	//方向
	float pad = 0.0f;				//パディング
	Vector4 Col	= Vector4::White;	//色
};

class DirectionLight : public LightBase
{
	bool StartSub();
	~DirectionLight();
public:
	/**
	 * @brief ライトの方向を設定する関数。
	 * @param _x x方向
	 * @param _y y方向
	 * @param _z z方向
	*/
	void SetLigDirection(float _x = 0.0f, float _y = -1.0f, float _z = 1.0f) {
		m_dirLigData.Dir.x = _x;
		m_dirLigData.Dir.y = _y;
		m_dirLigData.Dir.z = _z;
		//正規化。
		m_dirLigData.Dir.Normalize();
	}

	/**
	 * @brief ライトの方向を設定する関数。
	 * @param dir 方向
	*/
	void SetLigDirection(const Vector3& dir) {
		m_dirLigData.Dir = dir;
		//正規化。
		m_dirLigData.Dir.Normalize();
	}

	/**
	 * @brief ディレクションライトを取得。
	 * @return ディレクションライト
	*/
	Vector3* GetLigDirection() { 
		return &m_dirLigData.Dir;
	}

	/**
	 * @brief ライトの色を設定。
	 * @param _x 赤成分
	 * @param _y 緑成分
	 * @param _z 青成分
	*/
	void SetLigColor(float _x = 50.0f, float _y = 50.0f, float _z = 50.0f) {
		m_dirLigData.Col.x = _x;
		m_dirLigData.Col.y = _y;
		m_dirLigData.Col.z = _z;
	}

	/**
	 * @brief ライトの色を設定。
	 * @param col 色情報(RGB)
	*/
	void SetLigColor(const Vector3& col) {
		m_dirLigData.Col = col;
	}

	/**
	 * @brief ライトの情報を取得。
	 * @return ライトの情報
	*/
	void* GetLigData() { return &m_dirLigData; }

	ConstantBuffer cb;					//コンスタントバッファ
	DescriptorHeap ds;					//ディスクリプタヒープ
	DirectionLigData m_dirLigData;		//ディレクションライトの情報
};