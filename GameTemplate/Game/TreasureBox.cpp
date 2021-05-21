#include "stdafx.h"
#include "TreasureBox.h"
#include "Player.h"

bool TreasureBox::Start() {

	m_player = FindGO<Player>("player");
	m_player->GetRigidBody()->GetBody()->setIgnoreCollisionCheck(m_ghostBox.GetGhostObject(), true);
	Vector3 ghostPos = m_pos;
	ghostPos.x += 130.0f;
	ghostPos.y -= 100.0f;
	ghostPos.z += 150.0f;
	m_ghostBox.CreateBox(
		ghostPos,	//�������͍��W�B
		Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{ 300.0f, 200.0f, 400.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);

	m_skinModelRender = NewGO<SkinModelRender>(0);
	m_skinModelRender->SetFileNametkm("Assets/modelData/tkm/TreasureBox.tkm");
	m_skinModelRender->SetFileNametks("Assets/modelData/tks/TreasureBox.tks");

	m_animClip.Load("Assets/modelData/tka/TreasureBox.tka");
	m_animClip.SetLoopFlag(false);

	m_skinModelRender->InitAnimation(&m_animClip, 1);

	//���W��o�^�B
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

void TreasureBox::Update() {

	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

		if (m_ghostBox.IsSelf(contactObject) == true && m_player->GetKeyFlg()) {
			m_skinModelRender->SetAnimFlg(true);
			m_treasureFlg = true;
		}
		});
}