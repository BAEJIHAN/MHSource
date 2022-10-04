
#include "DesertRockWall.h"

CDesertRockWall::CDesertRockWall()
{
	SetTypeID<CDesertRockWall>();
}

CDesertRockWall::CDesertRockWall(const CDesertRockWall& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("DesertRockWallBox");
}

CDesertRockWall::~CDesertRockWall()
{
}

bool CDesertRockWall::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("DesertRockWallBox");

	SetRootComponent(m_Mesh);

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("DesertRockWall");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox->Set3DExtent(110.f, 30.f, 50.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CDesertRockWall::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertRockWall::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertRockWall* CDesertRockWall::Clone()
{
	return DBG_NEW CDesertRockWall(*this);
}
