/*!
 * @brief	ゴーストオブジェクト。
 */

#pragma once
#include "physics/tkPhysicsObjectBase.h"

	/*!
	 * @brief	ゴーストオブジェクト
	 *@detail
	 * ゴーストオブジェクトは剛体がすり抜けるあたり判定のオブジェクトです。
	 * キャラクターのチェックポイント通過判定、クリア判定などの
	 * キャラクターがすり抜ける必要のあるあたり判定に使えます。
	 */
	class CPhysicsGhostObject : public CPhysicsObjectBase{
	public:
		~CPhysicsGhostObject()
		{
			Release();
		}
		/*!
		* @brief	ゴーストオブジェクトを解放。
		*@detail
		* 明示的なタイミングでゴーストオブジェクトを削除したい場合に呼び出してください。
		*/
		void Release() override final;
		/*!
		* @brief	引数で渡されたゴーストオブジェクトが自分自身かどうか判定。
		*/
		bool IsSelf(const btCollisionObject& ghost) const
		{
			return &ghost == &m_ghostObject;
		}
		/*!
		* @brief	座標を設定。
		*/
		void SetPosition(const Vector3& pos)
		{
			auto& btTrans = m_ghostObject.getWorldTransform();
			btVector3 btPos;
			pos.CopyTo(btPos);
			btTrans.setOrigin(btPos);
		}
		/*!
		* @brief	回転を設定。
		*/
		void SetRotation(const Quaternion& rot)
		{
			auto& btTrans = m_ghostObject.getWorldTransform();
			btQuaternion btRot;
			rot.CopyTo(btRot);
			btTrans.setRotation(btRot);
		}
		void	setIgnoreCollisionCheck(const btCollisionObject* co, bool ignoreCollisionCheck) {
			m_ghostObject.setIgnoreCollisionCheck(co, ignoreCollisionCheck);
		}
		btGhostObject* GetGhostObject() { return &m_ghostObject; }
	private:
		/*!
		* @brief	ゴースト作成処理の共通処理。
		*/
		void CreateCommon(Vector3 pos, Quaternion rot) override;
	private:
		bool						m_isRegistPhysicsWorld = false;	//!<物理ワールドに登録しているかどうかのフラグ。
		btGhostObject				m_ghostObject;	//!<ゴースト
	};