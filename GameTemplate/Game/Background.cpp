#include "stdafx.h"
#include "Background.h"

bool Background::Start()
{

	//m_spriteRender = NewGO<SpriteRender>(0);
	//m_spriteRender->Init("Assets/Image/sample.dds", 1980.0f, 1080.0f);

	//これがlevelのLoadの基盤。
	//特定のオブジェクトを指定する（ここでいうフック）場合は、名前検索するなのね。
	m_level.Init("Assets/level/stage02.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"stage02_goal") == true) {
			return true;
		}
		else if (objData.EqualObjectName(L"") == true) {
			return true;
		}
		else if (objData.EqualObjectName(L"KeyBox") == true) {
			return true;
		}
		else if (objData.EqualObjectName(L"UnityChan") == true) {
			//UnityChan
			//m_player = NewGO
			//m_player->
			return true;
		}
		return false;//levelのオブジェクトをそのままロード。
	});
	//ModelInitData initData;
	//initData.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	////シェーダーファイルのファイルパスを指定する。
	//initData.m_fxFilePath = "Assets/shader/model.fx";
	////頂点シェーダーのエントリーポイント
	//initData.m_vsEntryPointFunc = "VSMain";
	//m_model.Init(initData);
	//
	////メッシュコライダーを作成。
	//m_physicsStaticObject.CreateFromModel(m_model, m_model.GetWorldMatrix());
	return true;
}
void Background::Update()
{

}
void Background::Render(RenderContext& rc)
{
	m_level.Draw(rc);
	m_model.Draw(rc);
}