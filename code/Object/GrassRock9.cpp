
#include "GrassRock9.h"

CGrassRock9::CGrassRock9()
{
	SetTypeID<CGrassRock9>();
}

CGrassRock9::CGrassRock9(const CGrassRock9& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("GrassRock9");
}

CGrassRock9::~CGrassRock9()
{
}

bool CGrassRock9::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("GrassRock9Collider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("GrassRock9");
	m_Mesh->SetRelativeScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(4.f, 4.f, 4.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, 1.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CGrassRock9::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CGrassRock9::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrassRock9* CGrassRock9::Clone()
{
	return DBG_NEW CGrassRock9(*this);
}
