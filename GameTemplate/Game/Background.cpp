#include "stdafx.h"
#include "Background.h"
#include "Magnet.h"
#include "Key.h"
#include "GameLevel2D.h"

bool Background::Start()
{
	m_magnet.resize(1);
	int sampleNum = 0;

	//m_fontRender = NewGO<FontRender>(2);
	//m_fontRender->Init(/*GameTime::GameTimeFunc().GetFrameDeltaTime()*/L"Hello",Vector2{(500.0f),(350.0f)});
	//m_fontRender = NewGO<FontRender>(2);
	//m_fontRender->Init(L"hello", Vector2{ (500.0f),(350.0f) });

	//TimeBackスプライトの上に表示させたいからゲーム画面のUIレイヤー1に+1した2にしている。
	//m_fontRender = NewGO<FontRender>(2);
	//m_fontRender->Init(L"hello",Vector2{(-535.0f),(310.0f)});	//��ʍ���


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

	//ゲーム画面のUI表示
	NewGO<GameLevel2D>(1,"gamescreenlevel2d");

	//背景画像を初期化。
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->SetPosition({ 0.0f,0.0f,0.0f });
	m_spriteRender->Init("Assets/image/eheheNS.dds", 1300.0f, 750.0f);


	//これがlevelのLoadの基盤。
	//特定のオブジェクトを指定する（ここでいうフック）場合は、名前検索する。
	m_level.Init("Assets/level/stage01_inv.tkl", [&](LevelObjectData& objData) {


		//return true;が自分で生成。return false;がパソコンが生成してくれる。
		//falseだと生成勝手にしてくれるけど、位置変えたりとかいじれない！！

		deathPosY = -500.0f;		//state02では-500.0fで死ぬ！

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
				m_key = NewGO<Key>(0,"key");
			}
			m_key->InitKey("Key");
			m_key->SetPositionKey(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"KeyBox") == true) {
			if (m_key == nullptr) {
				m_key = NewGO<Key>(0,"key");
			}
			m_key->InitDoor("KeyBox");
			m_key->SetPositionDoor(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N100_100") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N10");
			m_magnet[sampleNum]->SetPosition(objData.position);
			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S100_100") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init("Magnet_S100");
			m_magnet[sampleNum]->SetPosition(objData.position);
			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S10") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init("Magnet_S10");
			m_magnet[sampleNum]->SetPosition(objData.position);
			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S100") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init("Magnet_S100");
			m_magnet[sampleNum]->SetPosition(objData.position);
			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
			sampleNum++;
			return true;
		}
		//else if (objData.EqualObjectName(L"Magnet_N_01") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N();
		//	m_magnet[sampleNum]->Init("Magnet_N_01");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_N_02") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N();
		//	m_magnet[sampleNum]->Init("Magnet_N_02");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_N_03") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N();
		//	m_magnet[sampleNum]->Init("Magnet_N_03");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_N_04") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N();
		//	m_magnet[sampleNum]->Init("Magnet_N_04");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_N_05") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N();
		//	m_magnet[sampleNum]->Init("Magnet_N_05");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_N_06") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N();
		//	m_magnet[sampleNum]->Init("Magnet_N_06");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_N_07") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N(true);
		//	m_magnet[sampleNum]->Init("Magnet_N_07");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_Nplus_02") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N(true);

		//	m_magnet[sampleNum]->Init("Magnet_Nplus_02");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_Nplus_move_01") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N(true);
		//	m_magnet[sampleNum]->Init("Magnet_Nplus_move_01");


		//	Vector3 movePos_front = objData.position;
		//	movePos_front.x -= 900.0f;
		//	Vector3 movePos_back = objData.position;
		//	m_magnet[sampleNum]->SetMove(movePos_front, movePos_back);
		//	m_magnet[sampleNum]->SetPosition(movePos_front);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_Nplus_move_02") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N(true);
		//	m_magnet[sampleNum]->Init("Magnet_Nplus_move_02");

		//	Vector3 movePos_front = objData.position;
		//	movePos_front.x -= 400.0f;
		//	Vector3 movePos_back = objData.position;
		//	m_magnet[sampleNum]->SetMove(movePos_front, movePos_back);
		//	m_magnet[sampleNum]->SetPosition(movePos_front);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_Nplus_01") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_N(true);
		//	m_magnet[sampleNum]->Init("Magnet_Nplus_01");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_S_01") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_S();
		//	m_magnet[sampleNum]->Init("Magnet_S_01");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_S_02") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_S();
		//	m_magnet[sampleNum]->Init("Magnet_S_02");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_S_03") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_S();
		//	m_magnet[sampleNum]->Init("Magnet_S_03");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_S_04") == true) {
		//m_magnet.push_back(*(m_magnet.end() - 1));

		//m_magnet[sampleNum] = NewGO<Magnet>(0);
		//m_magnet[sampleNum]->SetState_S(true);
		//m_magnet[sampleNum]->Init("Magnet_S_04");
		//m_magnet[sampleNum]->SetPosition(objData.position);
		//sampleNum++;
		//return true;
		//}
		//else if (objData.EqualObjectName(L"magnet_S_05") == true) {
		//m_magnet.push_back(*(m_magnet.end() - 1));

		//m_magnet[sampleNum] = NewGO<Magnet>(0);
		//m_magnet[sampleNum]->SetState_S();
		//m_magnet[sampleNum]->Init("magnet_S_05");
		//m_magnet[sampleNum]->SetPosition(objData.position);
		//sampleNum++;
		//return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_Splus_01") == true) {
		//	m_magnet.push_back(*(m_magnet.end() - 1));
		//	m_magnet[sampleNum] = NewGO<Magnet>(0);
		//	m_magnet[sampleNum]->SetState_S(true);

		//	m_magnet[sampleNum]->Init("Magnet_Splus_01");
		//	m_magnet[sampleNum]->SetPosition(objData.position);
		//	sampleNum++;
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"Magnet_Splus_Move_01") == true) {
		//m_magnet.push_back(*(m_magnet.end() - 1));
		//m_magnet[sampleNum] = NewGO<Magnet>(0);
		//m_magnet[sampleNum]->SetState_S(true);
		//m_magnet[sampleNum]->Init("Magnet_Splus_Move_01");

		//Vector3 movePos_front = objData.position;
		//Vector3 movePos_back = objData.position;
		//movePos_back.x += 400.0f;
		//m_magnet[sampleNum]->SetMove(movePos_front, movePos_back);
		//m_magnet[sampleNum]->SetPosition(movePos_front);
		//sampleNum++;
		//return true;
		//}
		//else if (objData.EqualObjectName(L"move_01") == true) {
		//	return true;
		//}
		//else if (objData.EqualObjectName(L"KeyBox") == true) {
		//	return true;
		//}
		return false;//levelのオブジェクトをそのままロード。
	});

	//BGM再生。

	GameBGMSound = NewGO<CSoundSource>(0);

	GameBGMSound->Init(L"Assets/sound/GameBGM.wav");
	GameBGMSound->SetVolume(1.0f);
	GameBGMSound->Play(true);			//ループ再生。

	//ModelInitData initData;
	//initData.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	///シェーダーファイルのファイルパスを指定する。
	//initData.m_fxFilePath = "Assets/shader/model.fx";
	///頂点シェーダーのエントリーポイント
	//initData.m_vsEntryPointFunc = "VSMain";
	//m_model.Init(initData);
	//
	///メッシュコライダーを作成。
	//m_physicsStaticObject.CreateFromModel(m_model, m_model.GetWorldMatrix());
	return true;
}


Background::~Background()
{
	//背景削除。
	DeleteGO(m_spriteRender);
	//タイム削除。
	DeleteGO(m_fontRender);
}


void Background::Update()
{

}


void Background::Render(RenderContext& rc)
{
	m_level.Draw(rc);
	m_model.Draw(rc);
}