#include "Stonej31.h"

CStonej31::CStonej31()
{
	SetTypeID<CStonej31>();
}

CStonej31::CStonej31(const CStonej31& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej31Box");
}

CStonej31::~CStonej31()
{
}

bool CStonej31::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej31Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(35.f, 18.f, 8.f);
	m_ColliderBox->SetWorldPos(0.f, -1.5f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej31");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(30.f, 7.f, 30.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	return true;
}

void CStonej31::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej31::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej31* CStonej31::Clone()
{
	return DBG_NEW CStonej31(*this);
}
