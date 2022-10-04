
#include "TownCarriage.h"


CTownCarriage::CTownCarriage()
{
	SetTypeID<CTownCarriage>();
}

CTownCarriage::CTownCarriage(const CTownCarriage& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("TownCarriageCollider");
}

CTownCarriage::~CTownCarriage()
{
}

bool CTownCarriage::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("TownCarriageCollider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotY(true);
	m_ColliderBox->SetInheritRotZ(true);

	m_Mesh->SetMesh("TownCarriage");
	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativeRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox->Set3DExtent(7.f, 11.f, 6.f);
	m_ColliderBox->SetOffset(0.f, m_ColliderBox->GetInfo().Length.z - 2, -2.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CTownCarriage::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownCarriage::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownCarriage* CTownCarriage::Clone()
{
	return DBG_NEW CTownCarriage(*this);
}
