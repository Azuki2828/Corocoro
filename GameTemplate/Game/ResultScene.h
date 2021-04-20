#pragma once
class ResultLevel2D;

class ResultScene : public IGameObject
{
public:
	~ResultScene();
	bool Start();
	void Update();

private:
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[
	FontRender* m_fontRender = nullptr;
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
};