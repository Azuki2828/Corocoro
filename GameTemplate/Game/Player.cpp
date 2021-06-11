#include "stdafx.h"
#include "Player.h"
#include "Key.h"
#include "DirectionLight.h"
#include "MainCamera.h"
#include "Background.h"
#include "Game.h"

namespace {

	const char* PLAYER_TKM_FILEPATH_N = "Assets/modelData/tkm/Player_N50.tkm";
	const char* PLAYER_TKM_FILEPATH_S = "Assets/modelData/tkm/Player_S50.tkm";
	const char* PLAYER_TKS_FILEPATH_N = "Assets/modelData/tkm/Player_N50.tks";
	const char* PLAYER_TKS_FILEPATH_S = "Assets/modelData/tkm/Player_S50.tks";
	//プレイヤーのコリジョンの半径
	const float PLAYER_COLLI_RADIUS = 50.0f;
	const float PLAYER_MASS = 1.0f;
	const float DEAD_LINE = 500.0f;
	const float PLAYER_MOVE_SPEED = 100.0f;
	const Vector3 PLAYER_LOCAL_INTERIA = { 0.5f,0.5f,0.5f };
	const float PLAYER_FRICTION = 10.0f;
	const Vector3 PLAYER_LINIOR_FACTOR = { 1.0f,1.0f,0.0f };

	const float PLAYER_Z_MOVE_POWER = 0.0f;

	const Vector3 PLAYER_LIG_DIRECTION = { 0.0f, -1.0f, 1.0f };
	const Vector4 PLAYER_LIG_COLOR_N = { 25.0f, 25.0f, 25.0f, 1.0f };
	const Vector4 PLAYER_LIG_COLOR_S = { 25.0f, 25.0f, 55.0f, 1.0f };
	const Vector3 PLAYER_LIG_AMBIENT = { 0.8f, 0.8f, 0.8f };
	const float PLAYER_METARIC = 1.0f;
	const float PLAYER_SMOOTH = 0.35f;
	const float PLAYER_POW_VALUE = 2.0f;
	const Vector3 EFFECT_SCALE_CHANGE_STATE = { 95.0f,95.0f,95.0f };
	const char16_t* EFFECT_FILE_PATH_CHANGE_STATE_N = u"Assets/effect/State_N2.efk";
	const char16_t* EFFECT_FILE_PATH_CHANGE_STATE_S = u"Assets/effect/State_S2.efk";

	const float ADD_LIGHT_CAMERA_POS = 500.0f;
}

bool Player::Start()
{
	m_ligData[enPlayer_0].m_directionLigData[enData_Zeroth].Dir.Set(PLAYER_LIG_DIRECTION);
	m_ligData[enPlayer_0].m_directionLigData[enData_Zeroth].Dir.Normalize();
	m_ligData[enPlayer_0].m_directionLigData[enData_Zeroth].Col.Set(PLAYER_LIG_COLOR_N);
	m_ligData[enPlayer_0].ambient.Set(PLAYER_LIG_AMBIENT);
	m_ligData[enPlayer_0].metaric = PLAYER_METARIC;
	m_ligData[enPlayer_0].smooth = PLAYER_SMOOTH;
	m_ligData[enPlayer_0].powValue = PLAYER_POW_VALUE;

	m_ligData[enPlayer_1].m_directionLigData[enData_Zeroth].Dir.Set(PLAYER_LIG_DIRECTION);
	m_ligData[enPlayer_1].m_directionLigData[enData_Zeroth].Dir.Normalize();
	m_ligData[enPlayer_1].m_directionLigData[enData_Zeroth].Col.Set(PLAYER_LIG_COLOR_S);
	m_ligData[enPlayer_1].ambient.Set(PLAYER_LIG_AMBIENT);
	m_ligData[enPlayer_1].metaric = PLAYER_METARIC;
	m_ligData[enPlayer_1].smooth = PLAYER_SMOOTH;
	m_ligData[enPlayer_1].powValue = PLAYER_POW_VALUE;

	m_game = FindGO<Game>(NAME_GAME);

	auto mainCamera = FindGO<MainCamera>(NAME_MAIN_CAMERA);

	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, CAMERA_ROT_VALUE);
		m_rotZ.Apply(m_ligData[enPlayer_0].m_directionLigData[enData_Zeroth].Dir);
		m_rotZ.Apply(m_ligData[enPlayer_1].m_directionLigData[enData_Zeroth].Dir);
	});

	//プレイヤーのtkmとtksをロードする種。
	const char* tkmFilePaths[] = {
		PLAYER_TKM_FILEPATH_N,
		PLAYER_TKM_FILEPATH_S
	};
	const char* tksFilePaths[] = {
		PLAYER_TKS_FILEPATH_N,
		PLAYER_TKS_FILEPATH_S
	};


	//プレイヤーの初期化。
	for (int i = 0; i < enPlayer_Num; i++) {
		//SkinModelRenderをNewGO。
		m_skinModelRender[i] = NewGO<SkinModelRender>(enPriority_First);
		//tkmファイルをロード。
		m_skinModelRender[i]->SetFileNametkm(tkmFilePaths[i]);
		//tksファイルをロード。
		m_skinModelRender[i]->SetFileNametks(tksFilePaths[i]);
		m_skinModelRender[i]->SetShadowReceiverFlag(true);
		m_skinModelRender[i]->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);
		m_skinModelRender[i]->SetUserLigData(&m_ligData[i]);
		m_skinModelRender[i]->SetZprepassFlag(true);
		m_skinModelRender[i]->Init();
		if (i == enPlayer_1) {
			//プレイヤー1は最初は非アクティブ。
			m_skinModelRender[i]->Deactivate();
		}
	}

	{
		//エフェクト設定
		m_NCahgeState = NewGO<Effect>(enPriority_Zeroth);
		m_NCahgeState->Init(EFFECT_FILE_PATH_CHANGE_STATE_N);
		m_NCahgeState->SetScale(EFFECT_SCALE_CHANGE_STATE);
	}
	
	{
		//エフェクト再生
		m_SCahgeState = NewGO<Effect>(enPriority_Zeroth);
		m_SCahgeState->Init(EFFECT_FILE_PATH_CHANGE_STATE_S);
		m_SCahgeState->SetScale(EFFECT_SCALE_CHANGE_STATE);
	}

	//コライダーを初期化。
	m_sphereCollider.Create(PLAYER_COLLI_RADIUS);

	//剛体を初期化。
	RigidBodyInitData rbInitData;
	//質量を設定する。
	rbInitData.mass = PLAYER_MASS;
	rbInitData.collider = &m_sphereCollider;
	rbInitData.pos = m_pos;
	//回転のしやすさを設定する。0～1
	rbInitData.localInteria.Set(PLAYER_LOCAL_INTERIA);
	m_rigidBody.Init(rbInitData);
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

	//摩擦力を設定する。0～10
	m_rigidBody.SetFriction(PLAYER_FRICTION);
	//線形移動する要素を設定する。
	//0を指定した軸は移動しない。
	m_rigidBody.SetLinearFactor(PLAYER_LINIOR_FACTOR);


	//座標を登録。
	for (int i = 0; i < enPlayer_Num; i++) {
		m_skinModelRender[i]->SetPosition(m_pos);
	}

	return true;
}

