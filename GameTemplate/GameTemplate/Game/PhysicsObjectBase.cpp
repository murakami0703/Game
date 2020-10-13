#include "stdafx.h"
#include "PhysicsObjectBase.h"
#include "BoxCollider.h"
#include "Physics/CapsuleCollider.h"
#include "Physics/MeshCollider.h"
#include "SphereCollider.h"

using namespace std;
PhysicsObjectBase::PhysicsObjectBase()
{
}


PhysicsObjectBase::~PhysicsObjectBase()
{
}

void PhysicsObjectBase::CreateBox(CVector3 pos, CQuaternion rot, CVector3 size)
{
	Release();
	auto boxCollider = make_unique<BoxCollider>();
	boxCollider->Create(size);
	m_collider = move(boxCollider);
	CreateCommon(pos, rot);
}
void PhysicsObjectBase::CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height)
{
	Release();
	auto capusuleCollider = make_unique<CapsuleCollider>();
	capusuleCollider->Create(radius, height);
	m_collider = move(capusuleCollider);
	CreateCommon(pos, rot);
}

void PhysicsObjectBase::CreateSphere(CVector3 pos, CQuaternion rot, float radius)
{
	Release();
	auto sphereCollider = make_unique<SphereCollider>();
	sphereCollider->Create(radius);
	m_collider = move(sphereCollider);
	CreateCommon(pos, rot);
}

void PhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, SkinModelRender* skinModelRender)
{
	CreateMesh(pos, rot, scale, skinModelRender->GetSkinModel());
}
void PhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, const SkinModel& skinModel)
{
	Release();
	CMatrix mScale;
	mScale.MakeScaling(scale);
	auto meshCollider = make_unique<MeshCollider>();
	meshCollider->CreateFromSkinModel(skinModel, &mScale);
	m_collider = move(meshCollider);
	CreateCommon(
		pos,
		rot
	);

}