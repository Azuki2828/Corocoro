#pragma once

class Player;
class BackGround;
class MainCamera;
class GameLevel2D;
class Game;

namespace {

	const float BASE_KEY_ROT_VALUE = 180.0f;	//���̉�]�����ƂȂ�l
	const float KEY_GET_START_TIME = 3.0f;		//�Q�[�����J�n���Ă���Œ�ł��擾�ł���悤�ɂȂ�܂ł̎���
	const float SOUND_DERAY_COUNT = 2.0f;		//�A�b�v�e���|��BGM�������܂ł̎���

	const char16_t* KEY_GET_EFFECT_FILE_PATH = u"Assets/effect/KeyGet.efk";		//���擾�G�t�F�N�g�̃t�@�C���p�X
	const Vector3 KEY_GET_EFFECT_SCALE = { 200.0f,200.0f,200.0f };				//���擾�G�t�F�N�g�̊g�嗦
	const Vector3 KEY_GET_EFFECT_ADD_POS = { 0.0f,150.0f,0.0f };				//���擾�G�t�F�N�g�̍��W�i�����W������Z�j


	const Vector3 KEY_TRIGGER_BOX_ADD_POS = { 0.0f,125.0f,0.0f };		//���̃g���K�[�{�b�N�X�̍��W�i�����W������Z�j
	const Vector3 KEY_TRIGGER_BOX_SIZE = { 100.0f, 250.0f, 100.0f };	//���̃g���K�[�{�b�N�X�̊g�嗦


	const Vector3 KEY_LIG_FIRST_DIRECTION = { 1.0f, -1.0f, 1.0f };			//1�{�ڂ̃��C�g�̕���
	const Vector4 KEY_LIG_FIRST_COLOR = { 20.0f, 20.0f, 0.0f, 1.0f };		//1�{�ڂ̃��C�g�̃J���[
	const Vector3 KEY_LIG_SECOND_DIRECTION = { 1.0f,1.0f,1.0f };			//2�{�ڂ̃��C�g�̕���
	const Vector4 KEY_LIG_SECOND_COLOR = { 10.0f, 10.0f, 0.0f, 1.0f };		//2�{�ڂ̃��C�g�̃J���[

	const float KEY_METARIC = 1.0f;							//���̋����x
	const float KEY_SMOOTH = 0.6f;							//���̂Ȃ߂炩��
	const Vector3 KEY_AMBIENT = { 0.2f, 0.2f, 0.2f };		//�����󂯂����
	const float KEY_POW_VALUE = 0.7f;						//�i��

	const Vector3 TREASURE_BOX_FLOOR_LIG_DIRECTION = { -1.0f, -1.0f, -1.0f };		//�󔠂̏����󂯂郉�C�g�̕���
	const Vector4 TREASURE_BOX_FLOOR_LIG_COLOR = { 10.0f, 10.0f, 10.0f, 1.0f };		//�󔠂̏����󂯂郉�C�g�̃J���[
	const float TREASURE_BOX_FLOOR_METARIC = 1.0f;									//�󔠂̏��̋����x
	const float TREASURE_BOX_FLOOR_SMOOTH = 0.35f;									//�󔠂̏��̂Ȃ߂炩��
	const Vector3 TREASURE_BOX_FLOOR_AMBIENT = { 0.8f, 0.8f, 0.8f };				//�󔠂̏����󂯂����
}

class Key : public IGameObject
{
private:
	~Key();
	bool Start()override final;
	void Update()override final;

public:


	//��������������֐��B
	void InitKey(const char* name);

	//�h�A������������֐��B
	void InitDoor(const char* name);

	//���̍��W���擾����֐��B
	const Vector3 GetKeyPos() { return m_keyPos; }

	//���̍��W��ݒ肷��֐��B
	void SetKeyPos(const Vector3& pos) { m_keyPos = pos; }

	//�h�A�̍��W��ݒ肷��֐��B
	void SetDoorPos(const Vector3& pos) { m_doorPos = pos; }

	/**
	 * @brief ���̊g�嗦��ݒ肷��֐��B
	 * @param sca ���̊g�嗦
	*/
	void SetScaleKey(const Vector3& sca) {
		m_keyScale = sca;
	}

	/**
	 * @brief �󔠂̏��̊g�嗦��ݒ肷��֐��B
	 * @param sca �g�嗦
	*/
	void SetScaleDoor(const Vector3& sca) {
		m_doorScale = sca;
	}

	/**
	 * @brief ���̃g���K�[�{�b�N�X��ݒ肷��֐��B
	 * @param pos ���̍��W
	*/
	void SetTriggerBox(const Vector3 pos) {
		Vector3 ghostPos = pos;
		ghostPos += KEY_TRIGGER_BOX_ADD_POS;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			KEY_TRIGGER_BOX_SIZE	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
	}


private:
	bool m_getKeyFlg = false;						//���擾�t���O
	bool m_gameClearSoundFlag = true;				//�Q�[���N���A�̃T�E���h�Đ���1�񂾂��ɂ���t���O
	bool m_keyGetSoundFlag = true;					//���擾�̃T�E���h�Đ���1�񂾂��ɂ���t���O
	bool m_startUpTempoSoundFlg = false;			//�A�b�v�e���|BGM�̍Đ���1�񂾂��ɂ���t���O
	int m_delayCount = 0;							//�����擾���Ă��献�擾�̃T�E���h�Đ����I���܂ł̎��Ԃ�҂�����ϐ�
	float m_keyRotTime = 0.0f;						//������]�����鎞�̃^�C�}�[
	Vector3 m_keyPos = Vector3::Zero;				//���̍��W
	Vector3 m_keyScale = Vector3::One;				//���̊g�嗦
	Quaternion m_keyRot = Quaternion::Identity;		//���̉�]��
	Vector3 m_doorPos = Vector3::Zero;				//�󔠂̏��̍��W
	Vector3 m_doorScale = Vector3::One;				//�󔠂̏��̊g�嗦

	LigData m_ligKeyData;							//���̃��C�g�̃f�[�^
	LigData m_ligDoorData;							//�󔠂̏��̃��C�g�̃f�[�^
	PhysicsStaticObject m_physicsStaticObject;		//�󔠂̏��̐ÓI�����I�u�W�F�N�g
	CPhysicsGhostObject m_ghostBox;					//���̓����蔻��


	//���ꂼ��̃N���X�̃|�C���^

	MainCamera* m_mainCamera = nullptr;
	FontRender* m_fontRender = nullptr;
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	GameLevel2D* m_gameLevel2D = nullptr;
	SpriteRender* m_spriteRender = nullptr;
};