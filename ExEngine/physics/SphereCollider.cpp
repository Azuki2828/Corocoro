/*!
* @brief	���̃R���C�_�[�B
*/
#include "SphereCollider.h"
#include "stdafx.h"


void SphereCollider::Create(const float radius)
{
	m_shape = std::make_unique<btSphereShape>(radius);
}
