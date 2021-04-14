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
	m_skinModelRender_Key->SetShadowReceiverFlag(true);
	m_skinModelRender_Key->Init(true, false);
}

void Key::InitDoor(const char* name) {

	char filePathtkm[256];

	sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", name);
	m_skinModelRender_Door = NewGO<SkinModelRender>(0);
	m_skinModelRender_Door->SetFileNametkm(filePathtkm);
	m_skinModelRender_Door->SetShadowReceiverFlag(true);
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
		}
	}
}
