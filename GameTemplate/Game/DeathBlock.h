#pragma once
class Player;
class Key;
class BackGround;
class Game;

class DeathBlock : public IGameObject
{
private:
	bool Start()override;
	void Update()override;
	~DeathBlock();
public:

	/**
	 * @brief 初期化関数
	 * @param name 名前
	*/
	void Init(const char* name);

	/**
	 * @brief プレイヤーの初期座標（リスポーン地点）を決める関数
	 * @param pos 座標
	*/
	void SetStartPos(const Vector3& pos) {
		m_startPos = pos;
	}

	/**
	 * @brief 座標を設定する関数
	 * @param pos 座標
	*/
	void SetPosition(const Vector3& pos) {
		m_pos = pos;
	}

	/**
	 * @brief 拡大率を設定する関数
	 * @param sca 拡大率
	*/
	void SetScale(const Vector3& sca) {
		m_sca = sca;
	}

	/**
	 * @brief 自身の可動範囲を設定する関数
	 * @param pos_1 座標１
	 * @param pos_2 座標２
	*/
	void SetMove(const Vector3& pos_1, const Vector3& pos_2) {

		m_moveFlg = true;
		m_movePos[enData_Zeroth] = pos_1;
		m_movePos[enData_First] = pos_2;
	}

	/**
	 * @brief ゲーム終了フラグを受け取る関数
	 * @param flg フラグ
	*/
	void SetGameEndFlg(bool flg) {
		m_gameflg = flg;
	}


private:
	bool m_gameflg = false;							//ゲームが始まったかどうか
	bool m_hitPlayer = false;						//プレイヤーに当たったか
	bool m_moveFlg = false;							//自身が動くブロックかどうか
	bool m_respawnEfk = false;						//エフェクトを一度だけ発生させるためのフラグ
	bool m_deathFlg = false;						//プレイヤーが死んでいるかどうか
	int m_deathActiveState = 0;						//デスブロックに触れたときのキャラクターのステートを保持
	float m_hitTimer = 0.0f;						//プレイヤーが死亡しているときのコードで使用するタイマー
	Vector3 m_movePos[2];							//自身の可動域
	Vector3 m_pos = Vector3::Zero;					//自身の座標
	Vector3 m_sca = Vector3::One;					//自身の拡大率
	Vector3 m_startPos = Vector3::Zero;				//プレイヤーの初期座標
	Vector3 m_ghostPos = Vector3::Zero;				//トリガーボックスの座標
	CPhysicsGhostObject m_ghostBox;					//トリガーボックス

	LigData m_ligData;								//ライトのデータ


	//それぞれのクラスのポインタ

	Effect* m_death = nullptr;
	Effect* m_efkRespawn = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
	Player* m_player = nullptr;
	Key* m_key = nullptr;
	Game* m_game = nullptr;
	BackGround* m_backGround = nullptr;
};

