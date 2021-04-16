#pragma once
class PostEffect : public IGameObject
{
private:
	bool Start()override final;
public:
	PostEffect() {

	}
	~PostEffect() {

	}
	void InitLuminance(RenderTarget& renderTarget);
	Sprite& GetLuminanceSprite() { return sprite[0]; }
	Sprite& GetFinalSprite() { return sprite[1]; }
	GaussianBlur& GetGaussianBlurSprite(int val_) { return gaussianBlur[val_]; }
	void InitGaussianBlur(RenderTarget& renderTarget);
private:
	/*SpritePtr m_sprite[2];*/
	std::unique_ptr<Sprite[]> sprite = std::make_unique<Sprite[]>(2);
	std::unique_ptr<GaussianBlur[]> gaussianBlur = std::make_unique<GaussianBlur[]>(4);
};

