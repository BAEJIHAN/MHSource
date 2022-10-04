
#include "Tree4.h"

CTree4::CTree4()
{
	SetTypeID<CTree4>();
}

CTree4::CTree4(const CTree4& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Tree4Box");
}

CTree4::~CTree4()
{
}

bool CTree4::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Tree4Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(45.f, 34.f, 34.f);
	m_ColliderBox->SetWorldPos(12.f, 0.f, 20.f);
	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("Tree4");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CTree4::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CTree4::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTree4* CTree4::Clone()
{
	return DBG_NEW CTree4(*this);
}
