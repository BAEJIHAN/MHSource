
#include "TownTunnel.h"


CTownTunnel::CTownTunnel()
{
	SetTypeID<CTownTunnel>();
}

CTownTunnel::CTownTunnel(const CTownTunnel& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox1 = (CColliderBox3D*)FindComponent("TownTunnelCollider1");
	m_ColliderBox2 = (CColliderBox3D*)FindComponent("TownTunnelCollider2");
	m_ColliderBox3 = (CColliderBox3D*)FindComponent("TownTunnelCollider3");
}

CTownTunnel::~CTownTunnel()
{
}

bool CTownTunnel::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox1 = CreateComponent<CColliderBox3D>("TownTunnelCollider1");
	m_ColliderBox2 = CreateComponent<CColliderBox3D>("TownTunnelCollider2");
	m_ColliderBox3 = CreateComponent<CColliderBox3D>("TownTunnelCollider3");


	m_Mesh->AddChild(m_ColliderBox1);
	m_Mesh->AddChild(m_ColliderBox2);
	m_Mesh->AddChild(m_ColliderBox3);

	m_ColliderBox1->SetInheritRotX(true);
	m_ColliderBox1->SetInheritRotY(true);
	m_ColliderBox1->SetInheritRotZ(true);
	m_ColliderBox2->SetInheritRotX(true);
	m_ColliderBox2->SetInheritRotY(true);
	m_ColliderBox2->SetInheritRotZ(true);
	m_ColliderBox3->SetInheritRotX(true);
	m_ColliderBox3->SetInheritRotY(true);
	m_ColliderBox3->SetInheritRotZ(true);

	m_Mesh->SetMesh("TownTunnel");
	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox1->Set3DExtent(2.5f, 9.f, 10.f);
	m_ColliderBox1->SetWorldPos(-20.f, m_ColliderBox1->GetInfo().Length.z, 4.f);
	m_ColliderBox1->SetCollisionProfile("FieldObj");

	m_ColliderBox2->Set3DExtent(2.5f, 9.f, 10.f);
	m_ColliderBox2->SetWorldPos(20.f, m_ColliderBox2->GetInfo().Length.z, 4.f);
	m_ColliderBox2->SetCollisionProfile("FieldObj");
	
	m_ColliderBox3->Set3DExtent(6.f, 3.f, 6.f);
	m_ColliderBox3->SetWorldPos(-10.f, m_ColliderBox3->GetInfo().Length.z, -4.f);
	m_ColliderBox3->SetCollisionProfile("FieldObj");

	return true;
}

void CTownTunnel::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownTunnel::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownTunnel* CTownTunnel::Clone()
{
	return DBG_NEW CTownTunnel(*this);
}