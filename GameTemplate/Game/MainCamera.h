#pragma once

class Player;
class DirectionLight;
class MapChip;

namespace {

	const float CAMERA_ROT_WAIT_TIME = 1.5f;	//�����擾���Ă����]����܂ł̎���
	const int ROT_NUM = 90;						//��]���B90��Ŕ���]�B
}

class MainCamera : public IGameObject
{
private:
	bool Start() override final;
	void Update() override final;
	void FreeUpdate() override final;

public:

	/**
	 * @brief �J��������]���Ă��邩�m���߂�t���O
	 * @param flg 
	*/
	void SetRotFlg(bool flg) {
		m_rotFlg = flg;
	}

	//1�񂾂��J������180�x��]�����邽�߂̃t���O
	std::list<std::function< void() >> changeRotCameraEvent;
private:
	bool m_cameraRotFlg = false;					//�J��������]���Ă��邩�ǂ����̃t���O
	bool m_rotFlg = false;							//�J��������]������t���O�i1�񂾂����s�j
	int m_count = 0;								//��]���i0�`90�j
	float m_waitRot = 0.0f;							//�J��������]����܂ł̎���		
	Vector3 m_pos = Vector3::Zero;					//���_�B
	Vector3 m_tar = Vector3::Zero;					//�����_�B
	Vector3 m_rotAxis = { 0.0f,1.0f,0.0f };			//��]��
	Vector3 m_toPos = { 0.0f,200.0f,-1400.0f };		//�����_���王�_�܂ł̋���

	//���ꂼ��̎�
	Quaternion m_rotX = Quaternion::Identity;		
	Quaternion m_rotY = Quaternion::Identity;
	Quaternion m_rotZ = Quaternion::Identity;


	//���ꂼ��̃N���X�̃|�C���^

	Player* m_player = nullptr;
	DirectionLight* m_dir = nullptr;
	MapChip* m_mapChip = nullptr;
};

