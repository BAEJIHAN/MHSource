
#include "SmallTree2.h"

CSmallTree2::CSmallTree2()
{
	SetTypeID<CSmallTree2>();
}

CSmallTree2::CSmallTree2(const CSmallTree2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("SmallTree2Box");
}

CSmallTree2::~CSmallTree2()
{
}

bool CSmallTree2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("SmallTree2Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(3.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("SmallTree2");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CSmallTree2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CSmallTree2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CSmallTree2* CSmallTree2::Clone()
{
	return DBG_NEW CSmallTree2(*this);
}
