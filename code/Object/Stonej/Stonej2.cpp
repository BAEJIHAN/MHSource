#include "Stonej2.h"


CStonej2::CStonej2()
{
	SetTypeID<CStonej2>();
}

CStonej2::CStonej2(const CStonej2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej2Box");
}

CStonej2::~CStonej2()
{
}

bool CStonej2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej2Box");

	SetRootComponent(m_Mesh);
	m_Mesh->SetTransformState(Transform_State::None);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(19.f, 16.f, 8.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej2");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej2* CStonej2::Clone()
{
	return DBG_NEW CStonej2(*this);
}
