#include "stdafx.h"
#include "PostEffect.h"

bool PostEffect::Start() {

	//for (int i = 0; i < 2; i++) {
	//	m_sprite[i] = std::make_unique;
	//}

	return true;
}
void PostEffect::InitLuminance(RenderTarget& renderTarget) {
	// �P�x���o�p�̃X�v���C�g��������
	// �����������쐬����
	SpriteInitData luminanceSpriteInitData;

	// �P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
	luminanceSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";

	// ���_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
	luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";

	// �s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
	luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";

	// �X�v���C�g�̕��ƍ�����luminnceRenderTarget�Ɠ���
	luminanceSpriteInitData.m_width = 1280;
	luminanceSpriteInitData.m_height = 720;

	// �e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[
	luminanceSpriteInitData.m_textures[0] = &renderTarget.GetRenderTargetTexture();

	// �`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
	luminanceSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	// �쐬�����������������ƂɃX�v���C�g������������
	sprite[0].Init(luminanceSpriteInitData);
	//Sprite luminanceSprite;
	//luminanceSprite.Init(luminanceSpriteInitData);
}

void PostEffect::InitGaussianBlur(RenderTarget& renderTarget) {

	//GaussianBlur gaussianBlur[4];

	gaussianBlur[0].Init(&renderTarget.GetRenderTargetTexture());
	gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
	gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
	gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());

	// step-2 �{�P�摜���������ď������ނ��߂̃X�v���C�g��������

	SpriteInitData finalSpriteInitData;

	finalSpriteInitData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
	finalSpriteInitData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
	finalSpriteInitData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
	finalSpriteInitData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();

	finalSpriteInitData.m_width = 1280;
	finalSpriteInitData.m_height = 720;

	finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
	finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

	finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
	finalSpriteInitData.m_colorBufferFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	sprite[1].Init(finalSpriteInitData);
	//Sprite finalSprite;
	//finalSprite.Init(finalSpriteInitData);
}