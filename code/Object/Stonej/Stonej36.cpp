#include "Stonej36.h"

CStonej36::CStonej36()
{
	SetTypeID<CStonej36>();
}

CStonej36::CStonej36(const CStonej36& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej36Box");
}

CStonej36::~CStonej36()
{
}

bool CStonej36::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej36Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(3.f, 3.f, 1.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej36");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(30.f, 7.f, 30.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	return true;
}

void CStonej36::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej36::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej36* CStonej36::Clone()
{
	return DBG_NEW CStonej36(*this);
}
