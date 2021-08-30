#pragma once

#include "stdafx.h"
#include "DirectionLight.h"
#include "LightBase.h"

static const int MAX_DIRECTION_LIGHT = 8;	//�f�B���N�V�������C�g�̏����
static const int MAX_MODEL_OPTION = 100;	//���f���I�v�V�����̏����

//�֊s���̎��
enum {
	Edge_NULL,
	Edge_1,
	Edge_2
};

struct ModelOption {
	DirectionLigData directionLigData[MAX_DIRECTION_LIGHT];	//�f�B���N�V�������C�g�̃f�[�^
	Vector3 ambient = { 0.3f,0.3f,0.3f };
	float metaric = 0.0f;
	float smooth = 0.5f;
	int edge = Edge_NULL;
	float powValue = 0.0f;
	unsigned int LigID = 0;
	Vector2 pad;
	float uvNoiseMul = 0.0f;
	float uvNoiseOffset = 0.0f;
};

struct LigData {
	DirectionLigData directionLigData[MAX_DIRECTION_LIGHT];		//���ׂẴ��f�����󂯂�f�B���N�V�������C�g�̃f�[�^
	ModelOption modelOption[MAX_MODEL_OPTION];					//���f���I�v�V����
	Matrix m_viewProj;											//�v���W�F�N�V�����s��
	Vector3 eyePos = Vector3::Zero;								//���_�̍��W
};
//struct LigData {
//	DirectionLigData m_directionLigData[MAX_DIRECTION_LIGHT];	//�f�B���N�V�������C�g�̃f�[�^
//	Vector3 eyePos = Vector3::Zero;								//���_�̍��W
//	float pad;													//�p�f�B���O
//	Vector3 ambient;											//����
//	float pad1;													//�p�f�B���O
//	Matrix m_viewProj;											//�v���W�F�N�V�����s��
//	float metaric = 0.0f;										//�����x
//	float smooth = 0.5f;										//�Ȃ߂炩��
//	int edge = Edge_NULL;										//�֊s���̎��
//	float powValue = 0.0f;										//�i�藦
//	float uvNoiseMul = 0.0f;									//��Z����m�C�Y�̒l
//	float uvNoiseOffset = 0.0f;									//�m�C�Y�̃I�t�Z�b�g
//	unsigned int LigID = 0;										//���C�g��ID�B���C�g�̑Ώۂ𔻒f����Ƃ��Ɏg���B0���f�t�H�B
//};

class LightManager
{
public:
	/**
	 * @brief ���C�g�}�l�[�W���[�̃C���X�^���X���쐬����֐��B
	*/
	static void CreateInstance() {

		m_lightManager = new LightManager;
	}
	/**
	 * @brief ���C�g�}�l�[�W���[�̃C���X�^���X���擾����֐��B
	 * @return �C���X�^���X
	*/
	static LightManager* GetInstance() {

		return m_lightManager;
	}

	/**
	 * @brief ���f���I�v�V������ǉ�����֐��B
	 * @param modelOption ���f���I�v�V����
	*/
	void AddModelOption(const ModelOption& modelOption, unsigned int modelNum) {

		m_ligData.modelOption[modelNum] = modelOption;
	}

	void Update();

	/**
	 * @brief ���C�g��ǉ�����֐��B
	 * @param light ���C�g�̃C���X�^���X
	*/
	void AddLight(LightBase* light);

	/**
	 * @brief ���C�g���폜����֐��B
	 * @param light ���C�g�̃C���X�^���X
	*/
	void RemoveLight(LightBase* light);

	/**
	 * @brief ���C�g�̃f�[�^���擾����֐��B
	 * @return ���C�g�̃f�[�^
	*/
	LigData* GetLigData() { return &m_ligData; }
private:
	LigData m_ligData;									//���C�g�̃f�[�^
	static LightManager* m_lightManager;				//���C�g�}�l�[�W���[�̃C���X�^���X
	std::list<DirectionLigData*> m_directionLights;		//�f�B���N�V�������C�g�̃f�[�^
};

