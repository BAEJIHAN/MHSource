
#include "GrassRock7.h"

CGrassRock7::CGrassRock7()
{
	SetTypeID<CGrassRock7>();
}

CGrassRock7::CGrassRock7(const CGrassRock7& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("GrassRock7");
}

CGrassRock7::~CGrassRock7()
{
}

bool CGrassRock7::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("GrassRock7Collider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("GrassRock7");
	m_Mesh->SetRelativeScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(3.f, 3.f, 3.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CGrassRock7::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CGrassRock7::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrassRock7* CGrassRock7::Clone()
{
	return DBG_NEW CGrassRock7(*this);
}
