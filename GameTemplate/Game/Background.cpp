#include "stdafx.h"
#include "Background.h"

bool Background::Start()
{

	//これがlevelのLoadの基盤。
	//特定のオブジェクトを指定する（ここでいうフック）場合は、名前検索するなのね。
	m_level.Init("Assets/level/stage_00.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"Star") == true) {
			
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
	m_model.Draw(rc);
}