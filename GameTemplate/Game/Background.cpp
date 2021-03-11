#include "stdafx.h"
#include "Background.h"
#include "Magnet.h"
#include "Key.h"

bool Background::Start()
{
	m_magnet.resize(1);
	int sampleNum = 0;

	/*const char* MagnetName[] = {
		"Magnet_N_01",
		"Magnet_N_02",
		"Magnet_N_03",
		"Magnet_N_04",
		"Magnet_N_05",
		"Magnet_N_06",
		"Magnet_N_move_01",
		"Magnet_Nplus_01",
		"Magnet_S_01",
		"Magnet_S_02",
		"Magnet_S_03",
		"Magnet_Splus_01",
		"MagnetHoge",
	};*/
	//m_spriteRender = NewGO<SpriteRender>(0);
	//m_spriteRender->Init("Assets/Image/sample.dds", 1980.0f, 1080.0f);


	//これがlevelのLoadの基盤。
	//特定のオブジェクトを指定する（ここでいうフック）場合は、名前検索するなのね。
	m_level.Init("Assets/level/stage02.tkl", [&](LevelObjectData& objData) {

		/*if (objData.EqualObjectName(L"SampleMagnet_N_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init(MagnetName[sampleNum]);
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"SampleMagnet_S_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init(MagnetName[sampleNum]);
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}*/

		if (objData.EqualObjectName(L"Key") == true) {
			if (m_key == nullptr) {
				m_key = NewGO<Key>(0);
			}
			m_key->InitKey("Key");
			m_key->SetPositionKey(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"KeyBox") == true) {
			if (m_key == nullptr) {
				m_key = NewGO<Key>(0);
			}
			m_key->InitDoor("KeyBox");
			m_key->SetPositionDoor(objData.position);
			return true;
		}
		//else if (objData.EqualObjectName(L"") == true) {
		//	return true;
		//}
		else if (objData.EqualObjectName(L"Magnet_N_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_01");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_02") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_02");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_03") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_03");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_04") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_04");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_05") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_05");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_06") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_06");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_Nplus_move_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N(true);
			m_magnet[sampleNum]->Init("Magnet_Nplus_move_01");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_Nplus_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N(true);
			m_magnet[sampleNum]->Init("Magnet_Nplus_01");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init("Magnet_S_01");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S_02") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init("Magnet_S_02");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S_03") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init("Magnet_S_03");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S_05") == true) {
		m_magnet.push_back(*(m_magnet.end() - 1));
		m_magnet[sampleNum] = NewGO<Magnet>(0);
		m_magnet[sampleNum]->SetState_S();
		m_magnet[sampleNum]->Init("Magnet_S_05");
		m_magnet[sampleNum]->SetPosition(objData.position);
		sampleNum++;
		return true;
		}
		else if (objData.EqualObjectName(L"Magnet_Splus_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S(true);

			m_magnet[sampleNum]->Init("Magnet_Splus_01");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"KeyBox") == true) {
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