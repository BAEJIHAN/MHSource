
#include "DesertStalagmite3.h"

CDesertStalagmite3::CDesertStalagmite3()
{
	SetTypeID<CDesertStalagmite3>();
}

CDesertStalagmite3::CDesertStalagmite3(const CDesertStalagmite3& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStalagmite3Box");
}

CDesertStalagmite3::~CDesertStalagmite3()
{
}

bool CDesertStalagmite3::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStalagmite3Box");

	SetRootComponent(m_Mesh);

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("DesertStalagmite3");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(42.f, 34.f, 37.f);
	m_ColliderBox->SetOffset(11.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CDesertStalagmite3::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStalagmite3::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStalagmite3* CDesertStalagmite3::Clone()
{
	return DBG_NEW CDesertStalagmite3(*this);
}
