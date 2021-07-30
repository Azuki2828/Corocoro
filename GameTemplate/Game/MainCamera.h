#pragma once

class Player;
class DirectionLight;
class MapChip;

namespace {

	const float CAMERA_ROT_WAIT_TIME = 1.5f;	//鍵を取得してから回転するまでの時間
	const int ROT_NUM = 90;						//回転数。90回で半回転。
}

class MainCamera : public IGameObject
{
private:
	bool Start() override final;
	void Update() override final;
	void FreeUpdate() override final;

public:

	/**
	 * @brief カメラが回転しているか確かめるフラグ
	 * @param flg 
	*/
	void SetRotFlg(bool flg) {
		m_rotFlg = flg;
	}

	//1回だけカメラを180度回転させるためのフラグ
	std::list<std::function< void() >> changeRotCameraEvent;
private:
	bool m_cameraRotFlg = false;					//カメラが回転しているかどうかのフラグ
	bool m_rotFlg = false;							//カメラを回転させるフラグ（1回だけ実行）
	int m_count = 0;								//回転数（0～90）
	float m_waitRot = 0.0f;							//カメラが回転するまでの時間		
	Vector3 m_pos = Vector3::Zero;					//視点。
	Vector3 m_tar = Vector3::Zero;					//注視点。
	Vector3 m_rotAxis = { 0.0f,1.0f,0.0f };			//回転軸
	Vector3 m_toPos = { 0.0f,200.0f,-1400.0f };		//注視点から視点までの距離

	//それぞれの軸
	Quaternion m_rotX = Quaternion::Identity;		
	Quaternion m_rotY = Quaternion::Identity;
	Quaternion m_rotZ = Quaternion::Identity;


	//それぞれのクラスのポインタ

	Player* m_player = nullptr;
	DirectionLight* m_dir = nullptr;
	MapChip* m_mapChip = nullptr;
};

