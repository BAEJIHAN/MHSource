
#include "Grass8.h"

CGrass8::CGrass8()
{
	SetTypeID<CGrass8>();
}

CGrass8::CGrass8(const CGrass8& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CGrass8::~CGrass8()
{
}

bool CGrass8::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("Grass8");
	m_Mesh->SetRenderStateAll("NoneCull");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CGrass8::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CGrass8::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CGrass8* CGrass8::Clone()
{
	return DBG_NEW CGrass8(*this);
}
