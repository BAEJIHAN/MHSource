
#include "Wreck1.h"

CWreck1::CWreck1()
{
	SetTypeID<CWreck1>();
}

CWreck1::CWreck1(const CWreck1& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CWreck1::~CWreck1()
{
}

bool CWreck1::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("Wreck1");

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);
	m_Mesh->SetTransformState(Transform_State::None);

	return true;
}

void CWreck1::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CWreck1::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CWreck1* CWreck1::Clone()
{
	return DBG_NEW CWreck1(*this);
}
