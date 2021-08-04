#include "stdafx.h"
#include "TreasureBox.h"
#include "Player.h"
#include "Game.h"

namespace {
	const Vector3 TREASURE_BOX_GHOST_POS = { 130.0f,-100.0f,150.0f };
	const Vector3 TREASURE_BOX_SIZE = { 300.0f,200.0f,400.0f };
	const char* FILE_NAME_TKM_TREASURE_BOX = "Assets/modelData/tkm/TreasureBox.tkm";
	const char* FILE_NAME_TKS_TREASURE_BOX = "Assets/modelData/tks/TreasureBox.tks";
	const char* FILE_PATH_TKA_TREASURE_BOX_OPEN = "Assets/modelData/tka/TreasureBox.tka";

	const Vector3 LIG_DIRECTION_TREASURE_BOX = { 0.0f,1.0f,1.0f };
	const Vector4 LIG_COLOR_TREASURE_BOX = { 20.0f, 20.0f, 20.0f, 1.0f };
	const Vector3 TREASURE_BOX_AMBIENT = { 0.8f, 0.8f, 0.8f };
	const float TREASURE_BOX_METARIC = 1.0f;
	const float TREASURE_BOX_SMOOTH = 0.35f;
	const float TREASURE_BOX_POW_VALUE = 0.70f;

	const char16_t* FILE_PATH_EFFECT_SHINE = u"Assets/effect/treasure_4.efk";
	const Vector3 EFFECT_SHINE_SCALE = { 80.0f,80.0f,80.0f };
	const Vector3 ADD_EFFECT_POS = { 100.0f, -150.0f, 60.0f };

	const float TREASURE_BOX_FRICTION = 10.0f;
}


bool TreasureBox::Start() {

	m_player = FindGO<Player>(NAME_PLAYER);
	m_game = FindGO<Game>(NAME_GAME);
	m_player->GetRigidBody()->GetBody()->setIgnoreCollisionCheck(m_ghostBox.GetGhostObject(), true);
	Vector3 ghostPos = m_pos;
	ghostPos += TREASURE_BOX_GHOST_POS;
	m_ghostBox.CreateBox(
		ghostPos,	//第一引数は座標。
		Quaternion::Identity,		//第二引数は回転クォータニオン。
		TREASURE_BOX_SIZE	//第三引数はボックスのサイズ。
	);

	m_skinModelRender = NewGO<SkinModelRender>(enPriority_Zeroth);
	m_skinModelRender->SetFileNametkm(FILE_NAME_TKM_TREASURE_BOX);
	m_skinModelRender->SetFileNametks(FILE_NAME_TKS_TREASURE_BOX);
	//m_skinModelRender->SetShadowReceiverFlag(true);

	m_animClip.Load(FILE_PATH_TKA_TREASURE_BOX_OPEN);
	m_animClip.SetLoopFlag(false);

	m_skinModelRender->InitAnimation(&m_animClip, enAnimation_Open);

	//座標を登録。
	m_ligData.m_directionLigData[enData_Zeroth].Dir.Set(LIG_DIRECTION_TREASURE_BOX);
	m_ligData.m_directionLigData[enData_Zeroth].Dir.Normalize();
	m_ligData.m_directionLigData[enData_Zeroth].Col.Set(LIG_COLOR_TREASURE_BOX);
	m_ligData.ambient.Set(TREASURE_BOX_AMBIENT);
	m_ligData.metaric = TREASURE_BOX_METARIC;
	m_ligData.smooth = TREASURE_BOX_SMOOTH;
	m_ligData.edge = Edge_1;
	m_ligData.powValue = TREASURE_BOX_POW_VALUE;

	m_skinModelRender->SetUserLigData(&m_ligData);
	//m_skinModelRender->SetExpandShaderResourceView_2(&RenderTarget::GetZPrepassRenderTarget()->GetRenderTargetTexture());
	m_skinModelRender->SetColorBufferFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);
	m_skinModelRender->Init();

	m_skinModelRender->SetPosition(m_pos);
	m_skinModelRender->SetRotation(m_rot);
	m_skinModelRender->SetScale(m_sca);

	m_skinModelRender->UpdateWorldMatrix();
	m_physicsStaticObject.CreateFromModel(
		*m_skinModelRender->GetModel(),
		m_skinModelRender->GetModel()->GetWorldMatrix()
	);
	m_physicsStaticObject.SetFriction(TREASURE_BOX_FRICTION);
	return true;
}

TreasureBox::~TreasureBox() {
	DeleteGO(m_skinModelRender);
	m_effect->Stop();
	DeleteGO(m_effect);
	m_effect = nullptr;
}

void TreasureBox::Update() {

	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

		if (m_ghostBox.IsSelf(contactObject) == true && m_player->GetKeyFlg()) {

			if (!m_soundFlg) {
				SoundManager::GetInstance()->Play(enSE_BoxOpen);
				m_soundFlg = true;
				m_effect = nullptr;
				m_effect = NewGO<Effect>(enPriority_Zeroth);
				m_effect->Init(FILE_PATH_EFFECT_SHINE);
				m_effect->SetScale(EFFECT_SHINE_SCALE);
				Vector3 effPos = m_pos;
				effPos += ADD_EFFECT_POS;
				m_effect->SetPosition(effPos);
				m_effect->Play();
			}
			m_skinModelRender->SetAnimFlg(true);
			m_treasureFlg = true;
		}
	});
}