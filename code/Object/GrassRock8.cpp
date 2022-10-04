
#include "GrassRock8.h"

CGrassRock8::CGrassRock8()
{
	SetTypeID<CGrassRock8>();
}

CGrassRock8::CGrassRock8(const CGrassRock8& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("GrassRock8");
}

CGrassRock8::~CGrassRock8()
{
}

bool CGrassRock8::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("GrassRock8Collider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("GrassRock8");
	m_Mesh->SetRelativeScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(6.f, 6.f, 6.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, 4.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CGrassRock8::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CGrassRock8::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrassRock8* CGrassRock8::Clone()
{
	return DBG_NEW CGrassRock8(*this);
}
