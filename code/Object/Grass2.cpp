
#include "Grass2.h"

CGrass2::CGrass2()
{
	SetTypeID<CGrass2>();
}

CGrass2::CGrass2(const CGrass2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Grass2Box");
}

CGrass2::~CGrass2()
{
}

bool CGrass2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("Grass2");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CGrass2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrass2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrass2* CGrass2::Clone()
{
	return DBG_NEW CGrass2(*this);
}
