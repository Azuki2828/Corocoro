/*!
 *@brief	CGameObjectのマネージャ
 */
#include "stdafx.h"
#include "ExEngine.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::m_instance = nullptr;

GameObjectManager::GameObjectManager()
{
	if (m_instance != nullptr) {
		//インスタンスがすでに作られている。
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
	//死亡フラグがついているゲームオブジェクトを破棄する。
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
	//レンダラーを変更するならここを改造していくと良い。


	//シャドウマップにレンダリング。
		//レンダリングターゲットをシャドウマップに変更する。
	rc.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetShadowMap());
	rc.SetRenderTargetAndViewport(*RenderTarget::GetShadowMap());
	rc.ClearRenderTargetView(*RenderTarget::GetShadowMap());
	rc.SetRenderMode(RenderContext::Render_Mode::RenderMode_Shadow);


	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}

	//書き込み完了待ち。
	rc.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetShadowMap());

	// まず、レンダリングターゲットとして設定できるようになるまで待つ
	rc.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetZPrepassRenderTarget());

	// レンダリングターゲットを設定
	rc.SetRenderTargetAndViewport(*RenderTarget::GetZPrepassRenderTarget());

	// レンダリングターゲットをクリア
	rc.ClearRenderTargetView(*RenderTarget::GetZPrepassRenderTarget());
	rc.SetRenderMode(RenderContext::Render_Mode::RenderMode_ZPrepass);

	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}

	rc.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetZPrepassRenderTarget());

	// レンダリングターゲットをmainRenderTargetに変更する
		// レンダリングターゲットとして利用できるまで待つ
	rc.WaitUntilToPossibleSetRenderTarget(*RenderTarget::GetMainRenderTarget());
	// レンダリングターゲットを設定
	rc.SetRenderTargetAndViewport(*RenderTarget::GetMainRenderTarget());
	// レンダリングターゲットをクリア
	rc.ClearRenderTargetView(*RenderTarget::GetMainRenderTarget());

	rc.SetRenderMode(RenderContext::Render_Mode::RenderMode_Normal);
	for (auto& goList : m_gameObjectListArray) {
		for (auto& go : goList) {
			go->RenderWrapper(rc);
		}
	}

	//書き込み完了待ち。
	rc.WaitUntilFinishDrawingToRenderTarget(*RenderTarget::GetMainRenderTarget());

	PhysicsWorld::GetInstance()->DebubDrawWorld(rc);
}