/*!
 *@brief	CGameObject�̃}�l�[�W��
 */
#include "stdafx.h"
#include "ExEngine.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::m_instance = nullptr;

GameObjectManager::GameObjectManager()
{
	if (m_instance != nullptr) {
		//�C���X�^���X�����łɍ���Ă���B
		std::abort();
	}
	m_instance = this;
}
GameObjectManager::~GameObjectManager()
{
	m_instance = nullptr;
}
void GameObjectManager::ExecuteUpdate()
{	
	//���S�t���O�����Ă���Q�[���I�u�W�F�N�g��j������B
	for (auto& goList : m_gameObjectListArray) {
		goList.remove_if([&](IGameObject* go) {	
			if (go->IsDead()) {
				delete go;
				return true;
			}
			return false;	 
		});
	}

	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->StartWrapper();
		}
	}


	switch (g_engine->GetGameState()) {
	case GameState::State_Game:
		for (auto& goList : m_gameObjectListArray) {
			for (auto& go : goList) {
				go->UpdateWrapper();
			}
		}
		break;
	case GameState::State_Pause:
		for (auto& goList : m_gameObjectListArray) {
			for (auto& go : goList) {
				go->PauseUpdateWrapper();
			}
		}
		break;
	case GameState::State_Dead:
		for (auto& goList : m_gameObjectListArray) {
			for (auto& go : goList) {
				go->DeadUpdateWrapper();
			}
		}
		break;
	case GameState::State_Free:
		for (auto& goList : m_gameObjectListArray) {
			for (auto& go : goList) {
				go->FreeUpdateWrapper();
			}
		}
		break;
	}
}
void GameObjectManager::ExecuteRender(RenderContext& rc)
{
	//�����_���[��ύX����Ȃ炱�����������Ă����Ɨǂ��B


	//�V���h�E�}�b�v�Ƀ����_�����O�B
		//�����_�����O�^�[�Q�b�g���V���h�E�}�b�v�ɕύX����B
	rc.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetShadowMap());
	rc.SetRenderTargetAndViewport(*RenderTarget::GetShadowMap());
	rc.ClearRenderTargetView(*RenderTarget::GetShadowMap());
	rc.SetRenderMode(RenderContext::Render_Mode::RenderMode_Shadow);


	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}

	//�������݊����҂��B
	rc.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetShadowMap());

	// �܂��A�����_�����O�^�[�Q�b�g�Ƃ��Đݒ�ł���悤�ɂȂ�܂ő҂�
	rc.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetZPrepassRenderTarget());

	// �����_�����O�^�[�Q�b�g��ݒ�
	rc.SetRenderTargetAndViewport(*RenderTarget::GetZPrepassRenderTarget());

	// �����_�����O�^�[�Q�b�g���N���A
	rc.ClearRenderTargetView(*RenderTarget::GetZPrepassRenderTarget());
	rc.SetRenderMode(RenderContext::Render_Mode::RenderMode_ZPrepass);

	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}

	rc.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetZPrepassRenderTarget());

	// �����_�����O�^�[�Q�b�g��mainRenderTarget�ɕύX����
		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
	rc.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetMainRenderTarget());
	// �����_�����O�^�[�Q�b�g��ݒ�
	rc.SetRenderTargetAndViewport(*RenderTarget::GetMainRenderTarget());
	// �����_�����O�^�[�Q�b�g���N���A
	rc.ClearRenderTargetView(*RenderTarget::GetMainRenderTarget());

	rc.SetRenderMode(RenderContext::Render_Mode::RenderMode_Normal);
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}

	//�������݊����҂��B
	rc.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetMainRenderTarget());

	PhysicsWorld::GetInstance()->DebubDrawWorld(rc);
}