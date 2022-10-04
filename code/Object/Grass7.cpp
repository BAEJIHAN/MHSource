
#include "Grass7.h"

CGrass7::CGrass7()
{
	SetTypeID<CGrass7>();
}

CGrass7::CGrass7(const CGrass7& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CGrass7::~CGrass7()
{
}

bool CGrass7::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("Grass7");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CGrass7::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrass7::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrass7* CGrass7::Clone()
{
	return DBG_NEW CGrass7(*this);
}
