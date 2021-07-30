#pragma once

#include "stdafx.h"
#include "DirectionLight.h"
#include "LightBase.h"

static const int MAX_DIRECTION_LIGHT = 8;	//ディレクションライトの規定数

//輪郭線の種類
enum {
	Edge_NULL,
	Edge_1,
	Edge_2
};
struct LigData {
	DirectionLigData m_directionLigData[MAX_DIRECTION_LIGHT];	//ディレクションライトのデータ
	Vector3 eyePos = Vector3::Zero;								//視点の座標
	float pad;													//パディング
	Vector3 ambient;											//環境光
	float pad1;													//パディング
	Matrix m_viewProj;											//プロジェクション行列
	float metaric = 0.0f;										//金属度
	float smooth = 0.5f;										//なめらかさ
	int edge = Edge_NULL;										//輪郭線の種類
	float powValue = 0.0f;										//絞り率
	float uvNoiseMul = 0.0f;									//乗算するノイズの値
	float uvNoiseOffset = 0.0f;									//ノイズのオフセット
};

class LightManager
{
public:
	/**
	 * @brief ライトマネージャーのインスタンスを作成する関数。
	*/
	static void CreateInstance() {

		m_lightManager = new LightManager;
	}
	/**
	 * @brief ライトマネージャーのインスタンスを取得する関数。
	 * @return インスタンス
	*/
	static LightManager* GetInstance() {

		return m_lightManager;
	}

	void Update();

	/**
	 * @brief ライトを追加する関数。
	 * @param light ライトのインスタンス
	*/
	void AddLight(LightBase* light);

	/**
	 * @brief ライトを削除する関数。
	 * @param light ライトのインスタンス
	*/
	void RemoveLight(LightBase* light);

	/**
	 * @brief ライトのデータを取得する関数。
	 * @return ライトのデータ
	*/
	LigData* GetLigData() { return &m_ligData; }
private:
	LigData m_ligData;									//ライトのデータ
	static LightManager* m_lightManager;				//ライトマネージャーのインスタンス
	std::list<DirectionLigData*> m_directionLights;		//ディレクションライトのデータ
};

