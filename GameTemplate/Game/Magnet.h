#pragma once

class Player;
class Key;

class Magnet : public IGameObject
{
private:
	int m_timer = 0;			//<変更>動く磁石の一時停止のためm_timerを追加
public:
	bool Start() override final;
	void Update() override final;
	
	//磁力をNにする関数。
	void SetState_N(bool plusflg = false) {
		mState = State_N;
		if (plusflg) {
			plusFlg = true;
		}
	}
	//磁力Sにする関数。
	void SetState_S(bool plusflg = false) {
		mState = State_S; 
		if (plusflg) {
			plusFlg = true;
		}
	}

	//移動範囲を設定する関数。
	//front:前の座標。	back:後の座標。
	//xの値が小さい方をfrontに設定するようにしてください。
	void SetMove(Vector3 front, Vector3 back) { moveRange_front = front, moveRange_back = back, moveFlg = true; }

	//座標を登録する関数。
	void SetPosition(Vector3 pos) { m_pos = pos; }

	//初期化関数。
	void Init(const char* magnetName)
	{
		char filePathtkm[256];

		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", magnetName);
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetFileNametkm(filePathtkm);
		m_skinModelRender->SetShadowReceiverFlag(true);
		m_skinModelRender->Init(true, false);
	}
private:

	//プレイヤーに力を与える関数。
	void SetMagnetPower()const;

	bool plusFlg = false;		//強い磁石フラグ。
	bool moveFlg = false;		//動くフラグ。
	mutable Vector3 m_length;	//プレイヤーとの距離。
	Vector3 m_pos;				//座標。
	Vector3 moveRange_front;	//移動範囲の左端。
	Vector3 moveRange_back;		//移動範囲の右端。
	Vector3 moveSpeed;			//動く速さ。

	/// <summary>
	/// 磁極のステート。
	/// </summary>
	typedef enum {
		State_N,
		State_S,
		State_Nplus,
		State_Splus,
	}Magnet_State;

	Magnet_State mState;	//磁極のステート。

	Player* m_player = nullptr;
	Key* m_key = nullptr;

	SkinModelRender* m_skinModelRender = nullptr;
	PhysicsStaticObject m_physicsStaticObject;
};

