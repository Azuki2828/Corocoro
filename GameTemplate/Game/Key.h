#pragma once

class Player;
class Background;
class MainCamera;
class GameLevel2D;
class Game;

class Key : public IGameObject
{
public:
	bool Start()override final;

	~Key();

	//��������������֐��B
	void InitKey(const char* name);

	//�h�A������������֐��B
	void InitDoor(const char* name);

	//���̍��W���擾����֐��B
	const Vector3 GetKeyPos() { return m_keyPos; }

	//���̍��W��ݒ肷��֐��B
	void SetPositionKey(const Vector3& pos) { m_keyPos = pos; }

	//�h�A�̍��W��ݒ肷��֐��B
	void SetPositionDoor(const Vector3& pos) { m_doorPos = pos; }

	void SetScaleKey(const Vector3& sca) {
		m_keyScale = sca;
	}

	void SetScaleDoor(const Vector3& sca) {
		m_Doorscale = sca;
	}

	void Update()override final;
	bool GetdoorbreakFlg() { return m_doorbreakFlg; };

	void SetTriggerBox(const Vector3 pos) {
		Vector3 ghostPos = pos;
		//ghostPos.x += 300.0f;
		ghostPos.y += 125.0f;
		//ghostPos.z -= 300.0f;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			{ 100.0f, 250.0f, 100.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
	}



	//�Q�[���N���A���Ă���̕b�����J�E���g
	//���N���X�ł����̃J�E���g���Ԃ��Q�Ƃ���������public�ɓ���Ă���B
	int GameOverCount = 0;


private:
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	PhysicsStaticObject m_physicsStaticObject;
	bool getKeyFlg = false;
	bool m_doorbreakFlg = false;

	Player* m_player = nullptr;
	Game* m_game = nullptr;
	GameLevel2D* m_level2D = nullptr;
	Vector3 m_keyPos;		//���̍��W�B
	Vector3 m_keyScale;
	Vector3 m_doorPos;		//�h�A�̍��W�B
	Vector3 m_Doorscale;
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[
	CSoundSource* m_sound = nullptr;			//���ʉ��ǉ�

	CSoundSource* GameClearSound = nullptr;		//�Q�[���N���A�̃T�E���h�\�[�X
	bool GameClearSoundFlag = true;				//�Q�[���N���A�̃T�E���h�Đ���1�񂾂��ɂ���t���O
	CSoundSource* KeyGetSound = nullptr;		//���擾�̃T�E���h�\�[�X
	bool KeyGetSoundFlag = true;	//���擾�̃T�E���h�Đ���1�񂾂��ɂ���t���O
	CSoundSource* GameBGMSound_UpTempo = nullptr;	//�A�b�v�e���|��BGM�̃T�E���h�\�[�X

	int GetDelay = 0;	//�����擾���Ă��献�擾�̃T�E���h�Đ����I���܂ł̎��Ԃ�҂�����ϐ��B

	FontRender* m_fontRender = nullptr;

	MainCamera* maincamera;
	LigData m_ligKeyData;
	LigData m_ligDoorData;
	CPhysicsGhostObject m_ghostBox;
};