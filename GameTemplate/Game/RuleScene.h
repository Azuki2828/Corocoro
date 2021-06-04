#pragma once
class RuleLevel2D;

class RuleScene : public IGameObject
{
private:
	bool Start();
	~RuleScene();
	void Update();
private:
	enum ButtonSelect {
		back,
		next
	};

	enum PageSelect {
		ZeroPage,
		OnePage,
		TwoPage,
		ThreePage,
		FourPage,
		FivePage
	};

	bool m_scaleUpFlg = true;
	bool m_nextPageFlg = true;
	int m_pageNum = 1;
	int m_nowSelect = 1;	//�񋓂̒l���i�[����ϐ��B�͂��߂́u���v�{�^����1�B
	int m_onePageTimer = 0;
	int m_twoPageTimer = 0;
	int m_threePageTimer = 0;
	int m_fourPageTimer = 0;
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

	SpriteRender* m_keySpriteRender[5] = { nullptr };		//���X�v���C�g�����_�[
	SpriteRender* m_inryokuSpriteRender[6] = { nullptr };		//���̓X�v���C�g�����_�[
	SpriteRender* m_sekiryokuSpriteRender[6] = { nullptr };		//�˗̓X�v���C�g�����_�[
	SpriteRender* m_deathSpriteRender[6] = { nullptr };		//�f�X�X�v���C�g�����_�[
	SpriteRender* m_quarterSpriteRender[4] = { nullptr };		//�N�I�[�^�[�X�v���C�g�����_�[
	RuleLevel2D* m_sprite = nullptr;
};