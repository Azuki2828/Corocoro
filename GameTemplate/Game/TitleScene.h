#pragma once
class TitleLevel2D;

class TitleScene : public IGameObject
{
public:
	//TitleScene();		Start関数の方を使う。
	~TitleScene();
	bool Start();
	void Update();
private:
	TitleLevel2D* sprite = nullptr;

	//タイトルBGMのサウンドソース
	CSoundSource* TitleBGMSound = nullptr;

	//SpriteRender* m_spriteRender = nullptr;
};