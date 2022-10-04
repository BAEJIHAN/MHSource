#include "Stonej4.h"



CStonej4::CStonej4()
{
	SetTypeID<CStonej4>();
}

CStonej4::CStonej4(const CStonej4& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej4Box");
}

CStonej4::~CStonej4()
{
}

bool CStonej4::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej4Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_Mesh->SetTransformState(Transform_State::None);
	m_ColliderBox->Set3DExtent(7.f, 7.f, 7.f);
	m_ColliderBox->SetWorldPos(-3.f, 0.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej4");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej4::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej4::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej4* CStonej4::Clone()
{
	return DBG_NEW CStonej4(*this);
}
