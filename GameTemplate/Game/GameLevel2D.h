#pragma once
#include "level2D/Level2D.h"


namespace {
	const char* GAME_SCREEN_NO_KEY_FILE_PATH = "Assets/level2D/GameScreen_NoGetKey.casl";
	const char* GAME_SCREEN_YES_KEY_FILE_PATH = "Assets/level2D/GameScreen_YesGetKey.casl";
	const char* SPRITE_NO_GET_KEY_FILE_PATH = "GetKeyNO";
	const char* SPRITE_YES_GET_KEY_FILE_PATH = "KeyGet";
	const char* SPRITE_TIME_BACK = "TimeBack";
}

class GameLevel2D : public IGameObject
{
private:
	~GameLevel2D();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
public:

	void SetKeyFlg(bool flg) {
		m_getKeyFlag = flg;
	}
	bool GetKeyFlg() {
		return m_getKeyFlag;
	}

private:
	//�f�X�g���N�^��DeleteGO������K�v�����邩���m�F���邽�߂̃t���O
	bool m_getKeyFlag = true;							//�����擾���Ă��邩�擾���Ă��Ȃ����𔻒肷��ϐ��B
	bool m_flagSprite = false;
	bool m_flagSprite1 = false;
	bool m_flagSprite2 = false;
	bool m_flagSprite3 = false;

	
	//Key�N���X�Ŏg�����߂�public�ɒu���Ă���B
	//���֐������private�ŊǗ��ł���悤�ɂ��Ă��������B
	Level2D m_level2D;		//���x��2D�B
	Vector3 m_position = Vector3::Zero;	//���W�B
	Vector3 m_scale = Vector3::One;		//�傫���B

	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	SpriteRender* m_sprite;			//�X�v���C�g�B
	SpriteRender* m_sprite1;			//�X�v���C�g�B
	SpriteRender* m_sprite2;			//�X�v���C�g�B
	SpriteRender* m_sprite3;			//�X�v���C�g�B
};