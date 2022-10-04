
#include "TownCheckPoint.h"


CTownCheckPoint::CTownCheckPoint()
{
	SetTypeID<CTownCheckPoint>();
}

CTownCheckPoint::CTownCheckPoint(const CTownCheckPoint& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("TownCheckPointCollider");
}

CTownCheckPoint::~CTownCheckPoint()
{
}

bool CTownCheckPoint::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("TownCheckPointCollider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotY(true);
	m_ColliderBox->SetInheritRotZ(true);

	m_Mesh->SetMesh("TownCheckPoint");
	m_Mesh->SetRelativeScale(0.04f, 0.04f, 0.04f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox->Set3DExtent(9.f, 9.f, 20.f);
	m_ColliderBox->SetWorldPos(m_ColliderBox->GetInfo().Length.x, m_ColliderBox->GetInfo().Length.z, m_ColliderBox->GetInfo().Length.y - 1.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CTownCheckPoint::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownCheckPoint::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownCheckPoint* CTownCheckPoint::Clone()
{
	return DBG_NEW CTownCheckPoint(*this);
}
