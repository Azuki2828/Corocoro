#include "stdafx.h"
#include "Key.h"
#include "Player.h"

#include "Background.h"
#include "ResultScene.h"

#include "GameLevel2D.h"

bool Key::Start() {

	m_player = FindGO<Player>("player");


	//鍵があったら座標を登録。
	if (m_skinModelRender_Key != nullptr) {

		m_skinModelRender_Key->SetPosition(m_keyPos);
		//m_skinModelRender_Key->UpdateWorldMatrix();
		//m_physicsStaticObject.CreateFromModel(
		//	*m_skinModelRender_Key->GetModel(),
		//	m_skinModelRender_Key->GetModel()->GetWorldMatrix()
		//);
	}

	//ドアがあったら座標を登録+当たり判定を付ける。
	if (m_skinModelRender_Door != nullptr) {
		m_skinModelRender_Door->SetPosition(m_doorPos);
		m_skinModelRender_Door->UpdateWorldMatrix();
		m_physicsStaticObject.CreateFromModel(
			*m_skinModelRender_Door->GetModel(),
			m_skinModelRender_Door->GetModel()->GetWorldMatrix()
		);
	}


	return true;
}

Key::~Key() {

}


void Key::InitKey(const char* name) {

	char filePathtkm[256];

	sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
	m_skinModelRender_Key = NewGO<SkinModelRender>(0);
	m_skinModelRender_Key->SetFileNametkm(filePathtkm);
	m_skinModelRender_Key->Init(true, false);
}

void Key::InitDoor(const char* name) {

	char filePathtkm[256];

	sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
	m_skinModelRender_Door = NewGO<SkinModelRender>(0);
	m_skinModelRender_Door->SetFileNametkm(filePathtkm);
	m_skinModelRender_Door->Init(true, false);
}

void Key::Update() {

	getKeyFlg = m_player->GetKeyFlg();
	if (getKeyFlg == true) {
		m_spriteRender = NewGO<SpriteRender>(1);	//<//>1回だけ画像を呼びたい
		Vector3 vec = m_keyPos;
		vec.y += 100.0f;
		m_spriteRender->SetPosition(vec);									//<変更>鍵取ったら戻る合図(画像)を出す
		m_spriteRender->Init("Assets/Image/yazirusi.dds", 256.0f, 256.0f);
	}



	//3m以内なら鍵取得。
	Vector3 keyLength;

	keyLength = m_player->GetPosition() - m_keyPos;
	if (keyLength.Length() <= 200.0f) {
		DeleteGO(m_skinModelRender_Key);

		if (KeyGetSoundFlag == true) {

			//通常BGMを削除。
			Background* background = FindGO<Background>("background");
			DeleteGO(background->GameBGMSound);

			//GameScreen_NoGetKey.caslを削除し、GameScreen_YesGetKey.caslを呼ぶことで鍵取得のUIを作成する。

			//Flagをfalse(鍵取得中)にする。
			GameLevel2D* gamescreenlevel2d = FindGO<GameLevel2D>("gamescreenlevel2d");
			gamescreenlevel2d->NoGetKeyFlag = false;
			//前の鍵をゲットしていないときのUIを削除。
			DeleteGO(gamescreenlevel2d->m_sprite);

			//鍵取得時の効果音再生。

			KeyGetSound = NewGO<CSoundSource>(0);

			KeyGetSound->Init(L"Assets/sound/KeyGet.wav");
			KeyGetSound->SetVolume(1.0f);
			KeyGetSound->Play(false);

			//falseにして抜ける。
			KeyGetSoundFlag = false;
		}

		//鍵取得フラグをtrueに。
		m_player->SetKeyFlg(true);
	}

	//KeyGetSoundFlagがfalseになったら、
	if(KeyGetSoundFlag ==false) {
		GetDelay++;
	}

	if (GetDelay == 120) {
		//通常BGMのアップテンポ版を再生し変化をつけ、焦らす演出。
		GameBGMSound_UpTempo = NewGO<CSoundSource>(0);

		GameBGMSound_UpTempo->Init(L"Assets/sound/GameBGM._UpTempo.wav");
		GameBGMSound_UpTempo->SetVolume(1.0f);
		GameBGMSound_UpTempo->Play(true);		//ループ再生。
	}

	//鍵を取得しているうえでドアとの距離が3m以内ならドアを破壊。
	if (m_player->GetKeyFlg()) {
		Vector3 doorLength;
		doorLength = m_player->GetPosition() - m_doorPos;
		if (doorLength.Length() <= 300.0f) {

			if (GameClearSoundFlag == true) {

				//BGMを削除。
				DeleteGO(GameBGMSound_UpTempo);

				//ゲームクリアのサウンドを再生。
				GameClearSound = NewGO<CSoundSource>(0);

				GameClearSound->Init(L"Assets/sound/GameClear.wav");
				GameClearSound->SetVolume(1.0f);
				GameClearSound->Play(false);		//ワンショット再生。

				//falseにして抜ける。
				GameClearSoundFlag = false;
			}

			//Clear文字表示
			m_fontRender = NewGO<FontRender>(2);
			m_fontRender->Init(L"Clear!!", Vector2{ (50.0f),(25.0f) });

			//ドアのモデルデータを削除。
			DeleteGO(m_skinModelRender_Door);

			//ドアの当たり判定を削除。
			m_physicsStaticObject.Release();

			GameOverFlag = true;
		}
	}

	if (GameOverFlag == true) {
		//1.5秒カウント
		GameOverCount++;
		//ゲームクリアしてから1.5秒たったら、
		if (GameOverCount == 90) {
			//リザルトシーンクラスを呼び出す。
			NewGO<ResultScene>(0);
		}
	}
}