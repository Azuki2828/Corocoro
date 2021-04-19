#include "stdafx.h"
#include "Key.h"
#include "Player.h"

#include "Background.h"
#include "ResultScene.h"

#include "GameLevel2D.h"

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
		m_spriteRender = NewGO<SpriteRender>(1);	//<//>1�񂾂��摜���Ăт���
		Vector3 vec = m_keyPos;
		vec.y += 100.0f;
		m_spriteRender->SetPosition(vec);									//<�ύX>���������߂鍇�}(�摜)���o��
		m_spriteRender->Init("Assets/Image/yazirusi.dds", 256.0f, 256.0f);
	}



	//3m�ȓ��Ȃ献�擾�B
	Vector3 keyLength;

	keyLength = m_player->GetPosition() - m_keyPos;
	if (keyLength.Length() <= 200.0f) {
		DeleteGO(m_skinModelRender_Key);

		if (KeyGetSoundFlag == true) {

			//�ʏ�BGM���폜�B
			Background* background = FindGO<Background>("background");
			DeleteGO(background->GameBGMSound);

			//GameScreen_NoGetKey.casl���폜���AGameScreen_YesGetKey.casl���ĂԂ��ƂŌ��擾��UI���쐬����B

			//Flag��false(���擾��)�ɂ���B
			GameLevel2D* gamescreenlevel2d = FindGO<GameLevel2D>("gamescreenlevel2d");
			gamescreenlevel2d->NoGetKeyFlag = false;
			//�O�̌����Q�b�g���Ă��Ȃ��Ƃ���UI���폜�B
			DeleteGO(gamescreenlevel2d->m_sprite);

			//���擾���̌��ʉ��Đ��B

			KeyGetSound = NewGO<CSoundSource>(0);

			KeyGetSound->Init(L"Assets/sound/KeyGet.wav");
			KeyGetSound->SetVolume(1.0f);
			KeyGetSound->Play(false);

			//false�ɂ��Ĕ�����B
			KeyGetSoundFlag = false;
		}

		//���擾�t���O��true�ɁB
		m_player->SetKeyFlg(true);
	}

	//KeyGetSoundFlag��false�ɂȂ�����A
	if(KeyGetSoundFlag ==false) {
		GetDelay++;
	}

	if (GetDelay == 120) {
		//�ʏ�BGM�̃A�b�v�e���|�ł��Đ����ω������A�ł炷���o�B
		GameBGMSound_UpTempo = NewGO<CSoundSource>(0);

		GameBGMSound_UpTempo->Init(L"Assets/sound/GameBGM._UpTempo.wav");
		GameBGMSound_UpTempo->SetVolume(1.0f);
		GameBGMSound_UpTempo->Play(true);		//���[�v�Đ��B
	}

	//�����擾���Ă��邤���Ńh�A�Ƃ̋�����3m�ȓ��Ȃ�h�A��j��B
	if (m_player->GetKeyFlg()) {
		Vector3 doorLength;
		doorLength = m_player->GetPosition() - m_doorPos;
		if (doorLength.Length() <= 300.0f) {

			if (GameClearSoundFlag == true) {

				//BGM���폜�B
				DeleteGO(GameBGMSound_UpTempo);

				//�Q�[���N���A�̃T�E���h���Đ��B
				GameClearSound = NewGO<CSoundSource>(0);

				GameClearSound->Init(L"Assets/sound/GameClear.wav");
				GameClearSound->SetVolume(1.0f);
				GameClearSound->Play(false);		//�����V���b�g�Đ��B

				//false�ɂ��Ĕ�����B
				GameClearSoundFlag = false;
			}

			//Clear�����\��
			m_fontRender = NewGO<FontRender>(2);
			m_fontRender->Init(L"Clear!!", Vector2{ (50.0f),(25.0f) });

			//�h�A�̃��f���f�[�^���폜�B
			DeleteGO(m_skinModelRender_Door);

			//�h�A�̓����蔻����폜�B
			m_physicsStaticObject.Release();

			GameOverFlag = true;
		}
	}

	if (GameOverFlag == true) {
		//1.5�b�J�E���g
		GameOverCount++;
		//�Q�[���N���A���Ă���1.5�b��������A
		if (GameOverCount == 90) {
			//���U���g�V�[���N���X���Ăяo���B
			NewGO<ResultScene>(0);
		}
	}
}