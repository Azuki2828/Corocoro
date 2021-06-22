#include "stdafx.h"
#include "DeathBlock.h"
#include "Player.h"
#include "MainCamera.h"
#include "Key.h"
#include "Background.h"
#include "Game.h"

namespace {

	const Vector3 ADD_GHOST_POS = { 50.0f,50.0f,-200.0f };			//トリガーボックスの座標を合わせるための定数
	const Vector3 GHOST_SIZE = { 100.0f,100.0f,400.0f };			//トリガーボックスの元のサイズ

	const float ADD_UV_NOISE_OFFSET = 0.01f;						//ノイズを発生させるためのオフセットの変化幅
	const float TIMER_CLEAR = 0.0f;									//タイマーを初期化させるための定数
	const float HIT_TIMER_VALUE[] = { 2.5f,3.0f };					//タイマーの途中経過の定数


	const Vector3 DEATH_BLOCK_LIG_DIR = { -1.0f, -1.0f, -1.0f };				//ライトの方向
	const Vector3 DEATH_BLOCK_LIG_AMBIENT = { 0.8f, 0.8f, 0.8f };				//環境光の強さ
	const float DEATH_BLOCK_METARIC = 1.0f;										//金属度
	const float DEATH_BLOCK_SMOOTH = 0.1f;										//滑らかさ
	const float DEATH_BLOCK_POW_VALUE = 10.0f;									//絞る強さ
	const float UV_NOISE_MUL = 1.0f;								//ノイズに乗算する値
}

bool DeathBlock::Start() {

	m_player = FindGO<Player>(NAME_PLAYER);
	m_key = FindGO<Key>(NAME_KEY);
	m_backGround = FindGO<BackGround>(NAME_BACK_GROUND);
	m_game = FindGO<Game>(NAME_GAME);
	m_skinModelRender->SetPosition(m_pos);

	m_skinModelRender->SetScale(m_sca);

	m_death = NewGO<Effect>(enPriority_Zeroth);
	m_death->Init(DEATH_EFFECT_FILE_PATH);
	m_death->SetScale(EFFECT_SCALE);

	m_skinModelRender->SetScale(m_sca);
	auto mainCamera = FindGO<MainCamera>(NAME_MAIN_CAMERA);
	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, CAMERA_ROT_VALUE);
		m_rotZ.Apply(m_ligData.m_directionLigData[enData_Zeroth].Dir);
		});

	m_ghostPos = m_pos;
	m_ghostPos.x += ADD_GHOST_POS.x * m_sca.x;
	m_ghostPos.y += ADD_GHOST_POS.y * m_sca.y;
	m_ghostPos.z += ADD_GHOST_POS.z;

	m_ghostBox.CreateBox(
		m_ghostPos,	//第一引数は座標。
		Quaternion::Identity,		//第二引数は回転クォータニオン。
		{ GHOST_SIZE.x * m_sca.x, GHOST_SIZE.y * m_sca.y, GHOST_SIZE.z * m_sca.z}	//第三引数はボックスのサイズ。
	);

	m_skinModelRender->UpdateWorldMatrix();
	return true;
}

DeathBlock::~DeathBlock() {

	DeleteGO(m_skinModelRender);
}

void DeathBlock::Update() {

	if (m_moveFlg) {
		static bool move = false;
		if (!move) {
			Vector3 length = m_movePos[enData_First] - m_pos;
			length.Normalize();
			m_pos += length;
			m_ghostPos += length;
			if (m_pos.x >= m_movePos[enData_First].x) {
				move = true;
			}
		}
		else {
			Vector3 length = m_movePos[enData_Zeroth] - m_pos;
			length.Normalize();
			m_pos += length;
			m_ghostPos += length;
			if (m_pos.x <= m_movePos[enData_Zeroth].x) {
				move = false;
			}
		}
		m_skinModelRender->SetPosition(m_pos);
		m_ghostBox.SetPosition(m_ghostPos);
	}


	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {
		m_ligData.uvNoiseOffset += ADD_UV_NOISE_OFFSET;
		float t;
		m_ligData.uvNoiseOffset = modf(m_ligData.uvNoiseOffset, &t);
		if (m_ghostBox.IsSelf(contactObject)) {
			m_hitPlayer = true;
		}
		});


	if (m_hitPlayer && !m_player->GetTreasureFlg())
	{
		//死ぬエフェクト再生と効果音
		if (!m_player->Getrespawn()) {
			Effect* m_death = NewGO<Effect>(enPriority_Zeroth);
			m_death->Init(DEATH_EFFECT_FILE_PATH);
			m_death->SetScale(EFFECT_SCALE);
			m_player->Setrespawn(true);
			m_death->SetPosition(m_player->GetPosition());
			m_deathActiveState = m_player->DeactivatePlayerModel();
			m_death->Play();
			m_deathFlg = true;

			SoundManager::GetInstance()->Play(enSE_Death);
		}
		m_hitTimer += GameTime().GameTimeFunc().GetFrameDeltaTime();
		if (m_hitTimer >= HIT_TIMER_VALUE[enData_First])
		{
			SoundManager::GetInstance()->Play(enSE_ReStart);
			m_player->Setrespawn(false);
			m_hitTimer = TIMER_CLEAR;
			m_backGround->SetStart(true);
			m_hitPlayer = false;
			m_respawnEfk = false;

		}
		else if (m_hitTimer >= HIT_TIMER_VALUE[enData_Zeroth]) {

			if (m_player->GetKeyFlg()) {
				m_key = FindGO<Key>(NAME_KEY);
				m_player->SetPosition(m_key->GetKeyPos());
				m_player->ActivatePlayerModel(m_deathActiveState);
				m_deathFlg = false;
			}
			else {
				m_player->SetPosition(m_player->GetStartPos());
				m_player->ActivatePlayerModel(m_deathActiveState);
				m_deathFlg = false;
			}
			if (!m_respawnEfk) {
				m_efkRespawn = NewGO<Effect>(enPriority_Zeroth);
				m_efkRespawn->Init(DEATH_EFFECT_FILE_PATH);
				m_efkRespawn->SetScale(EFFECT_SCALE);
				m_efkRespawn->SetPosition(m_player->GetPosition());
				m_efkRespawn->Play();
				m_respawnEfk = true;
			}
		}
		else {
			m_player->SetPosition(m_player->GetPosition());
		}
		m_player->ClearPower();

		if (m_efkRespawn != nullptr) {
			m_efkRespawn->SetPosition(m_player->GetPosition());
		}
	}
}

void DeathBlock::Init(const char* name)
{
	char filePathtkm[NAME_SIZE];
	sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
	m_skinModelRender = NewGO<SkinModelRender>(enPriority_Zeroth);
	m_skinModelRender->SetFileNametkm(filePathtkm);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_skinModelRender->SetZprepassFlag(true);

	//座標を登録。
	m_ligData.m_directionLigData[enData_Zeroth].Dir.Set(DEATH_BLOCK_LIG_DIR);
	m_ligData.m_directionLigData[enData_Zeroth].Dir.Normalize();

	m_ligData.ambient.Set(DEATH_BLOCK_LIG_AMBIENT);
	m_ligData.metaric = DEATH_BLOCK_METARIC;
	m_ligData.smooth = DEATH_BLOCK_SMOOTH;
	m_ligData.edge = Edge_1;
	m_ligData.powValue = DEATH_BLOCK_POW_VALUE;
	m_ligData.uvNoiseMul = UV_NOISE_MUL;
	m_skinModelRender->SetUserLigData(&m_ligData);
	m_skinModelRender->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

	m_skinModelRender->Init();
}

