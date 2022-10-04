
#include "TownShadeScreen.h"


CTownShadeScreen::CTownShadeScreen()
{
	SetTypeID<CTownShadeScreen>();
}

CTownShadeScreen::CTownShadeScreen(const CTownShadeScreen& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox1 = (CColliderBox3D*)FindComponent("TownShadeScreenCollider1");
	m_ColliderBox2 = (CColliderBox3D*)FindComponent("TownShadeScreenCollider2");
	m_ColliderBox3 = (CColliderBox3D*)FindComponent("TownShadeScreenCollider3");
}

CTownShadeScreen::~CTownShadeScreen()
{
}

bool CTownShadeScreen::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox1 = CreateComponent<CColliderBox3D>("TownShadeScreenCollider1");
	m_ColliderBox2 = CreateComponent<CColliderBox3D>("TownShadeScreenCollider2");
	m_ColliderBox3 = CreateComponent<CColliderBox3D>("TownShadeScreenCollider3");

	m_Mesh->AddChild(m_ColliderBox1);
	m_Mesh->AddChild(m_ColliderBox2);
	m_Mesh->AddChild(m_ColliderBox3);

	m_ColliderBox1->SetInheritRot(true);
	m_ColliderBox2->SetInheritRot(true);
	m_ColliderBox3->SetInheritRot(true);

	m_Mesh->SetMesh("TownShadeScreen");
	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	m_ColliderBox1->Set3DExtent(20.f, 2.f, 10.f);
	m_ColliderBox1->SetWorldPos(0.f, m_ColliderBox1->GetInfo().Length.z, 0.f);
	m_ColliderBox1->SetCollisionProfile("FieldObj");

	m_ColliderBox2->Set3DExtent(2.f, 6.f, 10.f);
	m_ColliderBox2->SetWorldPos(-20.f, m_ColliderBox2->GetInfo().Length.z, -3.f);
	m_ColliderBox2->SetCollisionProfile("FieldObj");

	m_ColliderBox3->Set3DExtent(2.f, 6.f, 10.f);
	m_ColliderBox3->SetWorldPos(20.f, m_ColliderBox3->GetInfo().Length.z, -3.f);
	m_ColliderBox3->SetCollisionProfile("FieldObj");

	return true;
}

void CTownShadeScreen::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTownShadeScreen::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CTownShadeScreen* CTownShadeScreen::Clone()
{
	return DBG_NEW CTownShadeScreen(*this);
}
