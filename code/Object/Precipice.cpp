
#include "Precipice.h"

CPrecipice::CPrecipice()
{
	SetTypeID<CPrecipice>();
}

CPrecipice::CPrecipice(const CPrecipice& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("PrecipiceBox");
}

CPrecipice::~CPrecipice()
{
}

bool CPrecipice::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("PrecipiceBox");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);

	m_ColliderBox->SetInheritRot(true);
	m_ColliderBox->Set3DExtent(100.f);
	m_ColliderBox->SetWorldPos(0.f, m_ColliderBox->GetInfo().Length.z, 60.f);
	m_ColliderBox->SetCollisionProfile("FieldObj");

	m_Mesh->SetMesh("Precipice1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CPrecipice::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CPrecipice::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CPrecipice* CPrecipice::Clone()
{
	return DBG_NEW CPrecipice(*this);
}
