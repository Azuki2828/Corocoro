#pragma once
#include "stdafx.h"

class LightCamera : Camera
{
	//���C�g�J�����̃C���X�^���X���쐬����֐��B
	static void CreateLightCamera() {

		m_lightCamera = new LightCamera;
	}
	//���C�g�J�����̃C���X�^���X���擾����֐��B
	static LightCamera* GetLightCamera() {

		return m_lightCamera;
	}
private:
	static LightCamera* m_lightCamera;		//���C�g�J�����̃C���X�^���X
	Vector3 m_pos = Vector3::Zero;			//���W
	Vector3 m_tar = Vector3::One;			//�^�[�Q�b�g
};

