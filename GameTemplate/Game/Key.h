#pragma once

class Player;
class BackGround;
class MainCamera;
class GameLevel2D;
class Game;

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

	void SetScaleKey(const Vector3& sca) {
		m_keyScale = sca;
	}

	void SetScaleDoor(const Vector3& sca) {
		m_doorScale = sca;
	}

	float GetGameOverCount() {
		return m_gameOverCount;
	}


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


private:
	bool m_getKeyFlg = false;
	bool m_gameClearSoundFlag = true;				//�Q�[���N���A�̃T�E���h�Đ���1�񂾂��ɂ���t���O
	bool m_keyGetSoundFlag = true;	//���擾�̃T�E���h�Đ���1�񂾂��ɂ���t���O
	int m_gameOverCount = 0;
	int m_delayCount = 0;	//�����擾���Ă��献�擾�̃T�E���h�Đ����I���܂ł̎��Ԃ�҂�����ϐ��B
	Vector3 m_keyPos = Vector3::Zero;		//���̍��W�B
	Vector3 m_keyScale = Vector3::One;
	Vector3 m_doorPos = Vector3::Zero;		//�h�A�̍��W�B
	Vector3 m_doorScale = Vector3::One;

	

	LigData m_ligKeyData;
	LigData m_ligDoorData;
	PhysicsStaticObject m_physicsStaticObject;
	CPhysicsGhostObject m_ghostBox;

	/**
	 * @brief ���ꂼ��̃N���X�̃|�C���^
	*/

	MainCamera* maincamera;
	FontRender* m_fontRender = nullptr;
	SkinModelRender* m_skinModelRender_Key = nullptr;
	SkinModelRender* m_skinModelRender_Door = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	GameLevel2D* m_level2D = nullptr;
	SpriteRender* m_spriteRender = nullptr;		//�X�v���C�g�����_�[
};