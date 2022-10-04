
#include "TownBarrel.h"


CTownBarrel::CTownBarrel()
{
	SetTypeID<CTownBarrel>();
}

CTownBarrel::CTownBarrel(const CTownBarrel& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("TownBarrelCollider");
}

CTownBarrel::~CTownBarrel()
{
}

bool CTownBarrel::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("TownBarrelCollider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotY(true);
	m_ColliderBox->SetInheritRotZ(true);

	m_Mesh->SetMesh("TownBarrel");
	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox->Set3DExtent(2.5f, 2.f, 2.5f);
	m_ColliderBox->SetOffset(0.f, m_ColliderBox->GetInfo().Length.y, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CTownBarrel::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownBarrel::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownBarrel* CTownBarrel::Clone()
{
	return DBG_NEW CTownBarrel(*this);
}
