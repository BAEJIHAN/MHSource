
#include "DesertSmallStone.h"

CDesertSmallStone::CDesertSmallStone()
{
	SetTypeID<CDesertSmallStone>();
}

CDesertSmallStone::CDesertSmallStone(const CDesertSmallStone& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertSmallStoneBox");
}

CDesertSmallStone::~CDesertSmallStone()
{
}

bool CDesertSmallStone::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertSmallStoneBox");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(9.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("DesertSmallStone1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CDesertSmallStone::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertSmallStone::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertSmallStone* CDesertSmallStone::Clone()
{
	return DBG_NEW CDesertSmallStone(*this);
}
