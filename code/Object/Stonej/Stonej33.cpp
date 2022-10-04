#include "Stonej33.h"


CStonej33::CStonej33()
{
	SetTypeID<CStonej33>();
}

CStonej33::CStonej33(const CStonej33& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej33Box");
}

CStonej33::~CStonej33()
{
}

bool CStonej33::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej33Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(2.f, 2.f, 1.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej33");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(30.f, 11.f, 30.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	return true;
}

void CStonej33::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej33::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej33* CStonej33::Clone()
{
	return DBG_NEW CStonej33(*this);
}
