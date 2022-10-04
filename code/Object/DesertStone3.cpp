
#include "DesertStone3.h"

CDesertStone3::CDesertStone3()
{
	SetTypeID<CDesertStone3>();
}

CDesertStone3::CDesertStone3(const CDesertStone3& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStone3Box");
}

CDesertStone3::~CDesertStone3()
{
}

bool CDesertStone3::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStone3Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(12.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("DesertStone3");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CDesertStone3::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStone3::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStone3* CDesertStone3::Clone()
{
	return DBG_NEW CDesertStone3(*this);
}
