#pragma once

class Player;
class Background;
class MainCamera;
class GameLevel2D;
class Game;

class Key : public IGameObject
{
public:
	bool Start()override final;

	~Key();

	//鍵を初期化する関数。
	void InitKey(const char* name);

	//ドアを初期化する関数。
	void InitDoor(const char* name);

	//鍵の座標を取得する関数。
	const Vector3 GetKeyPos() { return m_keyPos; }

	//鍵の座標を設定する関数。
	void SetPositionKey(const Vector3& pos) { m_keyPos = pos; }

	//ドアの座標を設定する関数。
	void SetPositionDoor(const Vector3& pos) { m_doorPos = pos; }

	void SetScaleKey(const Vector3& sca) {
		m_keyScale = sca;
	}

	void SetScaleDoor(const Vector3& sca) {
		m_Doorscale = sca;
	}

	void Update()override final;
	bool GetdoorbreakFlg() { return m_doorbreakFlg; };

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



	//ゲームクリアしてからの秒数をカウント
	//他クラスでもそのカウント時間を参照したいからpublicに入れている。
	int GameOverCount = 0;


private:
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	PhysicsStaticObject m_physicsStaticObject;
	bool getKeyFlg = false;
	bool m_doorbreakFlg = false;

	Player* m_player = nullptr;
	Game* m_game = nullptr;
	GameLevel2D* m_level2D = nullptr;
	Vector3 m_keyPos;		//鍵の座標。
	Vector3 m_keyScale;
	Vector3 m_doorPos;		//ドアの座標。
	Vector3 m_Doorscale;
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー
	CSoundSource* m_sound = nullptr;			//効果音追加

	CSoundSource* GameClearSound = nullptr;		//ゲームクリアのサウンドソース
	bool GameClearSoundFlag = true;				//ゲームクリアのサウンド再生を1回だけにするフラグ
	CSoundSource* KeyGetSound = nullptr;		//鍵取得のサウンドソース
	bool KeyGetSoundFlag = true;	//鍵取得のサウンド再生を1回だけにするフラグ
	CSoundSource* GameBGMSound_UpTempo = nullptr;	//アップテンポ版BGMのサウンドソース

	int GetDelay = 0;	//鍵を取得してから鍵取得のサウンド再生が終わるまでの時間を待たせる変数。

	FontRender* m_fontRender = nullptr;

	MainCamera* maincamera;
	LigData m_ligKeyData;
	LigData m_ligDoorData;
	CPhysicsGhostObject m_ghostBox;
};