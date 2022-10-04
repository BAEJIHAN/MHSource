#include "Stonej10.h"



CStonej10::CStonej10()
{
	SetTypeID<CStonej10>();
}

CStonej10::CStonej10(const CStonej10& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej10Box");
}

CStonej10::~CStonej10()
{
}

bool CStonej10::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej10Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_Mesh->SetTransformState(Transform_State::None);
	m_ColliderBox->Set3DExtent(18.f, 14.f, 3.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 3.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej10");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej10::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej10::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej10* CStonej10::Clone()
{
	return DBG_NEW CStonej10(*this);
}
