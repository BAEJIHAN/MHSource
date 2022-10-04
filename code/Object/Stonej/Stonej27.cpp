#include "Stonej27.h"


CStonej27::CStonej27()
{
	SetTypeID<CStonej27>();
}

CStonej27::CStonej27(const CStonej27& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej27Box");
}

CStonej27::~CStonej27()
{
}

bool CStonej27::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej27Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(12.f, 27.f, 5.f);
	m_ColliderBox->SetWorldPos(0.f, -1.f, m_ColliderBox->GetInfo().Length.z - 1.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej27");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(33.f, 10.f, 30.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	return true;
}

void CStonej27::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej27::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej27* CStonej27::Clone()
{
	return DBG_NEW CStonej27(*this);
}
