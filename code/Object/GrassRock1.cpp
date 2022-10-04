
#include "GrassRock1.h"

CGrassRock1::CGrassRock1()
{
	SetTypeID<CGrassRock1>();
}

CGrassRock1::CGrassRock1(const CGrassRock1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("GrassRock1");
}

CGrassRock1::~CGrassRock1()
{
}

bool CGrassRock1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("GrassRock1Collider");

	m_Mesh->AddChild(m_ColliderBox);
	
	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("GrassRock1");
	m_Mesh->SetRelativeScale(0.01f, 0.01f, 0.01f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);
	m_ColliderBox->Set3DExtent(13.f, 13.f, 8.f);
	m_ColliderBox->SetRelativePos(0.f, 0.f, 3.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");


	return true;
}

void CGrassRock1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CGrassRock1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrassRock1* CGrassRock1::Clone()
{
	return DBG_NEW CGrassRock1(*this);
}
