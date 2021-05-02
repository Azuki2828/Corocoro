/*!
 *@brief	物理オブジェクトのベースクラス。
 */
#pragma once

	/*!
	 *@brief	物理オブジェクトのベースクラス。
	 *@detail
	 * template methodパターン
	 */
	class CPhysicsObjectBase{
	public:
		/*!
		* @brief	ゴーストオブジェクトを解放。
		*@detail
		* 明示的なタイミングでオブジェクトを削除したい場合に呼び出してください。
		*/
		virtual void Release() = 0;
		/*!
		* @brief	静的物理オブジェクト作成処理の共通処理。
		*/
		virtual void CreateCommon(Vector3 pos, Quaternion rot) = 0;
	public:
		/*!
		 *@brief	コンストラクタ。
		 */
		CPhysicsObjectBase()
		{
		}
		/*!
		 *@brief	デストラクタ。
		 */
		virtual ~CPhysicsObjectBase()
		{
			
		}
		/*!
		 * @brief	ボックス形状のゴーストオブジェクトを作成。
		 *@param[in]	pos			座標。
		 *@param[in]	rot			回転。
		 *@param[in]	size		サイズ。	
		 */
		void CreateBox(Vector3 pos, Quaternion rot, Vector3 size);
		/*!
		 * @brief	カプセル形状のゴーストオブジェクトを作成。
		 *@param[in]	pos			座標。
		 *@param[in]	rot			回転。
		 *@param[in]	radius		カプセルの半径。
		 *@param[in]	height		カプセルの高さ。
		 */
		void CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height );
		/*!
		* @brief	球体形状のゴーストオブジェクトを作成。
		*@param[in]	pos			座標。
		*@param[in]	rot			回転。
		*@param[in]	radius		球体の半径。
		*/
		void CreateSphere(Vector3 pos, Quaternion rot, float radius);
		/*!
		* @brief	メッシュ形状のゴーストオブジェクトを作成。
		*@param[in]	pos					座標。
		*@param[in]	rot					回転。
		*@param[in]	skinModelData		スキンモデルデータ。
		*/
		//void CreateMesh(Vector3 pos, Quaternion rot, const SkinModelData& skinModelData);
		//void CreateMesh(Vector3 pos, Quaternion rot, Vector3 scale, const SkinModel& skinModel);
		//void CreateMesh(Vector3 pos, Quaternion rot, Vector3 scale, SkinModelRender* skinModelRender);
	protected:
		std::unique_ptr<ICollider> m_collider;	//!<コライダー。
	};