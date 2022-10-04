
#include "Vine3.h"

CVine3::CVine3()
{
	SetTypeID<CVine3>();
}

CVine3::CVine3(const CVine3& obj)
{
	m_Mesh = (CStaticMeshComponent*)FindComponent("Mesh");
	m_ColliderBox = (CColliderBox3D*)FindComponent("Vine3Box");
}

CVine3::~CVine3()
{
}

bool CVine3::Init()
{
	m_Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_ColliderBox = CreateComponent<CColliderBox3D>("Vine3Box");

	SetRootComponent(m_Mesh);
	m_Mesh->AddChild(m_ColliderBox);
	m_ColliderBox->Set3DExtent(12.f, 12.f, 55.f);
	m_ColliderBox->SetWorldPos(0.f, 0.f, 40.f);
	m_ColliderBox->SetInheritRot(true);

	m_Mesh->SetMesh("Vine3");
	m_Mesh->SetRenderStateAll("NoneCull");
	m_Mesh->SetTransformState(Transform_State::None);

	m_Mesh->SetRelativeScale(0.05f, 0.05f, 0.05f);
	m_Mesh->SetRelativePos(13.f, 0.f, 0.f);
	m_Mesh->SetWorldRotation(-90.f, 0.f, 0.f);

	return true;
}

void CVine3::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CVine3::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

CVine3* CVine3::Clone()
{
	return DBG_NEW CVine3(*this);
}
