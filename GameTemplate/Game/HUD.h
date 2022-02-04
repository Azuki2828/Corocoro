#pragma once
#include "SpriteRender.h"
#include <vector>

namespace {

	const int RESET_SPRITE_NUM = 0;				//�����̃X�v���C�g��
}
struct SpriteData {
	int spriteNum = 0;							//�o�^�ԍ�
	Sprite sprite;								//�X�v���C�g�N���X�̃I�u�W�F�N�g
	SpriteInitData initData;					//�X�v���C�g�̃f�[�^
	Vector3 pos = Vector3::Zero;				//���W
	Quaternion rot = Quaternion::Identity;		//��]��
	Vector3 sca = Vector3::One;					//�g�嗦
	Vector4 mulColor = Vector4::White;			//��Z�J���[
	bool activate = true;						//�L���t���O
	int prio = 0;								//�\���D��x
};

class HUD
{
public:
	/**
	 * @brief HUD�N���X�̃C���X�^���X���쐬����֐��B
	*/
	static void CreateHUD() {
		m_hud = new HUD;
	}
	/**
	 * @brief HUD�N���X�̃C���X�^���X���擾����֐��B
	 * @return HUD�N���X�̃C���X�^���X
	*/
	static HUD* GetHUD() {
		return m_hud;
	}
	/**
	 * @brief �������֐��B
	 * @param num �X�v���C�g�ԍ�
	 * @param filepath �t�@�C���p�X
	 * @param width ��
	 * @param height ����
	 * @param mode �A���t�@�u�����f�B���O�̃��[�h
	 * @param prio �\���D��x
	*/
	void Init(int num, const char* filepath, float width, float height, AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans, int prio = 0);

	/**
	 * @brief �X�v���C�g�̃f�[�^����S�ĉ������֐��B
	*/
	void Release();

	/**
	 * @brief �`��֐��B
	 * @param rc �����_�[�R���e�L�X�g
	*/
	void Draw(RenderContext& rc);

	/**
	 * @brief ���W��ݒ肷��֐��B
	 * @param num �X�v���C�g�ԍ�
	 * @param pos ���W
	*/
	void SetPosition(int num,const Vector3& pos) { 
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->pos = pos;
				break;
			}
		}
	}

	/**
	 * @brief ��]����ݒ肷��֐��B
	 * @param num �X�v���C�g�ԍ�
	 * @param rot ��]��
	*/
	void SetRotation(int num, const Quaternion& rot) { 
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->rot = rot;
				break;
			}
		}
	}

	/**
	 * @brief �g�嗦��ݒ肷��֐��B
	 * @param num �X�v���C�g�ԍ�
	 * @param sca �g�嗦
	*/
	void SetScale(int num, const Vector3& sca) { 
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->sca = sca;
				break;
			}
		}
	}
	
	/**
	 * @brief �g�嗦���擾����֐��B
	 * @param num �X�v���C�g�ԍ�
	 * @return �g�嗦
	*/
	Vector3 GetScale(int num) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				return m_spriteData[i]->sca;
				break;
			}
		}
	}

	/**
	 * @brief ��Z�J���[��ݒ肷��֐��B
	 * @param num �X�v���C�g�ԍ�
	 * @param mulCol ��Z�J���[
	*/
	void SetMulColor(int num, const Vector4& mulCol) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->mulColor = mulCol;
				break;
			}
		}
	}

	/**
	 * @brief �X�v���C�g�𖳌��ɂ���֐��B
	 * @param num �X�v���C�g�ԍ�
	*/
	void Deactivate(int num) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->activate = false;
				break;
			}
		}
	}

	/**
	 * @brief �X�v���C�g��L���ɂ���֐��B
	 * @param num �X�v���C�g�ԍ�
	*/
	void Activate(int num) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->activate = true;
				break;
			}
		}
	}

	/**
	 * @brief �A�b�v�f�[�g�֐��Bmain�֐��ŌĂԕK�v������B
	*/
	void Update();

private:
	int m_maxPriority = 0;
	static HUD* m_hud;							//HUD�N���X�̃C���X�^���X
	std::vector<SpriteData*> m_spriteData;		//�X�v���C�g�̑��f�[�^�B
};

