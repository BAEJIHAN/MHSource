
#include "TownDragonHead.h"


CTownDragonHead::CTownDragonHead()
{
	SetTypeID<CTownDragonHead>();
}

CTownDragonHead::CTownDragonHead(const CTownDragonHead& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("TownDragonHeadCollider");
}

CTownDragonHead::~CTownDragonHead()
{
}

bool CTownDragonHead::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("TownDragonHeadCollider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotY(true);
	m_ColliderBox->SetInheritRotZ(true);

	m_Mesh->SetMesh("TownDragonHead");
	m_Mesh->SetRelativeScale(0.04f, 0.04f, 0.04f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox->Set3DExtent(8.f, 8.f, 10.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CTownDragonHead::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownDragonHead::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownDragonHead* CTownDragonHead::Clone()
{
	return DBG_NEW CTownDragonHead(*this);
}
