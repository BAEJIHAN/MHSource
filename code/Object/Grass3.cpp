
#include "Grass3.h"

CGrass3::CGrass3()
{
	SetTypeID<CGrass3>();
}

CGrass3::CGrass3(const CGrass3& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CGrass3::~CGrass3()
{
}

bool CGrass3::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("Grass3");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CGrass3::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrass3::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrass3* CGrass3::Clone()
{
	return DBG_NEW CGrass3(*this);
}
