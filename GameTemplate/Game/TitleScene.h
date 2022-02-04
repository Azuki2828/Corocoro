#pragma once
class TitleLevel2D;

class TitleScene : public IGameObject
{
private:
	~TitleScene();
	bool Start() override;
	void Update() override;
private:
	//�{�^����I�����邽�߂̗񋓌^
	enum Select {
		StartButton,
		RuleButton,
		EndButton,
	};
	bool m_scaleUpFlag = true;		//�g��k������t���O
	float m_ButtonScale = 0.0f;		//�{�^���̊g�嗦
	int m_nowSelect = 0;			//�I������

	//���ꂼ��̃N���X�̃|�C���^

	TitleLevel2D* m_titleLevel2D = nullptr;
};