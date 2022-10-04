
#include "TownSummerHouse.h"


CTownSummerHouse::CTownSummerHouse()
{
	SetTypeID<CTownSummerHouse>();
}

CTownSummerHouse::CTownSummerHouse(const CTownSummerHouse& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("TownSummerHouseCollider");
}

CTownSummerHouse::~CTownSummerHouse()
{
}

bool CTownSummerHouse::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("TownSummerHouseCollider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("TownSummerHouse");
	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox->Set3DExtent(13.f, 13.f, 10.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z - 2.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CTownSummerHouse::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownSummerHouse::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownSummerHouse* CTownSummerHouse::Clone()
{
	return DBG_NEW CTownSummerHouse(*this);
}
