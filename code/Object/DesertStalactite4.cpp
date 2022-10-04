
#include "DesertStalactite4.h"

CDesertStalactite4::CDesertStalactite4()
{
	SetTypeID<CDesertStalactite4>();
}

CDesertStalactite4::CDesertStalactite4(const CDesertStalactite4& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertStalactite4Box");
}

CDesertStalactite4::~CDesertStalactite4()
{
}

bool CDesertStalactite4::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertStalactite4Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("DesertStalactite4");
	m_Mesh->SetTransformState(Transform_State::None);

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, -60.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(45.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z + 40.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CDesertStalactite4::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertStalactite4::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertStalactite4* CDesertStalactite4::Clone()
{
	return DBG_NEW CDesertStalactite4(*this);
}
