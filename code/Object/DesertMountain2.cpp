
#include "DesertMountain2.h"

CDesertMountain2::CDesertMountain2()
{
	SetTypeID<CDesertMountain2>();
}

CDesertMountain2::CDesertMountain2(const CDesertMountain2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CDesertMountain2::~CDesertMountain2()
{
}

bool CDesertMountain2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("DesertMountain2");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CDesertMountain2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CDesertMountain2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CDesertMountain2* CDesertMountain2::Clone()
{
	return DBG_NEW CDesertMountain2(*this);
}
