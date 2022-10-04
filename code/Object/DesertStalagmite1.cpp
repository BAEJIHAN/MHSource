
#include "DesertStalagmite1.h"

CDesertStalagmite1::CDesertStalagmite1()
{
	SetTypeID<CDesertStalagmite1>();
}

CDesertStalagmite1::CDesertStalagmite1(const CDesertStalagmite1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStalagmite1Box");
}

CDesertStalagmite1::~CDesertStalagmite1()
{
}

bool CDesertStalagmite1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStalagmite1Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_Mesh->InheritRotation(true);

	m_Mesh->SetMesh("DesertStalagmite1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(20.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CDesertStalagmite1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStalagmite1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStalagmite1* CDesertStalagmite1::Clone()
{
	return DBG_NEW CDesertStalagmite1(*this);
}
