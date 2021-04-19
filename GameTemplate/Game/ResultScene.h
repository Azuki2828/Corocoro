#pragma once
class ResultScene : public IGameObject
{
public:
	~ResultScene();
	bool Start();
	void Update();
private:
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー

	FontRender* m_fontRender = nullptr;
};