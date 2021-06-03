#pragma once
class RuleLevel2D;

class RuleScene : public IGameObject
{
public:
	bool Start();
	~RuleScene();
	void Update();

	RuleLevel2D* sprite = nullptr;

private:
	//BGM�̃T�E���h�\�[�X
	CSoundSource* BGMSound = nullptr;
	//�ړ����ʉ��̃T�E���h�\�[�X
	CSoundSource* CursorMooveSound = nullptr;
	//������ʉ��̃T�E���h�\�[�X
	CSoundSource* DecisionSound = nullptr;

	RuleLevel2D* m_RuleLevel2D = nullptr;

	int NowSelect = 1;	//�񋓂̒l���i�[����ϐ��B�͂��߂́u���v�{�^����1�B

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
	//�摜�̑傫�������߂�ϐ�
	Vector3 Vscale = { 0.2f,0.2f,0.2f };
	float Fscale = 0.2f;
	bool ScaleUpFlag = true;

	//�{�^���̏����̑傫���B
	Vector3 vscale = { 0.2f,0.2f,0.2f };

	//�����y�[�W�ڂ̂����т�����ǂ�ł���̂��B
	int PageNum = 1;

	bool NextPageFlg = true;
	
	SpriteRender* m_KeySpriteRender[5] = { nullptr };		//���X�v���C�g�����_�[
	SpriteRender* m_InryokuSpriteRender[5] = { nullptr };		//���̓X�v���C�g�����_�[
	SpriteRender* m_SekiryokuSpriteRender[6] = { nullptr };		//�˗̓X�v���C�g�����_�[
	SpriteRender* m_DeathSpriteRender[6] = { nullptr };		//�f�X�X�v���C�g�����_�[
	SpriteRender* m_QuarterSpriteRender[4] = { nullptr };		//�N�I�[�^�[�X�v���C�g�����_�[

	int OnePageTimer = 0;
	float OnePageBallPos = -300.0f;
	Vector3 KeyPos = { 300.0f,-30.0f,0.0f };

	int TwoPageTimer = 0;
	float TwoPageBallPos = -300.0f;

	int ThreePageTimer = 0;
	float ThreePageBallPos = 125.0f;

	int FourPageTimer = 0;
	float FourPageBallPos = -250.0f;
};