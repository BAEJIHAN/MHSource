
#include "GrassRock3.h"

CGrassRock3::CGrassRock3()
{
	SetTypeID<CGrassRock3>();
}

CGrassRock3::CGrassRock3(const CGrassRock3& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("GrassRock3");
}

CGrassRock3::~CGrassRock3()
{
}

bool CGrassRock3::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("GrassRock3Collider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("GrassRock3");
	m_Mesh->SetRelativeScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(7.0f, 4.0f, 7.0f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, 3.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	return true;
}

void CGrassRock3::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CGrassRock3::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrassRock3* CGrassRock3::Clone()
{
	return DBG_NEW CGrassRock3(*this);
}
