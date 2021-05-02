#pragma once
class TitleLevel2D;

class TitleScene : public IGameObject
{
public:
	//TitleScene();		Start�֐��̕����g���B
	~TitleScene();
	bool Start();
	void Update();
private:
	TitleLevel2D* sprite = nullptr;

	//�^�C�g��BGM�̃T�E���h�\�[�X
	CSoundSource* TitleBGMSound = nullptr;
	//�ړ����ʉ��̃T�E���h�\�[�X
	CSoundSource* CursorMooveSound = nullptr;
	//������ʉ��̃T�E���h�\�[�X
	CSoundSource* DecisionSound = nullptr;


	//�{�^����I�����邽�߂̗񋓌^
	enum Select {
		StartButton,
		RuleButton,
		SettingButton,
		EndButton,
	};
	int NowSelect = 0;	//�񋓂̒l���i�[����ϐ��B�͂��߂́u�͂��߂�v�{�^����0�B

	TitleLevel2D* m_titleLevel2D = nullptr;

	//�摜�̑傫�������߂�ϐ�
	Vector3 Vscale = { 0.2f,0.2f,0.2f };
	float Fscale = 0.2f;
	bool ScaleUpFlag = true;

	//�{�^���̏����̑傫���B
	Vector3 vscale = { 0.2f,0.2f,0.2f };
};