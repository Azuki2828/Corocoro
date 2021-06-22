#pragma once
class ResultLevel2D;
class Game;
class SaveData;

class ResultScene : public IGameObject
{
private:
	~ResultScene();
	bool Start();
	void Update();

public:
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
	
private:
	//�{�^����I�����邽�߂̗񋓌^
	enum Select {
		enSelect_TitleBackButton,
		enSelect_EndButton,

		enSelect_Num
	};
	bool m_scaleUpFlag = true;
	bool m_newRecordFlg = false;
	int m_nowSelect = 0;	//�񋓂̒l���i�[����ϐ��B�͂��߂́u�͂��߂�v�{�^����0�B
	int m_stageNum = 0;
	float m_time = 0.0f;
	float m_nowTime = 0.0f;
	float m_bestTime = 0.0f;
	float m_fontScale = 0.25f;
	float m_fontScale2 = 0.2f;
	float m_recordPos = 1100.0f;
	Vector3 m_scale = { 0.0f,0.0f,0.0f };
	Vector3 m_standardScale[enSelect_Num] = { Vector3::One };
	Vector3 m_scale2 = { 0.25f,0.25f,0.25f };
	Vector3 m_scale3 = { 0.2f,0.2f,0.2f };

	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	Game* m_game;
	SaveData* m_saveData = nullptr;
	ResultLevel2D* m_resultLevel2D = nullptr;
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[
	FontRender* m_fontNowTime = nullptr;
	FontRender* m_fontBestTime = nullptr;
	FontRender* m_fontRender = nullptr;		//����̃^�C����\�����邽�߂̃t�H���g�����_�[
};