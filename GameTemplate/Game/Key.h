#pragma once

class Player;
class BackGround;
class MainCamera;
class GameLevel2D;
class Game;

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
		//ghostPos.x += 300.0f;
		ghostPos.y += 125.0f;
		//ghostPos.z -= 300.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			{ 100.0f, 250.0f, 100.0f }	//第三引数はボックスのサイズ。
		);
	}


private:
	bool m_getKeyFlg = false;
	bool m_gameClearSoundFlag = true;				//ゲームクリアのサウンド再生を1回だけにするフラグ
	bool m_keyGetSoundFlag = true;	//鍵取得のサウンド再生を1回だけにするフラグ
	int m_gameOverCount = 0;
	int m_delayCount = 0;	//鍵を取得してから鍵取得のサウンド再生が終わるまでの時間を待たせる変数。
	Vector3 m_keyPos = Vector3::Zero;		//鍵の座標。
	Vector3 m_keyScale = Vector3::One;
	Vector3 m_doorPos = Vector3::Zero;		//ドアの座標。
	Vector3 m_doorScale = Vector3::One;

	

	LigData m_ligKeyData;
	LigData m_ligDoorData;
	PhysicsStaticObject m_physicsStaticObject;
	CPhysicsGhostObject m_ghostBox;

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	MainCamera* maincamera;
	FontRender* m_fontRender = nullptr;
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	GameLevel2D* m_level2D = nullptr;
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー
};