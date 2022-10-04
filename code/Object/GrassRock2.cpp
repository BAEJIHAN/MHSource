
#include "GrassRock2.h"

CGrassRock2::CGrassRock2()
{
	SetTypeID<CGrassRock2>();
}

CGrassRock2::CGrassRock2(const CGrassRock2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("GrassRock2");
}

CGrassRock2::~CGrassRock2()
{
}

bool CGrassRock2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("GrassRock2Collider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("GrassRock2");
	m_Mesh->SetRelativeScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(5.f, 5.f, 5.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, 3.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CGrassRock2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CGrassRock2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrassRock2* CGrassRock2::Clone()
{
	return DBG_NEW CGrassRock2(*this);
}
