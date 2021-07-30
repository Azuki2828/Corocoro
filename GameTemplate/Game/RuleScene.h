#pragma once
class RuleLevel2D;


class RuleScene : public IGameObject
{
private:
	bool Start();
	~RuleScene();
	void Update();
private:
	//�I���{�^���̃��X�g
	enum ButtonSelect {
		back,
		next
	};

	//�y�[�W�ԍ�
	enum PageSelect {
		OnePage,
		TwoPage,
		ThreePage,
		FourPage,

		Page_Num
	};

	enum Page1Sprite {
		Page1Sprite_Key,
		Page1Sprite_RedBall,
		Page1Sprite_Start,
		Page1Sprite_Get,
		Page1Sprite_Goal,
	};

	enum Page2Sprite {
		Page2Sprite_Arrow,
		Page2Sprite_Red_Ball,
		Page2Sprite_Blue_Ball,
		Page2Sprite_Magnet01,
		Page2Sprite_Magnet02,
		Page2Sprite_Inryoku,

		Page2Sprite_Num
	};
	bool m_scaleUpFlg = true;						//�{�^�����g�債�Ă����t���O
	bool m_nextPageFlg = true;						//���̃y�[�W�ɂ����t���O
	int m_pageNum = 0;								//�I�𒆂̃y�[�W�ԍ�
	int m_nowSelect = 0;							//�񋓂̒l���i�[����ϐ��B�͂��߂́u���v�{�^����1�B
	int m_onePageTimer = 0;							//1�y�[�W�ڂ̊Ǘ�����
	int m_twoPageTimer = 0;							//2�y�[�W�ڂ̊Ǘ�����
	int m_threePageTimer = 0;						//3�y�[�W�ڂ̊Ǘ�����
	int m_fourPageTimer = 0;						//4�y�[�W�ڂ̊Ǘ�����
	float m_scale = 0.2f;							
	float m_onePageBallPos = -300.0f;
	float m_twoPageBallPos = -300.0f;
	float m_threePageBallPos = 125.0f;
	float m_fourPageBallPos = -250.0f;
	Vector3 m_scale2 = { 0.2f,0.2f,0.2f };
	Vector3 m_scale3 = { 0.2f,0.2f,0.2f };
	Vector3 m_keyPos = { 300.0f,-30.0f,0.0f };

	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	SpriteRender* m_page1SpriteRender[5] = { nullptr };		//���X�v���C�g�����_�[
	SpriteRender* m_inryokuSpriteRender[Page2Sprite_Num] = { nullptr };		//���̓X�v���C�g�����_�[
	SpriteRender* m_sekiryokuSpriteRender[6] = { nullptr };		//�˗̓X�v���C�g�����_�[
	SpriteRender* m_deathSpriteRender[6] = { nullptr };		//�f�X�X�v���C�g�����_�[
	SpriteRender* m_quarterSpriteRender[Page_Num] = { nullptr };		//�N�I�[�^�[�X�v���C�g�����_�[
	RuleLevel2D* m_level2D = nullptr;
};