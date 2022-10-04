
#include "DesertStalagmite2.h"

CDesertStalagmite2::CDesertStalagmite2()
{
	SetTypeID<CDesertStalagmite2>();
}

CDesertStalagmite2::CDesertStalagmite2(const CDesertStalagmite2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStalagmite2Box");
}

CDesertStalagmite2::~CDesertStalagmite2()
{
}

bool CDesertStalagmite2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStalagmite2Box");

	SetRootComponent(m_Mesh);

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("DesertStalagmite2");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(14.f, 14.f, 5.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CDesertStalagmite2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStalagmite2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStalagmite2* CDesertStalagmite2::Clone()
{
	return DBG_NEW CDesertStalagmite2(*this);
}
