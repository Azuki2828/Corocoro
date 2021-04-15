#include "stdafx.h"
#include "Key.h"
#include "Player.h"

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

	

	
	
	//3m以内なら鍵取得。
	Vector3 keyLength;

	keyLength = m_player->GetPosition() - m_keyPos;
	if (keyLength.Length() <= 300.0f && !m_player->GetKeyFlg()) {
		
		//鍵を消去して取得効果音を再生。
		DeleteGO(m_skinModelRender_Key);
		GetKey();
		
		//鍵取得フラグをtrueに。
		m_player->SetKeyFlg(true);
	}

	//鍵を取得しているうえでドアとの距離が2m以内ならドアを破壊。
	if (m_player->GetKeyFlg()) {
		Vector3 doorLength;
		doorLength = m_player->GetPosition() - m_doorPos;
		if (doorLength.Length() <= 200.0f) {
			DeleteGO(m_skinModelRender_Door);

			//ドアの当たり判定を削除。
			m_physicsStaticObject.Release();
			m_doorbreakFlg = true;
		}
	}
}

void Key::GetKey()
{
	m_sound = NewGO<CSoundSource>(0);
	m_sound->Init(L"Assets/sound/KeyGet.wav");		//鍵取った時の効果音追加
	m_sound->SetVolume(1.0f);
	m_sound->Play(false);

	m_spriteRender = NewGO<SpriteRender>(1);	
	Vector3 vec = m_keyPos;
	vec.y += 100.0f;
	m_spriteRender->SetPosition(vec);								//<変更>鍵取ったら戻る合図(画像)を出す
	m_spriteRender->Init("Assets/Image/yazirusi.dds", 256.0f, 256.0f);
}