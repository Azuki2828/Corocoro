#include "stdafx.h"
#include "Key.h"
#include "Player.h"

bool Key::Start() {

	m_player = FindGO<Player>("player");
	

	//��������������W��o�^�B
	if (m_skinModelRender_Key != nullptr) {

		m_skinModelRender_Key->SetPosition(m_keyPos);
		//m_skinModelRender_Key->UpdateWorldMatrix();
		//m_physicsStaticObject.CreateFromModel(
		//	*m_skinModelRender_Key->GetModel(),
		//	m_skinModelRender_Key->GetModel()->GetWorldMatrix()
		//);
	}

	//�h�A������������W��o�^+�����蔻���t����B
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

	

	
	
	//3m�ȓ��Ȃ献�擾�B
	Vector3 keyLength;

	keyLength = m_player->GetPosition() - m_keyPos;
	if (keyLength.Length() <= 300.0f && !m_player->GetKeyFlg()) {
		
		//�����������Ď擾���ʉ����Đ��B
		DeleteGO(m_skinModelRender_Key);
		GetKey();
		
		//���擾�t���O��true�ɁB
		m_player->SetKeyFlg(true);
	}

	//�����擾���Ă��邤���Ńh�A�Ƃ̋�����2m�ȓ��Ȃ�h�A��j��B
	if (m_player->GetKeyFlg()) {
		Vector3 doorLength;
		doorLength = m_player->GetPosition() - m_doorPos;
		if (doorLength.Length() <= 200.0f) {
			DeleteGO(m_skinModelRender_Door);

			//�h�A�̓����蔻����폜�B
			m_physicsStaticObject.Release();
			m_doorbreakFlg = true;
		}
	}
}

void Key::GetKey()
{
	m_sound = NewGO<CSoundSource>(0);
	m_sound->Init(L"Assets/sound/KeyGet.wav");		//����������̌��ʉ��ǉ�
	m_sound->SetVolume(1.0f);
	m_sound->Play(false);

	m_spriteRender = NewGO<SpriteRender>(1);	
	Vector3 vec = m_keyPos;
	vec.y += 100.0f;
	m_spriteRender->SetPosition(vec);								//<�ύX>���������߂鍇�}(�摜)���o��
	m_spriteRender->Init("Assets/Image/yazirusi.dds", 256.0f, 256.0f);
}