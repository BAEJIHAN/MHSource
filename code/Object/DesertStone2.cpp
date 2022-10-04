
#include "DesertStone2.h"

CDesertStone2::CDesertStone2()
{
	SetTypeID<CDesertStone2>();
}

CDesertStone2::CDesertStone2(const CDesertStone2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStone2Box");
}

CDesertStone2::~CDesertStone2()
{
}

bool CDesertStone2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStone2Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(17.f);
	m_ColliderBox->SetRelativePos(0.f, -1.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("DesertStone2");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CDesertStone2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStone2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStone2* CDesertStone2::Clone()
{
	return DBG_NEW CDesertStone2(*this);
}
