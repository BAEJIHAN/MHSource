
#include "Vine2.h"

CVine2::CVine2()
{
	SetTypeID<CVine2>();
}

CVine2::CVine2(const CVine2& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CVine2::~CVine2()
{
}

bool CVine2::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("Vine2");
	m_Mesh->SetRenderStateAll("NoneCull");
	m_Mesh->SetTransformState(Transform_State::None);

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 20.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CVine2::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CVine2::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CVine2* CVine2::Clone()
{
	return DBG_NEW CVine2(*this);
}
