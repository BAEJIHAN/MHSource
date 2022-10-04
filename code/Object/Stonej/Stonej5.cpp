#include "Stonej5.h"


CStonej5::CStonej5()
{
	SetTypeID<CStonej5>();
}

CStonej5::CStonej5(const CStonej5& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej5Box");
}

CStonej5::~CStonej5()
{
}

bool CStonej5::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej5Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_Mesh->SetTransformState(Transform_State::None);
	m_ColliderBox->Set3DExtent(5.f, 5.f, 3.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 1.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej5");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej5::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej5::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej5* CStonej5::Clone()
{
	return DBG_NEW CStonej5(*this);
}
