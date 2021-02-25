#pragma once

class TklFile
{
public:
	/// <summary>
	/// �{�[���B
	/// </summary>
	struct SBone {
		std::unique_ptr<char[]> name;	//���̖��O�B
		int parentNo;					//�e�̔ԍ��B
		float bindPose[4][3];			//�o�C���h�|�[�Y�B
		float invBindPose[4][3];		//�o�C���h�|�[�Y�̋t���B
		char ShadowCasterFlag;
		char ShadowReceiverFlag;
		int no;							//�{�[���̔ԍ��B
	};
	/// <summary>
	/// TKS�t�@�C�������[�h����B
	/// </summary>
	/// <param name="filePath"></param>
	void Load(const char* filePath);
	/// <summary>
	/// �{�[���ɑ΂��ăN�G�����s���B
	/// </summary>
	/// <param name="query">�N�G���֐�</param>
	void QueryBone(std::function<void(SBone& bone)> query)
	{
		for (auto& bone : m_bones) {
			query(bone);
		}
	}
	void BuildBoneMatrices();
	void CalcWorldTRS(Vector3& trans, Quaternion& rot, Vector3& scale);

	 int GetBone(int boneNo) const
	{
		return m_bones2[boneNo]->GetParentBoneNo();
	}

	 const wchar_t* GetName(int boneNo) const { 
		return m_bones2[boneNo]->GetName();
	 }

	 int GetBoneNum() { return m_numBone; }
private:
	int m_numBone = 0;			//���̐��B
	std::vector<SBone> m_bones;	//���̃��X�g�B
	using BonePtr = std::unique_ptr<Bone>;
	std::vector<BonePtr>	m_bones2;				//�{�[���̔z��B
	std::unique_ptr<Matrix[]>	m_boneMatrixs;	//�{�[���s��B
	bool m_isInited = false;								//�������ς݁H

	Matrix			m_worldMatrix;			//���[���h�s��B
	Vector3			m_positoin;				//���̃{�[���̃��[���h��Ԃł̈ʒu�B�Ō��CalcWorldTRS�����s�����Ƃ��̌��ʂ��i�[����Ă���B
	Vector3			m_scale;				//���̃{�[���̊g�嗦�B�Ō��CalcWorldTRS�����s�����Ƃ��̌��ʂ��i�[����Ă���B
	Quaternion		m_rotation;
};

