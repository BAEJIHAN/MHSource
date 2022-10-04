
#include "DesertStalactite1.h"

CDesertStalactite1::CDesertStalactite1()
{
	SetTypeID<CDesertStalactite1>();
}

CDesertStalactite1::CDesertStalactite1(const CDesertStalactite1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStalactite1Box");
}

CDesertStalactite1::~CDesertStalactite1()
{
}

bool CDesertStalactite1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStalactite1Box");

	SetRootComponent(m_Mesh);

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("DesertStalactite1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(35.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CDesertStalactite1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStalactite1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStalactite1* CDesertStalactite1::Clone()
{
	return DBG_NEW CDesertStalactite1(*this);
}
