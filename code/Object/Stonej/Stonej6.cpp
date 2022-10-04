#include "Stonej6.h"



CStonej6::CStonej6()
{
	SetTypeID<CStonej6>();
}

CStonej6::CStonej6(const CStonej6& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej6Box");
}

CStonej6::~CStonej6()
{
}

bool CStonej6::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej6Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_Mesh->SetTransformState(Transform_State::None);
	m_ColliderBox->Set3DExtent(8.f, 10.f, 8.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej6");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej6::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej6::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej6* CStonej6::Clone()
{
	return DBG_NEW CStonej6(*this);
}
