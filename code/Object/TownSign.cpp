
#include "TownSign.h"


CTownSign::CTownSign()
{
	SetTypeID<CTownSign>();
}

CTownSign::CTownSign(const CTownSign& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("TownSignCollider");
}

CTownSign::~CTownSign()
{
}

bool CTownSign::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("TownSignCollider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("TownSign");
	m_Mesh->SetRelativeScale(0.03f, 0.03f, 0.03f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);
	m_Mesh->SetRenderStateAll("NoneCull");

	m_ColliderBox->Set3DExtent(18.f, 7.f, 8.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 0.f);
	m_ColliderBox->SetCollisionProfile("NPC");

	return true;
}

void CTownSign::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownSign::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownSign* CTownSign::Clone()
{
	return DBG_NEW CTownSign(*this);
}
