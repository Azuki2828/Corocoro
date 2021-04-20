#include "stdafx.h"
#include "Player.h"
#include "Key.h"
#include "DirectionLight.h"
#include "MainCamera.h"
#include "Background.h"
#include "Game.h"

bool Player::Start()
{

	m_game = FindGO<Game>("game");

	////アニメーションクリップをロードする。
	//m_animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	//m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	//m_animationClips[enAnimClip_Run].Load("Assets/animData/walk.tka");
	//m_animationClips[enAnimClip_Run].SetLoopFlag(true);

	//キャラコンの初期化。
	//m_charaCon.Init(50.0f, 100.0f, m_pos);

	//プレイヤーのtkmとtksをロードする種。
	const char* tkmFilePaths[] = {
		"Assets/modelData/tkm/Player_N.tkm",
		"Assets/modelData/tkm/Player_S.tkm"
	};
	const char* tksFilePaths[] = {
		"Assets/modelData/tkm/Player_N.tks",
		"Assets/modelData/tkm/Player_S.tks"
	};


	//プレイヤーの初期化。
	for (int i = 0; i < enPlayer_Num; i++) {
		//SkinModelRenderをNewGO。
		m_skinModelRender[i] = NewGO<SkinModelRender>(1);
		//tkmファイルをロード。
		m_skinModelRender[i]->SetFileNametkm(tkmFilePaths[i]);
		//tksファイルをロード。
		m_skinModelRender[i]->SetFileNametks(tksFilePaths[i]);
		m_skinModelRender[i]->SetShadowCasterFlag(true);
		m_skinModelRender[i]->SetColorBufferFormat(DXGI_FORMAT_R32_FLOAT);
		m_skinModelRender[i]->Init(true, false);
		if (i == enPlayer_1) {
			//プレイヤー1は最初は非アクティブ。
			m_skinModelRender[i]->Deactivate();
		}
	}

	//アニメーションを設定。
	//m_skinModelRender->InitAnimation(m_animationClips, enAnimClip_Num);

	//コライダーを初期化。
	m_sphereCollider.Create(50.0f);

	//剛体を初期化。
	RigidBodyInitData rbInitData;
	//質量を設定する。
	rbInitData.mass = 1.0f;
	rbInitData.collider = &m_sphereCollider;
	//rbInitData.pos.y = 100.0f;
	rbInitData.pos = m_pos;
	//回転のしやすさを設定する。0～1
	rbInitData.localInteria.Set(
		0.5f,
		0.5f,
		0.5f
	);
	m_rigidBody.Init(rbInitData);

	//摩擦力を設定する。0～10
	m_rigidBody.SetFriction(10.0f);
	//線形移動する要素を設定する。
	//0を指定した軸は移動しない。
	m_rigidBody.SetLinearFactor(1.0f, 1.0f, 0.0f);


	//座標を登録。
	for (int i = 0; i < enPlayer_Num; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
	}

	return true;
}

Player::~Player()
{

}


void Player::Update()
{
	if (m_backGround == nullptr) {
		m_backGround = FindGO<Background>("background");
	}

	//重力を設定。
	//m_movePower.y -= 0.2f;

	//z方向には動かない。
	m_movePower.z = 0.0f;

	//座標を設定。
	//m_pos = m_charaCon.Execute(m_movePower, 1.0f);


	float deathPosY = -1000.0f;
	if (m_backGround != nullptr) {
		deathPosY = m_backGround->GetDeathPosY();
  }
	//壁に当たっているなら
	//if (m_charaCon.IsOnWall()) {
	//
	//	//1/2の力で跳ね返る。
	//	m_movePower.x *= -0.5f;
	//}

	//地面上にいるなら
	//if (m_charaCon.IsOnGround()) {
	//
	//	//右に動いてたら
	//	if (m_movePower.x >= 0.0f) {
	//		//摩擦。
	//		m_movePower.x -= 0.02f;
	//		//もし減らしすぎたら０にする。
	//		if (m_movePower.x < 0.0f) {
	//			m_movePower.x = 0.0f;
	//		}
	//	}//左に動いてたら
	//	else {
	//		//摩擦。
	//		m_movePower.x += 0.02f;
	//		//もし増やしすぎたら０にする。
	//		if (m_movePower.x > 0.0f) {
	//			m_movePower.x = 0.0f;
	//		}
	//	}
	//
	//}
	//
	//剛体の座標と回転を取得。
	Vector3 pos;
	Quaternion rot;
	m_rigidBody.GetPositionAndRotation(pos, rot);
	//剛体の座標と回転をモデルに反映。
	if (m_key == nullptr) {
		m_key = FindGO<Key>("key");

	}

	for (int i = 0; i < enPlayer_Num; i++) {
		m_pos = pos;
		m_rot = rot;
		if (m_pos.y < deathPosY || g_pad[0]->IsTrigger(enButtonB)) {

			if (getKeyFlg) {
				m_pos = m_key->GetKeyPos();

			
			}
			else {
				m_pos = { 300.0f,310.0f,0.0f };	//<変更>yが500以下になったら初期位置に戻るようにif文追加
				
			}
			m_rigidBody.SetPositionAndRotation(m_pos, m_rot);
		}
		//m_skinModelRender[i]->UpdateWorldMatrix(pos, rot, Vector3::One);
		m_skinModelRender[i]->SetPosition(m_pos);
		m_skinModelRender[i]->SetRotation(m_rot);
	}
	//m_model.UpdateWorldMatrix(pos, rot, g_vec3One);
	//剛体に力を加える。
	Vector3 force;
	force.x = g_pad[0]->GetLStickXF() * 500.0f;
	force.z = g_pad[0]->GetLStickYF() * 500.0f;
	//力を加える
	m_rigidBody.AddForce(
		m_movePower,		//力
		g_vec3Zero	//力を加える剛体の相対位置
	);
	m_movePower = { 0.0f,0.0f,0.0f };
	//Aボタンでプレイヤーの磁力を反転させる

	if (m_game->m_timer >= 200) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			ChangeState();

		//NとSを切り替えるときの効果音再生。

		NSChangeSound = NewGO<CSoundSource>(0);

		NSChangeSound->Init(L"Assets/sound/NSChange.wav");
		NSChangeSound->SetVolume(0.5f);
		NSChangeSound->Play(false);	//ワンショット再生

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

	Vector3 m_lightCameraTar = m_pos;

	Vector3 m_lightCameraPos = m_lightCameraTar;
	//m_lightCameraPos.z += 5.0f;
	m_lightCameraPos.y += 500.0f;

	//Vector3 Cpos = { 300.0f,400.0f,0.0f };
	//Vector3 CTar = { 300.0f,300.0f,0.0f };

	Camera::GetLightCamera()->SetPosition(m_lightCameraPos);
	Camera::GetLightCamera()->SetTarget(m_lightCameraTar);

	//Vector3 toCamere = g_camera3D->GetPosition() - g_camera3D->GetTarget();
	//g_camera3D->SetTarget(pos);
	//toCamere.y = 100.0f;
	//toCamere.z = -2500.0f;
	//g_camera3D->SetPosition(pos + toCamere);
	
	

	Key* key = FindGO<Key>("key");

	//ゲームクリアしてから5秒たったら、
	if (key->GameOverCount > 300) {
		//クラスを削除。
		DeleteGO(this);
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

	if (RenderContext::Render_Mode::RenderMode_Normal) {
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
}