
#include "DesertStalactite2.h"

CDesertStalactite2::CDesertStalactite2()
{
	SetTypeID<CDesertStalactite2>();
}

CDesertStalactite2::CDesertStalactite2(const CDesertStalactite2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStalactite2Box");
}

CDesertStalactite2::~CDesertStalactite2()
{
}

bool CDesertStalactite2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStalactite2Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("DesertStalactite2");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(25.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 3.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CDesertStalactite2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStalactite2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStalactite2* CDesertStalactite2::Clone()
{
	return DBG_NEW CDesertStalactite2(*this);
}
