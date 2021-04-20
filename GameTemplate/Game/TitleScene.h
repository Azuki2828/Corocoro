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


};