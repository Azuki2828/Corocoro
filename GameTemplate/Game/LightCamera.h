#pragma once
#include "stdafx.h"

class LightCamera : Camera
{
	static void CreateLightCamera() {

		m_lightCamera = new LightCamera;
	}
	static LightCamera* GetLightCamera() {

		return m_lightCamera;
	}
private:
	static LightCamera* m_lightCamera;
	Vector3 m_pos;
	Vector3 m_tar;
};

