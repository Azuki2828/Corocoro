#include "stdafx.h"
#include "Background.h"
#include "Magnet.h"
#include "Key.h"
#include "GameLevel2D.h"
#include "Game.h"
#include "Player.h"
#include "TreasureBox.h"
#include "DeathBlock.h"
#include "Seesaw.h"

bool BackGround::Start()
{

	//他クラスを探し出す
	m_game = FindGO<Game>(NAME_GAME);
	m_player = FindGO<Player>(NAME_PLAYER);

	//ステージ番号を取得
	m_stageNum = m_game->GetStageNum();

	//ゲーム中の背景画像を表示するクラスを作成
	m_level2D = NewGO<GameLevel2D>(enPriority_First, NAME_GAME_LEVEL2D);


	//背景画像を初期化
	m_spriteRender = NewGO<SpriteRender>(enPriority_Zeroth);
	m_spriteRender->SetPosition(Vector3::Zero);
	m_spriteRender->Init(GAME_BACKGROUND_UI, GAME_BACKGROUND_UI_WH.x, GAME_BACKGROUND_UI_WH.y);



	//ステージを初期化
	LevelInit(STAGE_FILE_PATH[m_stageNum]);


	//プレイヤーの初期座標を設定
	m_player->SetPosition(STAGE_START_POS[m_stageNum]);
	m_player->SetStartPos(STAGE_START_POS[m_stageNum]);



	//ゲーム中のBGMを再生
	SoundManager::GetInstance()->Play(enBGM_Game);

	return true;
}


BackGround::~BackGround()
{
	//ステージの磁石を削除
	/*for (int i = 0; i < m_magnet.size(); i++) {
		DeleteGO(m_magnet[i]);
		m_magnet[i] = nullptr;
	}*/

	for (const auto& e : m_magnet) {
		DeleteGO(e);
	}

	//ステージのシーソーを削除
	for (int i = 0; i < m_seesaw.size(); i++) {
		DeleteGO(m_seesaw[i]);
		m_seesaw[i] = nullptr;
	}

	//ステージのデスブロックを削除
	for (int i = 0; i < m_deathBlock.size(); i++) {
		DeleteGO(m_deathBlock[i]);
		m_deathBlock[i] = nullptr;
	}

	//ゲーム中の背景画像を削除
	DeleteGO(m_spriteRender);
	m_spriteRender = nullptr;

	//タイムUIを削除
	DeleteGO(m_fontRender);
	m_fontRender = nullptr;

	//Keyクラスのオブジェクトを削除
	DeleteGO(m_key);
	m_key = nullptr;

	//Playerクラスのオブジェクトを削除
	DeleteGO(m_player);
	m_player = nullptr;

	//TreasureBoxクラスのオブジェクトを削除
	DeleteGO(m_treasureBox);
	m_treasureBox = nullptr;

	//Level2Dクラスのオブジェクトを削除
	DeleteGO(m_level2D);
	m_level2D = nullptr;
}


void BackGround::Update()
{

	//シーソーの座標と回転をリセット(主にプレイヤーが死んだとき)
	if (m_seesawFlg) {
		for (int i = 0; i < m_seesaw.size(); i++) {
			m_seesaw[i]->SetStart();
		}
		m_seesawFlg = false;
	}


	//デバッグ用。各々の磁石の番号を確認したい時に使うコード。

	//static int sampleNum = 0;
	//Vector3 pos = m_magnet[sampleNum]->GetPosition();
	//if (g_pad[0]->IsTrigger(enButtonA)) {
	//	m_magnet[sampleNum]->SetPosition({ pos.x,pos.y,pos.z - 100.0f });
	//	sampleNum++;
	//}
}

