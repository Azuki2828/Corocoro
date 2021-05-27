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
	Vector3 m_pos;		//視点。
	Vector3 m_tar;		//注視点。
	Vector3 m_rotAxis = { 0.0f,1.0f,0.0f };
	//Vector3 toPos = { 0.0f,200.0f,-4000.0f };

	//注視点からのベクトル。
	//Vector3 toPos = { 0.0f,200.0f,-1400.0f };
	Vector3 toPos = { 0.0f,200.0f,-2500.0f };	//全体確認用のポジション。
	Quaternion m_rotX;
	Quaternion m_rotY;
	Quaternion m_rotZ;
	//Vector3 toPos = { 1000.0f,1000.0f,-3500.0f };

	//Z軸を基点に180度回転。
	//Vector3  m_rotZ={0.0f,0.0f,-1.0f};

	Player* m_player = nullptr;
	DirectionLight* m_dir = nullptr;
	MapChip* m_mapChip = nullptr;

	//ゲームスタート前にステージ全体をカメラで眺める関数。x==カメラのx座標、y==カメラのy座標を入れる。
	void Stage1ScrollCamera();
	int count = 0;
	int CamePosiFlag = 0;
	bool CameraScrollFlag = true;
	bool m_cameraRotFlg = false;
	int ScrollStaticTimer = 0;

	//1回だけカメラを180度回転させるためのフラグ
	bool RotFlg = false;
	std::list<std::function< void() >> changeRotCameraEvent;
};

