#pragma once
#include "level2D/Level2D.h"


namespace {
	const char* GAME_SCREEN_NO_KEY_FILE_PATH = "Assets/level2D/GameScreen_NoGetKey.casl";		//���̓_���X�v���C�g
	const char* GAME_SCREEN_YES_KEY_FILE_PATH = "Assets/level2D/GameScreen_YesGetKey.casl";		//���擾�X�v���C�g
	const char* SPRITE_NAME_NO_GET_KEY = "GetKeyNO";											//casl�t�@�C���ł̓_�����̖��O
	const char* SPRITE_NAME_YES_GET_KEY = "KeyGet";												//casl�t�@�C���ł̌��擾�̖��O
	const char* SPRITE_NAME_TIME_BACK = "TimeBack";												//casl�t�@�C���ł̎��ԃX�v���C�g�̖��O									
}

class GameLevel2D : public IGameObject
{
private:
	~GameLevel2D();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
public:

	/**
	 * @brief ���̎擾�t���O��ݒ肷��֐��B
	 * @param flg ���擾�t���O
	*/
	void SetKeyFlg(bool flg) {
		m_getKeyFlag = flg;
	}
	/**
	 * @brief �����擾���Ă��邩�ǂ����m���߂�֐��B
	 * @return ���擾�t���O
	*/
	bool GetKeyFlg() {
		return m_getKeyFlag;
	}

private:
	bool m_getKeyFlag = true;							//�����擾���Ă��邩�擾���Ă��Ȃ����𔻒肷��ϐ�
	
	//�f�X�g���N�^��DeleteGO������K�v�����邩���m�F���邽�߂̃t���O
	bool m_flagSprite = false;							//
	bool m_flagSprite1 = false;
	bool m_flagSprite2 = false;
	bool m_flagSprite3 = false;

	
	Level2D m_level2D;					//���x��2D
	Vector3 m_position = Vector3::Zero;	//���W
	Vector3 m_scale = Vector3::One;		//�g�嗦

	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	SpriteRender* m_sprite;				//�X�v���C�g�B
	SpriteRender* m_sprite1;			//�X�v���C�g�B
	SpriteRender* m_sprite2;			//�X�v���C�g�B
	SpriteRender* m_sprite3;			//�X�v���C�g�B
};