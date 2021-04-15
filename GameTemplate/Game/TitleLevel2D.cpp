#include "stdafx.h"
#include "TitleLevel2D.h"


bool TitleLevel2D::Start()
{


	//TitleScene���x����ǂݍ��ށB
	m_level2D.Init("Assets/level2D/TitleScene.casl", [&](Level2DObjectData& objdata) {
		//���O��BackScreen��������A
		if (objdata.EqualObjectName("BackScreen")) {

			SpriteInitData data;
			//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
			data.m_ddsFilePath[0] = objdata.ddsFilePath;
			//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
			data.m_fxFilePath = "Assets/shader/sprite.fx";
			//�X�v���C�g�̕��ƍ������擾����B
			data.m_width = objdata.width;
			data.m_height = objdata.height;
			data.m_alphaBlendMode = AlphaBlendMode_Trans;

			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite.Init(data);

			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//���O��Title��������A
		else if (objdata.EqualObjectName("Title")) {

			SpriteInitData data;
			//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
			data.m_ddsFilePath[0] = objdata.ddsFilePath;
			//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
			data.m_fxFilePath = "Assets/shader/sprite.fx";
			//�X�v���C�g�̕��ƍ������擾����B
			data.m_width = objdata.width;
			data.m_height = objdata.height;
			data.m_alphaBlendMode = AlphaBlendMode_Trans;

			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite.Init(data);

			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}
		//���O��Start��������A
		else if (objdata.EqualObjectName("Start")) {

			SpriteInitData data;
			//DDS�t�@�C��(�摜�f�[�^)�̃t�@�C���p�X���w�肷��B
			data.m_ddsFilePath[0] = objdata.ddsFilePath;
			//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
			data.m_fxFilePath = "Assets/shader/sprite.fx";
			//�X�v���C�g�̕��ƍ������擾����B
			data.m_width = objdata.width;
			data.m_height = objdata.height;
			data.m_alphaBlendMode = AlphaBlendMode_Trans;

			//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
			m_sprite.Init(data);

			//���W���擾����B
			m_position = objdata.position;
			//�傫����ݒ肷��B
			m_scale = objdata.scale;
			m_scale.x *= -1.0f;

			return true;
		}


		return false;
	});

	//Start�֐���return true;
	return true;
}

void TitleLevel2D::Update()
{
	m_sprite.Update(m_position, Quaternion::Identity, m_scale);
	//���x��2D�N���X��Sprite�̍X�V�����B
	m_level2D.Update();
}

void TitleLevel2D::Render(RenderContext& rc)
{
	m_sprite.Draw(rc);
	//���x��2D�N���X��Sprite�̕`�揈���B
	m_level2D.Draw(rc);
}