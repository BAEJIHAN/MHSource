
#include "TownPumpkinMan.h"


CTownPumpkinMan::CTownPumpkinMan()
{
	SetTypeID<CTownPumpkinMan>();
}

CTownPumpkinMan::CTownPumpkinMan(const CTownPumpkinMan& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("TownPumpkinManCollider");
}

CTownPumpkinMan::~CTownPumpkinMan()
{
}

bool CTownPumpkinMan::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("TownPumpkinManCollider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("TownPumpkinMan");
	m_Mesh->SetRelativeScale(0.03f, 0.03f, 0.03f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox->Set3DExtent(6.f, 6.f, 7.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CTownPumpkinMan::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownPumpkinMan::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownPumpkinMan* CTownPumpkinMan::Clone()
{
	return DBG_NEW CTownPumpkinMan(*this);
}
