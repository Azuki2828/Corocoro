#include "stdafx.h"
#include "TreasureBox.h"
#include "Player.h"
#include "Game.h"

bool TreasureBox::Start() {

	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
	m_player->GetRigidBody()->GetBody()->setIgnoreCollisionCheck(m_ghostBox.GetGhostObject(), true);
	Vector3 ghostPos = m_pos;
	ghostPos.x += 130.0f;
	ghostPos.y -= 100.0f;
	ghostPos.z += 150.0f;
	m_ghostBox.CreateBox(
		ghostPos,	//第一引数は座標。
		Quaternion::Identity,		//第二引数は回転クォータニオン。
		{ 300.0f, 200.0f, 400.0f }	//第三引数はボックスのサイズ。
	);

	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->SetFileNametkm("Assets/modelData/tkm/TreasureBox.tkm");
	m_skinModelRender->SetFileNametks("Assets/modelData/tks/TreasureBox.tks");

	m_animClip.Load("Assets/modelData/tka/TreasureBox.tka");
	m_animClip.SetLoopFlag(false);

	m_skinModelRender->InitAnimation(&m_animClip, 1);

	//座標を登録。
	m_ligData.m_directionLigData[0].Dir.Set(0, 1, 1);
	m_ligData.m_directionLigData[0].Dir.Normalize();
	m_ligData.m_directionLigData[0].Col.Set(20.0f, 20.0f, 20.0f, 1.0f);
	m_ligData.ambient.Set(0.8f, 0.8f, 0.8f);
	m_ligData.metaric = 1.0f;
	m_ligData.smooth = 0.35f; 
	m_ligData.edge = Edge_1;
	m_ligData.powValue = 0.7f;

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
	m_physicsStaticObject.SetFriction(10.0f);
	return true;
}

TreasureBox::~TreasureBox() {
	DeleteGO(m_skinModelRender);
	if (m_effect != nullptr) {
		DeleteGO(m_effect);
	}
}

void TreasureBox::Update() {

	static float effectTime = 0.0f;

	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

		if (m_ghostBox.IsSelf(contactObject) == true && m_player->GetKeyFlg()) {

			if (!soundFlg) {
				SoundManager::GetInstance()->Play(SE_BoxOpen);
				soundFlg = true;
				m_effect = nullptr;
				m_effect = NewGO<Effect>(0);
				m_effect->Init(u"Assets/effect/treasure_4.efk");
				m_effect->SetScale({ 80.0f,80.0f,80.0f });
				Vector3 effPos = m_pos;
				effPos += { 100.0f, -150.0f, 60.0f };
				m_effect->SetPosition(effPos);
				//treasure->Update();
				m_effect->Play();
			}
			m_skinModelRender->SetAnimFlg(true);
			m_treasureFlg = true;
			//m_game->SetGameFlg(true);
			
		}
	});


	static bool effectFlg = false;
	//if (m_player->GetTreasureFlg()) {
	//	effectTime += GameTime().GameTimeFunc().GetFrameDeltaTime();
	//	if (effectTime >= 0.5f && !effectFlg) {
	//		Effect* treasure = nullptr;
	//		treasure = NewGO<Effect>(0);
	//		treasure->Init(u"Assets/effect/treasure_4.efk");
	//		treasure->SetScale({ 80.0f,80.0f,80.0f });
	//		Vector3 effPos = m_pos;
	//		effPos += { 200.0f, -150.0f, -500.0f };
	//		treasure->SetPosition(effPos);
	//		//treasure->Update();
	//		treasure->Play();
	//	
	//		effectFlg = true;
	//	}
	//}
}