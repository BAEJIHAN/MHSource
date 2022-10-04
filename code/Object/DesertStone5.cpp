
#include "DesertStone5.h"

CDesertStone5::CDesertStone5()
{
	SetTypeID<CDesertStone5>();
}

CDesertStone5::CDesertStone5(const CDesertStone5& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStone5Box");
}

CDesertStone5::~CDesertStone5()
{
}

bool CDesertStone5::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStone5Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("DesertStone5");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(31.f, 20.f, 18.f);
	m_ColliderBox->SetWorldPos(2.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CDesertStone5::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStone5::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStone5* CDesertStone5::Clone()
{
	return DBG_NEW CDesertStone5(*this);
}
