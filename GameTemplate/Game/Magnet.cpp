#include "stdafx.h"
#include "Magnet.h"
#include "Player.h"
#include "Key.h"
#include "Game.h"
#include "MainCamera.h"
#include "ConstTriggerBoxValue.h"

bool Magnet::Start() {
	
	//���W��o�^
	m_skinModelRender->SetPosition(m_pos);
	//��]����o�^
	m_skinModelRender->SetRotation(m_rot);
	//�g�嗦��o�^
	m_skinModelRender->SetScale(m_sca);
	//�e�N���X�̃C���X�^���X��T��
	m_key = FindGO<Key>(NAME_KEY);
	m_game = FindGO<Game>(NAME_GAME);
	m_player = FindGO<Player>(NAME_PLAYER);

	//�J����������]�����Ƃ��̏���
	auto mainCamera = FindGO<MainCamera>(NAME_MAIN_CAMERA);
	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, CAMERA_ROT_VALUE);
		m_rotZ.Apply(m_modelOption.directionLigData[enData_Zeroth].Dir);
	});

	
	//�������̂���Ȃ��Ȃ���W���X�V���ē����蔻���t����B
	if (!m_moveFlg) {
		m_skinModelRender->UpdateWorldMatrix();
		m_physicsStaticObject.CreateFromModel(
			*m_skinModelRender->GetModel(),
			m_skinModelRender->GetModel()->GetWorldMatrix()
		);
		m_physicsStaticObject.SetFriction(MAGNET_FRICTION);
	}

	//���͂��e���͈͂�ݒ肷��B
	SetMagnetTriggerBox(m_game->GetStageNum());

	//�g���K�[�{�b�N�X�ƃv���C���[���ڐG���Ȃ��悤�ɐݒ肷��B
	m_player->GetRigidBody()->GetBody()->setIgnoreCollisionCheck(m_ghostBox.GetGhostObject(), true);
	return true;
}

Magnet::~Magnet() {
	//���f�����폜����B
	DeleteGO(m_skinModelRender);
}

void Magnet::Update() {

	//���W��o�^�B
	m_skinModelRender->SetPosition(m_pos);
	//�v���C���[�Ɍ������ĐL�т�x�N�g��(����)�B
	m_length = m_player->GetPosition() - m_magnetPos;
		PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

			//�g���K�[�{�b�N�X�ƐڐG
			if (m_ghostBox.IsSelf(contactObject)) {

				//���͂�^����B
				SetMagnetPower();
			}
		});

}

void Magnet::SetMagnetPower() {

	//�v���C���[�Ǝ��g�̎����ɂ������Ȃ玩�g�Ɍ������ĐL�т�x�N�g���ɂ���B
	if (m_magState != m_player->GetPlayerState()) {
		m_length *= REVERSE_VECTOR;
	}

	//�͂�萔�{����B
	float power = ReturnReciprocal(m_length.Length()) * MAGNET_POWER;

	//�x�N�g���𐳋K������B
	m_length.Normalize();

	//���K�������x�N�g���Ɏ��͂��|����B
	m_length *= power;

	//Z�����ւ̗͂��O�ɂ���B
	m_length.z = MAGNET_Z_POWER;

	//�v���C���[�ɗ͂�^����B
	m_player->ReceivePower(m_length);
}

