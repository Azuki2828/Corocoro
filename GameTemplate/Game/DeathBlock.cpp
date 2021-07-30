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


	const Vector3 DEATH_BLOCK_LIG_DIR = { -1.0f, -1.0f, -1.0f };	//ライトの方向
	const Vector3 DEATH_BLOCK_LIG_AMBIENT = { 0.8f, 0.8f, 0.8f };	//環境光の強さ
	const float DEATH_BLOCK_METARIC = 1.0f;							//金属度
	const float DEATH_BLOCK_SMOOTH = 0.1f;							//滑らかさ
	const float DEATH_BLOCK_POW_VALUE = 10.0f;						//絞る強さ
	const float UV_NOISE_MUL = 1.0f;								//ノイズに乗算する値

	const char* DEATH_BLOCK_STANDARD_FILE_PATH = "Assets/modelData/tkm/%s.tkm";		//基準となるtkmファイルのファイルパス
}

bool DeathBlock::Start() {

	//それぞれのクラスを探し出す。
	m_player = FindGO<Player>(NAME_PLAYER);
	m_key = FindGO<Key>(NAME_KEY);
	m_backGround = FindGO<BackGround>(NAME_BACK_GROUND);
	m_game = FindGO<Game>(NAME_GAME);


	//死んだときのエフェクトを初期化。
	m_death = NewGO<Effect>(enPriority_Zeroth);
	m_death->Init(DEATH_EFFECT_FILE_PATH);
	//エフェクトの拡大率を設定。
	m_death->SetScale(EFFECT_SCALE);

	//カメラが回転したときのデスブロックの処理。
	auto mainCamera = FindGO<MainCamera>(NAME_MAIN_CAMERA);
	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, CAMERA_ROT_VALUE);
		m_rotZ.Apply(m_ligData.m_directionLigData[enData_Zeroth].Dir);
		});

	//デスブロックの当たり判定を設定。
	m_ghostPos = m_pos;
	m_ghostPos.x += ADD_GHOST_POS.x * m_sca.x;
	m_ghostPos.y += ADD_GHOST_POS.y * m_sca.y;
	m_ghostPos.z += ADD_GHOST_POS.z;

	//デスブロックの当たり判定の初期化。
	m_ghostBox.CreateBox(
		m_ghostPos,																	//第一引数は座標。
		Quaternion::Identity,														//第二引数は回転クォータニオン。
		{ GHOST_SIZE.x * m_sca.x, GHOST_SIZE.y * m_sca.y, GHOST_SIZE.z * m_sca.z}	//第三引数はボックスのサイズ。
	);

	//座標を設定。
	m_skinModelRender->SetPosition(m_pos);
	//拡大率を設定。
	m_skinModelRender->SetScale(m_sca);
	//ワールド行列を更新。
	m_skinModelRender->UpdateWorldMatrix();
	return true;
}

DeathBlock::~DeathBlock() {

	//デスブロックのモデルを削除。
	DeleteGO(m_skinModelRender);
}

