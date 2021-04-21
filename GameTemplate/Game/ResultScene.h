#pragma once
class ResultLevel2D;
class Game;

class ResultScene : public IGameObject
{
public:
	~ResultScene();
	bool Start();
	void Update();
private:
	float nowTime = 0.0f;
	float bestTime = 0.0f;
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[
	FontRender* m_fontRender = nullptr;
	FontRender* m_nowTime = nullptr;
	FontRender* m_BestTime = nullptr;
	ResultLevel2D* sprite = nullptr;

	//�ړ����ʉ��̃T�E���h�\�[�X
	CSoundSource* CursorMooveSound = nullptr;
	//������ʉ��̃T�E���h�\�[�X
	CSoundSource* DecisionSound = nullptr;

	//�{�^����I�����邽�߂̗񋓌^
	enum Select {
		TitleBackButton,
		EndButton,
	};
	int NowSelect = 0;	//�񋓂̒l���i�[����ϐ��B�͂��߂́u�͂��߂�v�{�^����0�B

	ResultLevel2D* m_resultLevel2D = nullptr;
	Game* m_game = nullptr;
};