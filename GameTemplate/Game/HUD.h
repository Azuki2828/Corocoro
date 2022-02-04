#pragma once
#include "SpriteRender.h"
#include <vector>

namespace {

	const int RESET_SPRITE_NUM = 0;				//初期のスプライト数
}
struct SpriteData {
	int spriteNum = 0;							//登録番号
	Sprite sprite;								//スプライトクラスのオブジェクト
	SpriteInitData initData;					//スプライトのデータ
	Vector3 pos = Vector3::Zero;				//座標
	Quaternion rot = Quaternion::Identity;		//回転率
	Vector3 sca = Vector3::One;					//拡大率
	Vector4 mulColor = Vector4::White;			//乗算カラー
	bool activate = true;						//有効フラグ
	int prio = 0;								//表示優先度
};

class HUD
{
public:
	/**
	 * @brief HUDクラスのインスタンスを作成する関数。
	*/
	static void CreateHUD() {
		m_hud = new HUD;
	}
	/**
	 * @brief HUDクラスのインスタンスを取得する関数。
	 * @return HUDクラスのインスタンス
	*/
	static HUD* GetHUD() {
		return m_hud;
	}
	/**
	 * @brief 初期化関数。
	 * @param num スプライト番号
	 * @param filepath ファイルパス
	 * @param width 幅
	 * @param height 高さ
	 * @param mode アルファブレンディングのモード
	 * @param prio 表示優先度
	*/
	void Init(int num, const char* filepath, float width, float height, AlphaBlendMode mode = AlphaBlendMode::AlphaBlendMode_Trans, int prio = 0);

	/**
	 * @brief スプライトのデータをを全て解放する関数。
	*/
	void Release();

	/**
	 * @brief 描画関数。
	 * @param rc レンダーコンテキスト
	*/
	void Draw(RenderContext& rc);

	/**
	 * @brief 座標を設定する関数。
	 * @param num スプライト番号
	 * @param pos 座標
	*/
	void SetPosition(int num,const Vector3& pos) { 
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->pos = pos;
				break;
			}
		}
	}

	/**
	 * @brief 回転率を設定する関数。
	 * @param num スプライト番号
	 * @param rot 回転率
	*/
	void SetRotation(int num, const Quaternion& rot) { 
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->rot = rot;
				break;
			}
		}
	}

	/**
	 * @brief 拡大率を設定する関数。
	 * @param num スプライト番号
	 * @param sca 拡大率
	*/
	void SetScale(int num, const Vector3& sca) { 
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->sca = sca;
				break;
			}
		}
	}
	
	/**
	 * @brief 拡大率を取得する関数。
	 * @param num スプライト番号
	 * @return 拡大率
	*/
	Vector3 GetScale(int num) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				return m_spriteData[i]->sca;
				break;
			}
		}
	}

	/**
	 * @brief 乗算カラーを設定する関数。
	 * @param num スプライト番号
	 * @param mulCol 乗算カラー
	*/
	void SetMulColor(int num, const Vector4& mulCol) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->mulColor = mulCol;
				break;
			}
		}
	}

	/**
	 * @brief スプライトを無効にする関数。
	 * @param num スプライト番号
	*/
	void Deactivate(int num) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->activate = false;
				break;
			}
		}
	}

	/**
	 * @brief スプライトを有効にする関数。
	 * @param num スプライト番号
	*/
	void Activate(int num) {
		for (int i = 0; i < m_spriteData.size(); i++) {
			if (m_spriteData[i]->spriteNum == num) {
				m_spriteData[i]->activate = true;
				break;
			}
		}
	}

	/**
	 * @brief アップデート関数。main関数で呼ぶ必要がある。
	*/
	void Update();

private:
	int m_maxPriority = 0;
	static HUD* m_hud;							//HUDクラスのインスタンス
	std::vector<SpriteData*> m_spriteData;		//スプライトの総データ。
};

