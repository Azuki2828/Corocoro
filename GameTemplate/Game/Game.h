#pragma once

class Player;
class BackGround;
class MainCamera;
class GameTime;
class Key;
class SaveData;
class ResultScene;
class TreasureBox;

class Game : public IGameObject
{
private:
	bool Start()override final;
	~Game();
	void Update()override final;

public:
	/**
	 * @brief ゲーム中のタイムを取得する関数。
	 * @return タイム
	*/
	float GetTime()
	{
		return m_time;
	}
	/**
	 * @brief 最高記録を取得する関数。
	 * @return ステージごとの最高記録。
	*/
	float GetBestTime() {
		return m_resultTime[m_stageNum];
	}
	/**
	 * @brief ゲーム開始のサウンドを再生しているかどうか確かめる関数。
	 * @return ゲームスタートの開始サウンドの再生フラグ
	*/
	bool GetStartFlg() {
		return m_startSoundflg;
	}
	/**
	 * @brief ゲームの開始タイミングを取得する関数。
	 * @return ゲームが始まるまでの時間
	*/
	int GetGameStartTime() {
		return static_cast<int>(m_gameStartTime);
	}
	/**
	 * @brief ステージ番号を取得する関数。
	 * @return ステージ番号
	*/
	int GetStageNum() {
		return m_stageNum;
	}
	/**
	 * @brief ステージ番号を設定する関数。
	 * @param num ステージ番号
	*/
	void SetStageNum(int num) {
		m_stageNum = num;
	}
	/**
	 * @brief プレイヤーが、死亡する何かに当たったかどうか確かめる関数。
	 * @param flg プレイヤーの当たり判定フラグ
	*/
	void SetHitPlayer(bool flg) {
		m_hitPlayer = flg;
	}
	/**
	 * @brief ゲームが始まったかどうか確かめる関数。
	 * @return ゲームが始まっているかのフラグ
	*/
	bool GetGameFlg() {
		return m_gameStartFlg;
	}
	/**
	 * @brief 最高記録を保存する関数。
	 * @param num ステージ番号
	 * @param time 記録
	*/
	void SetResultTime(int num, float time) {
		m_resultTime[num] = time;
	}
	;
private:
	bool m_treasureFlg = false;					//宝箱が開いたかどうか
	bool m_respawnEfk = false;					//リスポーン時のエフェクトを再生したかどうか
	bool m_deathFlg = false;					//プレイヤーが死亡したかどうか
	bool m_hitPlayer = false;					//プレイヤーが死亡オブジェクトに触れたかどうか
	bool m_startSoundflg = true;				//カウントダウンのサウンドが再生されたかどうか
	bool m_gameStartFlg = false;				//ゲームが始まったかどうか
	bool m_countDownSprite = false;				//カウントダウンのスプライトが表示され始めたかどうか
	int m_deathActiveState = 0;					//デスブロックに触れたときのキャラクターのステートを保持
	int m_stageNum = 0;							//ステージ番号
	float m_time = 0.0f;						//ゲーム中のタイム
	float m_countDownTimer = 0.0f;				//カウントダウン時のスプライト管理用のタイマー
	float m_gameStartTime = 0.0f;				//ゲームが始まるまでの時間
	float m_resultTime[Stage_Num] = { 0.0f };	//ステージごとの最高記録
	float m_resultSceneTime = 0.0f;				//リザルト画面に映るまでのタイマー
	float m_hitTimer = 0.0f;					//プレイヤーが死亡しているときのコードで使用するタイマー

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	FontRender* m_fontRender = nullptr;
	GameTime* m_gametime = nullptr;
	Effect* m_effect = nullptr;
	Effect* m_efkRespawn = nullptr;
	Player* m_player = nullptr;
	BackGround* m_backGround = nullptr;
	MainCamera* m_camera = nullptr;
	DirectionLight* m_dirLight = nullptr;
	SaveData* m_saveData = nullptr;
	ResultScene* m_resultScene = nullptr;
	Key* m_key = nullptr;
	TreasureBox* m_treasureBox = nullptr;
};

