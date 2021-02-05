#include "stdafx.h"
#include "Player.h"
#include "DirectionLight.h"
#include "MainCamera.h"

void Player::InitSkeleton()
{
	m_skeleton.Init("Assets/modelData/unityChan.tks");
}
void Player::InitModel(void* data = nullptr)
{
	m_dirLight = NewGO<DirectionLight>(0);
	m_dirLight->Init();
	struct dir{
		Vector3 d;
		float pad;
		Vector3 c;
	};
	dir m_dir;
	m_dir.d = { 1.0f,-1.0f,-1.0f };
	m_dir.d.Normalize();
	m_dir.c = { 0.5f,0.5f,0.5f };

	
	//tkmファイルのファイルパスを指定する。
	initData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	//シェーダーファイルのファイルパスを指定する。
	initData.m_fxFilePath = "Assets/shader/model.fx";
	//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
	initData.m_vsEntryPointFunc = "VSMain";
	//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
	initData.m_vsSkinEntryPointFunc = "VSSkinMain";
	//スケルトンを指定する。
	initData.m_skeleton = &m_skeleton;
	//モデルの上方向を指定する。
	//3dsMaxではデフォルトZアップになっているが、
	//ユニティちゃんはアニメーションでYアップに変更されている。
	initData.m_modelUpAxis = enModelUpAxisY;


	if (data != nullptr) {
		initData.m_expandConstantBuffer = data;
		initData.m_expandConstantBufferSize = 44;
	}

	//作成した初期化データをもとにモデルを初期化する、
	m_model.Init(initData);

	//キャラコンを初期化。
	m_charaCon.Init(40.0f, 100.0f, g_vec3Zero);
}
void Player::InitAnimation()
{
	//アニメーションクリップをロードする。
	m_animationClips[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimClip_Run].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimClip_Run].SetLoopFlag(true);
	//アニメーションを初期化。
	m_animation.Init(
		m_skeleton,			//アニメーションを流し込むスケルトン。
		m_animationClips,	//アニメーションクリップ。
		enAnimClip_Num		//アニメーションの数。
	);
}
bool Player::Start()
{
	m_dirLight = NewGO<DirectionLight>(0);

	m_dirLight->SetLigDirection(1.0f, 1.0f, 1.0f);
	m_dirLight->SetLigColor(0.5f, 0.5f, 0.5f);
	m_dirLight->SetEyePos();
	//スケルトンをロード。
	InitSkeleton();
	//モデルを初期化。
	InitModel(m_dirLight->GetLigData());
	//アニメーションを初期化。
	InitAnimation();

	return true;
}
void Player::Update()
{
	//スケルトンを更新。
	m_skeleton.Update(m_model.GetWorldMatrix());
	//アニメーションを進める。
	m_animation.Progress(1.0f / 60.0f);

	Vector3 moveSpeed;
	moveSpeed.x = g_pad[0]->GetLStickXF() * -3.0f;
	moveSpeed.z = g_pad[0]->GetLStickYF() * -3.0f;
	m_charaCon.Execute(moveSpeed, 1.0f);
	m_model.UpdateWorldMatrix(m_charaCon.GetPosition(), g_quatIdentity, g_vec3One);
}
void Player::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}