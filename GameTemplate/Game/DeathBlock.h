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
	 * @param name ファイルパス
	*/
	void Init(const char* name)
	{
		char filePathtkm[256];
		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetFileNametkm(filePathtkm);
		m_skinModelRender->SetShadowReceiverFlag(true);
		m_skinModelRender->SetZprepassFlag(true);

		//座標を登録。
		m_ligData.m_directionLigData[0].Dir.Set(-1, -1, -1);
		m_ligData.m_directionLigData[0].Dir.Normalize();
		//m_ligData.m_directionLigData[0].Col.Set(10.0f, 10.0f, 0.0f, 1.0f);

		m_ligData.ambient.Set(0.8f, 0.8f, 0.8f);
		m_ligData.metaric = 1.0f;
		m_ligData.smooth = 0.1f;
		m_ligData.edge = Edge_1;
		m_ligData.powValue = 10.0f;
		m_ligData.uvNoiseMul = 1.0f;
		m_skinModelRender->SetUserLigData(&m_ligData);
		//m_skinModelRender->SetExpandShaderResourceView_2(&RenderTarget::GetZPrepassRenderTarget()->GetRenderTargetTexture());
		m_skinModelRender->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

		m_skinModelRender->Init(true, false);
	}

	void SetStartPos(const Vector3& pos) {
		m_startPos = pos;
	}

	void SetPosition(const Vector3& pos) {
		m_pos = pos;
	}

	void SetScale(const Vector3& sca) {
		m_sca = sca;
	}

	void SetMove(const Vector3& pos_1, const Vector3& pos_2) {

		m_moveFlg = true;
		m_movePos[0] = pos_1;
		m_movePos[1] = pos_2;
	}

	void SetGameEndFlg(bool flg) {
		m_gameflg = flg;
	}


private:
	bool m_gameflg = false;
	bool m_hitPlayer = false;
	bool m_moveFlg = false;
	bool m_respawnEfk = false;
	bool m_deathFlg = false;
	int m_timer = 0;
	int m_returnTimer = 0;
	int m_deathActiveState = 0; //デスブロックに触れたときのキャラクターのステートを保持
	Vector3 m_movePos[2] = { Vector3::Zero };
	Vector3 m_pos = Vector3::Zero;
	Vector3 m_sca = Vector3::One;
	Vector3 m_startPos = Vector3::Zero;
	Vector3 m_ghostPos = Vector3::Zero;
	CPhysicsGhostObject m_ghostBox;

	LigData m_ligData;

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	Effect* m_death = nullptr;
	Effect* m_efkRespawn = nullptr;
	SkinModelRender* m_skinModelRender = nullptr;
	Player* m_player = nullptr;
	Key* m_key = nullptr;
	Game* m_game = nullptr;
	BackGround* m_backGround = nullptr;
};

