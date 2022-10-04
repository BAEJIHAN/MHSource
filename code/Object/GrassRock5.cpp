
#include "GrassRock5.h"

CGrassRock5::CGrassRock5()
{
	SetTypeID<CGrassRock5>();
}

CGrassRock5::CGrassRock5(const CGrassRock5& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("GrassRock5");
}

CGrassRock5::~CGrassRock5()
{
}

bool CGrassRock5::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("GrassRock5Collider");

	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("GrassRock5");
	m_Mesh->SetRelativeScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	m_ColliderBox->Set3DExtent(3.f, 3.f, 3.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, 1.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");


	return true;
}

void CGrassRock5::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CGrassRock5::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrassRock5* CGrassRock5::Clone()
{
	return DBG_NEW CGrassRock5(*this);
}
