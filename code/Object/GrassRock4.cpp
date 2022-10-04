
#include "GrassRock4.h"

CGrassRock4::CGrassRock4()
{
	SetTypeID<CGrassRock4>();
}

CGrassRock4::CGrassRock4(const CGrassRock4& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("GrassRock4");
}

CGrassRock4::~CGrassRock4()
{
}

bool CGrassRock4::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("GrassRock4Collider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("GrassRock4");
	m_Mesh->SetRelativeScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(6.f, 6.f, 6.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, 1.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CGrassRock4::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CGrassRock4::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrassRock4* CGrassRock4::Clone()
{
	return DBG_NEW CGrassRock4(*this);
}
