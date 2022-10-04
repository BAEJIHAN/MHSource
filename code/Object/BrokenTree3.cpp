
#include "BrokenTree3.h"

CBrokenTree3::CBrokenTree3()
{
	SetTypeID<CBrokenTree3>();
}

CBrokenTree3::CBrokenTree3(const CBrokenTree3& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("BrokenTree3Collider");
}

CBrokenTree3::~CBrokenTree3()
{
}

bool CBrokenTree3::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("BrokenTree3Collider");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(7.f, 7.f, 7.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("BrokenTree3");

	m_Mesh->SetRelativeScale(0.005f, 0.005f, 0.005f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CBrokenTree3::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBrokenTree3::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CBrokenTree3* CBrokenTree3::Clone()
{
	return DBG_NEW CBrokenTree3(*this);
}
