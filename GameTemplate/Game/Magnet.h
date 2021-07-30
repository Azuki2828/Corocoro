#pragma once

class Player;
class Key;
class Game;

namespace {
	const float MAGNET_POWER = 100000.0f;		//基盤の磁力
	const float MAGNET_FRICTION = 10.0f;		//磁石の摩擦

	const Vector3 MAGNET_TRIGGER_BOX_ADD_POS_BASE = { 0.0f,0.0f,-200.0f };	//磁力の発生位置の調整

	const float MAGNET_Z_POWER = 0.0f;								//Z方向には磁力を発生させない
	const Vector4 MAGNET_N_LIG_COLOR = { 10.0f,10.0f,10.0f,1.0f };	//N磁石の色
	const Vector4 MAGNET_S_LIG_COLOR = { 10.0f,10.0f,30.0f,1.0f };	//S磁石の色
	const Vector3 MAGNET_LIG_DIR = { -1.0f,-1.0f,-1.0f };			//磁石のライトの方向
	const Vector3 MAGNET_LIG_AMBIENT = { 0.8f,0.8f,0.8f };			//磁石のライトの環境光の強さ
	const float MAGNET_METARIC = 1.0f;								//磁石の金属度
	const float MAGNET_SMOOTH = 0.35f;								//磁石のなめらかさ
	const float MAGNET_POW_VALUE = 10.0f;							//絞り率
}

class Magnet : public IGameObject
{
private:
	~Magnet();
	bool Start() override final;
	void Update() override final;

public:

	/**
	 * @brief 磁極をNにする関数。
	 * @param plusflg 強い磁石かどうかのフラグ
	*/
	void SetState_N(bool plusflg = false) {
		m_magState = State_N;
		m_ligData.m_directionLigData[enData_Zeroth].Col.Set(MAGNET_N_LIG_COLOR);
		if (plusflg) {
			m_plusFlg = true;
		}
	}
	/**
	 * @brief 磁極をSにする関数。
	 * @param plusflg 強い磁石かどうかのフラグ
	*/
	void SetState_S(bool plusflg = false) {
		m_magState = State_S;
		m_ligData.m_directionLigData[enData_Zeroth].Col.Set(MAGNET_S_LIG_COLOR);
		if (plusflg) {
			m_plusFlg = true;
		}
	}

	/**
	 * @brief １/ｎ倍の計算をする関数。
	 * @param n 分母
	 * @return 1/n倍した結果の値
	*/
	float ReturnReciprocal(float n) {

		float value = n;
		//n = 0なら無限大に発散するのでn = 0.0001fとする。
		if (value == 0) {
			value = 0.0001f;
		}

		//計算結果を返す。
		return 1.0f / value;
	}

	/**
	 * @brief 座標を設定する関数。
	 * @param pos 座標
	*/
	void SetPosition(Vector3 pos) { m_pos = pos; }

	/**
	 * @brief 回転率を設定する関数。
	 * @param rot 回転率
	*/
	void SetRotation(const Quaternion& rot) {
		m_rot = rot;
	}

	/**
	 * @brief 拡大率を設定する関数。
	 * @param sca 拡大率
	*/
	void SetScale(const Vector3& sca) {
		m_sca = sca;
	}

	/**
	 * @brief 座標を取得する関数。
	 * @return 座標
	*/
	Vector3 GetPosition() { return m_pos; }

	/**
	 * @brief トリガーボックスを作成する関数。
	 * @param type トリガーボックスのタイプ
	*/
	void CreateTriggerBox(int type);

	/**
	 * @brief プレイヤーに力を与える関数。
	*/
	void SetMagnetPower();

	/**
	 * @brief 磁石の影響範囲を決める関数。
	 * @param stageNum ステージ番号
	*/
	void SetMagnetTriggerBox(int stageNum);

	/**
	 * @brief 磁石の番号を設定する関数。
	 * @param num ステージ番号
	*/
	void SetMagnetNum(int num) {
		m_magnetNum = num;
	}

	/**
	 * @brief 磁石の基点を設定する関数。
	 * @param pos 基点となる座標
	*/
	void SetMagnetPosition(const Vector3& pos) {
		m_magnetPos = pos;
	}

	/**
	 * @brief 初期化関数。
	 * @param magnetName 磁石の名前
	*/
	void Init(const char* magnetName)
	{
		char filePathtkm[NAME_SIZE];

		//名前からモデルも作成。
		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", magnetName);
		m_skinModelRender = NewGO<SkinModelRender>(enPriority_Zeroth);
		m_skinModelRender->SetFileNametkm(filePathtkm);

		//シャドウを受けるフラグを設定
		m_skinModelRender->SetShadowReceiverFlag(true);

		//Ｚプレパスフラグを設定
		m_skinModelRender->SetZprepassFlag(true);

		//ライトの方向を設定
		m_ligData.m_directionLigData[enData_Zeroth].Dir.Set(MAGNET_LIG_DIR);
		m_ligData.m_directionLigData[enData_Zeroth].Dir.Normalize();
		
		//環境光を設定
		m_ligData.ambient.Set(MAGNET_LIG_AMBIENT);
		//金属度を設定
		m_ligData.metaric = MAGNET_METARIC;
		//なめらかさを設定
		m_ligData.smooth = MAGNET_SMOOTH;
		//輪郭線を設定
		m_ligData.edge = Edge_1;
		//絞り率を設定
		m_ligData.powValue = MAGNET_POW_VALUE;
		//ライトデータから独自のライトを設定
		m_skinModelRender->SetUserLigData(&m_ligData);
		//カラーバッファのフォーマットを指定
		m_skinModelRender->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);
		//初期化
		m_skinModelRender->Init();
	}
private:
	/// <summary>
	/// 磁極のステート。
	/// </summary>
	typedef enum {
		State_N,
		State_S,
		State_Nplus,
		State_Splus,
	}Magnet_State;

	//磁力の影響範囲のサンプル
	typedef enum {
		Left3,
		Left4,
		Left5,
		Right3,
		Right4,
		Down2,
		Down3,
		Down4,
		Up2,
		Up3,
		Up4,
	}TriggerBoxType;


	bool m_plusFlg = false;							//強い磁石フラグ
	bool m_moveFlg = false;							//動くフラグ
	int m_magnetNum = 0;							//磁石番号
	int m_timer = 0;								//<変更>動く磁石の一時停止のためm_timerを追加
	Vector3 m_length = Vector3::Zero;				//プレイヤーとの距離
	Vector3 m_pos = Vector3::Zero;					//座標
	Quaternion m_rot = Quaternion::Identity;		//回転率
	Vector3 m_sca = Vector3::One;					//拡大率
	Vector3 m_magnetPos = Vector3::Zero;			//磁力の発生場所。基点は左下なため、中心にする
	Vector3 m_moveRange_front = Vector3::Zero;		//移動範囲の左端
	Vector3 m_moveRange_back = Vector3::Zero;		//移動範囲の右端
	Vector3 m_moveSpeed = Vector3::Zero;			//動く速さ

	Magnet_State m_magState = State_N;				//磁極のステート。
	PhysicsStaticObject m_physicsStaticObject;		//当たり判定
	CPhysicsGhostObject m_ghostBox;					//トリガーボックス
	LigData m_ligData;								//ライトのデータ

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	SkinModelRender* m_skinModelRender = nullptr;
	Player* m_player = nullptr;
	Key* m_key = nullptr;
	Game* m_game = nullptr;
};

