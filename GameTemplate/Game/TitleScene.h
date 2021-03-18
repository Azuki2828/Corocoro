#pragma once
class TitleScene  : public IGameObject
{
public:
	TitleScene();
	~TitleScene();
	bool Start();
	void Update();


	SpriteRender* m_spriteRender = nullptr;

private:

};

