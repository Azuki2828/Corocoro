#pragma once
class ResultLevel2D;
class Game;
class SaveData;

class ResultScene : public IGameObject
{
private:
	bool Start();
	~ResultScene();
	void Update();

public:
	/**
	 * @brief 記録を取得する関数。
	 * @return 記録
	*/
	float GetTime()
	{
		return m_time;
	}

	/**
	 * @brief 今回のタイムを記録する関数
	 * @param time 今回のタイム
	*/
	void SetTime(const float time) {

		m_time = time;
	}

	/**
	 * @brief ステージ番号を設定する関数。
	 * @param num ステージ番号
	*/
	void SetStageNum(int num) {
		m_stageNum = num;
	}
	/**
	 * @brief ステージ番号を取得する関数。
	 * @return ステージ番号
	*/
	int GetStageNum() {
		return m_stageNum;
	}
	
private:
	//ボタンを選択するための列挙型
	enum Select {
		enSelect_TitleBackButton,
		enSelect_EndButton,

		enSelect_Num
	};
	bool m_scaleUpFlag = true;						//ボタンが拡大していくフラグ
	bool m_newRecordFlg = false;					//新記録フラグ
	int m_nowSelect = 0;							//列挙の値を格納する変数。はじめは「はじめる」ボタンの0。
	int m_stageNum = 0;								//ステージ番号
	float m_time = 0.0f;							//記録を保持する変数。
	float m_nowTime = 0.0f;							//今回の記録
	float m_bestTime = 0.0f;						//最高記録
	float m_fontScale = 0.25f;						//タイトルボタンのサイズ
	float m_fontScale2 = 0.2f;						//終了ボタンのサイズ
	float m_recordPos = 1100.0f;					//新記録！の座標
	Vector3 m_scale = Vector3::Zero;				//ボタンのサイズ
	Vector3 m_standardScale[enSelect_Num];			//それぞれのボタンの初期サイズ

	/**
	 * @brief それぞれのクラスのポインタ
	*/

	Game* m_game = nullptr;
	SaveData* m_saveData = nullptr;
	ResultLevel2D* m_resultLevel2D = nullptr;
	SpriteRender* m_spriteRender = nullptr;
	FontRender* m_fontNowTime = nullptr;
	FontRender* m_fontBestTime = nullptr;
	FontRender* m_fontRender = nullptr;
};