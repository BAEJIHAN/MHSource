
#include "Grass5.h"

CGrass5::CGrass5()
{
	SetTypeID<CGrass5>();
}

CGrass5::CGrass5(const CGrass5& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CGrass5::~CGrass5()
{
}

bool CGrass5::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("Grass5");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CGrass5::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrass5::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrass5* CGrass5::Clone()
{
	return DBG_NEW CGrass5(*this);
}
