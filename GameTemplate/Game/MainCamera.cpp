#include "stdafx.h"
#include "MainCamera.h"
#include "Player.h"

bool MainCamera::Start() {

	m_player = FindGO<Player>("player");

	//初期設定
	m_pos = m_player->GetPosition();
	m_pos.z += 100.0f;
	g_camera3D->SetPosition(m_pos);
	m_tar = m_player->GetPosition();
	g_camera3D->SetTarget(m_tar);
	g_camera3D->Update();

	return true;
}

void MainCamera::Update() {

	//m_pos = g_camera3D->GetPosition();
	//m_tar = g_camera3D->GetTarget();
	//toPos = m_tar - m_pos;
	//コントローラーの入力でY軸周りに回転するカメラを作成する。

	///g_pad[0]->GetRStickXF()はコントローラーの右スティックの入力量が取得できる関数。
	//m_rotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.05f);
	///回転クォータニオンでtoCameraPosを回す。
	//m_rotY.Apply(toPos);

	//Vector3 rotAxis;
	//rotAxis.Cross(g_vec3AxisY, toPos);
	//rotAxis.Normalize();

	//m_rotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.05f);
	//m_rotX.Apply(toPos);

	if (CameraScrollFlag == true) {
		//ここはステージ選択時に何ステージ目かでスウィッチさせてステージごとのカメラスクロール関数を呼ぶ。

		//ステージ1をカメラスクロールで眺める関数
		Stage1ScrollCamera();
	}
	//通常時の処理。
	else {
		if (m_player != nullptr) {
			//プレイヤーの場所を取得し、注視点の変数に入れる。
			m_tar = m_player->GetPosition();
			//プレイヤーのちょっと上に注視点を置く。
			m_tar.y += 50.0f;

		}
	}

	//新しい視点を、「新しい注視点　＋　toCameraPos」で求める。
	m_pos = m_tar + toPos;


	//新しい視点と注視点をカメラに設定する。
	g_camera3D->SetPosition(m_pos);
	g_camera3D->SetTarget(m_tar);
	g_camera3D->Update();
}


//ステージ1をカメラスクロールで眺める関数
void MainCamera::Stage1ScrollCamera() {
	switch (CamePosiFlag) {
	case 0:
		//スタートの場所で少し画面のスクロールを固定。スタート地点をプレイヤーに伝わりやすくする。
		ScrollStaticTimer++;
		//2秒静止。
		if (ScrollStaticTimer == 120) {
			CamePosiFlag = 1;
		}
		break;
	case 1:
		//スタート位置から右端に...
		m_tar.x += 30.0f;
		if (m_tar.x > 3000.0f) {
			CamePosiFlag = 2;
		}
		break;
	case 2:
		//2階層まで上にあがる。
		m_tar.y += 30.0f;
		if (m_tar.y > 1500.0f) {
			CamePosiFlag = 3;
		}
		break;
	case 3:
		//2階層の右端から左端に進む。
		m_tar.x -= 30.0f;
		if (m_tar.x < 700.0f) {
			CamePosiFlag = 4;
		}
		break;
	case 4:
		//3階層まで上にあがる。
		m_tar.y += 30.0f;
		if (m_tar.y > 2800.0f) {
			CamePosiFlag = 5;
		}
		break;
	case 5:
		//鍵の場所まで右に進む。
		m_tar.x += 30.0f;
		if (m_tar.x > 3000.0f) {
			CamePosiFlag = 6;
		}
		break;
	case 6:
		//鍵の場所で少し画面のスクロールを固定。目的地をプレイヤーに伝わりやすくする。
		ScrollStaticTimer++;
		//2秒静止。
		if (ScrollStaticTimer == 240) {
			CamePosiFlag = 7;
		}
		break;
	case 7:
		//カメラの場所から最短でスタートまで戻る。
		m_tar.x -= 40.0f;
		m_tar.y -= 35.0f;
		//プレイヤーの初期座標まで戻ったら、
		if (m_tar.x < 400.0f && m_tar.y < 370.0f) {
			//カメラをボール視点に戻したからカメラスクロールのフラグを抜ける。
			CameraScrollFlag = false;
		}
		break;
	}
}