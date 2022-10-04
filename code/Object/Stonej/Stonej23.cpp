#include "Stonej23.h"


CStonej23::CStonej23()
{
	SetTypeID<CStonej23>();
}

CStonej23::CStonej23(const CStonej23& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Stonej23Box");
}

CStonej23::~CStonej23()
{
}

bool CStonej23::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Stonej23Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(24.f, 17.f, 8.f);
	m_ColliderBox->SetWorldPos(0.f, -1.f, m_ColliderBox->GetInfo().Length.z);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);
	m_ColliderBox->SetInheritRotX(true);

	m_Mesh->SetMesh("stonej23");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(20.f, 0.f, 20.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CStonej23::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CStonej23::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CStonej23* CStonej23::Clone()
{
	return DBG_NEW CStonej23(*this);
}
