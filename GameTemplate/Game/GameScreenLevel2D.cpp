#include "stdafx.h"
#include "GameScreenLevel2D.h"

bool GameScreenLevel2D::Start()
{
	//���x����ǂݍ��ށB
	m_level2D.Init("Assets/level2D/GameScreen_NoGetKey.casl", [&](Level2DObjectData& objdata) {
		//���O��GetKeyNO��������B
		if (objdata.EqualObjectName("GetKeyNO")) {

			//m_spriteRender = NewGO<SpriteRender>(0);
			//m_spriteRender->Init(objdata.ddsFilePath, objdata.width, objdata.height);
			//m_spriteRender->SetPosition(objdata.position);


			SpriteInitData data;
			//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
			data.m_ddsFilePath[0] = objdata.ddsFilePath;
			//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
			data.m_fxFilePath = "Assets/shader/sprite.fx";
			//�X�v���C�g�̕��ƍ������擾����B
			data.m_width = objdata.width;
			data.m_height = objdata.height;
			data.m_alphaBlendMode = AlphaBlendMode_Trans;
			m_sprite = NewGO<SpriteRender>(0);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite->SetPosition(objdata.position);
			m_sprite->SetScale(objdata.scale);

			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

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
			m_sprite1 = NewGO<SpriteRender>(0);
			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite1->Init(objdata.ddsFilePath, objdata.width, objdata.height, AlphaBlendMode_Trans);
			m_sprite1->SetPosition(objdata.position);
			m_sprite1->SetScale(objdata.scale);


			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}


		//false���摜�o���B
		return false;
	});

	//Start�֐���return true;
	return true;
}

GameScreenLevel2D::~GameScreenLevel2D()
{
	DeleteGO(m_sprite);
	DeleteGO(m_sprite1);
}

void GameScreenLevel2D::Update()
{
	//m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//���x��2D�N���X��Sprite�̍X�V�����B
	m_level2D.Update();
}

void GameScreenLevel2D::Render(RenderContext& rc)
{
	//m_sprite.Draw(rc);
	//���x��2D�N���X��Sprite�̕`�揈���B
	m_level2D.Draw(rc);
}
