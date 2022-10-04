
#include "SmallTree4.h"

CSmallTree4::CSmallTree4()
{
	SetTypeID<CSmallTree4>();
}

CSmallTree4::CSmallTree4(const CSmallTree4& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("SmallTree4Box");
}

CSmallTree4::~CSmallTree4()
{
}

bool CSmallTree4::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("SmallTree4Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(3.f, 4.f, 3.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("SmallTree4");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CSmallTree4::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CSmallTree4::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSmallTree4* CSmallTree4::Clone()
{
	return DBG_NEW CSmallTree4(*this);
}
