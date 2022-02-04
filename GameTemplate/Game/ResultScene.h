#pragma once
class ResultLevel2D;
class Game;
class SaveData;

class ResultScene : public IGameObject
{
private:
	bool Start();
	~ResultScene();
	void Update();

public:
	/**
	 * @brief �L�^���擾����֐��B
	 * @return �L�^
	*/
	float GetTime()
	{
		return m_time;
	}

	/**
	 * @brief ����̃^�C�����L�^����֐�
	 * @param time ����̃^�C��
	*/
	void SetTime(const float time) {

		m_time = time;
	}

	/**
	 * @brief �X�e�[�W�ԍ���ݒ肷��֐��B
	 * @param num �X�e�[�W�ԍ�
	*/
	void SetStageNum(int num) {
		m_stageNum = num;
	}
	/**
	 * @brief �X�e�[�W�ԍ����擾����֐��B
	 * @return �X�e�[�W�ԍ�
	*/
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
	bool m_scaleUpFlag = true;						//�{�^�����g�債�Ă����t���O
	bool m_newRecordFlg = false;					//�V�L�^�t���O
	int m_nowSelect = 0;							//�񋓂̒l���i�[����ϐ��B�͂��߂́u�͂��߂�v�{�^����0�B
	int m_stageNum = 0;								//�X�e�[�W�ԍ�
	float m_time = 0.0f;							//�L�^��ێ�����ϐ��B
	float m_nowTime = 0.0f;							//����̋L�^
	float m_bestTime = 0.0f;						//�ō��L�^
	float m_fontScale = 0.25f;						//�^�C�g���{�^���̃T�C�Y
	float m_fontScale2 = 0.2f;						//�I���{�^���̃T�C�Y
	float m_recordPos = 1100.0f;					//�V�L�^�I�̍��W
	Vector3 m_scale = Vector3::Zero;				//�{�^���̃T�C�Y
	Vector3 m_standardScale[enSelect_Num];			//���ꂼ��̃{�^���̏����T�C�Y

	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	Game* m_game = nullptr;
	SaveData* m_saveData = nullptr;
	ResultLevel2D* m_resultLevel2D = nullptr;
	SpriteRender* m_spriteRender = nullptr;
	FontRender* m_fontNowTime = nullptr;
	FontRender* m_fontBestTime = nullptr;
	FontRender* m_fontRender = nullptr;
};