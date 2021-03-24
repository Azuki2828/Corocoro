#include "stdafx.h"
#include "system/system.h"
#include "Player.h"
#include "Background.h"
#include "MainCamera.h"
#include "Background2.h"
#include "PhysicsBall.h"
#include "Seesaw.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̃C���X�^���X���쐬����B
	GameObjectManager::CreateInstance();
	PhysicsWorld::CreateInstance();
	CSoundEngine::CreateInstance();
	CSoundEngine::GetInstance()->Init();

	//�v���C���[�𐶐��B
	NewGO<Player>(0,"player");
	//�J�����𐶐��B
	NewGO<MainCamera>(0);
	//�w�i�𐶐��B
	NewGO<Background>(0);
	//NewGO<Background2>(0);
	//NewGO<PhysicsBall>(0);
	//NewGO<Seesaw>(0);
	

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();
		

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		
		GameObjectManager::GetInstance()->ExecuteUpdate();
		//�������[���h�̍X�V�B
		PhysicsWorld::GetInstance()->Update(g_gameTime->GetFrameDeltaTime());
		GameObjectManager::GetInstance()->ExecuteRender(renderContext);

		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		g_engine->EndFrame();
	}
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���폜�B
	GameObjectManager::DeleteInstance();
	return 0;
}

