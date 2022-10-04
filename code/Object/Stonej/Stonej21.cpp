#include "Stonej21.h"

CStonej21::CStonej21()
{
	SetTypeID<CStonej21>();
}

CStonej21::CStonej21(const CStonej21& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej21Box");
}

CStonej21::~CStonej21()
{
}

bool CStonej21::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej21Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(70.f, 80.f, 40.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, m_ColliderBox->GetInfo().Length.z - 17.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");
	
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej21");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(0.f, 17.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->GetTransform()->SetTransformState(Transform_State::None);

	return true;
}

void CStonej21::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej21::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej21* CStonej21::Clone()
{
	return DBG_NEW CStonej21(*this);
}
