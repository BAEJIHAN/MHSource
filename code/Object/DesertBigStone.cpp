
#include "DesertBigStone.h"

CDesertBigStone::CDesertBigStone()
{
	SetTypeID<CDesertBigStone>();
}

CDesertBigStone::CDesertBigStone(const CDesertBigStone& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertBigStoneBox");
}

CDesertBigStone::~CDesertBigStone()
{
}

bool CDesertBigStone::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertBigStoneBox");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(47.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("DesertBigStone1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CDesertBigStone::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertBigStone::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertBigStone* CDesertBigStone::Clone()
{
	return DBG_NEW CDesertBigStone(*this);
}
