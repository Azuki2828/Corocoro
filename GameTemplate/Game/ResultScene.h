#pragma once
class ResultLevel2D;
class Game;
class SaveData;

class ResultScene : public IGameObject
{
public:
	~ResultScene();
	bool Start();
	void Update();
	SaveData* NewrecordFlg = nullptr;


	float m_result;
	bool finishFlg = false;
	float GetTime()		//Game����Ƃ��Ă���
	{
		return m_time;
	}

	void SetStageNum(int num) {
		m_stageNum = num;
	}

	int GetStageNum() {
		return m_stageNum;
	}
	FontRender* m_fontRender;		//����̃^�C����\�����邽�߂̃t�H���g�����_�[
	Game* m_game;
	float m_time;
	



private:
	int m_stageNum = 0;
	float nowTime = 0.0f;
	float bestTime = 0.0f;
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

	//�摜�̑傫�������߂�ϐ�
	Vector3 Vscale = { 0.0f,0.0f,0.0f };
	float Fscale = 0.25f;
	float Fscale1 = 0.2f;
	bool ScaleUpFlag = true;

	//�{�^���̏����̑傫���B
	Vector3 vscale = { 0.25f,0.25f,0.25f };
	Vector3 vscale1 = { 0.2f,0.2f,0.2f };

	//true�̎��A�V�L�^�I�\���B
	bool NewRecordFlg = false;
	//NewGO�����̂�1��ɂ��邽�߂̃t���O
	bool NewRecordFlgSub = true;
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[
	float RecordPos = 1100.0f;
};