void BackGround::LevelInit(const char* filePath) {


	//caslファイルに登録された名前からオブジェクトを探し、各々を設定する
	//trueは何もしない。falseはそのまま表示。MapChipクラスでモデル生成される
	m_level.Init(filePath, [&](LevelObjectData& objData) {

		if (objData.EqualObjectName(GetObjectName(enObject_Key))) {
			if (m_key == nullptr) {
				//キークラスがなかったら生成。
				m_key = NewGO<Key>(enPriority_Zeroth, NAME_KEY);
			}
			//鍵を初期化。
			m_key->InitKey(GetObjectName(enObject_Key));
			//鍵の座標を設定。
			m_key->SetKeyPos(objData.position);
			//鍵の拡大率を設定。
			m_key->SetScaleKey(objData.scale);
			//鍵の当たり判定を設定。
			m_key->SetTriggerBox(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_KeyGround))) {
			if (m_key == nullptr) {
				//キークラスがなかったら生成。
				m_key = NewGO<Key>(enPriority_Zeroth, NAME_KEY);
			}
			//鍵の土台を設定。
			m_key->InitDoor(GetObjectName(enObject_KeyGround));
			//土台の座標を設定。
			m_key->SetDoorPos(objData.position);
			//土台の拡大率を設定。
			m_key->SetScaleDoor(objData.scale);

			//エフェクトを宝箱の中から発生させる。
			Effect* treasure = nullptr;
			treasure = NewGO<Effect>(enPriority_Zeroth);
			treasure->Init(DEATH_EFFECT_FILE_PATH);
			treasure->SetScale(EFFECT_SCALE);
			Vector3 effPos = objData.position;
			effPos += ADD_EFFECT_POS;
			treasure->SetPosition(effPos);
			treasure->Play();
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_TreasureBox))) {

			//宝箱クラスを生成。
			m_treasureBox = NewGO<TreasureBox>(enPriority_Zeroth, NAME_TREASURE_BOX);
			Vector3 pos = objData.position;
			pos += ADD_TREASURE_BOX_POS;
			//宝箱の座標を設定。
			m_treasureBox->SetPosition(pos);
			//宝箱の回転率を設定。
			m_treasureBox->SetRotation(objData.rotation);
			//宝箱の拡大率を設定。
			m_treasureBox->SetScale(TREASURE_BOX_SCALE_UP);
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_Magnet_N100_100))) {
			//磁石クラスを生成。
			m_magnet.push_back(NewGO<Magnet>(enPriority_Zeroth));
			//N極に設定する。
			m_magnet[m_magnetNum]->SetState_N();
			//磁石を初期化。
			m_magnet[m_magnetNum]->Init(GetObjectName(enObject_Magnet_N100_100));
			//磁石の座標を設定。
			m_magnet[m_magnetNum]->SetPosition(objData.position);
			//磁石の回転率を設定。
			m_magnet[m_magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += ADD_MAGNET_POS50;
			m_magPos.y += ADD_MAGNET_POS50;
			//磁力の発生場所を調整。
			m_magnet[m_magnetNum]->SetMagnetPosition(m_magPos);
			//磁石番号を設定。
			m_magnet[m_magnetNum]->SetMagnetNum(m_magnetNum);
			//磁石の数を１カウントする。
			m_magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_Magnet_S100_100))) {
			//磁石クラスを生成。
			m_magnet.push_back(NewGO<Magnet>(enPriority_Zeroth));
			//S極に設定する。
			m_magnet[m_magnetNum]->SetState_S();
			//磁石を初期化。
			m_magnet[m_magnetNum]->Init(GetObjectName(enObject_Magnet_S100_100));
			//磁石の座標を設定。
			m_magnet[m_magnetNum]->SetPosition(objData.position);
			//磁石の回転率を設定。
			m_magnet[m_magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += ADD_MAGNET_POS50;
			m_magPos.y += ADD_MAGNET_POS50;
			//磁力の発生場所を調整。
			m_magnet[m_magnetNum]->SetMagnetPosition(m_magPos);
			//磁石番号を設定。
			m_magnet[m_magnetNum]->SetMagnetNum(m_magnetNum);
			//磁石の数を１カウントする。
			m_magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_Magnet_N100_200_Triangle))) {
			//磁石クラスを生成。
			m_magnet.push_back(NewGO<Magnet>(enPriority_Zeroth));
			//N極に設定する。
			m_magnet[m_magnetNum]->SetState_N();
			//磁石を初期化。
			m_magnet[m_magnetNum]->Init(GetObjectName(enObject_Magnet_N100_200_Triangle));
			//磁石の座標を設定。
			m_magnet[m_magnetNum]->SetPosition(objData.position);
			//磁石の回転率を設定。
			m_magnet[m_magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += ADD_MAGNET_POS150;
			m_magPos.y -= ADD_MAGNET_POS50;
			//磁力の発生場所を調整。
			m_magnet[m_magnetNum]->SetMagnetPosition(m_magPos);
			//磁石番号を設定。
			m_magnet[m_magnetNum]->SetMagnetNum(m_magnetNum);
			//磁石の数を１カウントする。
			m_magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_Magnet_S100_200_Triangle))) {
			//磁石クラスを生成。
			m_magnet.push_back(NewGO<Magnet>(enPriority_Zeroth));
			//S極に設定する。
			m_magnet[m_magnetNum]->SetState_S();
			//磁石を初期化。
			m_magnet[m_magnetNum]->Init(GetObjectName(enObject_Magnet_S100_200_Triangle));
			//磁石の座標を設定。
			m_magnet[m_magnetNum]->SetPosition(objData.position);
			//磁石の回転率を設定。
			m_magnet[m_magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += ADD_MAGNET_POS150;
			m_magPos.y -= ADD_MAGNET_POS50;
			//磁力の発生場所を調整。
			m_magnet[m_magnetNum]->SetMagnetPosition(m_magPos);
			//磁石番号を設定。
			m_magnet[m_magnetNum]->SetMagnetNum(m_magnetNum);
			//磁石の数を１カウントする。
			m_magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_Magnet_NUnder100_200_Triangle))) {
			//磁石クラスを生成。
			m_magnet.push_back(NewGO<Magnet>(enPriority_Zeroth));
			//N極に設定する。
			m_magnet[m_magnetNum]->SetState_N();
			//磁石を初期化。
			m_magnet[m_magnetNum]->Init(GetObjectName(enObject_Magnet_NUnder100_200_Triangle));
			//磁石の座標を設定。
			m_magnet[m_magnetNum]->SetPosition(objData.position);
			//磁石の回転率を設定。
			m_magnet[m_magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += ADD_MAGNET_POS150;
			m_magPos.y -= ADD_MAGNET_POS50;
			//磁力の発生場所を調整。
			m_magnet[m_magnetNum]->SetMagnetPosition(m_magPos);
			//磁石番号を設定。
			m_magnet[m_magnetNum]->SetMagnetNum(m_magnetNum);
			//磁石の数を１カウントする。
			m_magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_Magnet_N100_Under200_Triangle))) {
			//磁石クラスを生成。
			m_magnet.push_back(NewGO<Magnet>(enPriority_Zeroth));
			//N極に設定する。
			m_magnet[m_magnetNum]->SetState_N();
			//磁石を初期化。
			m_magnet[m_magnetNum]->Init(GetObjectName(enObject_Magnet_N100_Under200_Triangle));
			//磁石の座標を設定。
			m_magnet[m_magnetNum]->SetPosition(objData.position);
			//磁石の回転率を設定。
			m_magnet[m_magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += ADD_MAGNET_POS50;
			m_magPos.y += ADD_MAGNET_POS50;
			//磁力の発生場所を調整。
			m_magnet[m_magnetNum]->SetMagnetPosition(m_magPos);
			//磁石番号を設定。
			m_magnet[m_magnetNum]->SetMagnetNum(m_magnetNum);
			//磁石の数を１カウントする。
			m_magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_Magnet_SUnder100_200_Triangle))) {
			//磁石クラスを生成。
			m_magnet.push_back(NewGO<Magnet>(enPriority_Zeroth));
			//S極に設定する。
			m_magnet[m_magnetNum]->SetState_S();
			//磁石を初期化。
			m_magnet[m_magnetNum]->Init(GetObjectName(enObject_Magnet_SUnder100_200_Triangle));
			//磁石の座標を設定。
			m_magnet[m_magnetNum]->SetPosition(objData.position);
			//磁石の回転率を設定。
			m_magnet[m_magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += ADD_MAGNET_POS150;
			m_magPos.y -= ADD_MAGNET_POS50;
			//磁力の発生場所を調整。
			m_magnet[m_magnetNum]->SetMagnetPosition(m_magPos);
			//磁石番号を設定。
			m_magnet[m_magnetNum]->SetMagnetNum(m_magnetNum);
			//磁石の数を１カウントする。
			m_magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_Magnet_SUnder100_Under200_Triangle))) {
			//磁石クラスを生成。
			m_magnet.push_back(NewGO<Magnet>(enPriority_Zeroth));
			//S極に設定する。
			m_magnet[m_magnetNum]->SetState_S();
			//磁石を初期化。
			m_magnet[m_magnetNum]->Init(GetObjectName(enObject_Magnet_SUnder100_Under200_Triangle));
			//磁石の座標を設定。
			m_magnet[m_magnetNum]->SetPosition(objData.position);
			//磁石の回転率を設定。
			m_magnet[m_magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += ADD_MAGNET_POS50;
			m_magPos.y += ADD_MAGNET_POS50;
			//磁力の発生場所を調整。
			m_magnet[m_magnetNum]->SetMagnetPosition(m_magPos);
			//磁石番号を設定。
			m_magnet[m_magnetNum]->SetMagnetNum(m_magnetNum);
			//磁石の数を１カウントする。
			m_magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_Magnet_S100_Under200_Triangle))) {
			//磁石クラスを生成。
			m_magnet.push_back(NewGO<Magnet>(enPriority_Zeroth));
			//S極に設定する。
			m_magnet[m_magnetNum]->SetState_S();
			//磁石を初期化。
			m_magnet[m_magnetNum]->Init(GetObjectName(enObject_Magnet_S100_Under200_Triangle));
			//磁石の座標を設定。
			m_magnet[m_magnetNum]->SetPosition(objData.position);
			//磁石の回転率を設定。
			m_magnet[m_magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += ADD_MAGNET_POS50;
			m_magPos.y -= ADD_MAGNET_POS50;
			//磁力の発生場所を調整。
			m_magnet[m_magnetNum]->SetMagnetPosition(m_magPos);
			//磁石番号を設定。
			m_magnet[m_magnetNum]->SetMagnetNum(m_magnetNum);
			//磁石の数を１カウントする。
			m_magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_DeathBlock))) {
			//デスブロッククラスを生成。
			m_deathBlock.push_back(NewGO<DeathBlock>(enPriority_Zeroth));
			//デスブロックを初期化。
			m_deathBlock[m_deathBlockNum]->Init(GetObjectName(enObject_DeathBlock));
			//デスブロックの座標を設定。
			m_deathBlock[m_deathBlockNum]->SetPosition(objData.position);
			//デスブロックの拡大率を設定。
			m_deathBlock[m_deathBlockNum]->SetScale(objData.scale);
			//デスブロックにプレイヤーのスタート位置を記憶させる。
			m_deathBlock[m_deathBlockNum]->SetStartPos(STAGE_START_POS[m_stageNum]);
			//デスブロックの数を１カウントする。
			m_deathBlockNum++;
			return true;
		}
		else if (objData.EqualObjectName(GetObjectName(enObject_Seesaw))) {
			//シーソークラスを生成。
			m_seesaw.push_back(NewGO<Seesaw>(enPriority_Zeroth));
			//シーソーの座標を設定。
			m_seesaw[m_seesawNum]->SetPosition(objData.position);
			//シーソーの回転率を設定。
			m_seesaw[m_seesawNum]->SetRotation(objData.rotation);
			//シーソーを初期化。
			m_seesaw[m_seesawNum]->Init(GetObjectName(enObject_Seesaw));
			//シーソーにプレイヤーのスタート位置を記憶させる。
			m_seesaw[m_seesawNum]->StartRot(objData.rotation);
			//シーソーの数を１カウントする。
			m_seesawNum++;
			return true;
		}

		return false;
	});
}


void BackGround::Render(RenderContext& rc)
{
	//ステージのオブジェクトを描画。
	m_level.Draw(rc);
}