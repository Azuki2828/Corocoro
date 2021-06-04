#include "stdafx.h"
#include "GameLevel2D.h"

bool GameLevel2D::Start()
{
		//���x����ǂݍ��ށB
		m_level2D.Init("Assets/level2D/GameScreen_NoGetKey.casl", [&](Level2DObjectData& objdata) {

			//���O��GetKeyNO��������B
			if (objdata.EqualObjectName("GetKeyNO")) {

				m_sprite = NewGO<SpriteRender>(0);
				//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
				m_sprite->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				m_sprite->SetPosition(objdata.position);
				m_sprite->SetScale(objdata.scale);

				m_flagSprite = true;

				return true;
			}
			//���O��TimeBack��������B
			else if (objdata.EqualObjectName("TimeBack")) {

				m_sprite1 = NewGO<SpriteRender>(0);
				//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
				m_sprite1->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				m_sprite1->SetPosition(objdata.position);
				m_sprite1->SetScale(objdata.scale);

				m_flagSprite1 = true;

				return true;
			}


			//false���摜�o���B
			return false;
		});

	//Start�֐���return true;
	return true;
}

GameLevel2D::~GameLevel2D()
{
	if (m_flagSprite == true) {
		DeleteGO(m_sprite);
		m_flagSprite = false;
	}
	if (m_flagSprite1 == true) {
		DeleteGO(m_sprite1);
		m_flagSprite1 = false;
	}
	if (m_flagSprite2 == true) {
		DeleteGO(m_sprite2);
		m_flagSprite2 = false;
	}
	if (m_flagSprite3 == true) {
		DeleteGO(m_sprite3);
		m_flagSprite3 = false;
	}
}

void GameLevel2D::Update()
{

	//NoGetKey��false�A�܂茮���擾����Ă���Ƃ��A
	if (m_getKeyFlag == false) {

		//���x����ǂݍ��ށB
		m_level2D.Init("Assets/level2D/GameScreen_YesGetKey.casl", [&](Level2DObjectData& objdata) {

			//���O��GetKeyNO��������B
			if (objdata.EqualObjectName("KeyGet")) {

				SpriteInitData data;
				//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
				data.m_ddsFilePath[0] = objdata.ddsFilePath;
				//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
				data.m_fxFilePath = "Assets/shader/sprite.fx";
				//�X�v���C�g�̕��ƍ������擾����B
				data.m_width = objdata.width;
				data.m_height = objdata.height;
				data.m_alphaBlendMode = AlphaBlendMode_Trans;

				m_sprite2 = NewGO<SpriteRender>(0);
				//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
				m_sprite2->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				m_sprite2->SetPosition(objdata.position);
				m_sprite2->SetScale(objdata.scale);

				m_flagSprite2 = true;

				//���̓_���̂���폜
				if (m_flagSprite == true) {
					DeleteGO(m_sprite);
					m_flagSprite = false;
				}

				return true;
			}
			//���O��TimeBack��������B
			else if (objdata.EqualObjectName("TimeBack")) {

				SpriteInitData data;
				//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
				data.m_ddsFilePath[0] = objdata.ddsFilePath;
				//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
				data.m_fxFilePath = "Assets/shader/sprite.fx";
				//�X�v���C�g�̕��ƍ������擾����B
				data.m_width = objdata.width;
				data.m_height = objdata.height;
				data.m_alphaBlendMode = AlphaBlendMode_Trans;

				m_sprite3 = NewGO<SpriteRender>(0);
				//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
				m_sprite3->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
				m_sprite3->SetPosition(objdata.position);
				m_sprite3->SetScale(objdata.scale);

				m_flagSprite3 = true;

				return true;
			}

			//false���摜�o���B
			return false;
		});

		//true�ɂ��Ĕ�����
		m_getKeyFlag = true;
	}


	//m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//���x��2D�N���X��Sprite�̍X�V�����B
	m_level2D.Update();
}

void GameLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//���x��2D�N���X��Sprite�̕`�揈���B
	m_level2D.Draw(rc);
}
