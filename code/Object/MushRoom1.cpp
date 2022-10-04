
#include "MushRoom1.h"

CMushRoom1::CMushRoom1()
{
	SetTypeID<CMushRoom1>();
}

CMushRoom1::CMushRoom1(const CMushRoom1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CMushRoom1::~CMushRoom1()
{
}

bool CMushRoom1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("MushRoom1");

	m_Mesh->SetRelativeScale(0.1f, 0.1f, 0.1f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CMushRoom1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CMushRoom1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CMushRoom1* CMushRoom1::Clone()
{
	return DBG_NEW CMushRoom1(*this);
}
