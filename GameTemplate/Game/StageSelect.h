#pragma once
class StageSelectLevel2D;
class Game;

class StageSelect : public IGameObject
{
private:
	bool Start();
	~StageSelect();
	void Update();
private:
		//�{�^����I�����邽�߂̗񋓌^
	enum Select {
		BackButton,
		KetteiButton,
	};

	enum StageNumber
	{
		StageOne,
		StageTwo,
		StageThree,
		StageFour,
		FinalStage		//FinalStage�Ƀ}�C�i�X1���邱�ƂŃX�e�[�W�̑��������߂�B
	};
	bool ScaleUpFlag = true;
	int NowSelectStage = 0;
	int NowSelect = 1;	//�񋓂̒l���i�[����ϐ��B�͂��߂́u�����Ă��v�{�^����1�B
	float Fscale = 0.23f;
	float Fscale1 = 0.18f;
	Vector3 Vscale = { 0.0f,0.0f,0.0f };
	Vector3 vscale = { 0.23f,0.23f,0.23f };
	Vector3 vscale1 = { 0.18f,0.18f,0.18f };


	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	StageSelectLevel2D* m_sprite = nullptr;
	SpriteRender* m_stageSpriteRender[4][2] = { nullptr };		//�X�e�[�W�����X�v���C�g�����_�[
	Game* m_game = nullptr;
};