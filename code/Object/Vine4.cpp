
#include "Vine4.h"

CVine4::CVine4()
{
	SetTypeID<CVine4>();
}

CVine4::CVine4(const CVine4& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
}

CVine4::~CVine4()
{
}

bool CVine4::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("Vine4");
	m_Mesh->SetRenderStateAll("NoneCull");
	m_Mesh->SetTransformState(Transform_State::None);

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CVine4::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CVine4::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CVine4* CVine4::Clone()
{
	return DBG_NEW CVine4(*this);
}
