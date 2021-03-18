#include "stdafx.h"
#include "Background.h"
#include "Magnet.h"
#include "Key.h"

bool Background::Start()
{
	m_magnet.resize(1);
	int sampleNum = 0;

	/*const char* MagnetName[] = {
		"Magnet_N_01",
		"Magnet_N_02",
		"Magnet_N_03",
		"Magnet_N_04",
		"Magnet_N_05",
		"Magnet_N_06",
		"Magnet_N_move_01",
		"Magnet_Nplus_01",
		"Magnet_S_01",
		"Magnet_S_02",
		"Magnet_S_03",
		"Magnet_Splus_01",
		"MagnetHoge",
	};*/


	//�w�i�摜���������B
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->Init("Assets/Image/sample.dds", 1980.0f, 1080.0f);


	//���ꂪlevel��Load�̊�ՁB
	//����̃I�u�W�F�N�g���w�肷��i�����ł����t�b�N�j�ꍇ�́A���O��������Ȃ̂ˁB
	m_level.Init("Assets/level/stage02.tkl", [&](LevelObjectData& objData) {

		/*if (objData.EqualObjectName(L"SampleMagnet_N_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init(MagnetName[sampleNum]);
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"SampleMagnet_S_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init(MagnetName[sampleNum]);
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}*/

		if (objData.EqualObjectName(L"Key") == true) {
			if (m_key == nullptr) {
				m_key = NewGO<Key>(0,"key");
			}
			m_key->InitKey("Key");
			m_key->SetPositionKey(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"KeyBox") == true) {
			if (m_key == nullptr) {
				m_key = NewGO<Key>(0,"key");
			}
			m_key->InitDoor("KeyBox");
			m_key->SetPositionDoor(objData.position);
			return true;
		}
		//else if (objData.EqualObjectName(L"") == true) {
		//	return true;
		//}
		else if (objData.EqualObjectName(L"Magnet_N_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_01");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_02") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_02");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_03") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_03");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_04") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_04");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_05") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_05");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_06") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N();
			m_magnet[sampleNum]->Init("Magnet_N_06");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N_07") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N(true);
			m_magnet[sampleNum]->Init("Magnet_N_07");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_Nplus_02") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N(true);

			m_magnet[sampleNum]->Init("Magnet_Nplus_02");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_Nplus_move_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N(true);
			m_magnet[sampleNum]->Init("Magnet_Nplus_move_01");

			Vector3 movePos_front = objData.position;
			movePos_front.x -= 900.0f;
			Vector3 movePos_back = objData.position;
			m_magnet[sampleNum]->SetMove(movePos_front, movePos_back);
			m_magnet[sampleNum]->SetPosition(movePos_front);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_Nplus_move_02") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N(true);
			m_magnet[sampleNum]->Init("Magnet_Nplus_move_02");

			Vector3 movePos_front = objData.position;
			movePos_front.x -= 400.0f;
			Vector3 movePos_back = objData.position;
			m_magnet[sampleNum]->SetMove(movePos_front, movePos_back);
			m_magnet[sampleNum]->SetPosition(movePos_front);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_Nplus_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_N(true);
			m_magnet[sampleNum]->Init("Magnet_Nplus_01");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init("Magnet_S_01");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S_02") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init("Magnet_S_02");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S_03") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S();
			m_magnet[sampleNum]->Init("Magnet_S_03");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S_04") == true) {
		m_magnet.push_back(*(m_magnet.end() - 1));

		m_magnet[sampleNum] = NewGO<Magnet>(0);
		m_magnet[sampleNum]->SetState_S(true);
		m_magnet[sampleNum]->Init("Magnet_S_04");
		m_magnet[sampleNum]->SetPosition(objData.position);
		sampleNum++;
		return true;
		}
		else if (objData.EqualObjectName(L"magnet_S_05") == true) {
		m_magnet.push_back(*(m_magnet.end() - 1));

		m_magnet[sampleNum] = NewGO<Magnet>(0);
		m_magnet[sampleNum]->SetState_S();
		m_magnet[sampleNum]->Init("magnet_S_05");
		m_magnet[sampleNum]->SetPosition(objData.position);
		sampleNum++;
		return true;
		}
		else if (objData.EqualObjectName(L"Magnet_Splus_01") == true) {
			m_magnet.push_back(*(m_magnet.end() - 1));
			m_magnet[sampleNum] = NewGO<Magnet>(0);
			m_magnet[sampleNum]->SetState_S(true);

			m_magnet[sampleNum]->Init("Magnet_Splus_01");
			m_magnet[sampleNum]->SetPosition(objData.position);
			sampleNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"move_01") == true) {
			return true;
		}
		else if (objData.EqualObjectName(L"KeyBox") == true) {
			return true;
		}
		return false;//level�̃I�u�W�F�N�g�����̂܂܃��[�h�B
	});
	//ModelInitData initData;
	//initData.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	////�V�F�[�_�[�t�@�C���̃t�@�C���p�X���w�肷��B
	//initData.m_fxFilePath = "Assets/shader/model.fx";
	////���_�V�F�[�_�[�̃G���g���[�|�C���g
	//initData.m_vsEntryPointFunc = "VSMain";
	//m_model.Init(initData);
	//
	////���b�V���R���C�_�[���쐬�B
	//m_physicsStaticObject.CreateFromModel(m_model, m_model.GetWorldMatrix());
	return true;
}
void Background::Update()
{

}
void Background::Render(RenderContext& rc)
{
	m_level.Draw(rc);
	m_model.Draw(rc);
}