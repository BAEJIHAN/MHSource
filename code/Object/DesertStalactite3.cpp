
#include "DesertStalactite3.h"

CDesertStalactite3::CDesertStalactite3()
{
	SetTypeID<CDesertStalactite3>();
}

CDesertStalactite3::CDesertStalactite3(const CDesertStalactite3& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStalactite3Box");
}

CDesertStalactite3::~CDesertStalactite3()
{
}

bool CDesertStalactite3::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStalactite3Box");

	SetRootComponent(m_Mesh);

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("DesertStalactite3");
	m_Mesh->SetTransformState(Transform_State::None);

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(13.f, -65.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(40.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z + 60.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CDesertStalactite3::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStalactite3::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStalactite3* CDesertStalactite3::Clone()
{
	return DBG_NEW CDesertStalactite3(*this);
}
