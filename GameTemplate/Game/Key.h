#pragma once

class Player;
class BackGround;
class MainCamera;
class GameLevel2D;
class Game;

namespace {

	const float BASE_KEY_ROT_VALUE = 180.0f;
	const float KEY_GET_START_TIME = 3.0f;
	const float SOUND_DERAY_COUNT = 2.0f;

	const char16_t* KEY_GET_EFFECT_FILE_PATH = u"Assets/effect/KeyGet.efk";
	const Vector3 KEY_GET_EFFECT_SCALE = { 200.0f,200.0f,200.0f };
	const Vector3 KEY_GET_EFFECT_ADD_POS = { 0.0f,150.0f,0.0f };


	const Vector3 KEY_TRIGGER_BOX_ADD_POS = { 0.0f,125.0f,0.0f };
	const Vector3 KEY_TRIGGER_BOX_SIZE = { 100.0f, 250.0f, 100.0f };


	const Vector3 KEY_LIG_FIRST_DIRECTION = { 1.0f, -1.0f, 1.0f };
	const Vector4 KEY_LIG_FIRST_COLOR = { 20.0f, 20.0f, 0.0f, 1.0f };
	const Vector3 KEY_LIG_SECOND_DIRECTION = { 1.0f,1.0f,1.0f };
	const Vector4 KEY_LIG_SECOND_COLOR = { 10.0f, 10.0f, 0.0f, 1.0f };
	const float KEY_METARIC = 1.0f;
	const float KEY_SMOOTH = 0.6f;
	const Vector3 KEY_AMBIENT = { 0.2f, 0.2f, 0.2f };
	const float KEY_POW_VALUE = 0.7f;

	const Vector3 TREASURE_BOX_FLOOR_LIG_DIRECTION = { -1.0f, -1.0f, -1.0f };
	const Vector4 TREASURE_BOX_FLOOR_LIG_COLOR = { 10.0f, 10.0f, 10.0f, 1.0f };
	const float TREASURE_BOX_METARIC = 1.0f;
	const float TREASURE_BOX_SMOOTH = 0.35f;
	const Vector3 TREASURE_BOX_AMBIENT = { 0.8f, 0.8f, 0.8f };
}

class Key : public IGameObject
{
private:
	~Key();
	bool Start()override final;
	void Update()override final;

public:


	//鍵を初期化する関数。
	void InitKey(const char* name);

	//ドアを初期化する関数。
	void InitDoor(const char* name);

	//鍵の座標を取得する関数。
	const Vector3 GetKeyPos() { return m_keyPos; }

	//鍵の座標を設定する関数。
	void SetKeyPos(const Vector3& pos) { m_keyPos = pos; }

	//ドアの座標を設定する関数。
	void SetDoorPos(const Vector3& pos) { m_doorPos = pos; }

	void SetScaleKey(const Vector3& sca) {
		m_keyScale = sca;
	}

	void SetScaleDoor(const Vector3& sca) {
		m_doorScale = sca;
	}

	float GetGameOverCount() {
		return m_gameOverCount;
	}


	void SetTriggerBox(const Vector3 pos) {
		Vector3 ghostPos = pos;
		ghostPos += KEY_TRIGGER_BOX_ADD_POS;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			KEY_TRIGGER_BOX_SIZE	//第三引数はボックスのサイズ。
		);
	}


private:
	bool m_getKeyFlg = false;
	bool m_gameClearSoundFlag = true;				//ゲームクリアのサウンド再生を1回だけにするフラグ
	bool m_keyGetSoundFlag = true;	//鍵取得のサウンド再生を1回だけにするフラグ
	bool m_startUpTempoSoundFlg = false;
	int m_gameOverCount = 0;
	int m_delayCount = 0;	//鍵を取得してから鍵取得のサウンド再生が終わるまでの時間を待たせる変数。
	float m_keyRotTime = 0.0f;
	Vector3 m_keyPos = Vector3::Zero;		//鍵の座標。
	Vector3 m_keyScale = Vector3::One;
	Quaternion m_keyRot = Quaternion::Identity;
	Vector3 m_doorPos = Vector3::Zero;		//ドアの座標。
	Vector3 m_doorScale = Vector3::One;

	

	LigData m_ligKeyData;
	LigData m_ligDoorData;
	PhysicsStaticObject m_physicsStaticObject;
	CPhysicsGhostObject m_ghostBox;


	//それぞれのクラスのポインタ

	MainCamera* maincamera;
	FontRender* m_fontRender = nullptr;
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	GameLevel2D* m_gameLevel2D = nullptr;
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー
};