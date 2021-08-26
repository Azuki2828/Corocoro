#include "stdafx.h"
#include "Magnet.h"
#include "Player.h"
#include "Key.h"
#include "Game.h"
#include "MainCamera.h"
#include "ConstTriggerBoxValue.h"

bool Magnet::Start() {
	
	//座標を登録
	m_skinModelRender->SetPosition(m_pos);
	//回転率を登録
	m_skinModelRender->SetRotation(m_rot);
	//拡大率を登録
	m_skinModelRender->SetScale(m_sca);
	//各クラスのインスタンスを探す
	m_key = FindGO<Key>(NAME_KEY);
	m_game = FindGO<Game>(NAME_GAME);
	m_player = FindGO<Player>(NAME_PLAYER);

	//カメラが半回転したときの処理
	auto mainCamera = FindGO<MainCamera>(NAME_MAIN_CAMERA);
	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, CAMERA_ROT_VALUE);
		m_rotZ.Apply(m_modelOption.directionLigData[enData_Zeroth].Dir);
	});

	
	//動く物体じゃないなら座標を更新して当たり判定を付ける。
	if (!m_moveFlg) {
		m_skinModelRender->UpdateWorldMatrix();
		m_physicsStaticObject.CreateFromModel(
			*m_skinModelRender->GetModel(),
			m_skinModelRender->GetModel()->GetWorldMatrix()
		);
		m_physicsStaticObject.SetFriction(MAGNET_FRICTION);
	}

	//磁力を影響範囲を設定する。
	SetMagnetTriggerBox(m_game->GetStageNum());

	//トリガーボックスとプレイヤーが接触しないように設定する。
	m_player->GetRigidBody()->GetBody()->setIgnoreCollisionCheck(m_ghostBox.GetGhostObject(), true);
	return true;
}

Magnet::~Magnet() {
	//モデルを削除する。
	DeleteGO(m_skinModelRender);
}

void Magnet::Update() {

	//座標を登録。
	m_skinModelRender->SetPosition(m_pos);
	//プレイヤーに向かって伸びるベクトル(長さ)。
	m_length = m_player->GetPosition() - m_magnetPos;
		PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {

			//トリガーボックスと接触
			if (m_ghostBox.IsSelf(contactObject)) {

				//磁力を与える。
				SetMagnetPower();
			}
		});

}

void Magnet::SetMagnetPower() {

	//プレイヤーと自身の磁磁極が同じなら自身に向かって伸びるベクトルにする。
	if (m_magState != m_player->GetPlayerState()) {
		m_length *= REVERSE_VECTOR;
	}

	//力を定数倍する。
	float power = ReturnReciprocal(m_length.Length()) * MAGNET_POWER;

	//ベクトルを正規化する。
	m_length.Normalize();

	//正規化したベクトルに磁力を掛ける。
	m_length *= power;

	//Z方向への力を０にする。
	m_length.z = MAGNET_Z_POWER;

	//プレイヤーに力を与える。
	m_player->ReceivePower(m_length);
}

