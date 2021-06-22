#pragma once

class Player;
class DirectionLight;
class MapChip;

namespace {

	const float CAMERA_ROT_WAIT_TIME = 1.5f;
	const int ROT_NUM = 90;
}

class MainCamera : public IGameObject
{
private:
	bool Start() override final;
	void Update() override final;
	void FreeUpdate() override final;

public:
	bool GetCameraScrollFlg() {
		return m_cameraScrollFlag;
	}

	void SetRotFlg(bool flg) {
		m_rotFlg = flg;
	}

	//1�񂾂��J������180�x��]�����邽�߂̃t���O
	std::list<std::function< void() >> changeRotCameraEvent;
private:
	bool m_cameraScrollFlag = true;
	bool m_cameraRotFlg = false;
	bool m_rotFlg = false;
	int m_count = 0;
	int m_cameraPosFlag = 0;
	int m_scrollStaticTimer = 0;
	float m_waitRot = 0.0f;
	Vector3 m_pos = Vector3::Zero;		//���_�B
	Vector3 m_tar = Vector3::Zero;		//�����_�B
	Vector3 m_rotAxis = { 0.0f,1.0f,0.0f };
	Vector3 m_toPos = { 0.0f,200.0f,-1400.0f };
	//Vector3 m_toPos = { 0.0f,200.0f,-2500.0f };	//�S�̊m�F�p�̃|�W�V�����B
	Quaternion m_rotX = Quaternion::Identity;
	Quaternion m_rotY = Quaternion::Identity;
	Quaternion m_rotZ = Quaternion::Identity;


	//���ꂼ��̃N���X�̃|�C���^

	Player* m_player = nullptr;
	DirectionLight* m_dir = nullptr;
	MapChip* m_mapChip = nullptr;
};

