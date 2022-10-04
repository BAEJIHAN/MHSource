
#include "DesertMountain1.h"

CDesertMountain1::CDesertMountain1()
{
	SetTypeID<CDesertMountain1>();
}

CDesertMountain1::CDesertMountain1(const CDesertMountain1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CDesertMountain1::~CDesertMountain1()
{
}

bool CDesertMountain1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);
	m_Mesh->SetMesh("DesertMountain1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CDesertMountain1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertMountain1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertMountain1* CDesertMountain1::Clone()
{
	return DBG_NEW CDesertMountain1(*this);
}
