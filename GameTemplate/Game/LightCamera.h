#pragma once
#include "stdafx.h"

class LightCamera : Camera
{
	//ライトカメラのインスタンスを作成する関数。
	static void CreateLightCamera() {

		m_lightCamera = new LightCamera;
	}
	//ライトカメラのインスタンスを取得する関数。
	static LightCamera* GetLightCamera() {

		return m_lightCamera;
	}
private:
	static LightCamera* m_lightCamera;		//ライトカメラのインスタンス
	Vector3 m_pos = Vector3::Zero;			//座標
	Vector3 m_tar = Vector3::One;			//ターゲット
};

