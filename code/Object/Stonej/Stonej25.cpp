#include "Stonej25.h"


CStonej25::CStonej25()
{
	SetTypeID<CStonej25>();
}

CStonej25::CStonej25(const CStonej25& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej25Box");
}

CStonej25::~CStonej25()
{
}

bool CStonej25::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej25Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(70.f, 70.f, 35.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, m_ColliderBox->GetInfo().Length.z - 15.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej25");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(40.f, 15.f, 40.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	return true;
}

void CStonej25::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej25::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej25* CStonej25::Clone()
{
	return DBG_NEW CStonej25(*this);
}
