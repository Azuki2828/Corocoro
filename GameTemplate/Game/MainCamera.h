#pragma once

class Player;
class DirectionLight;
class MapChip;

class MainCamera : public IGameObject
{
public:
	bool Start() override final;
	void Update() override final;
	void FreeUpdate() override final;

	float waitRot = 0.0f;
	Vector3 m_pos;		//���_�B
	Vector3 m_tar;		//�����_�B
	Vector3 m_rotAxis = { 0.0f,1.0f,0.0f };
	//Vector3 toPos = { 0.0f,200.0f,-4000.0f };

	//�����_����̃x�N�g���B
	//Vector3 toPos = { 0.0f,200.0f,-1400.0f };
	Vector3 toPos = { 0.0f,200.0f,-2500.0f };	//�S�̊m�F�p�̃|�W�V�����B
	Quaternion m_rotX;
	Quaternion m_rotY;
	Quaternion m_rotZ;
	//Vector3 toPos = { 1000.0f,1000.0f,-3500.0f };

	//Z������_��180�x��]�B
	//Vector3  m_rotZ={0.0f,0.0f,-1.0f};

	Player* m_player = nullptr;
	DirectionLight* m_dir = nullptr;
	MapChip* m_mapChip = nullptr;

	//�Q�[���X�^�[�g�O�ɃX�e�[�W�S�̂��J�����Œ��߂�֐��Bx==�J������x���W�Ay==�J������y���W������B
	void Stage1ScrollCamera();
	int count = 0;
	int CamePosiFlag = 0;
	bool CameraScrollFlag = true;
	bool m_cameraRotFlg = false;
	int ScrollStaticTimer = 0;

	//1�񂾂��J������180�x��]�����邽�߂̃t���O
	bool RotFlg = false;
	std::list<std::function< void() >> changeRotCameraEvent;
};

