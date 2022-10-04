
#include "DesertStone1.h"

CDesertStone1::CDesertStone1()
{
	SetTypeID<CDesertStone1>();
}

CDesertStone1::CDesertStone1(const CDesertStone1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStone1Box");
}

CDesertStone1::~CDesertStone1()
{
}

bool CDesertStone1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStone1Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(17.f);
	m_ColliderBox->SetRelativePos(0.f, -1.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("DesertStone1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CDesertStone1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStone1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStone1* CDesertStone1::Clone()
{
	return DBG_NEW CDesertStone1(*this);
}
