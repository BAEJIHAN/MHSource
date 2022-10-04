#include "Stonej22.h"


CStonej22::CStonej22()
{
	SetTypeID<CStonej22>();
}

CStonej22::CStonej22(const CStonej22& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej22Box");
}

CStonej22::~CStonej22()
{
}

bool CStonej22::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej22Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(25.f, 18.f, 4.5f);
	m_ColliderBox->SetWorldPos(2.f, 0.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej22");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	//m_Mesh->SetRelativePos(20.f, 0.f, 20.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej22::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej22::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej22* CStonej22::Clone()
{
	return DBG_NEW CStonej22(*this);
}