void DeathBlock::Update() {


	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {
		//ノイズをかけていく。
		m_ligData.uvNoiseOffset += ADD_UV_NOISE_OFFSET;
		float t;
		m_ligData.uvNoiseOffset = modf(m_ligData.uvNoiseOffset, &t);

		//プレイヤーと当たったか。
		if (m_ghostBox.IsSelf(contactObject)) {
			//当たったフラグをtrueに。
			m_hitPlayer = true;
		}
		});


	//プレイヤーと当たった。
	if (m_hitPlayer && !m_player->GetTreasureFlg())
	{
		
		if (!m_player->GetRespawn()) {
			//死亡エフェクトを再生。
			Effect* m_death = NewGO<Effect>(enPriority_Zeroth);
			m_death->Init(DEATH_EFFECT_FILE_PATH);
			m_death->SetScale(EFFECT_SCALE);
			m_death->SetPosition(m_player->GetPosition());
			m_death->Play();

			//死亡SEを再生。
			SoundManager::GetInstance()->Play(enSE_Death);

			//プレイヤーのリスポーンフラグを設定。
			m_player->SetRespawn(true);
			m_deathActiveState = m_player->DeactivatePlayerModel();
			m_deathFlg = true;
		}

		//プレイヤーと当たってからの時間（１フレーム当たり）を加算。
		m_hitTimer += GameTime().GameTimeFunc().GetFrameDeltaTime();

		//３秒経過。
		if (m_hitTimer >= HIT_TIMER_VALUE[enData_First])
		{
			//リスポーンSEを再生。
			SoundManager::GetInstance()->Play(enSE_ReStart);
			//プレイヤーのリスポーンフラグを再設定。
			m_player->SetRespawn(false);
			m_hitPlayer = false;
			m_respawnEfk = false;
			//シーソーの回転率を元に戻す。
			m_backGround->SetStart(true);

			//タイマーを元に戻す。
			m_hitTimer = TIMER_CLEAR;

		}
		//2.5秒経過。
		else if (m_hitTimer >= HIT_TIMER_VALUE[enData_Zeroth]) {

			//プレイヤーが既に鍵を取得しているなら
			if (m_player->GetKeyFlg()) {
				m_key = FindGO<Key>(NAME_KEY);
				//プレイヤーを鍵の位置に設定。
				m_player->SetPosition(m_key->GetKeyPos());
				//プレイヤーを有効にする。
				m_player->ActivatePlayerModel(m_deathActiveState);
				m_deathFlg = false;
			}
			//プレイヤーが鍵を取得していないなら
			else {
				//プレイヤーをスタート地点に設定。
				m_player->SetPosition(m_player->GetStartPos());
				//プレイヤーを有効にする。
				m_player->ActivatePlayerModel(m_deathActiveState);
				m_deathFlg = false;
			}
			//リスポーンのエフェクトが生成されていないなら。
			if (!m_respawnEfk) {
				//エフェクトを生成。
				m_efkRespawn = NewGO<Effect>(enPriority_Zeroth);
				m_efkRespawn->Init(DEATH_EFFECT_FILE_PATH);
				m_efkRespawn->SetScale(EFFECT_SCALE);
				m_efkRespawn->SetPosition(m_player->GetPosition());
				m_efkRespawn->Play();
				m_respawnEfk = true;
			}
		}
		else {
			//プレイヤーの座標をその場に設定。
			m_player->SetPosition(m_player->GetPosition());
		}
		//プレイヤーにかかる力を無効にする。
		m_player->ClearPower();

		if (m_efkRespawn != nullptr) {
			//リスポーンエフェクトの発生場所をプレイヤーの場所にする。
			m_efkRespawn->SetPosition(m_player->GetPosition());
		}
	}
}

void DeathBlock::Init(const char* name)
{
	char filePathtkm[NAME_SIZE];
	sprintf(filePathtkm, DEATH_BLOCK_STANDARD_FILE_PATH, name);
	m_skinModelRender = NewGO<SkinModelRender>(enPriority_Zeroth);
	//tkmファイルを設定。
	m_skinModelRender->SetFileNametkm(filePathtkm);
	//シャドウレシーバーフラグを設定。
	m_skinModelRender->SetShadowReceiverFlag(true);
	//Zプリパスを設定。
	m_skinModelRender->SetZprepassFlag(true);

	//ディレクションライトの向きを設定。
	m_ligData.m_directionLigData[enData_Zeroth].Dir.Set(DEATH_BLOCK_LIG_DIR);
	//正規化。
	m_ligData.m_directionLigData[enData_Zeroth].Dir.Normalize();

	//環境光を設定。
	m_ligData.ambient.Set(DEATH_BLOCK_LIG_AMBIENT);
	//金属度を設定。
	m_ligData.metaric = DEATH_BLOCK_METARIC;
	//なめらかさを設定。
	m_ligData.smooth = DEATH_BLOCK_SMOOTH;
	//輪郭線のタイプを設定。
	m_ligData.edge = Edge_1;
	//絞り率を設定。
	m_ligData.powValue = DEATH_BLOCK_POW_VALUE;
	//ノイズの強さを設定。
	m_ligData.uvNoiseMul = UV_NOISE_MUL;
	//ユーザー定義のライト情報を設定。
	m_skinModelRender->SetUserLigData(&m_ligData);
	//カラーバッファのフォーマットを指定。
	m_skinModelRender->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);
	//モデルを初期化。
	m_skinModelRender->Init();
}

