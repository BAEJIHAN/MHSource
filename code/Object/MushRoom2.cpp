
#include "MushRoom2.h"

CMushRoom2::CMushRoom2()
{
	SetTypeID<CMushRoom2>();
}

CMushRoom2::CMushRoom2(const CMushRoom2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CMushRoom2::~CMushRoom2()
{
}

bool CMushRoom2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);;

	m_Mesh->SetMesh("MushRoom2");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CMushRoom2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CMushRoom2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CMushRoom2* CMushRoom2::Clone()
{
	return DBG_NEW CMushRoom2(*this);
}
