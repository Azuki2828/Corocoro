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

	//SpriteRender* m_spriteRender = nullptr;
};