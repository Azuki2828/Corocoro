#pragma once

enum class SoundType {
	Type_BGM,
	Type_SE,
	Type_Effect,

	Type_Num
};

class SoundManager
{

	struct SoundData {
		int soundNum = 0;							//�T�E���h�̓o�^�ԍ�
		bool roopFlg = false;						//���[�v�t���O
		const wchar_t* soundName = nullptr;			//�T�E���h�̃t�@�C���p�X
		float soundVolume = 1.0f;					//�T�E���h�̉���
		CSoundSource* sound = nullptr;				//�T�E���h�\�[�X(����)
		SoundType soundType = SoundType::Type_BGM;	//�T�E���h�̎��
	};
private:
	static SoundManager* m_soundManager;
	float m_bgmVolume = 1.0f;
	float m_seVolume = 1.0f;
	float m_effectVolume = 1.0f;
public:

	void Init(const wchar_t* filePath, int num, bool flg = false, SoundType sType = SoundType::Type_BGM, float vol = 1.0f);
	static void CreateInstance() {

		m_soundManager = new SoundManager;
	}

	static SoundManager* GetInstance() {

		return m_soundManager;
	}
	void Update();

	void Play(int num);

	bool IsPlaying(int num);

	/// <summary>
	/// ���ʂ�ݒ肷��֐��B
	/// </summary>
	/// <param name="num : �T�E���h�ԍ�"> (�P�`)</param>
	/// <param name="vol : �T�E���h�{�����[��"> (0.0f�`1.0f��ݒ�)</param>
	void SetSoundSourceVolume(int num, float vol);

	void SetRoopFlg(int num, bool flg);
	
	void Release(int num);

	void SetVolume(float vol,SoundType type = SoundType::Type_BGM) {
		switch (type) {
		case SoundType::Type_BGM:
			m_bgmVolume = vol;
			break;
		case SoundType::Type_SE:
			m_seVolume = vol;
			break;
		case SoundType::Type_Effect:
			m_effectVolume = vol;
			break;
		}
	}
	std::vector<SoundData> m_soundData;
};

