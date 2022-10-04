
#include "Precipice2.h"

CPrecipice2::CPrecipice2()
{
	SetTypeID<CPrecipice2>();
}

CPrecipice2::CPrecipice2(const CPrecipice2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Precipice2Box");
}

CPrecipice2::~CPrecipice2()
{
}

bool CPrecipice2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Precipice2Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(185.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 130.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("Precipice2");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CPrecipice2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CPrecipice2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPrecipice2* CPrecipice2::Clone()
{
	return DBG_NEW CPrecipice2(*this);
}
