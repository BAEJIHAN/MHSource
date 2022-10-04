
#include "SmallTree3.h"

CSmallTree3::CSmallTree3()
{
	SetTypeID<CSmallTree3>();
}

CSmallTree3::CSmallTree3(const CSmallTree3& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("SmallTree3Box");
}

CSmallTree3::~CSmallTree3()
{
}

bool CSmallTree3::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("SmallTree3Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(3.f, 4.f, 3.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("SmallTree2");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CSmallTree3::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CSmallTree3::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSmallTree3* CSmallTree3::Clone()
{
	return DBG_NEW CSmallTree3(*this);
}
