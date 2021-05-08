#pragma once

#include "../GameTemplate/Game/GameTime.h"
#include "../GameTemplate/Game/stdafx.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include "physics/RigidBody.h"
#include "physics/Physics.h"
#include "physics/MeshCollider.h"
#include "physics/CollisionAttr.h"
#include "physics/CharacterController.h"
#include "physics/PhysicsStaticObject.h"
#include "physics/BoxCollider.h"
#include "physics/CapsuleCollider.h"
#include "physics/SphereCollider.h"
#include "physics/DebugWireframe.h"
#include "physics/tkPhysicsObjectBase.h"
#include "physics/tkPhysicsGhostObject.h"

#include "gameObject/GameObjectManager.h"
#include "gameObject/IGameObject.h"

#include "Effekseer.h"
#include "EffekseerRendererDX12.h"
#include "effect/EffectEngine.h"
#include "effect/effect.h"

extern GameTime* g_gameTime;