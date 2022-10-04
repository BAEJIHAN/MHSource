
#include "TownRampart.h"


CTownRampart::CTownRampart()
{
	SetTypeID<CTownRampart>();
}

CTownRampart::CTownRampart(const CTownRampart& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("TownRampartCollider");
}

CTownRampart::~CTownRampart()
{
}

bool CTownRampart::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("TownRampartCollider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("TownRampart");
	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox->Set3DExtent(16.f, 2.f, 10.f);
	m_ColliderBox->SetWorldPos(m_ColliderBox->GetInfo().Length.x, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CTownRampart::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownRampart::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownRampart* CTownRampart::Clone()
{
	return DBG_NEW CTownRampart(*this);
}
