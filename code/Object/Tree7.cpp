
#include "Tree7.h"

CTree7::CTree7()
{
	SetTypeID<CTree7>();
}

CTree7::CTree7(const CTree7& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Tree7Box");
}

CTree7::~CTree7()
{
}

bool CTree7::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Tree7Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(10.f);
	m_ColliderBox->SetWorldPos(-4.f, 0.f, 0.f);
	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("Tree7");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CTree7::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CTree7::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTree7* CTree7::Clone()
{
	return DBG_NEW CTree7(*this);
}
