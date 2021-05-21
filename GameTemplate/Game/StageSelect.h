#pragma once
class StageSelectLevel2D;
class Game;

class StageSelect:public IGameObject
{
public:
	bool Start();
	~StageSelect();
	void Update();
private:
	StageSelectLevel2D* sprite = nullptr;

	//�ړ����ʉ��̃T�E���h�\�[�X
	CSoundSource* CursorMooveSound = nullptr;
	//������ʉ��̃T�E���h�\�[�X
	CSoundSource* DecisionSound = nullptr;
	//BGM�̃T�E���h�\�[�X
	CSoundSource* BGMSound = nullptr;

	int NowSelect = 1;	//�񋓂̒l���i�[����ϐ��B�͂��߂́u�����Ă��v�{�^����1�B
		//�{�^����I�����邽�߂̗񋓌^
	enum Select {
		BackButton,
		KetteiButton,
	};

		//�摜�̑傫�������߂�ϐ�
	Vector3 Vscale = { 0.0f,0.0f,0.0f };
	float Fscale = 0.23f;
	float Fscale1 = 0.18f;
	bool ScaleUpFlag = true;

	//�{�^���̏����̑傫���B
	Vector3 vscale = { 0.23f,0.23f,0.23f };
	Vector3 vscale1 = { 0.18f,0.18f,0.18f };

	//���ݑI������Ă���X�e�[�W�ԍ�
	int NowSelectStage = 1;

	enum StageNumber
	{
		Stagenull,		//StageOne��1�ɂȂ�悤�ɍ��킹�邽�ߗp�ӂ��ꂽStagenull(�g��Ȃ�)
		StageOne,
		StageTwo,
		StageThree,
		FinalStage		//FinalStage�Ƀ}�C�i�X1���邱�ƂŃX�e�[�W�̑��������߂�B
	};

	SpriteRender* m_StageSpriteRender[3][2] = { nullptr };		//�X�e�[�W�����X�v���C�g�����_�[
	Game* m_game = nullptr;
};