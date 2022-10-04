#include "Stonej16.h"


CStonej16::CStonej16()
{
	SetTypeID<CStonej16>();
}

CStonej16::CStonej16(const CStonej16& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej16Box");
}

CStonej16::~CStonej16()
{
}

bool CStonej16::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej16Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_Mesh->SetTransformState(Transform_State::None);
	m_ColliderBox->Set3DExtent(8.f, 5.f, 4.f);
	m_ColliderBox->SetWorldPos(0.f, 1.f, 0.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");


	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);


	m_Mesh->SetMesh("stonej16");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej16::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej16::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej16* CStonej16::Clone()
{
	return DBG_NEW CStonej16(*this);
}
