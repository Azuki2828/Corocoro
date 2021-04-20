#pragma once

class Player;
class Background;

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
	void SetPositionKey(Vector3 pos) { m_keyPos = pos; }

	//ドアの座標を設定する関数。
	void SetPositionDoor(Vector3 pos) { m_doorPos = pos; }

	void Update()override final;


	//ゲームクリアしてからの秒数をカウント
	//他クラスでもそのカウント時間を参照したいからpublicに入れている。
	int GameOverCount = 0;


private:
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	PhysicsStaticObject m_physicsStaticObject;
	bool getKeyFlg = false;

	Player* m_player = nullptr;
	Vector3 m_keyPos;		//鍵の座標。
	Vector3 m_doorPos;		//ドアの座標。
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー

	CSoundSource* GameClearSound = nullptr;		//ゲームクリアのサウンドソース
	bool GameClearSoundFlag = true;				//ゲームクリアのサウンド再生を1回だけにするフラグ
	CSoundSource* KeyGetSound = nullptr;		//鍵取得のサウンドソース
	bool KeyGetSoundFlag = true;	//鍵取得のサウンド再生を1回だけにするフラグ
	CSoundSource* GameBGMSound_UpTempo = nullptr;	//アップテンポ版BGMのサウンドソース

	int GetDelay = 0;	//鍵を取得してから鍵取得のサウンド再生が終わるまでの時間を待たせる変数。

	bool GameOverFlag = false;

};

