#include "stdafx.h"
#include "TklFile.h"

void TklFile::Load(const char* filePath)
{
	int ThrowNum = 0;
	float* ThrowNumF = 0;
	int version;
	//std::vector<int>ThrowNumVec;
	auto fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		return;
	}
	fread(&version, sizeof(version), 1, fp);
	//骨の数を取得。
	fread(&m_numBone, sizeof(m_numBone), 1, fp);
	m_bones.resize(m_numBone);
	for (int i = 0; i < m_numBone; i++) {
		auto& bone = m_bones.at(i);
		size_t nameCount = 0;
		//骨の名前を取得。
		fread(&nameCount, 1, 1, fp);
		bone.name = std::make_unique<char[]>(nameCount + 1);
		fread(bone.name.get(), nameCount + 1, 1, fp);
		//親のIDを取得。
		fread(&bone.parentNo, sizeof(bone.parentNo), 1, fp);
		//バインドポーズを取得。
		fread(bone.bindPose, sizeof(bone.bindPose), 1, fp);
		//バインドポーズの逆数を取得。
		fread(bone.invBindPose, sizeof(bone.invBindPose), 1, fp);

		char shadowFlag;
		fread(&shadowFlag, sizeof(shadowFlag), 1, fp);
		fread(&shadowFlag, sizeof(shadowFlag), 1, fp);
		int buffer;
		fread(&buffer, sizeof(buffer), 1, fp);
		//ThrowNumVec.resize(ThrowNum);
		for (int i = 0; i < ThrowNum; i++) {
			fread(&buffer, sizeof(ThrowNum), 1, fp);
		}
		fread(&buffer, sizeof(ThrowNum), 1, fp);
		for (int i = 0; i < ThrowNum; i++) {
			fread(&buffer, sizeof(ThrowNumF), 1, fp);
		}
		fread(&buffer, sizeof(ThrowNum), 1, fp);
		for (int i = 0; i < ThrowNum; i++) {
			fread(&buffer, sizeof(ThrowNum), 1, fp);
			fread(&buffer, sizeof(ThrowNum), 1, fp);
		}
		fread(&buffer, sizeof(ThrowNum), 1, fp);
		for (int i = 0; i < ThrowNum; i++) {
			fread(&buffer, sizeof(ThrowNum), 1, fp);
		}
		//ボーンの番号。
		bone.no = i;
	}

	fclose(fp);


	//ボーン行列を構築する。
	BuildBoneMatrices();
}

void TklFile::BuildBoneMatrices()
{
	QueryBone([&](TklFile::SBone& tksBone) {
		//バインドポーズ。
		Matrix bindPoseMatrix;
		memcpy(bindPoseMatrix.m[0], &tksBone.bindPose[0], sizeof(tksBone.bindPose[0]));
		memcpy(bindPoseMatrix.m[1], &tksBone.bindPose[1], sizeof(tksBone.bindPose[1]));
		memcpy(bindPoseMatrix.m[2], &tksBone.bindPose[2], sizeof(tksBone.bindPose[2]));
		memcpy(bindPoseMatrix.m[3], &tksBone.bindPose[3], sizeof(tksBone.bindPose[3]));
		bindPoseMatrix.m[0][3] = 0.0f;
		bindPoseMatrix.m[1][3] = 0.0f;
		bindPoseMatrix.m[2][3] = 0.0f;
		bindPoseMatrix.m[3][3] = 1.0f;

		//バインドポーズの逆行列。
		Matrix invBindPoseMatrix;
		memcpy(invBindPoseMatrix.m[0], &tksBone.invBindPose[0], sizeof(tksBone.invBindPose[0]));
		memcpy(invBindPoseMatrix.m[1], &tksBone.invBindPose[1], sizeof(tksBone.invBindPose[1]));
		memcpy(invBindPoseMatrix.m[2], &tksBone.invBindPose[2], sizeof(tksBone.invBindPose[2]));
		memcpy(invBindPoseMatrix.m[3], &tksBone.invBindPose[3], sizeof(tksBone.invBindPose[3]));
		invBindPoseMatrix.m[0][3] = 0.0f;
		invBindPoseMatrix.m[1][3] = 0.0f;
		invBindPoseMatrix.m[2][3] = 0.0f;
		invBindPoseMatrix.m[3][3] = 1.0f;

		wchar_t boneName[256];
		mbstowcs(boneName, tksBone.name.get(), 256);
		BonePtr bone = std::make_unique<Bone>(
			boneName,
			bindPoseMatrix,
			invBindPoseMatrix,
			tksBone.parentNo,
			tksBone.no
			);
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		//ボーンのバリデーションチェック。
		//maxScriptでやりたいところではあるが、とりあえずこっち。
		auto it = std::find_if(m_bones.begin(), m_bones.end(), [&](auto& bone) {return wcscmp(boneName, bone->GetName()) == 0;  });
		if (it != m_bones.end()) {
			//同名のボーンが見つかった。
			_bstr_t b(boneName);
			const char* c = b;
			TK_WARNING("同名のボーンが見つかりました。未定の動作です。データを修正してください。%s", c);
		}
#endif
		m_bones2.push_back(std::move(bone));
		});
	for (auto& bone : m_bones2) {
		if (bone->GetParentBoneNo() != -1) {
			m_bones2.at(bone->GetParentBoneNo())->AddChild(bone.get());
			//ローカルマトリクスを計算。
			const Matrix& parentMatrix = m_bones2.at(bone->GetParentBoneNo())->GetInvBindPoseMatrix();
			Matrix localMatrix;
			localMatrix = bone->GetBindPoseMatrix() * parentMatrix;
			bone->SetLocalMatrix(localMatrix);
		}
		else {
			bone->SetLocalMatrix(bone->GetBindPoseMatrix());
		}
	}


	//ボーン行列を確保
	m_boneMatrixs = std::make_unique<Matrix[]>(m_bones2.size());
	m_isInited = true;

}

void TklFile::CalcWorldTRS(Vector3& trans, Quaternion& rot, Vector3& scale)
{
	Matrix mWorld = m_worldMatrix;
	//行列から拡大率を取得する。
	scale.x = mWorld.v[0].Length();
	scale.y = mWorld.v[1].Length();
	scale.z = mWorld.v[2].Length();
	m_scale = scale;
	//行列から平行移動量を取得する。
	trans.Set(mWorld.v[3]);
	m_positoin = trans;
	//行列から拡大率と平行移動量を除去して回転量を取得する。
	mWorld.v[0].Normalize();
	mWorld.v[1].Normalize();
	mWorld.v[2].Normalize();
	mWorld.v[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
	rot.SetRotation(mWorld);
	m_rotation = rot;
}