void Magnet::SetMagnetTriggerBox(int stageNum) {

	//磁力の影響範囲を決める
	Vector3 ghostPos = m_pos;
	ghostPos += MAGNET_TRIGGER_BOX_ADD_POS_BASE;
	switch (stageNum) {		//ステージ番号

	case Stage_One:


		switch (m_magnetNum) {		//磁石番号

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
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_644	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_Fifth:
			ghostPos.x -= ADD_POS_100;
			ghostPos.y -= ADD_POS_150;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_434	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_Fifteenth:
			ghostPos.x += ADD_POS_200;
			ghostPos.y -= ADD_POS_150;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_434	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_Sixteenth:
			ghostPos.x += ADD_POS_100;
			ghostPos.y += ADD_POS_100;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_644	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_Twentieth:
			ghostPos.x += ADD_POS_200;
			ghostPos.y += ADD_POS_250;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_434	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_TwentyFirst:
			ghostPos.x -= ADD_POS_100;
			ghostPos.y += ADD_POS_250;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_434	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_TwentyFifth:
			ghostPos.x -= ADD_POS_50;
			ghostPos.y -= ADD_POS_150;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_334	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_TwentyEighth:
			ghostPos.x -= ADD_POS_50;
			ghostPos.y += ADD_POS_250;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_334	//第三引数はボックスのサイズ。
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
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_344	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_Twelfth:
			ghostPos.x -= ADD_POS_50;
			ghostPos.y -= ADD_POS_200;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_344	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_Fifteenth:
			ghostPos.x += ADD_POS_150;
			ghostPos.y -= ADD_POS_200;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_344	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_TwentySecond:
			ghostPos.x += ADD_POS_50;
			ghostPos.y += ADD_POS_200;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_524	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_TwentyThird:
			ghostPos.x += ADD_POS_50;
			ghostPos.y -= ADD_POS_100;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_524	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_TwentyFourth:
			ghostPos.x += ADD_POS_50;
			ghostPos.y -= ADD_POS_50;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_354	//第三引数はボックスのサイズ。
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
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_234	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_TwentyThird:
			ghostPos.x += ADD_POS_200;
			ghostPos.y -= ADD_POS_50;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_434	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_TwentyFourth:
			ghostPos.x -= ADD_POS_100;
			ghostPos.y += ADD_POS_50;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_454	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_TwentyFifth:
		case enMagnet_TwentySixth:
			ghostPos.x += ADD_POS_50;
			ghostPos.y += ADD_POS_50;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_154	//第三引数はボックスのサイズ。
			);
			break;
		case enMagnet_TwentySeventh:
			ghostPos.x += ADD_POS_50;
			ghostPos.y += ADD_POS_50;
			m_ghostBox.CreateBox(
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_534	//第三引数はボックスのサイズ。
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
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_324	//第三引数はボックスのサイズ。
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
				ghostPos,	//第一引数は座標。
				Quaternion::Identity,		//第二引数は回転クォータニオン。
				TYPE_334	//第三引数はボックスのサイズ。
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

	//磁力の影響範囲のサンプル
	Vector3 ghostPos = m_pos;
	ghostPos += MAGNET_TRIGGER_BOX_ADD_POS_BASE;
	switch (type) {
	case Left3:
		ghostPos.x -= ADD_POS_150;
		ghostPos.y += ADD_POS_50;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_314	//第三引数はボックスのサイズ。
		);
		break;
	case Left4:
		ghostPos.x -= ADD_POS_200;
		ghostPos.y += ADD_POS_50;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_414	//第三引数はボックスのサイズ。
		);
		break;
	case Left5:
		ghostPos.x -= ADD_POS_250;
		ghostPos.y += ADD_POS_50;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_514	//第三引数はボックスのサイズ。
		);
		break;
	case Right3:
		ghostPos.x += ADD_POS_250;
		ghostPos.y += ADD_POS_50;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_314	//第三引数はボックスのサイズ。
		);
		break;
	case Right4:
		ghostPos.x += ADD_POS_300;
		ghostPos.y += ADD_POS_50;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_414	//第三引数はボックスのサイズ。
		);
		break;
	case Down2:
		ghostPos.x += ADD_POS_50;
		ghostPos.y -= ADD_POS_100;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_124	//第三引数はボックスのサイズ。
		);
		break;
	case Down3:
		ghostPos.x += ADD_POS_50;
		ghostPos.y -= ADD_POS_150;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_134	//第三引数はボックスのサイズ。
		);
		break;
	case Down4:
		ghostPos.x += ADD_POS_50;
		ghostPos.y -= ADD_POS_200;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_144	//第三引数はボックスのサイズ。
		);
		break;
	case Up2:
		ghostPos.x += ADD_POS_50;
		ghostPos.y += ADD_POS_200;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_124	//第三引数はボックスのサイズ。
		);
		break;
	case Up3:
		ghostPos.x += ADD_POS_50;
		ghostPos.y += ADD_POS_250;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_134	//第三引数はボックスのサイズ。
		);
		break;
	case Up4:
		ghostPos.x += ADD_POS_50;
		ghostPos.y += ADD_POS_300;
		m_ghostBox.CreateBox(
			ghostPos,	//第一引数は座標。
			Quaternion::Identity,		//第二引数は回転クォータニオン。
			TYPE_144	//第三引数はボックスのサイズ。
		);
		break;
	}
}