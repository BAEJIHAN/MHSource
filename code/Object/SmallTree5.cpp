
#include "SmallTree5.h"

CSmallTree5::CSmallTree5()
{
	SetTypeID<CSmallTree5>();
}

CSmallTree5::CSmallTree5(const CSmallTree5& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("SmallTree5Box");
}

CSmallTree5::~CSmallTree5()
{
}

bool CSmallTree5::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("SmallTree5Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(3.f, 4.f, 3.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("SmallTree5");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CSmallTree5::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CSmallTree5::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSmallTree5* CSmallTree5::Clone()
{
	return DBG_NEW CSmallTree5(*this);
}
