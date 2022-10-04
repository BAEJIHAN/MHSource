
#include "TownPassage.h"


CTownPassage::CTownPassage()
{
	SetTypeID<CTownPassage>();
}

CTownPassage::CTownPassage(const CTownPassage& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox1 = (CColliderBox3D*)FindComponent("TownPassageCollider1");
	m_ColliderBox2 = (CColliderBox3D*)FindComponent("TownPassageCollider2");
}

CTownPassage::~CTownPassage()
{
}

bool CTownPassage::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox1 = CreateComponent<CColliderBox3D>("TownPassageCollider1");
	m_ColliderBox2 = CreateComponent<CColliderBox3D>("TownPassageCollider2");

	m_Mesh->AddChild(m_ColliderBox1);
	m_Mesh->AddChild(m_ColliderBox2);

	m_ColliderBox1->SetInheritRotX(true);
	m_ColliderBox1->SetInheritRotY(true);
	m_ColliderBox1->SetInheritRotZ(true);

	m_ColliderBox2->SetInheritRotX(true);
	m_ColliderBox2->SetInheritRotY(true);
	m_ColliderBox2->SetInheritRotZ(true);

	m_Mesh->SetMesh("TownPassage");
	m_Mesh->SetRelativeScale(0.04f, 0.04f, 0.04f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox1->Set3DExtent(5.f, 20.f, 17.f);
	m_ColliderBox1->SetWorldPos(-18.f, m_ColliderBox1->GetInfo().Length.z, 0.f);
	m_ColliderBox1->SetCollisionProfile("FieldObj");

	m_ColliderBox2->Set3DExtent(5.f, 20.f, 17.f);
	m_ColliderBox2->SetWorldPos(18.f, m_ColliderBox2->GetInfo().Length.z, 0.f);
	m_ColliderBox2->SetCollisionProfile("FieldObj");

	return true;
}

void CTownPassage::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownPassage::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownPassage* CTownPassage::Clone()
{
	return DBG_NEW CTownPassage(*this);
}
