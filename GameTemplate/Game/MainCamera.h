#pragma once

class Player;

class MainCamera : public IGameObject
{
public:
	bool Start() override final;
	void Update() override final;

	Vector3 m_pos;		//視点。
	Vector3 m_tar;		//注視点。
	//Vector3 toPos = { 0.0f,200.0f,-4000.0f };

	//注視点からのベクトル。
	Vector3 toPos = { 0.0f,200.0f,-1800.0f };

	//回転。
	Quaternion m_rotY;
	Quaternion m_rotX;

	Player* m_player = nullptr;

	//ゲームスタート前にステージ全体をカメラで眺める関数。x==カメラのx座標、y==カメラのy座標を入れる。
	void Stage1ScrollCamera();
	int CamePosiFlag = 0;
	bool CameraScrollFlag = true;
	int ScrollStaticTimer = 0;
};

