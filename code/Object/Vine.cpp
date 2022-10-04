
#include "Vine.h"

CVine::CVine()
{
	SetTypeID<CVine>();
}

CVine::CVine(const CVine& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("VineBox");
}

CVine::~CVine()
{
}

bool CVine::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");

	SetRootComponent(m_Mesh);

	m_Mesh->SetMesh("Vine");
	m_Mesh->SetRenderStateAll("NoneCull");
	m_Mesh->SetTransformState(Transform_State::None);

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CVine::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CVine::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CVine* CVine::Clone()
{
	return DBG_NEW CVine(*this);
}
