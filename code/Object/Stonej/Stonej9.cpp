#include "Stonej9.h"


CStonej9::CStonej9()
{
	SetTypeID<CStonej9>();
}

CStonej9::CStonej9(const CStonej9& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej9Box");
}

CStonej9::~CStonej9()
{
}

bool CStonej9::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej9Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_Mesh->SetTransformState(Transform_State::None);
	m_ColliderBox->Set3DExtent(18.f, 14.f, 3.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 1.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej9");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej9::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej9::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej9* CStonej9::Clone()
{
	return DBG_NEW CStonej9(*this);
}
