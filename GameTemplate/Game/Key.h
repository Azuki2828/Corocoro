#pragma once

class Player;
class Background;

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
	void SetPositionKey(Vector3 pos) { m_keyPos = pos; }

	//�h�A�̍��W��ݒ肷��֐��B
	void SetPositionDoor(Vector3 pos) { m_doorPos = pos; }

	void Update()override final;


	//�Q�[���N���A���Ă���̕b�����J�E���g
	//���N���X�ł����̃J�E���g���Ԃ��Q�Ƃ���������public�ɓ���Ă���B
	int GameOverCount = 0;


private:
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	PhysicsStaticObject m_physicsStaticObject;
	bool getKeyFlg = false;

	Player* m_player = nullptr;
	Vector3 m_keyPos;		//���̍��W�B
	Vector3 m_doorPos;		//�h�A�̍��W�B
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[

	CSoundSource* GameClearSound = nullptr;		//�Q�[���N���A�̃T�E���h�\�[�X
	bool GameClearSoundFlag = true;				//�Q�[���N���A�̃T�E���h�Đ���1�񂾂��ɂ���t���O
	CSoundSource* KeyGetSound = nullptr;		//���擾�̃T�E���h�\�[�X
	bool KeyGetSoundFlag = true;	//���擾�̃T�E���h�Đ���1�񂾂��ɂ���t���O
	CSoundSource* GameBGMSound_UpTempo = nullptr;	//�A�b�v�e���|��BGM�̃T�E���h�\�[�X

	int GetDelay = 0;	//�����擾���Ă��献�擾�̃T�E���h�Đ����I���܂ł̎��Ԃ�҂�����ϐ��B

	bool GameOverFlag = false;

};

