
#include "GrassRock6.h"

CGrassRock6::CGrassRock6()
{
	SetTypeID<CGrassRock6>();
}

CGrassRock6::CGrassRock6(const CGrassRock6& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("GrassRock6");
}

CGrassRock6::~CGrassRock6()
{
}

bool CGrassRock6::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("GrassRock6Collider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("GrassRock6");
	m_Mesh->SetRelativeScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(3.f, 3.f, 3.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CGrassRock6::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrassRock6::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrassRock6* CGrassRock6::Clone()
{
	return DBG_NEW CGrassRock6(*this);
}
