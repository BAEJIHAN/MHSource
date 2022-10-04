
#include "Tent2.h"


CTent2::CTent2()
{
	SetTypeID<CTent2>();
}

CTent2::CTent2(const CTent2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Tent2");
}

CTent2::~CTent2()
{
}

bool CTent2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Tent2Collider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("Tent2");
	m_Mesh->SetRelativeScale(0.08f, 0.08f, 0.08f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(36.f, 36.f, 18.f);
	m_ColliderBox->SetWorldPos(0.f, 18.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CTent2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTent2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTent2* CTent2::Clone()
{
	return DBG_NEW CTent2(*this);
}