Player::~Player()
{
	for (int i = 0; i < enPlayer_Num; i++) {
		DeleteGO(m_skinModelRender[i]);
	}
}


void Player::Update()
{

	for (auto& ligData : m_ligData) {
		ligData.eyePos = g_camera3D->GetPosition();
	}

	//m_rigidBody.SetLinearFactor(1.0f, 1.0f, 0.0f);
	if (m_backGround == nullptr) {
		m_backGround = FindGO<BackGround>(NAME_BACK_GROUND);
	}

	//z方向には動かない。
	m_movePower.z = PLAYER_Z_MOVE_POWER;
	if (m_backGround != nullptr) {
		m_deathPosY = m_backGround->GetDeathPosY();
	}

	//剛体の座標と回転を取得。
	Vector3 pos;
	Quaternion rot;
	m_rigidBody.GetPositionAndRotation(pos, rot);
	//剛体の座標と回転をモデルに反映。
	if (m_key == nullptr) {
		m_key = FindGO<Key>(NAME_KEY);

	}
	if (m_treasureBox == nullptr) {
		m_treasureBox = FindGO<TreasureBox>(NAME_TREASURE_BOX);
	}

	for (int i = 0; i < enPlayer_Num; i++) {
		m_pos = pos;
		m_rot = rot;
		if (m_pos.y < m_deathPosY) {

			m_game->SetHitPlayer(true);
		}
		m_skinModelRender[i]->SetPosition(m_pos);
		m_skinModelRender[i]->SetRotation(m_rot);
	}
	//力を加える
	m_rigidBody.AddForce(
		m_movePower,		//力
		Vector3::Zero	//力を加える剛体の相対位置
	);
	m_movePower = Vector3::Zero;

	//プレイヤーの位置に合わせる。
	m_SCahgeState->SetPosition(m_pos);
	m_NCahgeState->SetPosition(m_pos);


	if (m_game->GetGameFlg()) {
			//Aボタンでプレイヤーの磁力を反転させる
		if (!m_deathFlag) { //死んでいる場合、処理を動かさない。
			if (g_pad[enData_Zeroth]->IsTrigger(enButtonA) && !m_treasureBox->GetTreasureFlg()) {
				ChangeState();

				//NとSを切り替えるときの効果音再生。


				SoundManager::GetInstance()->Play(SE_NSChange);

				//アクティブフラグを更新。
				for (int i = 0; i < enPlayer_Num; i++) {
					if (m_skinModelRender[i]->IsActive()) {
						m_skinModelRender[i]->Deactivate();
					}
					else {
						m_skinModelRender[i]->Activate();
					}
				}

			}
		}
		

		Vector3 m_lightCameraTar = m_pos;

		Vector3 m_lightCameraPos = m_lightCameraTar;
		if (m_getKeyFlg) {
			m_lightCameraPos.y -= ADD_LIGHT_CAMERA_POS;
		}
		else {
			m_lightCameraPos.y += ADD_LIGHT_CAMERA_POS;
		}

		Camera::GetLightCamera()->SetPosition(m_lightCameraPos);
		Camera::GetLightCamera()->SetTarget(m_lightCameraTar);
	}

	//pStateの極とモデルの極が違う場合、モデルの極をpStateの極に合わせる。
	//if (!m_deathFlag) { //死んでいる場合、処理を動かさない。
	//	if (pState == State_N && m_skinModelRender[enPlayer_0]->IsActive())
	//	{

	//	}
	//	else if (pState == State_S && m_skinModelRender[enPlayer_1]->IsActive())
	//	{

	//	}
	//	else {
	//		for (int i = 0; i < enPlayer_Num; i++) {
	//			m_skinModelRender[i]->Deactivate();
	//		}

	//		m_skinModelRender[pState]->Activate();
	//	}
	//}
}

void Player::FreeUpdate() {
	
	m_rigidBody.SetPositionAndRotation(m_pos, m_rot);
}

void Player::ChangeState() {
	if (pState == State_N) {
		pState = State_S;
		m_SCahgeState->SetPosition(m_pos);
		m_SCahgeState->Play();
	}
	else {
		pState = State_N;
		m_NCahgeState->SetPosition(m_pos);
		m_NCahgeState->Play();
	}
}