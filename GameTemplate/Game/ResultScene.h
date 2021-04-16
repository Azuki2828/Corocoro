#pragma once
class ResultScene : public IGameObject
{
public:
	ResultScene();
	~ResultScene();
	bool Start();
	void Update();
private:
	SpriteRender* m_spriteRender = nullptr;		//スプライトレンダー
};