#include "stdafx.h"
#include "Background2.h"

bool Background2::Start()
{
	ModelInitData initData;
	initData.m_tkmFilePath = "Assets/modelData/bg/bg2.tkm";
	//シェーダーファイルのファイルパスを指定する。
	initData.m_fxFilePath = "Assets/shader/model.fx";
	//頂点シェーダーのエントリーポイント
	initData.m_vsEntryPointFunc = "VSMain";
	m_model.Init(initData);

	//メッシュコライダーを作成。
	m_physicsStaticObject.CreateFromModel(m_model, m_model.GetWorldMatrix());
	m_physicsStaticObject.SetFriction(10.0f);
	return true;
}
void Background2::Update()
{

}
void Background2::Render(RenderContext& rc)
{
	m_model.Draw(rc);
}