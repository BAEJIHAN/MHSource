
#include "Tent1.h"


CTent1::CTent1()
{
	SetTypeID<CTent1>();
}

CTent1::CTent1(const CTent1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Tent1");
}

CTent1::~CTent1()
{
}

bool CTent1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Tent1Collider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("Tent1");
	m_Mesh->SetRelativeScale(0.08f, 0.08f, 0.08f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(20.f, 30.f, 10.f);
	m_ColliderBox->SetWorldPos(0.f, 10.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CTent1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTent1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTent1* CTent1::Clone()
{
	return DBG_NEW CTent1(*this);
}
