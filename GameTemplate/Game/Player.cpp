#include "stdafx.h"
#include "Player.h"
#include "DirectionLight.h"
#include "MainCamera.h"

#include "Key.h"


bool Player::Start()
{


	///アニメーションクリップをロードする。
	//m_animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	//m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	//m_animationClips[enAnimClip_Run].Load("Assets/animData/walk.tka");
	//m_animationClips[enAnimClip_Run].SetLoopFlag(true);

	//キャラコンの初期化。
	m_charaCon.Init(50.0f, 50.0f, m_pos);

	//プレイヤーのtkmとtksをロードする種。
	const char* tkmFilePaths[] = {
		"Assets/modelData/tkm/RedBall.tkm",
		"Assets/modelData/tkm/BlueBall.tkm"
	};
	/*const char* tksFilePaths[] = {
		"Assets/modelData/tkm/Player_N.tks",
		"Assets/modelData/tkm/Player_S.tks"
	};*/

	//プレイヤーの初期化。
	for (int i = 0; i < enPlayer_Num; i++) {
		//SkinModelRenderをNewGO。
		m_skinModelRender[i] = NewGO<SkinModelRender>(1);
		//tkmファイルをロード。
		m_skinModelRender[i]->SetFileNametkm(tkmFilePaths[i]);
		//tksファイルをロード。
		//m_skinModelRender[i]->SetFileNametks(tksFilePaths[i]);
		m_skinModelRender[i]->Init(true, false);
		if (i == enPlayer_1) {
			//Sは最初は非アクティブ。
			m_skinModelRender[i]->Deactivate();
		}
	}



		//アニメーションを設定。
	//m_skinModelRender->InitAnimation(m_animationClips, enAnimClip_Num);

	m_rotation.SetRotationDeg(g_vec3AxisY, rot);

	//座標を登録。
	for (int i = 0; i < enPlayer_Num; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
		m_skinModelRender[i]->SetRotation(m_rotation);
	}

	return true;
}


Player::~Player()
{
}



void Player::Update()
{
	//リスポーンした瞬間(3秒)の間は行われない処理。
	//リスポーンしたときに動かないようにするため。
	if (RespornFlag == false) {

		//回転量を加算
		rot1 -= 0.01f;

		m_rotation1.SetRotationDeg(g_vec3AxisZ, rot1);
		m_rotation.Multiply(m_rotation1);

		//重力を設定。
		m_movePower.y -= 0.2f;

		//z方向には動かない。
		m_movePower.z = 0.0f;


		//座標を設定。
		m_pos = m_charaCon.Execute(m_movePower, 1.0f);

		//壁に当たっているなら
		if (m_charaCon.IsOnWall()) {

			//1/2の力で跳ね返る。
			m_movePower.x *= -0.5f;
		}

		//地面上にいるなら
		if (m_charaCon.IsOnGround()) {

			//右に動いてたら
			if (m_movePower.x >= 0.0f) {
				//摩擦。
				m_movePower.x -= 0.02f;
				//もし減らしすぎたら０にする。
				if (m_movePower.x < 0.0f) {
					m_movePower.x = 0.0f;
				}
			}//左に動いてたら
			else {
				//摩擦。
				m_movePower.x += 0.02f;
				//もし増やしすぎたら０にする。
				if (m_movePower.x > 0.0f) {
					m_movePower.x = 0.0f;
				}
			}

		}
	}
	//リスポーンフラグがtrueの時、
	else {
		//RespornCount変数を加算(タイマーの役割)
		RespornCount++;
		//もし3秒たったら、
		if (RespornCount == 180) {
			//RespornFlagをfalseにしてelseを抜ける。
			RespornFlag = false;
			//カウントを0(初期値)に戻す。
			RespornCount = 0;
		}
	}

	//リスポーン!!!!!!!!

	//Bボタンを連続で押されないようにするPushFlag
	if (PushBFlag == true) {
		//Bボタンでプレイヤーの位置を初期値に戻したい
		if (g_pad[0]->IsTrigger(enButtonB)) {
			//鍵の情報もらいます。
			Key* key = FindGO<Key>("key");
			//鍵をゲットしていなかったらスタート位置にリスポーンする。
			if (key->getKeyFlg == false) {
				//座標の移動
				m_pos = { 300.0f,300.0f,0.0f };
			}
			//鍵をゲットしていたら鍵の場所にリスポーンする。
			else {
				//鍵があった座標をプレイヤーの座標変数に代入。
				m_pos = key->m_keyPos;
			}
			//キャラコンの初期化。
			m_charaCon.Init(50.0f, 50.0f, m_pos);
			//動く力の初期化
			m_movePower = { 0.0f,0.0f,0.0f };

			//もしプレイヤーがSのときリスポーンしたなら、
			if (m_skinModelRender[1]->IsActive() == true) {

				//プレイヤーをSからNに変換する。

				ChangeState();

				//アクティブフラグを更新。
				for (int i = 0; i < enPlayer_Num; i++) {
					if (m_skinModelRender[i]->IsActive() == true) {
						m_skinModelRender[i]->Deactivate();
					}
					else {
						m_skinModelRender[i]->Activate();
					}
				}
			}

			//リスポーンしたときに動かないようにする
			RespornFlag = true;

			//falseにすることでBボタンを押しても処理しないようにする。
			PushBFlag = false;
		}
	}
	//PushBFlag == falseのとき、
	else {
		//タイマー加算
		PushBCount++;
		//3秒経過すると、
		if (PushBCount == 180) {
			//タイマーの初期化
			PushBCount = 0;
			//Bボタンが押せる状態に戻す。
			PushBFlag = true;
		}
	}


	//座標を登録。
	for (int i = 0; i < enPlayer_Num; i++) {

		m_skinModelRender[i]->SetPosition(m_pos);

		m_skinModelRender[i]->SetRotation(m_rotation);
	}

	//リスポーンした瞬間(3秒)の間は行われない処理。
	//リスポーンしたときにプレイヤーをSに変えられないようにするため。
	if (RespornFlag == false) {
		//Aボタンでプレイヤーの磁力を反転させる
		if (g_pad[0]->IsTrigger(enButtonA)) {
			ChangeState();

			//アクティブフラグを更新。
			for (int i = 0; i < enPlayer_Num; i++) {
				if (m_skinModelRender[i]->IsActive() == true) {
					m_skinModelRender[i]->Deactivate();
				}
				else {
					m_skinModelRender[i]->Activate();
				}
			}
		}
	}





}

void Player::ChangeState() {
	if (pState == State_N) {
		pState = State_S;
	}
	else {
		pState = State_N;
	}
}

void Player::Render(RenderContext& rc) {

	wchar_t numtext[5][64];

	swprintf_s(numtext[0], L"State:%d", pState);
	//swprintf_s(numtext[1], L"vit+%d", m_plus_vit);

	m_font.Begin(rc);

	m_font.Draw(
		numtext[0],
		{ 120.0f, 10.0f },
		{ 0.55f,0.0f,0.0f,1.0f },
		0.0f,
		0.4f,
		{ 0.5f,0.5f }
	);

	m_font.End(rc);
}