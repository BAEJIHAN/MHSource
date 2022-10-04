
#include "DesertStone4.h"

CDesertStone4::CDesertStone4()
{
	SetTypeID<CDesertStone4>();
}

CDesertStone4::CDesertStone4(const CDesertStone4& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStone4Box");
}

CDesertStone4::~CDesertStone4()
{
}

bool CDesertStone4::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStone4Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("DesertStone4");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(13.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CDesertStone4::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStone4::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStone4* CDesertStone4::Clone()
{
	return DBG_NEW CDesertStone4(*this);
}
