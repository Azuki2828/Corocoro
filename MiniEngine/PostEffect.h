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
	void InitDeferrdSprite() {
		// �|�X�g�G�t�F�N�g�I�Ƀf�B�t�@�[�h���C�e�B���O���s�����߂̃X�v���C�g��������
		SpriteInitData spriteInitData;

		// ��ʑS�̂Ƀ����_�����O����̂ŕ��ƍ����̓t���[���o�b�t�@�[�̕��ƍ����Ɠ���
		spriteInitData.m_width = FRAME_BUFFER_W;
		spriteInitData.m_height = FRAME_BUFFER_H;

		// �f�B�t�@�[�h���C�e�B���O�Ŏg�p����e�N�X�`����ݒ�
		spriteInitData.m_textures[0] = &RenderTarget::GetRenderTarget(enAlbedoMap)->GetRenderTargetTexture();
		spriteInitData.m_textures[1] = &RenderTarget::GetRenderTarget(enNormalAndDepthMap)->GetRenderTargetTexture();
		spriteInitData.m_textures[2] = &RenderTarget::GetRenderTarget(enWorldPosAndLigIDMap)->GetRenderTargetTexture();

		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_expandConstantBuffer = LightManager::GetInstance()->GetLigData();
		spriteInitData.m_expandConstantBufferSize = sizeof(*LightManager::GetInstance()->GetLigData());

		// �������f�[�^���g���ăX�v���C�g���쐬
		Sprite defferdLightinSpr;
		defferdLightinSpr.Init(spriteInitData);
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

	Sprite m_deferredSprite;
};