void Magnet::SetMagnetTriggerBox(int stageNum) {

	//���͂̉e���͈͂����߂�
	Vector3 ghostPos = m_pos;
	ghostPos += MAGNET_TRIGGER_BOX_ADD_POS_BASE;
	switch (stageNum) {		//�X�e�[�W�ԍ�

	case Stage_One:


		switch (m_magnetNum) {		//���Δԍ�

		case enMagnet_First:
		case enMagnet_Second:
		case enMagnet_Third:
		case enMagnet_Fourth:
		case enMagnet_Nineth:
		case enMagnet_TwentySixth:
		case enMagnet_ThirtyFourth:
		case enMagnet_ThirtyFifth:
		case enMagnet_ThirtySixth:
		case enMagnet_ThirtySeventh:
			CreateTriggerBox(Left3);
			break;
		case enMagnet_Eleventh:
		case enMagnet_TwentyFourth:
		case enMagnet_TwentySeventh:
			CreateTriggerBox(Down3);
			break;
		case enMagnet_Sixth:
		case enMagnet_Seventh:
		case enMagnet_Eighth:
		case enMagnet_Tenth:
		case enMagnet_Twelfth:
		case enMagnet_Thirteenth:
		case enMagnet_Fourteenth:
		case enMagnet_Seventeenth:
		case enMagnet_Eighteenth:
		case enMagnet_Nineteenth:
		case enMagnet_TwentySecond:
		case enMagnet_ThirtyFirst:
		case enMagnet_ThirtySecond:
		case enMagnet_ThirtyThird:
			CreateTriggerBox(Right3);
			break;
		case enMagnet_TwentyThird:
		case enMagnet_TwentyNineth:
		case enMagnet_Thirtieth:
			CreateTriggerBox(Up3);
			break;
		case enMagnet_Zero:
			ghostPos.x += ADD_POS_100;
			ghostPos.y -= ADD_POS_100;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_644	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_Fifth:
			ghostPos.x -= ADD_POS_100;
			ghostPos.y -= ADD_POS_150;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_434	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_Fifteenth:
			ghostPos.x += ADD_POS_200;
			ghostPos.y -= ADD_POS_150;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_434	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_Sixteenth:
			ghostPos.x += ADD_POS_100;
			ghostPos.y += ADD_POS_100;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_644	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_Twentieth:
			ghostPos.x += ADD_POS_200;
			ghostPos.y += ADD_POS_250;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_434	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_TwentyFirst:
			ghostPos.x -= ADD_POS_100;
			ghostPos.y += ADD_POS_250;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_434	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_TwentyFifth:
			ghostPos.x -= ADD_POS_50;
			ghostPos.y -= ADD_POS_150;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_334	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_TwentyEighth:
			ghostPos.x -= ADD_POS_50;
			ghostPos.y += ADD_POS_250;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_334	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		}
		break;
	case Stage_Two:
		switch (m_magnetNum) {
		case enMagnet_First:
		case enMagnet_Third:
		case enMagnet_Tenth:
		case enMagnet_Eleventh:
			CreateTriggerBox(Up4);
			break;
		case enMagnet_Fourth:
		case enMagnet_Fifth:
		case enMagnet_Sixth:
			CreateTriggerBox(Right3);
			break;
		case enMagnet_Seventh:
		case enMagnet_Eighth:
		case enMagnet_Nineth:
			CreateTriggerBox(Right4);
			break;
		case enMagnet_Thirteenth:
		case enMagnet_Fourteenth:
			CreateTriggerBox(Down4);
			break;
		case enMagnet_Sixteenth:
		case enMagnet_Seventeenth:
		case enMagnet_Eighteenth:
			CreateTriggerBox(Left3);
			break;
		case enMagnet_Nineteenth:
		case enMagnet_Twentieth:
		case enMagnet_TwentyFirst:
			CreateTriggerBox(Left5);
			break;
		case enMagnet_Zero:
		case enMagnet_Second:
			ghostPos.x -= ADD_POS_50;
			ghostPos.y += ADD_POS_300;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_344	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_Twelfth:
			ghostPos.x -= ADD_POS_50;
			ghostPos.y -= ADD_POS_200;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_344	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_Fifteenth:
			ghostPos.x += ADD_POS_150;
			ghostPos.y -= ADD_POS_200;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_344	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_TwentySecond:
			ghostPos.x += ADD_POS_50;
			ghostPos.y += ADD_POS_200;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_524	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_TwentyThird:
			ghostPos.x += ADD_POS_50;
			ghostPos.y -= ADD_POS_100;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_524	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_TwentyFourth:
			ghostPos.x += ADD_POS_50;
			ghostPos.y -= ADD_POS_50;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_354	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		}

		break;
	case Stage_Three:
		switch (m_magnetNum) {
		case enMagnet_Zero:
		case enMagnet_First:
		case enMagnet_Second:
		case enMagnet_Third:
		case enMagnet_Fourth:
		case enMagnet_Fifth:
		case enMagnet_Sixth:
		case enMagnet_Seventh:
		case enMagnet_Eighth:
			CreateTriggerBox(Right4);
			break;
		case enMagnet_Nineth:
		case enMagnet_Tenth:
		case enMagnet_Eleventh:
			CreateTriggerBox(Up3);
			break;
		case enMagnet_Fourteenth:
		case enMagnet_Fifteenth:
		case enMagnet_Sixteenth:
		case enMagnet_Seventeenth:
		case enMagnet_Eighteenth:
		case enMagnet_Nineteenth:
			CreateTriggerBox(Left4);
			break;
		case enMagnet_Twentieth:
		case enMagnet_TwentyFirst:
		case enMagnet_TwentySecond:
			CreateTriggerBox(Down2);
			break;
		case enMagnet_Twelfth:
		case enMagnet_Thirteenth:
			ghostPos.x += ADD_POS_100;
			ghostPos.y += ADD_POS_150;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_234	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_TwentyThird:
			ghostPos.x += ADD_POS_200;
			ghostPos.y -= ADD_POS_50;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_434	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_TwentyFourth:
			ghostPos.x -= ADD_POS_100;
			ghostPos.y += ADD_POS_50;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_454	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_TwentyFifth:
		case enMagnet_TwentySixth:
			ghostPos.x += ADD_POS_50;
			ghostPos.y += ADD_POS_50;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_154	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_TwentySeventh:
			ghostPos.x += ADD_POS_50;
			ghostPos.y += ADD_POS_50;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_534	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		}
		break;
	case Stage_Four:
		switch (m_magnetNum) {
		case enMagnet_Zero:
		case enMagnet_First:
			CreateTriggerBox(Up3);
			break;
		case enMagnet_Second:
		case enMagnet_Third:
		case enMagnet_Fourth:
			CreateTriggerBox(Down2);
			break;
		case enMagnet_Fifth:
			ghostPos.x -= ADD_POS_50;
			ghostPos.y -= ADD_POS_100;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_324	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_Sixth:
		case enMagnet_Tenth:
			CreateTriggerBox(Left3);
			break;
		case enMagnet_Seventh:
		case enMagnet_Eighth:
		case enMagnet_Nineth:
		case enMagnet_ThirtyThird:
		case enMagnet_ThirtyFourth:
		case enMagnet_ThirtyFifth:
			CreateTriggerBox(Right3);
			break;
		case enMagnet_Eleventh:
		case enMagnet_ThirtySixth:
		case enMagnet_ThirtySeventh:
			ghostPos.x += ADD_POS_150;
			ghostPos.y += ADD_POS_150;
			m_ghostBox.CreateBox(
				ghostPos,	//�������͍��W�B
				Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
				TYPE_334	//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			break;
		case enMagnet_Twelfth:
		case enMagnet_Thirteenth:
		case enMagnet_Fourteenth:
		case enMagnet_Fifteenth:
		case enMagnet_Sixteenth:
		case enMagnet_Seventeenth:
		case enMagnet_Eighteenth:
		case enMagnet_Nineteenth:
			CreateTriggerBox(Up2);
			break;
		case enMagnet_Twentieth:
		case enMagnet_TwentyFirst:
		case enMagnet_TwentySecond:
		case enMagnet_TwentyThird:
		case enMagnet_TwentyFourth:
		case enMagnet_TwentyFifth:
		case enMagnet_TwentySixth:
		case enMagnet_TwentySeventh:
		case enMagnet_TwentyEighth:
		case enMagnet_TwentyNineth:
		case enMagnet_Thirtieth:
		case enMagnet_ThirtyFirst:
		case enMagnet_ThirtySecond:
			CreateTriggerBox(Down3);
			break;
		}
		break;
	}
}

void Magnet::CreateTriggerBox(int type) {

	//���͂̉e���͈͂̃T���v��
	Vector3 ghostPos = m_pos;
	ghostPos += MAGNET_TRIGGER_BOX_ADD_POS_BASE;
	switch (type) {
	case Left3:
		ghostPos.x -= ADD_POS_150;
		ghostPos.y += ADD_POS_50;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_314	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Left4:
		ghostPos.x -= ADD_POS_200;
		ghostPos.y += ADD_POS_50;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_414	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Left5:
		ghostPos.x -= ADD_POS_250;
		ghostPos.y += ADD_POS_50;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_514	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Right3:
		ghostPos.x += ADD_POS_250;
		ghostPos.y += ADD_POS_50;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_314	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Right4:
		ghostPos.x += ADD_POS_300;
		ghostPos.y += ADD_POS_50;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_414	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Down2:
		ghostPos.x += ADD_POS_50;
		ghostPos.y -= ADD_POS_100;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_124	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Down3:
		ghostPos.x += ADD_POS_50;
		ghostPos.y -= ADD_POS_150;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_134	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Down4:
		ghostPos.x += ADD_POS_50;
		ghostPos.y -= ADD_POS_200;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_144	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Up2:
		ghostPos.x += ADD_POS_50;
		ghostPos.y += ADD_POS_200;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_124	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Up3:
		ghostPos.x += ADD_POS_50;
		ghostPos.y += ADD_POS_250;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_134	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	case Up4:
		ghostPos.x += ADD_POS_50;
		ghostPos.y += ADD_POS_300;
		m_ghostBox.CreateBox(
			ghostPos,	//�������͍��W�B
			Quaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
			TYPE_144	//��O�����̓{�b�N�X�̃T�C�Y�B
		);
		break;
	}
}