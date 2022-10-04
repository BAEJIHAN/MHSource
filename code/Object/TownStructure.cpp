
#include "TownStructure.h"


CTownStructure::CTownStructure()
{
	SetTypeID<CTownStructure>();
}

CTownStructure::CTownStructure(const CTownStructure& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox1 = (CColliderBox3D*)FindComponent("TownStructureCollider1");
	m_ColliderBox2 = (CColliderBox3D*)FindComponent("TownStructureCollider2");
}

CTownStructure::~CTownStructure()
{
}

bool CTownStructure::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox1 = CreateComponent<CColliderBox3D>("TownStructureCollider1");
	m_ColliderBox2 = CreateComponent<CColliderBox3D>("TownStructureCollider2");

	m_Mesh->AddChild(m_ColliderBox1);
	m_Mesh->AddChild(m_ColliderBox2);

	m_ColliderBox1->SetInheritRot(true);
	m_ColliderBox2->SetInheritRot(true);

	m_Mesh->SetMesh("TownStructure");
	m_Mesh->SetRelativeScale(0.03f, 0.03f, 0.03f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox1->Set3DExtent(2.5f, 2.f, 2.5f);
	m_ColliderBox1->SetWorldPos(-40.f, m_ColliderBox1->GetInfo().Length.z, 0.f);
	m_ColliderBox1->SetCollisionProfile("FieldObj");

	m_ColliderBox2->Set3DExtent(2.5f, 2.f, 2.5f);
	m_ColliderBox2->SetWorldPos(40.f, m_ColliderBox2->GetInfo().Length.z, 0.f);
	m_ColliderBox2->SetCollisionProfile("FieldObj");

	return true;
}

void CTownStructure::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownStructure::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownStructure* CTownStructure::Clone()
{
	return DBG_NEW CTownStructure(*this);
}
